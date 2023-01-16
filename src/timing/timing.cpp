#include "timing.h"

const int state;

bool startWelding (uint8_t pwm, uint8_t delay) {
   // TODO
   unsigned long previousMillis=0;
   unsigned long currentMillis = millis();
   if (state == LOW)
   {
      if(currentMillis == on_delay){
       analogWrite(Pin,duty_cycle);

      }
      
   }
    if (state == HIGH)
  {   
      previousMillis = currentMillis;
      if(currentMillis-previousMillis>=off_delay){
        analogWrite(Pin,0);
      }
  }
  return true;
}

void stopWelding () {
   // TODO
}