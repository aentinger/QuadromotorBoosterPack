/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this file contains the code how to control the LXRobotics quadromotor booster pack
 * @file LXR_Quadromotor_BoosterPack.h
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef LXR_QUADROMOTOR_BOOSTER_PACK_H_
#define LXR_QUADROMOTOR_BOOSTER_PACK_H_

#include <stdint.h>

#define LXR_FOUR_SINGLE_MOTORS
//#define LXR_TWO_DUAL_MOTORS
//#define LXR_ONE_SINGLE_MOTOR

#if (defined LXR_FOUR_SINGLE_MOTORS && defined LXR_TWO_DUAL_MOTORS) || (defined LXR_TWO_DUAL_MOTORS && defined LXR_ONE_SINGLE_MOTOR) || (defined LXR_FOUR_SINGLE_MOTORS && defined LXR_ONE_SINGLE_MOTOR)
	#error "You can only choose one configuration at a time"
#endif

/**
 * @brief initializes the booster pack
 */
void init_quadromotor_booster_pack();

typedef enum {FWD, BWD} E_DIRECTION;

#if defined LXR_FOUR_SINGLE_MOTORS || defined LXR_TWO_DUAL_MOTORS || defined LXR_ONE_SINGLE_MOTOR

/**
 * @brief set speed for motor 1
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_1_set_speed(uint16_t const speed);
/**
 * @brief set direction for motor 1
 */
void motor_1_set_direction(E_DIRECTION const dir);

#endif

#if defined LXR_FOUR_SINGLE_MOTORS || defined LXR_TWO_DUAL_MOTORS

/**
 * @brief set speed for motor 2
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_2_set_speed(uint16_t const speed);
/**
 * @brief set direction for motor 2
 */
void motor_2_set_direction(E_DIRECTION const dir);

#endif

#if defined LXR_FOUR_SINGLE_MOTORS

/**
 * @brief set speed for motor 3
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_3_set_speed(uint16_t const speed);
/**
 * @brief set direction for motor 3
 */
void motor_3_set_direction(E_DIRECTION const dir);
/**
 * @brief set speed for motor 4
 * @param speed 0 means no speak and 1000 means full speed
 */
void motor_4_set_speed(uint16_t const speed);
/**
 * @brief set direction for motor 4
 */
void motor_4_set_direction(E_DIRECTION const dir);

#endif

#endif
