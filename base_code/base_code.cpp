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

    //vector<int> kernel_size = {3, 5, 7, 9, 11, 13, 15};
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    //vector<vector<long long int>> image_size = {/*{1024, 768},{2048, 2048}, */ {1024, 768} /*, {4194304, 768}, {16777216, 768}*/};
    cout << "Image size"
         << "\t"
         << k
         << "\t"
         << "Performance"
         << "\t"
         << "Expected" << endl;
    /*for (int i = 0; i < kernel_size.size(); i++)
    {*/
    int **kernel_data = (int **)malloc(k * sizeof(int *));
    for (int a = 0; a < k; a++)
        kernel_data[a] = (int *)malloc(k * sizeof(int));

    for (int g = 0; g < k; g++)
    {
        for (int h = 0; h < k; h++)
        {
            kernel_data[g][h] = (rand() % 3) + (-1);
        }
    }

    /*for (int j = 0; j < image_size.size(); j++)
        {
    //vector<vector<int>> image_data(n, vector<int>(m, rand() % 255));*/
    int **image_data = (int **)malloc(n * sizeof(int *));
    for (int a = 0; a < n; a++)
        image_data[a] = (int *)malloc(m * sizeof(int));

    for (int g = 0; g < n; g++)
    {
        for (int h = 0; h < m; h++)
        {
            image_data[g][h] = (rand() % 256);
        }
    }

    int **new_image_data = (int **)malloc(n * sizeof(int *));
    for (int a = 0; a < n; a++)
        new_image_data[a] = (int *)malloc(m * sizeof(int));

    clock_start = system_clock::now();
#pragma omp paralel for
    for (int i = floor(k / 2); i < (n - int(floor(k / 2))); ++i)
    {
        for (int j = floor(k / 2); j < (m - int(floor(k / 2))); ++j)
        {
            long int conv_out = 0;

            for (int a = 0; a < k; ++a)
            {
#pragma omp parallel for reduction(+ \
                                   : conv_out)
                for (int b = 0; b < k; ++b)
                {
                    conv_out += kernel_data[a][b] * image_data[i - int(floor(k / 2)) + a][j - int(floor(k / 2)) + b];
                }
            }
            new_image_data[i][j] = conv_out;
        }
    }

    clock_end = system_clock::now();

    elapsed_time = clock_end - clock_start;
    double run_time = elapsed_time.count();
    /*for (int y = 0; y < n; y++)
            {
                for (int z = 0; z < m; z++)
                {
                    cout << new_image_data[y][z] << " ";
                }
                cout << endl;
            }*/
    cout << n << "*" << m << "\t" << k << "\t" << ((n - k + 1) * (m - k + 1)) / (run_time) << "\t" << (1638.4 * (pow(10, 9))) / ((2 * k * k) - 1) << endl;

    return 0;
}