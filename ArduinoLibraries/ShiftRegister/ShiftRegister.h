/*
 * ShiftRegister.h
 *
 *  Created on: Dec 14, 2010
 *      Author: VAPREA
 */

#ifndef SHIFTREGISTER_H_
#define SHIFTREGISTER_H_

#include <stdint.h>
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// allowable values for bit_order
#define SHIFT_MSBIT_FIRST  0
#define SHIFT_LSBIT_FIRST  1

// allowable values for byte order
#define SHIFT_LAST_DIGIT_FIRST   0
#define SHIFT_FIRST_DIGIT_FIRST  1

class ShiftRegister{
public:
    ShiftRegister();
    ShiftRegister(uint8_t data_pin, uint8_t clk_pin, uint8_t latch_pin);
    void loadValues(const uint16_t * const value_array, const uint16_t num_bytes, const uint8_t byte_order, const uint8_t bit_order);
    void loadValue(const uint16_t value, const uint8_t bit_order);
    void setDataPin(uint8_t data_pin);
    void setClockPin(uint8_t clock_pin);
    void setLatchPin(uint8_t latch_pin);
    uint8_t data, clk, latch;
    void pulse_clk( void );
    void pulse_rck( void );
    void shift_in_bit( const uint8_t bit );    
private:

};

#endif /* SHIFTREGISTER_H_ */
