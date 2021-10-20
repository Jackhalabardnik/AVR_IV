

#include <avr/io.h>

int main(void)
{
	DDRD |= 0x20;				// Ustawiam 5 pin na linii D jako wyjœcie

	TCCR1A |= 0x82;				// Ustawiam TIMER 1 w tryb Fast PWM i w³¹czam tryb nieodwracaj¹cy
	TCCR1B |= 0x18;				// Ustawiam TIMER 1 w tryb Fast PWM i 

	ICR1 = 35625; 				// Ustawiam szczyt PWM na 0,57s
	OCR1A = 11875;				// Ustawiam moment porównania na 0,19s

	TCCR1B |= 0x03;				// ustawiam prescaler na 1/64


    while (1) 
    {	
		asm("nop");	
    }
}
