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

Run `make test` in the root directory and the tests should be compiled and run.

### Test case #1

### Test case #2

### Test case #3

### Test case #4
