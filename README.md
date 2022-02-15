# Alarm Clock CLI

## Summary

This is program is a simple alarm clock cli that allows you to set one or multiple alarms in the future. This project was made as an submission to NTNU's Operating Systems course. `TDT4186`. Where the goal was to create a C program for Unix-like operating systems that uses various processes modifying functions such as `fork()` and `exec()` etc..

> Note that there seems to be some problems regarding time.h header files causing several warnings to appear, however the program runs as intended.

> Note when an alarm is terminated the program needs to cycle through its menu once before you as the user can see the updated array displayed in stdout.

## Documentation

To find documentation for various functions, look into their respective header files.

<br />

# How to run

1. Make sure you have `GNU Make`, `GCC` and `mpg123` running on your `Linux` environment.

   > MacOS should work fine, but I've not tested this...

2. Download an mp3 audio file (whatever you'd like) and name it `alarm.mp3` and locate it in the `/audio` folder.

3. Finally run `make run` in the root directory

<br />

## Tests

Although this program is small there is still quite a bit of functionalty that needs to be tested. Below are four test cases that should cover must of the critical functions within the program.

### How to run

Run `make test` in the root directory and the tests should be compiled and ran.

### Test case #1

The first test, is the function test_time(). This function test how we assign the time in the function schedule menu from a fixed size input which represents a day and time. This input is then parsed as a time_t type. Then to test the context present in show_time() and get_current_time() function from menu.c, the input of a fixed unix time that is 1 hour less than our previous date and time in our fixed sized input. Then we test the function schedule menu to see if the time inputed and the fixed time which represents in our main program the local time is exactly equal to 3600 seconds that represents 1 hour. If the difference is equal to 3600 then the test passses if it does not then the test failed. 

This test is meant to test the different c library time function to see if there is no issues with the time configured on the OS.

### Test case #2

test_create_alarm() function creates an alarm with a fixed time and date and tests the function alarm_init() and set_alarm() in alarm.c and the push() in clock.c. If the clock struct pointer is not increased then the test fails because it means that the alarm is not set correctly.

### Test case #3

The test_list_menu() should test the list_menu() function and test that the time stored in clock is correct if not the test fails. 

### Test case #4

test_remove_alarm() function test the remove_alarm() function in clock.c. If the test fails it means that the alarm is not removed correctly. 

