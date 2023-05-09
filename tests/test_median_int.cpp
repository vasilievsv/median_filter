#include "minunit.h"
#include "median.h"



//static int rc = 0;
//static char *buff = NULL;

MU_TEST(test_int) 
{

    MedianFilter<int> filter(7);

    for (int i = 0; i != 10; i++)
    {
        auto newValue = rand()%10;
        auto medianValue = filter.Insert(newValue);

        printf("raw_value: %d \tmedian_value: %d\r\n", newValue, medianValue);


        usleep(5000);
    }
}




int main()
{
    MU_RUN_TEST(test_int);
    MU_REPORT();
    return MU_EXIT_CODE;
}