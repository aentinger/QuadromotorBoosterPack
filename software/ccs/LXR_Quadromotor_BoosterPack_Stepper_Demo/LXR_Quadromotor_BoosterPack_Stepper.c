/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this file contains the code how to control a stepper motor with the LXRobotics quadromotor booster pack
 * @file LXR_Quadromotor_BoosterPack_Stepper.c
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "LXR_Quadromotor_BoosterPack_Stepper.h"
#include <msp430.h>

/* DEFINES */
#define M1_1_DIR		(P1DIR)
#define M1_2_DIR		(P1DIR)
#define M1_1_OUT		(P1OUT)
#define M1_2_OUT		(P1OUT)
#define M1_1			(1<<3)
#define M1_2			(1<<4)

#define M2_1_DIR		(P2DIR)
#define M2_2_DIR		(P2DIR)
#define M2_1_OUT		(P2OUT)
#define M2_2_OUT		(P2OUT)
#define M2_1			(1<<0)
#define M2_2			(1<<3)

#define M3_1_DIR		(P2DIR)
#define M3_2_DIR		(P2DIR)
#define M3_1_OUT		(P2OUT)
#define M3_2_OUT		(P2OUT)
#define M3_1			(1<<7)
#define M3_2			(1<<6)

#define M4_1_DIR		(P2DIR)
#define M4_2_DIR		(P2DIR)
#define M4_1_OUT		(P2OUT)
#define M4_2_OUT		(P2OUT)
#define M4_1			(1<<5)
#define M4_2			(1<<4)

/* MACROS */
#define M1_1_HIGH		M1_1_OUT |= M1_1
#define M1_1_LOW		M1_1_OUT &= ~M1_1
#define M1_2_HIGH		M1_2_OUT |= M1_2
#define M1_2_LOW		M1_2_OUT &= ~M1_2

#define M2_1_HIGH		M2_1_OUT |= M2_1
#define M2_1_LOW		M2_1_OUT &= ~M2_1
#define M2_2_HIGH		M2_2_OUT |= M2_2
#define M2_2_LOW		M2_2_OUT &= ~M2_2

#define M3_1_HIGH		M3_1_OUT |= M3_1
#define M3_1_LOW		M3_1_OUT &= ~M3_1
#define M3_2_HIGH		M3_2_OUT |= M3_2
#define M3_2_LOW		M3_2_OUT &= ~M3_2

#define M4_1_HIGH		M4_1_OUT |= M4_1
#define M4_1_LOW		M4_1_OUT &= ~M4_1
#define M4_2_HIGH		M4_2_OUT |= M4_2
#define M4_2_LOW		M4_2_OUT &= ~M4_2

/* CONSTANTS */
static uint8_t const NUMBER_OF_STEPS = 4;

/* DATA TYPES */
typedef struct {
	uint8_t current_step;
} s_stepper_params;

/* DATA */
static volatile s_stepper_params m_motor_1_params = {0};
static volatile s_stepper_params m_motor_2_params = {0};

/* PROTOTYPES */
void motor_1_step(uint8_t const step);
void motor_2_step(uint8_t const step);

/* GLOBAL FUNCTIONS */

/**
 * @brief initializes the booster pack
 */
void init_quadromotor_booster_pack_stepper()  {
	// set all gpios to outputs and low
	M1_1_DIR |= M1_1;	M1_1_LOW;
	M1_2_DIR |= M1_2;	M1_2_LOW;
	M2_1_DIR |= M2_1;	M2_1_LOW;
	M2_2_DIR |= M2_2;	M2_2_LOW;
	M3_1_DIR |= M3_1;	M3_1_LOW;
	M3_2_DIR |= M3_2;	M3_2_LOW;
	M4_1_DIR |= M4_1;	M4_1_LOW;
	M4_2_DIR |= M4_2;	M4_2_LOW;

	// disable all secondary port functions
	P1SEL = 0x00; P1SEL2 = 0x00;
	P2SEL = 0x00; P2SEL2 = 0x00;
}

/**
 * @brief steps the motor one step forward or one step backwards
 */
void motor_1_do_one_step(E_DIRECTION const dir) {
	if(dir == FWD) {
		(m_motor_1_params.current_step == (NUMBER_OF_STEPS-1)) ? m_motor_1_params.current_step = 0 : m_motor_1_params.current_step++;
	} else if(dir == BWD) {
		(m_motor_1_params.current_step == 0) ? m_motor_1_params.current_step = (NUMBER_OF_STEPS-1) : m_motor_1_params.current_step--;
	}
	motor_1_step(m_motor_1_params.current_step);
}

/**
 * @brief steps the motor one step forward or one step backwards
 */
void motor_2_do_one_step(E_DIRECTION const dir) {
	if(dir == FWD) {
		(m_motor_2_params.current_step == (NUMBER_OF_STEPS-1)) ? m_motor_2_params.current_step = 0 : m_motor_2_params.current_step++;
	} else if(dir == BWD) {
		(m_motor_2_params.current_step == 0) ? m_motor_2_params.current_step = (NUMBER_OF_STEPS-1) : m_motor_2_params.current_step--;
	}
	motor_2_step(m_motor_2_params.current_step);
}

/* LOCAL FUNCTIONS */

// M1+ = Coil 1A
// M1- = Coil 1B
// M2+ = Coil 2A
// M2- = Coil 2B

/**
 * @brief steps the motor to step number step
 */
void motor_1_step(uint8_t const step) {
	switch(step) {
	case 0: {
		M1_1_HIGH;
		M1_2_LOW;
		M2_1_HIGH;
		M2_2_LOW;
	} break;
	case 1: {
		M1_1_HIGH;
		M1_2_LOW;
		M2_1_LOW;
		M2_2_HIGH;
	} break;
	case 2: {
		M1_1_LOW;
		M1_2_HIGH;
		M2_1_LOW;
		M2_2_HIGH;
	} break;
	case 3: {
		M1_1_LOW;
		M1_2_HIGH;
		M2_1_HIGH;
		M2_2_LOW;
	} break;
	default: break;
	}
}

// M3+ = Coil 1A
// M3- = Coil 1B
// M4+ = Coil 2A
// M4- = Coil 2B

/**
 * @brief steps the motor to step number step
 */
void motor_2_step(uint8_t const step) {
	switch(step) {
	case 0: {
		M3_1_HIGH;
		M3_2_LOW;
		M4_1_HIGH;
		M4_2_LOW;
	} break;
	case 1: {
		M3_1_HIGH;
		M3_2_LOW;
		M4_1_LOW;
		M4_2_HIGH;
	} break;
	case 2: {
		M3_1_LOW;
		M3_2_HIGH;
		M4_1_LOW;
		M4_2_HIGH;
	} break;
	case 3: {
		M3_1_LOW;
		M3_2_HIGH;
		M4_1_HIGH;
		M4_2_LOW;
	} break;
	default: break;
	}
}
