

#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER0_COMP_vect) {        				// Przerwanie TIMER0
	
	if((PIND & 0x0F) != 0x0F)						// Wykrywam �e na jedenym z wierszy jest logiczne 0
	{
		char row = PIND & 0x0F;					// Zapami�tuj� kt�ra to kolumna
		char backup_DDRD = DDRD;
		char backup_PORTD = PORTD;

		DDRD ^= 0xFF;							// Zamieniam linie wierszy
		PORTD ^= 0xFF;							// Zamieniam podci�gni�cia linii wierszy

		char column = PIND & 0xF0;				// Odczytuj� stan linii kolumn
		PORTA = ~(row | column);					// Ustawiam port A
		DDRD = backup_DDRD;							// Przywracam zapisane stany linii
		PORTD = backup_PORTD;
	}
}

int main(void)
{
	DDRA = 0xFF;                // Ustawiam ca�� lini� A i C jako wyj�cie
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
