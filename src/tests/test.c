#include "test.h"
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void test_time(){
    //testing input from user 2022-01-31 15:15:02
    //test function schedule menu in menu.c
    char input[] = "2022-01-31 15:15:02";
    wchar_t buff[40];
    
    printf("%s\n", input);
    struct tm time2;
    strptime(input, "%F %T", &time2);

    time2.tm_hour -= 1;
    
    time_t timer2 = timegm(&time2);

    //testing from show_time() and get_current_time()
    //with value 2022-01-31 14:15:23
    time_t timer1;
    struct tm* newtime1 = malloc(sizeof(struct tm));
    timer1 = 1643638502; //2022-01-31 14:15:23
    newtime1 = gmtime(&timer1);

    wcsftime(buff, sizeof buff, L"%F %T", newtime1);
    printf("%ls\n", buff);

    int difference = difftime(mktime(newtime1), timer2) * (-1);

    //if difference not equal to 3600 exactly 1 hour than test fails
    if(difference == 3600)
    {
        printf("Difference == 3600 1 hour between time 1 and time 2 \n");
        SUCCESS("TEST 1 PASSED");
    }
    else{
        FAIL("TEST 1 FAILED", 1, difference);
       
    }
}






int main(){
    printf("%s\n", "test case 1");
    printf("%s\n", "test function create alarm in menu.c");
    struct clock_t* clock = malloc(sizeof(struct clock_t));
    clock_init(clock);
    test_time();
}