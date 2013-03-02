#include <ShiftRegister.h>

/* * * * * * * * * * * * * * * * * * *
 * pin 5 = ShiftRegister.SER (data)  *
 * pin 7 = ShiftRegister.CLK (clock) *
 * pin 9 = ShiftRegister.RCK (latch) *
 * * * * * * * * * * * * * * * * * * */
ShiftRegister sr(5, 7, 9);
byte pattern[4] = {0xAA, 0x55, 0x33, 0xCC};
int flag = 0;

void setup()
{
  /* nothing to do here */
}

void loop()
{
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *  Shift out alternating mirrored pattern order at 2Hz  *
   *    assumes 4 chained shift registers are used         *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
   if(flag)
   {
     /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      *  on odd flags, shift out pattern with:                    *
      *    byte 0 first (first digit first)                       *
      *    and bit 0 first for each byte (least significant bit)  *
      *                  time0                           time31   *
      *  bit-shift order: 01010101 10101010 11001100 00110011     *
      *                     0xAA     0x55     0x33     0xCC       *
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */     
     sr.loadValues(pattern, 4, SHIFT_FIRST_DIGIT_FIRST, SHIFT_LSBIT_FIRST);
   }
   else
   {
     /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      *  on even flags, shift out pattern with:                   *
      *    byte 3 first (last digit first)                        *
      *    and bit 7 first for each byte (most significant bit)   *
      *                  time0                           time31   *      
      *  bit-shift order: 11001100 00110011 01010101 10101010     *
      *                     0xCC     0x33     0x55     0xAA       *     
      * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */    
     sr.loadValues(pattern, 4, SHIFT_LAST_DIGIT_FIRST, SHIFT_MSBIT_FIRST);
   }
   
   flag = 1 - flag;                /* toggle the flag variable         */
   delay(500);                     /* count up at 2 counts per second  */
}
