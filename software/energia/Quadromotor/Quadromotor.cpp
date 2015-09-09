/**
 * @author Alexander Entinger, MSc
 * @brief energia library file for the LXRobotics Quadromotor Booster Pack ( https://www.lxrobotics.com/produkte/booster-packs/quadromotor-boosterpack )
 * @file Quadromotor.h
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
/* INCLUDES */

#include "Quadromotor.h"

/* FUNCTIONS */

/* C */

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
static volatile uint16_t const MAX_SPEED = 1000;

/* DATA TYPES */

typedef struct {
	uint16_t speed;
	E_DIRECTION dir;
} s_motor_params;

/* GLOBAL FUNCTIONS */

/**
 * @brief initializes the booster pack
 */
void init_quadromotor_booster_pack()  {
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

#if defined LXR_FOUR_SINGLE_MOTORS || defined LXR_TWO_DUAL_MOTORS || defined LXR_ONE_SINGLE_MOTOR
	TA0CTL |= TASSEL_2;	// select SMCLK as clock source, thats 16 MHz, divider = 8, 1 timerstep = 500 ns
	TA0CTL |= 0xC0;
	TA0CTL |= TACLR;		// clear the timer

	TA0CCR0 = 2016;		// equals 1 ms
	TA0CCTL0 &= CCIFG;
	TA0CCTL0 |= CCIE;		// enable capture compare interrupt

	TA0CTL &= ~TAIFG;	// clear the inerrupt flag
	TA0CTL |= TAIE;		// enable the interrupt
	TA0CTL |= MC_1;		// timer counts up to TACCR0

	TA0CCR1 = 0x0000;
	TA0CCTL1 &= CCIFG;
	TA0CCTL1 |= CCIE;		// enable capture compare interrupt
#if !defined LXR_ONE_SINGLE_MOTOR
	TA0CCR2 = 0x0000;
	TA0CCTL2 &= CCIFG;
	TA0CCTL2 |= CCIE;		// enable capture compare interrupt
#endif
#endif

#if defined LXR_FOUR_SINGLE_MOTORS
	TA1CTL |= TASSEL_2;	// select SMCLK as clock source, thats 16 MHz, divider = 8, 1 timerstep = 500 ns
	TA1CTL |= 0xC0;
	TA1CTL |= TACLR;		// clear the timer

	TA1CCR0 = 2016;		// equals 1 ms
	TA1CCTL0 &= CCIFG;
	TA1CCTL0 |= CCIE;		// enable capture compare interrupt

	TA1CTL &= ~TAIFG;	// clear the inerrupt flag
	TA1CTL |= TAIE;		// enable the interrupt
	TA1CTL |= MC_1;		// timer counts up to TACCR0

	TA1CCR1 = 0x0000;
	TA1CCTL1 &= CCIFG;
	TA1CCTL1 |= CCIE;		// enable capture compare interrupt
	TA1CCR2 = 0x0000;
	TA1CCTL2 &= CCIFG;
	TA1CCTL2 |= CCIE;		// enable capture compare interrupt
#endif
}

#if defined LXR_FOUR_SINGLE_MOTORS || defined LXR_TWO_DUAL_MOTORS || defined LXR_ONE_SINGLE_MOTOR
static volatile s_motor_params m_motor_1 = {0, FWD};
#endif
#if defined LXR_FOUR_SINGLE_MOTORS || defined LXR_TWO_DUAL_MOTORS
static volatile s_motor_params m_motor_2 = {0, FWD};
#endif
#if defined LXR_FOUR_SINGLE_MOTORS
static volatile s_motor_params m_motor_3 = {0, FWD};
static volatile s_motor_params m_motor_4 = {0, FWD};
#endif


#if defined LXR_FOUR_SINGLE_MOTORS || defined LXR_TWO_DUAL_MOTORS || defined LXR_ONE_SINGLE_MOTOR

/**
 * @brief set speed for motor 1
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_1_set_speed(uint16_t const speed) {
	noInterrupts();
	if(speed <= MAX_SPEED) {
		m_motor_1.speed = (speed<<1); // multiply with 2
	}
	interrupts();
}

/**
 * @brief set direction for motor 1
 */
void motor_1_set_direction(E_DIRECTION const dir) {
	noInterrupts();
	m_motor_1.dir = dir;
	interrupts();
}

#endif

#if defined LXR_FOUR_SINGLE_MOTORS || defined LXR_TWO_DUAL_MOTORS

/**
 * @brief set speed for motor 2
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_2_set_speed(uint16_t const speed) {
	noInterrupts();
	if(speed <= MAX_SPEED) {
		m_motor_2.speed = (speed<<1); // multiply with 2
	}
	interrupts();
}

/**
 * @brief set direction for motor 2
 */
void motor_2_set_direction(E_DIRECTION const dir) {
	noInterrupts();
	m_motor_2.dir = dir;
	interrupts();
}

#endif

#if defined LXR_FOUR_SINGLE_MOTORS

/**
 * @brief set speed for motor 3
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_3_set_speed(uint16_t const speed) {
	noInterrupts();
	if(speed <= MAX_SPEED) {
		m_motor_3.speed = (speed<<1); // multiply with 2
	}
	interrupts();
}

/**
 * @brief set direction for motor 3
 */
void motor_3_set_direction(E_DIRECTION const dir) {
	noInterrupts();
	m_motor_3.dir = dir;
	interrupts();
}

/**
 * @brief set speed for motor 4
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_4_set_speed(uint16_t const speed) {
	noInterrupts();
	if(speed <= MAX_SPEED) {
		m_motor_4.speed = (speed<<1); // multiply with 2
	}
	interrupts();
}

/**
 * @brief set direction for motor 4
 */
void motor_4_set_direction(E_DIRECTION const dir) {
	noInterrupts();
	m_motor_4.dir = dir;
	interrupts();
}

#endif

#if defined LXR_FOUR_SINGLE_MOTORS

/**
 * @brief Timer A0 Interrupt Service Routine for CCR0
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
	// update the capture compare registers
	TA0CCR1 = m_motor_1.speed;
	TA0CCR2 = m_motor_2.speed;
	// set the pins
	if(m_motor_1.speed > 0) {
		if(m_motor_1.dir == FWD) {
			M1_1_HIGH; M1_2_LOW;
		} else if(m_motor_1.dir == BWD) {
			M1_1_LOW; M1_2_HIGH;
		}
	} else {
		M1_1_LOW; M1_2_LOW;
	}
	if(m_motor_2.speed > 0) {
		if(m_motor_2.dir == FWD) {
			M2_1_HIGH; M2_2_LOW;
		} else if(m_motor_2.dir == BWD) {
			M2_1_LOW; M2_2_HIGH;
		}
	} else {
		M2_1_LOW; M2_2_LOW;
	}
}

/**
 * @brief Timer A0 Interrupt Service Routine for all the other interrupts
 */
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void) {

	switch (TA0IV) {
	case 0: break; // no interrupt
	case 2: {
		M1_1_LOW; M1_2_LOW;
	}
		break;
	case 4: {
		M2_1_LOW; M2_2_LOW;
	}
		break;
	case 6:	break; // reserved
	case 8:	break; // reserved
	case 10: break; // overflow
	default: break;
	}
}

/**
 * @brief Timer A1 Interrupt Service Routine for CCR0
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void) {
	// update the capture compare registers
	TA1CCR1 = m_motor_3.speed;
	TA1CCR2 = m_motor_4.speed;
	// set the pins
	if(m_motor_3.speed > 0) {
		if(m_motor_3.dir == FWD) {
			M3_1_HIGH; M3_2_LOW;
		} else if(m_motor_3.dir == BWD) {
			M3_1_LOW; M3_2_HIGH;
		}
	} else {
		M3_1_LOW; M3_2_LOW;
	}
	if(m_motor_4.speed > 0) {
		if(m_motor_4.dir == FWD) {
			M4_1_HIGH; M4_2_LOW;
		} else if(m_motor_4.dir == BWD) {
			M4_1_LOW; M4_2_HIGH;
		}
	} else {
		M4_1_LOW; M4_2_LOW;
	}
}

/**
 * @brief Timer A1 Interrupt Service Routine for all the other interrupts
 */
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void) {

	switch (TA1IV) {
	case 0: break; // no interrupt
	case 2: {
		M3_1_LOW; M3_2_LOW;
	}
		break;
	case 4: {
		M4_1_LOW; M4_2_LOW;
	}
		break;
	case 6:	break; // reserved
	case 8:	break; // reserved
	case 10: break; // overflow
	default: break;
	}
}

#endif

#if defined LXR_TWO_DUAL_MOTORS

/**
 * @brief Timer A0 Interrupt Service Routine for CCR0
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
	// update the capture compare registers
	TA0CCR1 = m_motor_1.speed;
	TA0CCR2 = m_motor_2.speed;
	// set the pins
	if(m_motor_1.speed > 0) {
		if(m_motor_1.dir == FWD) {
			M1_1_HIGH; M1_2_LOW;
			M2_1_HIGH; M2_2_LOW;
		} else if(m_motor_1.dir == BWD) {
			M1_1_LOW; M1_2_HIGH;
			M2_1_LOW; M2_2_HIGH;
		}
	} else {
		M1_1_LOW; M1_2_LOW;
		M2_1_LOW; M2_2_LOW;
	}
	if(m_motor_2.speed > 0) {
		if(m_motor_2.dir == FWD) {
			M3_1_HIGH; M3_2_LOW;
			M4_1_HIGH; M4_2_LOW;
		} else if(m_motor_2.dir == BWD) {
			M3_1_LOW; M3_2_HIGH;
			M4_1_LOW; M4_2_HIGH;
		}
	} else {
		M3_1_LOW; M3_2_LOW;
		M4_1_LOW; M4_2_LOW;
	}
}

/**
 * @brief Timer A0 Interrupt Service Routine for all the other interrupts
 */
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void) {

	switch (TA0IV) {
	case 0: break; // no interrupt
	case 2: {
		M1_1_LOW; M1_2_LOW;
		M2_1_LOW; M2_2_LOW;
	}
		break;
	case 4: {
		M3_1_LOW; M3_2_LOW;
		M4_1_LOW; M4_2_LOW;
	}
		break;
	case 6:	break; // reserved
	case 8:	break; // reserved
	case 10: break; // overflow
	default: break;
	}
}

#endif

#if defined LXR_ONE_SINGLE_MOTOR

/**
 * @brief Timer A0 Interrupt Service Routine for CCR0
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void) {
	// update the capture compare registers
	TA0CCR1 = m_motor_1.speed;
	// set the pins
	if(m_motor_1.speed > 0) {
		if(m_motor_1.dir == FWD) {
			M1_1_HIGH; M1_2_LOW;
			M2_1_HIGH; M2_2_LOW;
			M3_1_HIGH; M3_2_LOW;
			M4_1_HIGH; M4_2_LOW;
		} else if(m_motor_1.dir == BWD) {
			M1_1_LOW; M1_2_HIGH;
			M2_1_LOW; M2_2_HIGH;
			M3_1_LOW; M3_2_HIGH;
			M4_1_LOW; M4_2_HIGH;

		}
	} else {
		M1_1_LOW; M1_2_LOW;
		M2_1_LOW; M2_2_LOW;
		M3_1_LOW; M3_2_LOW;
		M4_1_LOW; M4_2_LOW;
	}
}

/**
 * @brief Timer A0 Interrupt Service Routine for all the other interrupts
 */
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void) {

	switch (TA0IV) {
	case 0: break; // no interrupt
	case 2: {
		M1_1_LOW; M1_2_LOW;
		M2_1_LOW; M2_2_LOW;
		M3_1_LOW; M3_2_LOW;
		M4_1_LOW; M4_2_LOW;
	}
		break;
	case 4: break;
	case 6:	break; // reserved
	case 8:	break; // reserved
	case 10: break; // overflow
	default: break;
	}
}

#endif

/* CPP INTERFACE */

/**
 * @brief initializes the booster pack
 */
void Quadromotor::begin()
{
  init_quadromotor_booster_pack();
}

/**
 * @brief set the speed of the motor
 */
void Quadromotor::set_speed(E_MOTOR const motor, uint16_t const speed)
{
  switch(motor)
  {
#ifdef LXR_FOUR_SINGLE_MOTORS
    case M1: motor_1_set_speed(speed); break;
    case M2: motor_2_set_speed(speed); break;
    case M3: motor_3_set_speed(speed); break;
    case M4: motor_4_set_speed(speed); break;
#endif
#ifdef LXR_TWO_DUAL_MOTORS
    case M1: motor_1_set_speed(speed); break;
    case M2: motor_2_set_speed(speed); break;
#endif
#ifdef LXR_ONE_SINGLE_MOTOR
    case M1: motor_1_set_speed(speed); break;
#endif
    default: break;
  }
}
  
/**
 * @brief set the direction of the motor
 */
void Quadromotor::set_direction(E_MOTOR const motor, E_DIRECTION const dir)
{
    switch(motor)
    {
#ifdef LXR_FOUR_SINGLE_MOTORS
    case M1: motor_1_set_direction(dir); break;
    case M2: motor_2_set_direction(dir); break;
    case M3: motor_3_set_direction(dir); break;
    case M4: motor_4_set_direction(dir); break;
#endif
#ifdef LXR_TWO_DUAL_MOTORS
    case M1: motor_1_set_direction(dir); break;
    case M2: motor_2_set_direction(dir); break;
#endif
#ifdef LXR_ONE_SINGLE_MOTOR
    case M1: motor_1_set_direction(dir); break;
#endif
    default: break;
   }
}
