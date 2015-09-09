/**
 * @author Alexander Entinger, MSc
 * @brief energia library file for the LXRobotics Quadromotor Booster Pack ( https://www.lxrobotics.com/produkte/booster-packs/quadromotor-boosterpack )
 * @file Quadromotor.h
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef QUADROMOTOR_BOOSTERPACK_H_
#define QUADROMOTOR_BOOSTERPACK_H_

/* INCLUDES */

#include "Energia.h"

#include <stdint.h>

/* CONSTANTS */

static volatile uint16_t const MAX_SPEED = 1000;

/* TYPEDEFS */

typedef enum {FWD, BWD} E_DIRECTION;
typedef enum {M1, M2, M3, M4} E_MOTOR;

/* PROTOTYPES */

class Quadromotor
{
  public:
  
  /**
   * @brief initializes the booster pack
   */
  static void begin();
   
  /**
   * @brief set the speed of the motor
   */
  static void set_speed(E_MOTOR const motor, uint16_t const speed);
  
  /**
   * @brief set the direction of the motor
   */
  static void set_direction(E_MOTOR const motor, E_DIRECTION const dir);
   
   private:

   /**
    * @brief Constructor/Destructor are private - no public constructing
    */
   Quadromotor() { }   
   ~Quadromotor() { }   
};

#endif
