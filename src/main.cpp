//
// https://habr.com/ru/post/588270/
// https://en.wikipedia.org/wiki/Median_filter
// https://www.emo.org.tr/ekler/2130c418d4f02c7_ek.pdf
// https://www.youtube.com/watch?v=6BRoiaKCQ8o
//
// middle = (max(a, b) == max(b, c)) ? max(a, c) : max(b, min(a, c)); // c++
//


#include "LinkedList/LinkedList.h"
#include "median.h"


int main()
{
    MedianFilter<int> filter(7);

    for (int i = 0; i != 10; i++)
    {
        int newValue = rand() % 10;
        int medianValue = filter.Insert( newValue );

        printf("New value: %d \tMedian value: %d\r\n", newValue, medianValue);
        
        usleep(5000);
    }


    return 0;
}