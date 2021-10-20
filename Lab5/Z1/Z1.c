#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect) {		// przerwanie TIMER1
    PORTA &= 0xFE;				// wy��czam LED0
    
    TCCR1B &= 0xF8; 			// wy��czam TIMER1
}


ISR (INT0_vect) 				// przerwanie INT0 
{
	TCNT1 =0;					// resetuj� licznik
    TCCR1B |= 0x03 ; 			// w��czam TIMER1 ustawiaj�c prescaler w tryb 1/64
    
    PORTA |= 0x01;				// w��czam LED0
}


int main(void)
{
	DDRC = 0xff;				// Ustawiam lini� C jako wyj�cie
    DDRA |= 0x01;				// Ustawiam pierwszy bit na linii A jako 
    PORTD |= 0x04;				// Podci�gam przycisk pod lini� zasilania

	MCUCR |= 0x02; 				// ustawienie aktywacji przerwania INT0 w tryb falling-edge
    GICR |= 0x40; 				// w��czenie przerwania INT0

	OCR1A = 31250;				// ustawienie momentu przerwania na 31250 (0,5s)

	TIMSK |= 0x10; 				// w��czenie przerwania TIMER1

	sei();						// w��czam obs�ug� przerwa�
	
    while (1) 
    {	
		PORTC ^= 0xff;			// neguj� stan portu C w celu zmiany jego stanu
		_delay_ms(50);			// czekam 50ms

    }
}
