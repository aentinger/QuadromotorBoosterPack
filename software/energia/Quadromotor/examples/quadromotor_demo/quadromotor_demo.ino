/**
 * @author Alexander Entinger, MSc
 * @brief demo sketch file for the LXRobotics Quadromotor Booster Pack ( https://www.lxrobotics.com/produkte/booster-packs/quadromotor-boosterpack )
 * @file Quadromotor_demo.h
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "Quadromotor.h"

void setup()
{
  Quadromotor::begin();
}

void loop()
{
  // drive forward
  Quadromotor::set_direction(M1, FWD);
  Quadromotor::set_direction(M2, FWD);
  Quadromotor::set_direction(M3, FWD);
  Quadromotor::set_direction(M4, FWD); 
  ramp_up();
  ramp_down();

  // drive backward
  Quadromotor::set_direction(M1, BWD);
  Quadromotor::set_direction(M2, BWD);
  Quadromotor::set_direction(M3, BWD);
  Quadromotor::set_direction(M4, BWD); 
  ramp_up();
  ramp_down();
}

void ramp_up()
{
  for(uint16_t speed = 0; speed < MAX_SPEED; speed+=50)
  {
      Quadromotor::set_speed(M1, speed);
    Quadromotor::set_speed(M2, speed);
    Quadromotor::set_speed(M3, speed);
    Quadromotor::set_speed(M4, speed);  
    delay(100);
  }
}

void ramp_down()
{
  for(uint16_t speed = MAX_SPEED; speed > 100; speed-=50)
  {
    Quadromotor::set_speed(M1, speed);
    Quadromotor::set_speed(M2, speed);
    Quadromotor::set_speed(M3, speed);
    Quadromotor::set_speed(M4, speed);  
    delay(100);
  }
}
