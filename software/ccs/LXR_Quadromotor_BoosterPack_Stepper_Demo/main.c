/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief main file for demonstrating how to control a stepper motor with the LXRobotics Quadromotor BoosterPack
 * @file main.c
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include <msp430.h> 
#include "LXR_Quadromotor_BoosterPack_Stepper.h"

/* PROTOTYPE SECTION */
void setup_clock();

/* PROGRAM SECTION */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    setup_clock();

    init_quadromotor_booster_pack_stepper();

    for(;;) {
    	motor_1_do_one_step(FWD);
    	motor_2_do_one_step(BWD);
    	_delay_cycles(10000);
    }
	
	return 0;
}


/**
 * @brief setup the clock so the internal dco generates 16 MHz
 */
void setup_clock() {
	  if (CALBC1_16MHZ==0xFF) {					// If calibration constants erased
	    for(;;) asm(" NOP ");                    // do not load, trap CPU!!
	  }
	  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
	  BCSCTL1 = CALBC1_16MHZ;                   // Set range
	  DCOCTL = CALDCO_16MHZ;                    // Set DCO step + modulation*/
}
