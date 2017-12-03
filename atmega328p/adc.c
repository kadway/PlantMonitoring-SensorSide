/*
 * adc.c
 *
 *  Created on: Oct 5, 2017
 *      Author: johny
 */


#include "adc.h"

void initADC(void){

 // DIDR0 = 0x00;           //Digital input disabled on all ADC ports
 // PRR &= ~(1<<PRADC);     //ADC turned on
  // AREF = AVcc
  ADMUX = (1<<REFS0);
  // ADC Enable and prescaler of 128
  // 16000000/128 = 125000
  ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE);
}

uint16_t adc_read(uint8_t ch){
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing

  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1<<ADSC);

  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));

  return (ADC);
}

void adc_read_int(uint8_t ch){
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing

  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1<<ADSC)|(1<<ADIE);

  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  return;
}
