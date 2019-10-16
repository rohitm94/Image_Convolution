// Image_Convolution base code

#include <iostream>
#include <immintrin.h>
#include <omp.h>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[])
{
    chrono::time_point<system_clock> clock_start, clock_end;
    chrono::duration<double> elapsed_time;

    vector<int> kernel_size = {3, 5, 7, 9, 11, 13, 15};
    //int k = atoi(argv[1]);
    //int n = atoi(argv[2]);
    //int m = atoi(argv[3]);
    vector<vector<long long int>> image_size = {/*{1024, 768},{2048, 2048}, */ {1024, 768} /*, {4194304, 768}, {16777216, 768}*/};
    cout << "Image size"
         << "\t"
         << "K"
         << "\t"
         << "Performance"
         << "\t"
         << "Expected" << endl;
    for (int i = 0; i < kernel_size.size(); i++)
    {
        int **kernel_data = (int **)malloc(kernel_size[i] * sizeof(int *));
        for (int a = 0; a < kernel_size[i]; a++)
            kernel_data[a] = (int *)malloc(kernel_size[i] * sizeof(int));

        for (int g = 0; g < kernel_size[i]; g++)
        {
            for (int h = 0; h < kernel_size[i]; h++)
            {
                kernel_data[g][h] = (rand() % 3) + (-1);
            }
        }

        for (int j = 0; j < image_size.size(); j++)
        {
            //vector<vector<int>> image_data(image_size[j][0], vector<int>(image_size[j][1], rand() % 255));
            int **image_data = (int **)malloc(image_size[j][0] * sizeof(int *));
            for (int a = 0; a < image_size[j][0]; a++)
                image_data[a] = (int *)malloc(image_size[j][1] * sizeof(int));

            for (int g = 0; g < image_size[j][0]; g++)
            {
                for (int h = 0; h < image_size[j][1]; h++)
                {
                    image_data[g][h] = (rand() % 256);
                }
            }

            int **new_image_data = (int **)malloc(image_size[j][0] * sizeof(int *));
            for (int a = 0; a < image_size[j][0]; a++)
                new_image_data[a] = (int *)malloc(image_size[j][1] * sizeof(int));

            clock_start = system_clock::now();

            for (int k = floor(kernel_size[i] / 2); k < (image_size[j][0] - int(floor(kernel_size[i] / 2))); ++k)
            {
                for (int l = floor(kernel_size[i] / 2); l < (image_size[j][1] - int(floor(kernel_size[i] / 2))); ++l)
                {
                    long int conv_out = 0;

                    for (int a = 0; a < kernel_size[i]; ++a)
                    {
#pragma omp parallel for reduction(+ \
                                   : conv_out)
                        for (int b = 0; b < kernel_size[i]; ++b)
                        {
                            conv_out += kernel_data[a][b] * image_data[k - int(floor(kernel_size[i] / 2)) + a][l - int(floor(kernel_size[i] / 2)) + b];
                        }
                    }
                    new_image_data[k][l] = conv_out;
                }
            }

            clock_end = system_clock::now();

            elapsed_time = clock_end - clock_start;
            double run_time = elapsed_time.count();
            /*for (int y = 0; y < image_size[j][0]; y++)
            {
                for (int z = 0; z < image_size[j][1]; z++)
                {
                    cout << new_image_data[y][z] << " ";
                }
                cout << endl;
            }*/
            cout << image_size[j][0] << "*" << image_size[j][1] << "\t" << kernel_size[i] << "\t" << ((image_size[j][0] - kernel_size[i] + 1) * (image_size[j][1] - kernel_size[i] + 1)) / (run_time) << "\t" << (1638.4 * (pow(10, 9))) / ((2 * kernel_size[i] * kernel_size[i]) - 1) << endl;
        }
    }
    // vector<vector<int>> kernel_data(k, vector<int> (k, 1));

    // vector<vector<int>> image_data(n, vector<int> (m, rand()%256));

    return 0;
}