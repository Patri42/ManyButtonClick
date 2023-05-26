
# Arduino Button Sequence Detector and LED Controller

This repository contains an Arduino project written in C. The code monitors three buttons (Button A, Button B, Button C) and controls an LED light based on the sequence of button presses. Specifically, if Button A is pressed three times in a row, the LED lights up.


## Project Structure

**main.c**: Main file that handles the button presses and controls the LED.

**millis.c** and **millis.h**: A lightweight millisecond tracking library.

**uart.c** and **uart.h**: Handles the UART communication for debugging purposes.

**Makefile**: A makefile for building and flashing the Arduino code.


## Requirements

An Arduino board (the code is specifically written for ATmega328p).

Three buttons connected to your Arduino.

An LED connected to your Arduino.

AVR GCC toolchain installed on your computer.

AVRDUDE for flashing the code to your Arduino.


## Building and Flashing

1. Clone this repository to your local machine.
2. Navigate to the project directory in your terminal.
3. Run ```make``` to build the project.
4. Run ```make isp``` to flash the code to your Arduino.

## File Details

**millis.h**
This header file is part of a lightweight millisecond tracking library. It includes function declarations for initializing the millisecond tracking, getting the current millisecond count, resuming, pausing, resetting the millisecond count, and adding/subtracting milliseconds.

**uart.h**
This header file provides the link between the Arduino Uno and the standard C I/O. It's designed for blocking I/O and doesn't use interrupts. It includes function declarations for initializing the UART communication, putting a character on the UART, and getting a character from the UART.
