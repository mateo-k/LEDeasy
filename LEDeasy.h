#ifndef LEDeasy_h
#define LEDeasy_h
#include <Arduino.h>  

class LEDeasy {
  public:
  typedef enum STATE_t{
    OFF, ON, SLOW, MED, FAST
  }STATE_t;
  typedef enum BLINK_STATE_t{
    BLINK_OFF,BLINK_ON
  } BLINK_STATE_t;
  
  public:
  //Constructor, setup blinks LED pin, and blinking parameters
  LEDeasy(uint8_t pin, uint16_t on_time = 20, uint16_t slow_off_time = 2000, uint16_t med_off_time = 500, uint16_t fast_off_time = 200);
    
  //update() function needs to be run periodically if LEDeasy need blinking functionality
  void update(bool sleeping = false);
  void on();
  void off();
  void blink_slow();
  void blink_med();
  void blink_fast();
  STATE_t get_state();
  BLINK_STATE_t get_blink_state();
  
  private:
  void blink_(STATE_t state);
  
  private:
  uint8_t pin_;
  uint32_t prev_ms_;
  uint16_t on_time_;
  uint16_t slow_off_time_;
  uint16_t med_off_time_;
  uint16_t fast_off_time_;
  STATE_t state_;
  BLINK_STATE_t blink_state_;
};

#endif