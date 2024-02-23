
/**
 * @file    Motor Check.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"

void delay(unsigned short delay_t) { //done
    SIM->SCGC6 |= (1 << 24); // Clock Enable TPM2 bit 24
    SIM->SOPT2 |= (0x2 << 24); // Set TPMSRC to OSCERCLK ("10")
    TPM0->CONF |= (0x1 << 17); // Stop on Overflow. (don't reset)
    TPM0->SC = (0x1 << 7) | (0x07); // Reset Timer Overflow Flag, Set Prescaler 128 (111) 7 registers
    TPM0->MOD = delay_t * 61 + delay_t/2; //wait to hit next tick. delay_t = 0.001s. 61 = 8MHz/128

    TPM0->SC |= 0x01 << 3; // Start the clock!
    while(!(TPM0->SC & 0x80)){} // Wait until Overflow Flag

    TPM0->SC &= ~TPM_SC_CMOD_MASK; // Stop the timer
    TPM0->SC |= TPM_SC_TOF_MASK; // Clear TOF flag
    return;
}

void stop(){ //done
	//Right stop
	GPIOB->PCOR |= (1 << 1);   // Set PTB1 to low (AI1)
	GPIOB->PCOR |= (1 << 0); // Set PTB0 to low (AI2)
	//Left stop
	GPIOC->PCOR |= (1 << 1);   // Set PTC1 to low (BI1)
	GPIOC->PCOR |= (1 << 2); // Set PTC2 to low (BI2)
}

void straight(){ //done
	// Set the PWM duty cycle for the motors
	TPM2->CONTROLS[0].CnV = 7000; // set duty cycle to 50% or more
	TPM2->CONTROLS[1].CnV = 7000; // set duty cycle to 50%
	//Right forward
	GPIOB->PSOR |= (1 << 1);   // Set PTB1 to high (AI1)
    GPIOB->PCOR |= 1 << 0; // Set PTB0 to low (AI2)
    //Left forwards
    GPIOC->PCOR |= (1 << 1);   // Set PTC1 to low (BI1)
    GPIOC->PSOR |= 1 << 2; // Set PTC2 to high (BI2)
	delay(800);
	stop();
}

void turnCW90(){ //done
	// Set the PWM duty cycle for the motors
	TPM2->CONTROLS[0].CnV = 7000; // set duty cycle to 50% or more
	TPM2->CONTROLS[1].CnV = 7000; // set duty cycle to 50%
	//Right backwards
	GPIOB->PCOR |= (1 << 1);   // Set PTB1 to low (AI1)
    GPIOB->PSOR |= 1 << 0; // Set PTB0 to high (AI2)
	//Left forwards
	GPIOC->PSOR &= ~(1 << 1);   // Set PTC1 to low (BI1)
	GPIOC->PSOR |= 1 << 2; // Set PTC2 to high (BI2)
	delay(500);
	stop();
}

void turnCCW90(){ //done
	// Set the PWM duty cycle for the motors
	TPM2->CONTROLS[0].CnV = 7000; // set duty cycle to 50% or more (LEFT)
	TPM2->CONTROLS[1].CnV = 7000; // set duty cycle to 50% (RIGHT)
	//Right forwards
	GPIOB->PSOR |= (1 << 1);   // Set PTB1 to high (AI1)
    GPIOB->PCOR |= 1 << 0; // Set PTB0 to low (AI2)
	//Left backwards
	GPIOC->PSOR |= (1 << 1);   // Set PTC1 to high (BI1)
	GPIOC->PCOR |= 1 << 2; // Set PTC2 to low (BI2)
	delay(500);
	stop();
}

void turnCCWCurve(){ //done
	// Set the PWM duty cycle for the motors
	TPM2->CONTROLS[0].CnV = 7900; // set duty cycle to 50% or more
	TPM2->CONTROLS[1].CnV = 4300; // set duty cycle to 50%
	//Right forward
    GPIOB->PSOR |= (1 << 1);   // Set PTB1 to high (AI1)
    GPIOB->PCOR |= 1 << 0; // Set PTB0 to low (AI2)
	//Left forwards
	GPIOC->PSOR &= ~(1 << 1);   // Set PTC1 to low (BI1)
	GPIOC->PSOR |= 1 << 2; // Set PTC2 to high (BI2)

	for (int i = 0; i < 4; i++){
		delay(900);
	}

	stop();
}

void turnCWCurve(){
	// Set the PWM duty cycle for the motors
	TPM2->CONTROLS[0].CnV = 4300; // set duty cycle to 50% or more
	TPM2->CONTROLS[1].CnV = 7900; // set duty cycle to 50%
	//Right forward
    GPIOB->PSOR |= (1 << 1);   // Set PTB1 to high (AI1)
    GPIOB->PCOR |= 1 << 0; // Set PTB0 to low (AI2)
	//Left forwards
	GPIOC->PSOR &= ~(1 << 1);   // Set PTC1 to low (BI1)
	GPIOC->PSOR |= 1 << 2; // Set PTC2 to high (BI2)

	for (int i = 0; i < 4; i++){
		delay(900);
	}

	stop();
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

    /*Turning LED2 on TO TEST SW1*/
    SIM->SCGC5 |= 1<<13; // Enable port E
    PORTE->PCR[29] &= ~(0x7 << 8); //Clear MUX
    PORTE->PCR[29] |= (0x1 << 8); //Set E29 to GPIO Function
    GPIOE->PDDR |= 1<<29; //Set E29 Output
    /*Enabling SW1 (PTC3) and SW2 (PTC12) with interrupt*/
    SIM->SCGC5 |= 1<<11;  // Enable Port C Clock
    PORTC->PCR[3] &= 0xF0703; // Clear First
    PORTC->PCR[3] |= 0xF0703 & ((0xA << 16) | (1 << 8) | 0x3 ); // Set MUX bits, enable pullups, interrupt on falling edge
    GPIOC->PDDR &= ~(1 << 3); // Setup Pin 3 Port C as input
    PORTC->PCR[12] &= 0xF0703; // Clear First
    PORTC->PCR[12] |= 0xF0703 & ((0xA << 16) | (1 << 8) | 0x3 ); // Set MUX bits, enable pullups, interrupt on falling edge
    GPIOC->PDDR &= ~(1 << 12); // Setup Pin 12 Port C as input

    /*Enabling PTB*/
    SIM->SCGC5 |= 1<<10; // Enable port B


    // Setting Up the motors :D -------------------------------------------
    /*Left Motor*/
    PORTB->PCR[0] &= ~(0x7 << 8); //Clear MUX PTB0
    PORTB->PCR[1] &= ~(0x7 << 8); //Clear MUX PTB1
    PORTB->PCR[0] |= (0x1 << 8); //Set B0 to GPIO Function
    PORTB->PCR[1] |= (0x1 << 8); //Set B1 to GPIO Function
    GPIOB->PDDR |= 1<<0; //Set B0 Output
    GPIOB->PDDR |= 1<<1; //Set B1 Output
    /*RightMotor*/
    PORTC->PCR[1] &= ~(0x7 << 8); //Clear MUX PTC1
    PORTC->PCR[2] &= ~(0x7 << 8); //Clear MUX PTC2
    PORTC->PCR[1] |= (0x1 << 8); //Set C1 to GPIO Function
    PORTC->PCR[2] |= (0x1 << 8); //Set C2 to GPIO Function
    GPIOC->PDDR |= 1<<1; //Set C1 Output
    GPIOC->PDDR |= 1<<2; //Set C2 Output


    // Setup Timer/PWM ------------------------------------------------------
    SIM->SCGC6 |= (1 << 24); // Clock Enable TPM0 bit 26
    SIM->SOPT2 |= (0x2 << 24); // Set TPMSRC to OSCERCLK ("10")
    // TPM0->CONF |= (0x1 << 17); // Stop on Overflow. (don't reset)
    // TPM0->SC = (0x1 << 7) | (0x07); // Reset Timer Overflow Flag, Set Prescaler 128 (111) 7 registers
    // TPM0->SC |= 0x01 << 3 | 0x7; // Start the clock!
    // TPM2
    SIM->SCGC6 |= (1 << 26); // Clock Enable TPM2 bit 26
    SIM->SOPT2 |= (0x2 << 26); // Set TPMSRC to OSCERCLK ("10")
    // TPM2->CONF |= (0x1 << 17); // Stop on Overflow. (don't reset)
    TPM2->SC |= (0x1 << 3) || (0x01 << 3); // Reset Timer Overflow Flag, Set Prescaler 128 (111) 7 registers
    // TPM2->MOD = 123; //wait to hit next tick. delay_t = 0.001s. 61 = 8MHz/128
    TPM2->SC |= 0x01 << 3; // Start the clock!

    // Pg 173
    PORTB->PCR[2] &= ~(0x700); // Setup PTB2 as TPM2_CH0
    PORTB->PCR[2] |= (0x300); // Set PCR mux for PTB2 as TPM2_CH0 (Alt 3)
    PORTB->PCR[3] &= ~(0x700); // Setup PTB3 as TPM2_CH1
    PORTB->PCR[3] |= (0x300); // Set PCR mux for PTB3 as TPM2_CH1 (Alt 3)
    TPM2->CONTROLS[0].CnSC |= (0x2 << 2) | (0x2 << 4);  // Edge PWMA
    TPM2->CONTROLS[1].CnSC |= (0x2 << 2) | (0x2 << 4);  // Edge PWMB
    TPM2->MOD = 7999;

    /* Force the counter to be placed into memory. */
    volatile static int i = 1 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        __asm volatile ("nop");

        int sw1 = 0;
        int sw2 = 0;

        // Corners
        if (!(GPIOC->PDIR & (1 << 3))){
        	sw1 = 1;
        	delay(700);
        }
        if (sw1 == 1){
        	straight();
        	delay(300);
        	turnCCW90();
        	delay(300);
        	straight();
        	delay(300);
        	turnCCW90();
        	delay(300);
        	straight();
        	delay(300);
        	turnCW90();
        	delay(300);
        	straight();
        	delay(300);
        	turnCW90();
        	delay(300);
        	straight();
        	sw1 = 0;
        }

        // Curve
        if (!(GPIOC->PDIR & (1 << 12))){
        	sw2 = 1;
            delay(700);
        }
        if (sw2 == 1){
        	turnCCWCurve();
        	delay(100);
        	turnCWCurve();
            sw2 = 0;
        }

    }

    return 0 ;
}
