

#define F_CPU 4000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

volatile int multi_counter = 0;						// Licznik multipleksacji
volatile int write_counter = 0;						// Licznik wpisywania
volatile char last_character = -1;					// Flaga ostatniego znaku
volatile char was_char_pressed = 0;					// Flaga pomagaj¹ca stwierdziæ czy w poprzedniej iteracji zosta³ wciœniêty klawisz
volatile char no_entry = 1;							// Flaga pamiêtaj¹ca czy by³o jakiegokolwiek wejœcie

const char transcode[] PROGMEM  = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }; // Umieszczam dane w pamiêci programu


void sendHalfByte(char data)
{		
	PORTA |= 0x02; 								// Wysy³am flagê ENABLE
	PORTA = (PORTA & 0x0F) | (data & 0xF0);		// Wysy³am pó³ bajta
	PORTA &= 0xFD;								// Usuwam flagê ENABLE
}

void sendByte(char data)
{
	sendHalfByte(data);							// Wysy³am górn¹ po³owê bajtu
	_delay_us(2);								// OpóŸnienie w celu wykrycia stanu "0" na pinie ENABLE
	sendHalfByte(data << 4);					// Wysy³am doln¹ po³owê bajtu
}

void sendCommand(char data)
{
	sendByte(data);								// Wysy³am komendê
	_delay_us(50);								// Czekam na przetworzenie komendy
}

void sendChar(char data)
{
	sendByte(data);								// Wysy³am znak
	_delay_us(1500);							// Czekam na wypisanie znaku
}

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

ISR (INT0_vect) 								// Przerwanie INT0 
{
	PORTA &= 0xFE;								// Prze³¹czam LCD w tryb wprowadzania komend
	_delay_us(2);								// OpóŸnienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x01);							// Czyszczê wyœwietlacz
	write_counter = 0;							// Resetujê licznik wpisywania na ekran
	PORTA |= 0x01;								// Prze³¹czam LCD w tryb wprowadzania danych
}

ISR (TIMER0_COMP_vect) {        								// Przerwanie TIMER0
	PORTB = (~_BV(multi_counter+4) & 0xF0) | (PORTB & 0x0F);	// Ustawiam 0 na dany bit w PORTD a resztê starszych bitów na 1
	if((PINB & 0x0F) != 0x0F)									// Sprawdzam czy dany klawisz jest naciœniêty
	{
		char code = ((debinary(~PINB & 0x0F)-1) * 4) + multi_counter;	// Dekodujê znak z klawiatury
		if(write_counter < 16 && (code != last_character || no_entry))			// Sprawdzam czy mo¿na wpisaæ kolejny znak
		{
			sendChar(pgm_read_byte_near(transcode + code));		// wypisujê zdekodowany znak klawisza
			write_counter++;
		}
		last_character = code;									// Zapamiêtujê kod klawisza
		was_char_pressed = 1;									// Zauwa¿am ¿e wcisn¹³em jakiœ klawisz
	}
	multi_counter++;											// zwiêkszam licznik multipleksacji i w razie czego wracam do 0
	if(multi_counter >= 4) 
	{
		if(was_char_pressed)									// sprawdzam czy w poprzedniej iteracji zosta³ naciœniêty jakiœ klawisz
		{
			no_entry = 0;										// ustawiam flagê braku wpisywania na wartoœæ fa³sz
		}
		else
		{
			no_entry = 1;
		}
		was_char_pressed = 0;									// resetujê flagê sprawdzaj¹c¹ czy nacisn¹³em jakiœ klawisz
		multi_counter = 0;
	}
}

int main(void)
{
	_delay_ms(15); 								// Czekam a¿ wyœwietlacz LCD zostanie zainicjalizowany

	DDRA |= 0xF3;								// Ustawiam czêœæ linii A jako wyjœcie
	DDRB |= 0xF0;								// Ustawiam kolumny jako wejœcie

	PORTD |= 0x04;								// podci¹gam 2 PIND pod zasilanie
	PORTB |= 0x0F;								// Podci¹gam wiersze pod zasilanie

	MCUCR |= 0x0A;								// Ustawienie aktywacji przerwania w tryb falling-edge;

	GICR |= 0x40;								// W³¹czenie przerwañ INT0

	OCR0 = 156;                    				// ustawienie momentu przerwania na 156 (0,01s)

    TIMSK |= 0x02;                 				// w³¹czenie przerwania TIMER0

    TCCR0 |= 0b01000100;            			// w³¹czam tryb CTC i ustawiam prescaler na 1/256

	
	sendHalfByte(0x30);							// Inicjalizacja standardowymi bajtami
	_delay_ms(5);								// Czekam zgodnie z dokumentacj¹
	sendHalfByte(0x30);							
	_delay_us(101);
	sendCommand(0x32);
	sendCommand(0x28);							// Ustawiam tryb 2 linii i znaków 5x8
	sendCommand(0x08);							// Wy³¹czam wyœwietlacz zgodnie z dokumentacj¹
	sendCommand(0x01);							// Czyszczê wyœwietlacz
	sendCommand(0x06);							// Ustawiam kierunek wyprowadzania tekstu i sposób wyprowadzania na wyœwietlacz
	sendCommand(0x0F);							// W³¹czam wyœwietlacz i ustawiam znak na pozycji kursora na miganie
	PORTA |= 0x01;								// Prze³¹czam LCD w tryb wprowadzania danych

	sei();										// W³¹czam obs³uge przerwañ

	while(1) {}									// Pêtla g³ówna programu
}
