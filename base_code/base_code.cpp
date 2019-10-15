// Image_Convolution base code

#include <iostream>
#include <immintrin.h>
#include <omp.h>
#include <chrono>
#include <vector>
#include <stdlib.h>

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
    vector<vector<int>> image_size = {{1024, 768}, {2048, 2048}, {8192, 8192}, {4194304, 768}, {16777216, 768}};

    for (int i = 0; i < kernel_size.size(); i++)
    {

        vector<vector<int>> kernel_data(kernel_size[i], vector<int>(kernel_size[i], 1));

        for (int j = 0; j < image_size.size(); j++)
        {
            vector<vector<int>> image_data(image_size[j][0], vector<int>(image_size[j][1], rand() % 256));
            for (int a = 0; a < kernel_data.size(); a++)
            {
                for (int b = 0; b < kernel_data.size(); b++)
                {
                    cout << kernel_data[a][b] << endl;
                }
            }
        }
    }
    // vector<vector<int>> kernel_data(k, vector<int> (k, 1));

    // vector<vector<int>> image_data(n, vector<int> (m, rand()%256));

    return 0;
}