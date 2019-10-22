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

    int k = atoi(argv[1]);
    long n = atoi(argv[2]);
    long int m = atoi(argv[3]);

    if (k = 3 && n == 1024 && m == 768)
    {
        cout << "Image size(n*m)"
             << "\t"
             << "k"
             << "\t"
             << "Performance"
             << "\t"
             << "Expected" << endl;
    }

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
    long int conv_out = 0;
#pragma omp parallel for reduction(+ \
                                   : conv_out)
    for (int i = floor(k / 2); i < (n - int(floor(k / 2))); ++i)
    {
        for (int j = floor(k / 2); j < (m - int(floor(k / 2))); ++j)
        {
            for (int a = 0; a < k; ++a)
            {
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

    cout << n << "*" << m << "\t" << k << "\t" << ((n - k + 1) * (m - k + 1)) / (run_time) << "\t" << (1638.4 * (pow(10, 9))) / ((2 * k * k) - 1) << endl;

    return 0;
}