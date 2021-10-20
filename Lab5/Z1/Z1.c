#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect) {		// przerwanie TIMER1
    PORTA &= 0xFE;				// wy³¹czam LED0
    
    TCCR1B &= 0xF8; 			// wy³¹czam TIMER1
}


ISR (INT0_vect) 				// przerwanie INT0 
{
	TCNT1 =0;					// resetujê licznik
    TCCR1B |= 0x03 ; 			// w³¹czam TIMER1 ustawiaj¹c prescaler w tryb 1/64
    
    PORTA |= 0x01;				// w³¹czam LED0
}


int main(void)
{
	DDRC = 0xff;				// Ustawiam liniê C jako wyjœcie
    DDRA |= 0x01;				// Ustawiam pierwszy bit na linii A jako 
    PORTD |= 0x04;				// Podci¹gam przycisk pod liniê zasilania

	MCUCR |= 0x02; 				// ustawienie aktywacji przerwania INT0 w tryb falling-edge
    GICR |= 0x40; 				// w³¹czenie przerwania INT0

	OCR1A = 31250;				// ustawienie momentu przerwania na 31250 (0,5s)

	TIMSK |= 0x10; 				// w³¹czenie przerwania TIMER1

	sei();						// w³¹czam obs³ugê przerwañ
	
    while (1) 
    {	
		PORTC ^= 0xff;			// negujê stan portu C w celu zmiany jego stanu
		_delay_ms(50);			// czekam 50ms

    }
}
