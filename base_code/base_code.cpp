// Image_Convolution base code

#include <iostream>
#include <immintrin.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[])
{

    chrono::time_point<system_clock> clock_start, clock_end;
    chrono::duration<double> elapsed_time;

    int thread_count, thread_id;

#pragma omp parallel
    {
    }

    cout << endl;
    return 0;
}