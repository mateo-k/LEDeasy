#include "LEDeasy.h"

LEDeasy::LEDeasy(uint8_t pin, uint16_t on_time, uint16_t slow_off_time, uint16_t med_off_time, uint16_t fast_off_time):
  pin_(pin), on_time_(on_time), slow_off_time_(slow_off_time), med_off_time_(med_off_time), fast_off_time_(fast_off_time)
  {
  state_ = OFF;
  blink_state_ = BLINK_OFF;
}
void LEDeasy::update(bool sleeping){
  if(sleeping == true){
    digitalWrite(pin_,LOW);
    return;
  }
  uint32_t now = millis();    
  if(now < prev_ms_) prev_ms_ = 0; //TIMER OVERFLOW PROTECTION
  uint16_t off_time;
  if(state_ == OFF) digitalWrite(pin_,LOW); //CONSTANT OFF
  else if(state_ == ON) digitalWrite(pin_, HIGH); //CONSTANT ON
  else{ //BLINKING
    switch(state_){
      case SLOW: off_time = slow_off_time_; break;
      case MED: off_time = med_off_time_; break;
      case FAST: off_time = fast_off_time_; break;
    }
    if(blink_state_ == BLINK_OFF){
      if(prev_ms_ + off_time < now){
        prev_ms_ = now;
        blink_state_ = BLINK_ON;
        digitalWrite(pin_,HIGH);
      }
    }else{
      if(prev_ms_ + on_time_ < now){
        prev_ms_ = now;
        blink_state_ = BLINK_OFF;
        digitalWrite(pin_,LOW);
      }
    }
  } //END BLINKING SECTION
}
void LEDeasy::on(){
  state_ = ON;
  digitalWrite(pin_,HIGH);
}
void LEDeasy::off(){
  state_ = OFF;
  digitalWrite(pin_, LOW);
}
void LEDeasy::blink_slow(){
  blink_(SLOW);
}
void LEDeasy::blink_med(){
  blink_(MED);
}
void LEDeasy::blink_fast(){
  blink_(FAST);
}
LEDeasy::STATE_t LEDeasy::get_state(){
  return state_;
}
LEDeasy::BLINK_STATE_t LEDeasy::get_blink_state(){
  return blink_state_;
}
void LEDeasy::blink_(LEDeasy::STATE_t state){
  if( state_ == ON ){
    digitalWrite(pin_,LOW);
    prev_ms_ = millis();
    blink_state_ = BLINK_OFF;
  }else if( state_ == OFF){
    digitalWrite(pin_, HIGH);
    prev_ms_ = millis();
    blink_state_ = BLINK_ON;
  }   
  state_ = state;
}