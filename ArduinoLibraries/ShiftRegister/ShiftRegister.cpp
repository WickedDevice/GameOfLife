/*
 * ShiftRegister.cpp
 *
 *  Created on: Dec 14, 2010
 *      Author: VAPREA
 */
#include "ShiftRegister.h"

#define CLK_HIGH()(digitalWrite(clk,    HIGH))
#define CLK_LOW() (digitalWrite(clk,    LOW))
#define RCK_HIGH()(digitalWrite(latch,  HIGH))
#define RCK_LOW() (digitalWrite(latch,  LOW))
#define SER_HIGH()(digitalWrite(data,   HIGH))
#define SER_LOW() (digitalWrite(data,   LOW))
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

void ShiftRegister::loadValue(const uint16_t value, const uint8_t bit_order){
  loadValues(&value, 1, SHIFT_LAST_DIGIT_FIRST, bit_order);
}

void ShiftRegister::loadValues( const uint16_t * const value_array, const uint16_t num_bytes, const uint8_t byte_order, const uint8_t bit_order ){

  int8_t ii = 0, jj = 0;
  uint16_t temp = 0;
  const int8_t next_bit   = (bit_order == SHIFT_MSBIT_FIRST)        ? -1 : 1;
  const int16_t next_byte  = (byte_order == SHIFT_LAST_DIGIT_FIRST)  ? -1 : 1;
  int8_t bit_index;
  int8_t byte_index = (byte_order == SHIFT_LAST_DIGIT_FIRST)  ?  num_bytes - 1 : 0;

  for(ii = 0; ii < num_bytes; ii++){
      temp = value_array[byte_index];
      bit_index = (bit_order == SHIFT_MSBIT_FIRST) ?  15 : 0;
      for(jj = 0; jj < 16; jj++){
          shift_in_bit(EXTRACT_BIT(temp, bit_index));
          bit_index += next_bit;
      }
      byte_index += next_byte;
  }

  pulse_rck();
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
  if(bit == 0){
    SER_LOW();
  }
  else{
    SER_HIGH();
  }
  pulse_clk();
}
