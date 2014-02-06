/**
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 * @brief demo file how to use the quadromotor booster pack
 * @file main.c
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include <msp430.h> 

#include "LXR_Quadromotor_BoosterPack.h"

/* PROTOTYPE SECTION */
void setup_clock();
void test_four_single_motors();
void test_two_dual_motors();
void test_single_motor();

/* PROGRAM SECTION */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    setup_clock();

    init_quadromotor_booster_pack();

    test_four_single_motors();
    //test_two_dual_motors();
    //test_single_motor();

    for(;;) {
    	// loop forever, dont return
    	asm(" NOP ");
    }
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

/**
 * @brief use the booster pack to control 4 different motors independently from one another
 */
void test_four_single_motors() {
	motor_1_set_direction(FWD);
	motor_1_set_speed(250);

	motor_2_set_direction(BWD);
	motor_2_set_speed(500);

	motor_3_set_direction(FWD);
	motor_3_set_speed(750);

	motor_4_set_direction(BWD);
	motor_4_set_speed(1000);
}

/**
 * @brief use the booster pack to control 2 different motors independently from one another, but with double strength
 */
void test_two_dual_motors() {
	motor_1_set_direction(FWD);
	motor_1_set_speed(250);

	motor_2_set_direction(BWD);
	motor_2_set_speed(750);
}

/**
 * @brief use the booster pack to control 1 but with four times the strength of one single motor
 */
void test_single_motor() {
	motor_1_set_direction(FWD);
	motor_1_set_speed(500);
}
