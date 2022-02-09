#include "test.h"
#include <wchar.h>

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

    //printf("%d seconds\n", difference);

    //if difference not equal to 3600 exactly 1 hour than test fails
    if(difference == 3600){
        printf("%s\n", "Difference == 3600 1 hour between time 1 and time 2");
        printf("%s\n", "TEST 1 PASSED");
    }else{
        printf("%s\n", "TEST 1 FAILED");
    }
}

void test_create_alarm(alarm_clock_t* clock){
    char input[] = "2022-01-31 15:15:02";
    struct tm time2;
    alarm_t alarm;

    time2.tm_hour -= 1;
    
    time_t timer2 = timegm(&time2);
    int difference = 3600; // 1 hour difference

    create_alarm(clock, timer2, difference);
    if(clock->length == 1){
        printf("%s\n", "TEST 2 PASSED");
    }else{
        printf("%s\n", "TEST 2 FAILED");
    }

}

void test_list_menu(alarm_clock_t *clock){
    list_menu(clock);
    printf("%s\n", "TEST 3 PASSED");
}

void test_remove_alarm(alarm_clock_t* clock){
    int index = 0;
    remove_alarm(clock, index);
    if(clock->length == 0){
        printf("%s\n", "TEST 4 PASSED");
    }else{
        printf("%s\n", "TEST 4 FAILED");
    }
}




int main(){
    alarm_clock_t* clock = initialize();
    printf("%s\n", "test case 1");
    printf("%s\n", "test function check time in menu.c ");
    test_time();
    
    printf("%s\n", "test case 2");
    printf("%s\n", "test create_alarm() function in clock.c");
    test_create_alarm(clock);
    
    printf("%s\n", "test case 3");
    printf("%s\n", "test list_menu() function in clock.c");
    test_list_menu(clock);

    printf("%s\n", "test case 4");
    printf("%s\n", "test remove_alarm() function in clock.c");
    test_remove_alarm(clock);




    return 0;
}