
#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int counter = 0;					// licznik multipleksacji

int debinary(int x)							// wyodr�bniam numer bitu na podstawie warto�ci dziesi�tnej
{
	if(x == 8) {
		return 4;
	}
	if(x == 4) {
		return 3;
	}
	return x;
}

ISR (TIMER0_COMP_vect) {        						// Przerwanie TIMER0
	PORTD = (~_BV(counter+4) & 0xF0) | (PORTD & 0x0F);	// Ustawiam 0 na dany bit w PORTD a reszt� starszych bit�w na 1
	if((PIND & 0x0F) != 0x0F)							// Sprawdzam czy dany klawisz jest naci�ni�ty
	{
		PORTA = (((debinary(~PIND & 0x0F)-1) * 4) + counter) | (PORTA & 0xF0);		// wypisuj� zdekodowany znak klawisza
	}
	counter++;										// zwi�kszam licznik multipleksacji i w razie czego wracam do 0
	if(counter >= 4) 
	{
		counter = 0;
	}
	
}

int main(void)
{
	DDRA = 0x0F;                // Ustawiam ca�� lini� A i C jako wyj�cie
    DDRC = 0xFF;
    DDRD = 0xF0;                // Ustawiam starsze bity linii D jako wyj�cie

    PORTD |= 0x0F;                // podci�gam m�odsze bity PORTD pod zasilanie

    OCR0 = 195;                    // ustawienie momentu przerwania na 195 (0,05s)

    TIMSK |= 0x02;                 // w��czenie przerwania TIMER0

    TCCR0 |= 0b01000101;            // w��czam tryb CTC i ustawiam prescaler na 1/1024

    sei();                        // w��czam obs�ug� przerwa�
	
	
    while (1) 
    {    
        PORTC ^= 0xFF;            // animacja
        _delay_ms(50);
    }
}
