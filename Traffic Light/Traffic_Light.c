/**
 * @file    Traffic-Light.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include <stdlib.h>

void delay();

void delay(){
	for(int i = 0; i < 900000; i++){
		i++;
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
	    //PTD5 is output
	    GPIOD->PDDR |= (1 << 5);
	    // Initialize (active low)
	    GPIOD->PDOR |= (1 << 5);  // OFF

	/* Set up LED2 RED */
	    // Turning LED1 light (red) on
	    SIM->SCGC5 |= 1<<13; // Enable port E
	    // Set port mux
	    PORTE->PCR[29] &= ~(0x7 << 8); //Clear MUX
	    PORTE->PCR[29] |= 0x700 & (0x1 << 8); //Set E29 to GPIO Function
	    // PTD26 is output
	    GPIOE->PDDR |= 1<<29; //Set E29 Output
	    // Initialize (active low)
	    GPIOE->PDOR &= ~(1 << 29);  // OFF

	/* Set up PTE30 YELLOW */
	    // Turning external LED on
	    // SIM->SCGC5 |= 1 << 13;  // Already enabled port E
	    // Set port mux
	    PORTE->PCR[30] &= ~(0x7 << 8);  // Clear MUX
	    PORTE->PCR[30] |= 0x700 & (0x1 << 8);  // Set E30 to GPIO Function
	    // PTE30 is output
	    GPIOE->PDDR |= 1 << 30;  // Set E30 Output
	    // Initialize (active high)
	    GPIOE->PDOR &= ~(1 << 30);  // OFF

	    // Setup SW1
	    SIM->SCGC5 |= 1 << 11;  // Enable port C
	    PORTC->PCR[3] &= ~0x703; // Clear mux and PE/PS bits
	    PORTC->PCR[3] |= 0x703 & ((1 << 8) | 0x03); // Set MUX bits to GPIO, Set pullup and pull enable.
	    GPIOC->PDDR &= ~(1 << 3); // Clear Data direction (input)


	    /* Force the counter to be placed into memory. */
	    volatile static int i = 0 ;
	    /* Enter an infinite loop, just incrementing a counter. */
	    while(1) {
	        i++ ;
	        /* 'Dummy' NOP to allow source level single stepping of
	            tight while() loop */
	        __asm volatile ("nop");

	        while ((GPIOC->PDIR & (1 << 3))){
	        GPIOE->PDOR &= ~(1<<29); //red on
	        delay();
	        delay();
	        delay();
	        GPIOE->PDOR |= (1<<29);
	        delay();
	        GPIOD->PDOR &= ~(1<<5); //green
	        delay();
	        delay();
	        delay();
	        GPIOD->PDOR |= (1<<5);
	        delay();
	        GPIOE->PDOR |= (1 << 30); //yellow
	        delay();
	        delay();
	        delay();
	        GPIOE->PDOR &= ~(1 << 30);
	        delay();
	        }

	        if (!(GPIOC->PDIR & (1 << 3))){
	        GPIOD->PDOR |= (1<<5);
	        GPIOE->PDOR |= (1<<29);
	        	while (!(GPIOC->PDIR & (1 << 3))){
					GPIOE->PDOR |= (1 << 30); // Turn on yellow
					delay();
					delay();
					delay();
					GPIOE->PDOR &= ~(1 << 30); // Turn off yellow
					delay();
	        	}
	        }


    }

    return 0 ;
}
