//https://stackoverflow.com/questions/32671134/generating-sine-wave-array-in-c-with-noise

#include "minunit.h"
#include "median.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>



MU_TEST(test_reference) 
{
    srand((unsigned)time(NULL));
    MedianFilter<double> filter(7);

    std::ofstream myfile;
    myfile.open("example_reference.csv");

    myfile << "time,raw_value,median_value,\n";

    for (int i = 0; i != 360; i++)
    {
        auto newValue = (float)( sin(1*i*(M_PI / 180)));
        auto medianValue = filter.Insert(newValue);

        printf("New value: %f \tMedian value: %f\r\n", newValue, medianValue);
        myfile << i << "," << newValue << "," << medianValue << "\n";
        usleep(5000);
    }

    myfile.close();
}

MU_TEST(test_noise)
{
    srand((unsigned)time(NULL));
    MedianFilter<double> filter(128);

    std::ofstream myfile;
    myfile.open("example_noise.csv");

    myfile << "time,raw_value,median_value,\n";

    for (int i = 0; i != 360; i++)
    {
        auto newValue = (float)(sin(1 * i*(M_PI / 180)) + sqrt(0.01) * (rand() % 10));
        auto medianValue = filter.Insert(newValue);

        printf("New value: %f \tMedian value: %f\r\n", newValue, medianValue);
        myfile << i << "," << newValue << "," << medianValue << "\n";

    }

    myfile.close();
}


int main()
{
    MU_RUN_TEST(test_reference);
    MU_RUN_TEST(test_noise);
    MU_REPORT();
    return MU_EXIT_CODE;
}