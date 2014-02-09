/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this file contains the code how to control a stepper motor with the LXRobotics quadromotor booster pack
 * @file LXR_Quadromotor_BoosterPack_Stepper.h
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef LXR_QUADROMOTOR_BOOSTER_PACK_STEPPER_H_
#define LXR_QUADROMOTOR_BOOSTER_PACK_STEPPER_H_

#include <stdint.h>

/**
 * @brief initializes the booster pack
 */
void init_quadromotor_booster_pack_stepper();

typedef enum {FWD, BWD} E_DIRECTION;

/**
 * @brief steps the motor one step forward or one step backwards
 */
void motor_1_do_one_step(E_DIRECTION const dir);

/**
 * @brief steps the motor one step forward or one step backwards
 */
void motor_2_do_one_step(E_DIRECTION const dir);

#endif
