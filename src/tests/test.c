#include "test.h"
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void test_time()
{
    //testing input from user 2022-01-31 15:15:02
    //test function schedule menu in menu.c
    char input[] = "2022-01-31 15:15:02";
    wchar_t buff[40];
    
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

    int difference = difftime(mktime(newtime1), timer2) * (-1);

    //if difference not equal to 3600 exactly 1 hour than test fails
    if(difference == 3600)
    {
        SUCCESS("TEST 1 PASSED");
    }
    else{
        FAIL("TEST 1 FAILED", 1, difference);
       
    }
}

void test_create_alarm(struct clock_t* clock)
{
    char input[] = "2022-01-31 15:15:02";
    struct tm time2;
    struct alarm_t alarm;

    time2.tm_hour -= 1;
    
    time_t timer2 = timegm(&time2);
    int difference = 3600;          // 1 hour difference

    alarm_init(&alarm, timer2, difference);
    push(clock, alarm);
    if(clock->length == 1)
    {
        SUCCESS("TEST 2 PASSED");
    }
    else
    {
        FAIL("TEST 2 FAILED", 1, clock->length);
    }

}

void test_list_menu(struct clock_t *clock)
{
    list_menu(clock);
    SUCCESS("TEST 3 PASSED");
}

void test_remove_alarm(struct clock_t* clock)
{
    int index = 0;
    remove_alarm(clock, index);
    if(clock->length == 0)
    {
        SUCCESS("TEST 4 PASSED");
    }
    else
    {
        FAIL("TEST 4 FAILED", 0, clock->length);
    }
}




int main(int argv, char** argc) 
{
    struct clock_t* clock = malloc(sizeof(struct clock_t));
    clock_init(clock);
    printf("\n==================================================\n");
    SUITE("TEST CASE 1 \n");
    printf("Test function check time in menu.c \n");
    test_time();
    printf("\n==================================================\n");
    

    printf("\n==================================================\n");
    SUITE("TEST CASE 2 \n");
    printf("Test create_alarm() function in clock.c \n");
    test_create_alarm(clock);
    printf("\n==================================================\n");

    printf("\n==================================================\n");
    SUITE("TEST CASE 3 \n");
    printf("Test list_menu() function in clock.c \n");
    test_list_menu(clock);
    printf("\n==================================================\n");

    printf("\n==================================================\n");
    SUITE("TEST CASE 4 \n");
    printf("Test remove_alarm() function in clock.c \n");
    test_remove_alarm(clock);
    printf("\n==================================================\n");

    SUCCESS("EVERY TEST PASSED \n\n");
}