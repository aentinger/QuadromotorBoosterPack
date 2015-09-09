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
  
  Quadromotor::set_direction(M1, FWD);
  Quadromotor::set_direction(M2, BWD);
  Quadromotor::set_direction(M3, FWD);
  Quadromotor::set_direction(M4, BWD);
}

static uint8_t speed = 0;
static boolean is_speed_increasing = true;

void loop()
{
  Quadromotor::set_speed(M1, speed);
  Quadromotor::set_speed(M2, speed);
  Quadromotor::set_speed(M3, speed);
  Quadromotor::set_speed(M4, speed);  
  
  if(is_speed_increasing)
  {
    speed += 10;
    if(speed > 200)
    {
      is_speed_increasing = false;
    }
  }
  else
  {
     speed -= 10;
     if(speed < 20)
     {
      is_speed_increasing = true; 
     }
  }
  
  delay(100);
}
