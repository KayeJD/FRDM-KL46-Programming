/**
 * @file    Morse_Code.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include <string.h>
#include <stdlib.h>

/*
 *  message: This is the pointer to the first character of the string “hey”. You can use message to access the entire string, like this: printf("%s", message);.
 *  *message: This is the value of the first character of the string “hey”. You can use *message to access the first character of the string, like this: printf("%c", *message);.
 *  &message: This is the address of the pointer message. You can use &message to pass the pointer to a function that expects a pointer to a pointer, like this: some_function(&message);
 */

void delay(unsigned short delay_t) {
    SIM->SCGC6 |= (1 << 24); // Clock Enable TPM0
    SIM->SOPT2 |= (0x2 << 24); // Set TPMSRC to OSCERCLK
    TPM0->CONF |= (0x1 << 17); // Stop on Overflow
    TPM0->SC = (0x1 << 7) | (0x07); // Reset Timer Overflow Flag, Set Prescaler 128
    TPM0->MOD = delay_t * 61 + delay_t/2; //
    TPM0->SC |= 0x01 << 3; // Start the clock!
    while(!(TPM0->SC & 0x80)){} // Wait until Overflow Flag

    TPM0->SC &= ~TPM_SC_CMOD_MASK; // Stop the timer
    TPM0->SC |= TPM_SC_TOF_MASK; // Clear TOF flag
    return;
}

// ADD NEW PARAM THAT DETERMINES WHICH LIGHT TO USE

void dot(bool word){ //SHOULD BE 200ms
	if (word){
		GPIOD->PDOR &= ~(1<<5); //GREEN on
		delay(200);
	}
	else{
		GPIOE->PDOR &= ~(1<<29); //RED on
		delay(200);
	}

	GPIOD->PDOR |= (1 << 5); // Green OFF.
	GPIOE->PDOR |= (1 << 29); // Red OFF.
	delay(250);
}

void dash(bool word){ //SHOULD BE 500ms
	if (word){
		GPIOD->PDOR &= ~(1<<5); //GREEN on
		delay(500);
	}
	else{
		GPIOE->PDOR &= ~(1<<29); //RED on
		delay(500);
	}

	GPIOD->PDOR |= (1 << 5); // Green OFF.
	GPIOE->PDOR |= (1 << 29); // Red OFF.
	delay(250);
}

void period(bool word){ //SHOULD BE 500ms
	if (word){
		GPIOD->PDOR &= ~(1<<5); //GREEN on
		delay(600);
	}
	else{
		GPIOE->PDOR &= ~(1<<29); //RED on
		delay(600);
	}

	GPIOD->PDOR |= (1 << 5); // Green OFF.
	GPIOE->PDOR |= (1 << 29); // Red OFF.
}

void displayMorse(const char *message, int length) {
    bool evenWord = false; //toggle lights. false = RED

    for (int i = 0; message[i] != '\0'; i++) {
    	char c = message[i];
            switch (c){
            	case ' ':
            		evenWord = !evenWord;
            		break;
            	case '.':
            		evenWord = !evenWord;
            	    period(evenWord);
            	    return;
            	case 'a':
            		dot(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'b':
            		dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'c':
            		dash(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'd':
           			dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'e':
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'f':
            		dot(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'g':
            		dash(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'h':
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'i':
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'j':
            		dot(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'k':
            		dash(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'l':
            		dot(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'm':
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'n':
            		dash(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 'o':
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'p':
            		dot(evenWord);
            		dash(evenWord);
            		dash(evenWord);
           			dot(evenWord);
            		delay(350);
            		break;
            	case 'q':
            		dash(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'r':
            		dot(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 's':
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case 't':
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'u':
            		dot(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'v':
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'w':
            		dot(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'x':
            		dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'y':
            		dash(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case 'z':
            		dash(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case '0':
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
        			break;
            	case '1':
            		dot(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case '2':
            		dot(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case '3':
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case '4':
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dash(evenWord);
            		delay(350);
            		break;
            	case '5':
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case '6':
            		dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case '7':
            		dash(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case '8':
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	case '9':
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dash(evenWord);
            		dot(evenWord);
            		delay(350);
            		break;
            	default:
            		break;
          	}
    }

}

int main(void) {

	/* Init board hardware. */
	 BOARD_InitBootPins();
	 BOARD_InitBootClocks();
	 BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	    /* Init FSL debug console. */
	    BOARD_InitDebugConsole();
	#endif

		/* Set up LED1 GREEN */
		    // Turning LED1 light (green) on
		    SIM->SCGC5 |= 1<<12; //Enable port D
		    // Set port mux
		    PORTD->PCR[5] &= ~(0x700); //Clear PTD5 mux
		    PORTD->PCR[5] |= 0x700 & (1 << 8); //Set PTD5 GPIO
		    GPIOD->PDDR |= (1 << 5); //Set D5 Output
		    // Initialize (active low)
		    GPIOD->PDOR |= (1 << 5);  // OFF

		/* Set up LED2 RED */
		    // Turning LED1 light (red) on
		    SIM->SCGC5 |= 1<<13; // Enable port E
		    // Set port mux
		    PORTE->PCR[29] &= ~(0x7 << 8); //Clear MUX
		    PORTE->PCR[29] |= 0x700 & (0x1 << 8); //Set E29 to GPIO Function
		    GPIOE->PDDR |= 1<<29; //Set E29 Output
		    // Initialize (active low)
		    GPIOE->PDOR |= (1 << 29);  // OFF

		    SIM->SCGC6 |= (1 << 24); // Clock Enable TPM0


	    /* Force the counter to be placed into memory. */
	    volatile static int i = 0 ;
	    while(1) {
	        i++ ;
	        __asm volatile ("nop");

	        //bool foo = true;
	        char *message = "CSE 320.";
	        int length = strlen(message);
	        displayMorse(message, length);

    }

    return 0 ;
}
