
#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int counter = 0;					// licznik multipleksacji

int debinary(int x)							// wyodrêbniam numer bitu na podstawie wartoœci dziesiêtnej
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
	PORTD = (~_BV(counter+4) & 0xF0) | (PORTD & 0x0F);	// Ustawiam 0 na dany bit w PORTD a resztê starszych bitów na 1
	if((PIND & 0x0F) != 0x0F)							// Sprawdzam czy dany klawisz jest naciœniêty
	{
		PORTA = (((debinary(~PIND & 0x0F)-1) * 4) + counter) | (PORTA & 0xF0);		// wypisujê zdekodowany znak klawisza
	}
	counter++;										// zwiêkszam licznik multipleksacji i w razie czego wracam do 0
	if(counter >= 4) 
	{
		counter = 0;
	}
	
}

int main(void)
{
	DDRA = 0x0F;                // Ustawiam ca³¹ liniê A i C jako wyjœcie
    DDRC = 0xFF;
    DDRD = 0xF0;                // Ustawiam starsze bity linii D jako wyjœcie

    PORTD |= 0x0F;                // podci¹gam m³odsze bity PORTD pod zasilanie

    OCR0 = 195;                    // ustawienie momentu przerwania na 195 (0,05s)

    TIMSK |= 0x02;                 // w³¹czenie przerwania TIMER0

    TCCR0 |= 0b01000101;            // w³¹czam tryb CTC i ustawiam prescaler na 1/1024

    sei();                        // w³¹czam obs³ugê przerwañ
	
	
    while (1) 
    {    
        PORTC ^= 0xFF;            // animacja
        _delay_ms(50);
    }
}
