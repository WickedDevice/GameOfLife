/*
 * ShiftRegister.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: VAPREA
 */
#include "ShiftRegister.h"

#define CLK_HIGH()(PORTD |= _BV(7))
#define CLK_LOW() (PORTD &= ~_BV(7))
#define RCK_HIGH()(PORTB |= _BV(1))
#define RCK_LOW() (PORTB &= ~_BV(1))
#define SER_HIGH()(PORTD |= _BV(5))
#define SER_LOW() (PORTD &= ~_BV(5))
#define EXTRACT_BIT(reg, bit)      ((reg >> bit) & 1)

ShiftRegister::ShiftRegister(){

}

ShiftRegister::ShiftRegister(uint8_t data_pin, uint8_t clk_pin, uint8_t latch_pin){
    setDataPin(data_pin);
    setClockPin(clk_pin);
    setLatchPin(latch_pin);
}

void ShiftRegister::setDataPin(uint8_t data_pin){
    data = data_pin;
    pinMode(data_pin,       OUTPUT);
    digitalWrite(data_pin,  LOW);
}

void ShiftRegister::setClockPin(uint8_t clock_pin){
    clk = clock_pin;
    pinMode(clock_pin,        OUTPUT);
    digitalWrite(clock_pin,   LOW);
}

void ShiftRegister::setLatchPin(uint8_t latch_pin){
    latch = latch_pin;
    pinMode(latch_pin,      OUTPUT);
    digitalWrite(latch_pin, LOW);
}

void ShiftRegister::loadValue(const uint16_t value){
  loadValues(&value, 1);
}

void ShiftRegister::loadValues( const uint16_t * const value_array, const uint16_t num_bytes ){

  int8_t ii = 0, jj = 0;
  uint16_t temp = 0;

  for(ii = 0; ii < num_bytes; ii++){
      temp = value_array[ii];
      for(jj = 0; jj < 16; jj++){
          if(temp & 1){
            SER_HIGH();
          }
          else{
            SER_LOW();
          }
          CLK_HIGH();
          CLK_LOW();          
          temp >>=1;
      }
  }

  RCK_HIGH();
  RCK_LOW();
}

void ShiftRegister::pulse_clk( void ){
  CLK_HIGH();
  CLK_LOW();
}

void ShiftRegister::pulse_rck( void ){
  RCK_HIGH();
  RCK_LOW();
}

void ShiftRegister::shift_in_bit( const uint8_t bit ){

}
