/*
 * try.c
 *
 * Created: 1/21/2020 9:38:24 AM
 * Author : Muhammad Syed
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#define CLOC PD4 //Clock for clock r and clock in of ADC

void CLOC1(void);

int main(void)

{	
	DDRC = 0x00; // Pin defined for reading ADC input 
	DDRB = 0x01; //Setting pin for OCR0
	DDRD|= (1<<CLOC); //Setting Clock pin
	TCCR0|= (1<<WGM00)|(0<<WGM01)|(1<<CS00)|(1<<COM01)|(0<<COM00); //PWM setting output
	TCCR1B = (1<<CS12)|((1<<CS10));
	TCNT1 = 0;     //counter pin 
    char value;    // Variable for reading for ADC
    while (1) 
    {	
		
		CLOC1(); // giving clock to ADC for reading values
		value = PINC; // saving readings
		
		//comparing values for ranges
		if (value<=64)
		{
			OCR0 = 10;
		}
		else if ((value>64)&&(value<=128))
		{
			OCR0 = 80;
		}
		else if ((value>128)&&(value<=193))
		{
			OCR0 = 160;
		}
		else{
			OCR0 = 255;
			}
		
	}
}

// function of clock
void CLOC1(void){
	if (TCNT1>=50)
	{
		PORTD^=(1<<CLOC);
		TCNT1 = 0;
	}
}
