

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

const int czas_trwania_przebiegu_1 = 10000;  // 0,16s
volatile int czas_trwania_przebiegu_2;

ISR (TIMER1_COMPA_vect) {		// przerwanie TIMER1
    PORTA ^= 0x01;				// neguj� stan LED0
    if(OCR1A == czas_trwania_przebiegu_2)		// zmieniam czas trwania przebiegu w zale�no�ci od stanu
    {
        OCR1A = czas_trwania_przebiegu_1;
    }
    else
    {
        OCR1A = czas_trwania_przebiegu_2;
    }
}

ISR (INT0_vect) 				// przerwanie INT0 
{
	PORTA |= 0x80;				// zapalam LED7

    if(czas_trwania_przebiegu_2 != 12000)			// je�eli czas stanu 0 jest wi�kszy ni� minimalny
    {
        if(czas_trwania_przebiegu_2 - 5000 > 12000) // je�eli mo�na jeszcze skr�ci� czas 
        {
			if(OCR1A == czas_trwania_przebiegu_2)	// je�eli aktualnie jeste�my w stanie 0
			{
	            czas_trwania_przebiegu_2 -= 5000;		// skracamy czas
				OCR1A = czas_trwania_przebiegu_2;		// aktualizujemy licznik
				if(OCR1A >= TCNT1)						// sprawdzamy czy TCNT1 nie przekroczy�o licznika i ewentualnie poprawiamy jego warto��
				{
					TCNT1 = OCR1A - 1;
				}
			}
			else										// je�eli jeste�my w stanie 1 to po prostu skracamy czas
			{
				czas_trwania_przebiegu_2 -= 5000;
			}

			PORTA &= 0x7F;									// nie osi�gn�li�my minimalnej warto�ci, wy��czamy LED7
        }
        else											// je�eli nie da si� dalej skr�ci�
        {
			if(OCR1A == czas_trwania_przebiegu_2)	// je�eli aktualnie jeste�my w stanie 0
			{
	            czas_trwania_przebiegu_2 = 12000;		// skracamy czas
				OCR1A = czas_trwania_przebiegu_2;		// aktualizujemy licznik
				if(OCR1A >= TCNT1)						// sprawdzamy czy TCNT1 nie przekroczy�o licznika i ewentualnie poprawiamy jego warto��
				{
					TCNT1 = OCR1A - 1;
				}
			}
			else										// je�eli jeste�my w stanie 1 to po prostu skracamy czas
			{
				czas_trwania_przebiegu_2 = 12000;
			}
        }
    }
}

int main(void)
{
	DDRC = 0xff;				// Ustawiam lini� C jako wyj�cie
    DDRA |= 0x81;				// Ustawiam pierwszy bit na linii A jako 
    PORTD |= 0x04;				// Podci�gam przycisk pod lini� zasilania

	MCUCR |= 0x02; 				// ustawienie aktywacji przerwania INT0 w tryb falling-edge
    GICR |= 0x40; 				// w��czenie przerwania INT0

	TIMSK |= 0x10; 				// w��czenie przerwania TIMER1
	TCCR1B |=  0x08;			// w��czenie timera w trybie ctc

	czas_trwania_przebiegu_2 = 20000;        // 0.32s

    OCR1A = czas_trwania_przebiegu_2;

	TCCR1B |= 0x03;				// ustawiam prescaler na 1/64

	sei();						// w��czam obs�ug� przerwa�
	
    while (1) 
    {	
		PORTC ^= 0xff;			// neguj� stan portu C w celu zmiany jego stanu
		_delay_ms(25);			// czekam 50ms

    }
}
