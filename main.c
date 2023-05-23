// Bygg en krets med Ardino och tre knappar (A,B,C). Och en LED
// Trycker man på A tre gånger på raken ska LED lysa.
// Dvs håll reda på de tre senaste klicken hela tiden

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "millis.h"

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)
#define LED_PIN 0
#define BUTTON_A_PIN 3
#define BUTTON_B_PIN 2
#define BUTTON_C_PIN 1


#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 


#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

#define SIZE 3 // Counter variabel

int buttonPresses [SIZE];
int counter = 0; 

int main(void){
    init_serial();
    millis_init();
    sei();
    volatile millis_t antalMilliSekunderSenasteBytet = 0;
    BIT_SET(DDRB,LED_PIN); //OUTPUT MODE

    //Sätt till INPUT_PULLUP
    BIT_CLEAR(DDRB,BUTTON_A_PIN); // INPUT MODE
    BIT_SET(PORTB,BUTTON_A_PIN);

    BIT_CLEAR(DDRB,BUTTON_B_PIN); 
    BIT_SET(PORTB,BUTTON_B_PIN); 
    
    BIT_CLEAR(DDRB,BUTTON_C_PIN); 
    BIT_SET(PORTB,BUTTON_C_PIN); 

    // DATA DIRECTION = avgör mode
    // om output så skickar vi  1 eller 0 på motsvarande pinne på PORT
    // om input så läser vi  1 eller 0 på motsvarande pinne på PIN
    //bool blinking = false;
    bool blinking = true;
    while(1){
    // Check each button separately
        if(!BIT_CHECK(PINB, BUTTON_A_PIN)){ 
            _delay_ms(300); //Delay for debouncing
            buttonPresses[counter % SIZE] = 1; // Button A is pressed, add 1 to the array
            counter++;
        }
        if(!BIT_CHECK(PINB, BUTTON_B_PIN)){ 
            _delay_ms(300); 
            buttonPresses[counter % SIZE] = 2; // Button B is pressed, add 2 to the array
            counter++;
        }
        if(!BIT_CHECK(PINB, BUTTON_C_PIN)){ 
            _delay_ms(300); 
            buttonPresses[counter % SIZE] = 3; // Button C is pressed, add 3 to the array
            counter++;
        }

        if (counter >= SIZE && buttonPresses[0]==1 && buttonPresses[1]==1 && buttonPresses[2]==1 ){
            // All three buttons are A, turn on the LED
            BIT_SET(PORTB, LED_PIN);
        }
        else {
            // Not all buttons are A, turn off the LED
            BIT_CLEAR(PORTB, LED_PIN);
        }

        millis_t s = millis_get() - antalMilliSekunderSenasteBytet;

        if((s > 1000)){
            BIT_FLIP(PORTB,LED_PIN);
            antalMilliSekunderSenasteBytet = millis_get();
        }
    }

    return 0;
}
