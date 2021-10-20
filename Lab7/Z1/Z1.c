
#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (INT0_vect) 								// Przerwanie INT0 
{	
	cli();															// Upewniam siê ¿e nie dojdzie do wykonania przerwania podczas tego przerwania
	PORTB += 1;
	for(int i = 0; i < 4; i++) 
	{
		PORTD = (~_BV(i+4) & 0xF0) | (PORTD & 0x0F);				// Ustawiam 0 na danym bicie i resztê na 1 (pomijam m³odsze bity)
		_delay_us(10);
		if(!(PIND & 0x04))							// Sprawdzam czy dany klawisz jest naciœniêty
		{
			PORTA = (PORTA & 0x0F) | (((i + 1) << 4) & 0xF0);
		}
	}

	PORTD &= 0x0F;

	GIFR |= 0b01000000;				// upewniam siê ¿e nie dojdzie do paso¿ytniczych przerwañ

	sei();															// W³¹czam obs³ugê przerwañ
}

ISR (INT1_vect) 				// Przerwanie INT1 
{
	cli();									// Upewniam siê ¿e nie dojdzie do wykonania przerwania podczas tego przerwania
	PORTC += 1;
	for(int i = 0; i < 4; i++) 
	{
		PORTD = (~_BV(i+4) & 0xF0) | (PORTD & 0x0F);				// Ustawiam 0 na danym bicie i resztê na 1 (pomijam m³odsze bity)
		_delay_us(10);
		if(!(PIND & 0x08))
		{
			PORTA = (PORTA & 0x0F) | (((i + 5) << 4) & 0xF0);		// Sprawdzam czy dany klawisz jest naciœniêty
		}
	}

	PORTD &= 0x0F;

	GIFR |= 0b10000000;				// upewniam siê ¿e nie dojdzie do paso¿ytniczych przerwañ

	sei();
}

int main(void)
{
	DDRA = 0xFF;					// Ustawiam PORT A,B i C jako wejœcie
	DDRB = 0xFF;					
	DDRC = 0xFF;

	DDRD = 0xF0;					// Ustawiam 4 starsze bity portu D jako wejœcie

	PORTD |= 0x0C;					// Podci¹gam pod zasilanie 2 i 3 PIND

	MCUCR |= 0x0A;					// Ustawienie aktywacji obu przerwañ w tryb falling-edge;
	

	GICR |= 0xC0;					// W³¹czenie przerwañ INT0 i INT1

	sei();							// W³¹czam globaln¹ obs³ugê przerwañ


    while (1) 
    {	

		PORTA ^=0x0F;				// Wykonujê animacjê
		_delay_ms(50);				// opóŸnienie 50ms
    }
}
