

#define F_CPU 4000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

volatile int multi_counter = 0;						// Licznik multipleksacji
volatile int write_counter = 0;						// Licznik wpisywania
volatile char last_character = -1;					// Flaga ostatniego znaku
volatile char was_char_pressed = 0;					// Flaga pomagaj�ca stwierdzi� czy w poprzedniej iteracji zosta� wci�ni�ty klawisz
volatile char no_entry = 1;							// Flaga pami�taj�ca czy by�o jakiegokolwiek wej�cie

const char transcode[] PROGMEM  = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }; // Umieszczam dane w pami�ci programu


void sendHalfByte(char data)
{		
	PORTA |= 0x02; 								// Wysy�am flag� ENABLE
	PORTA = (PORTA & 0x0F) | (data & 0xF0);		// Wysy�am p� bajta
	PORTA &= 0xFD;								// Usuwam flag� ENABLE
}

void sendByte(char data)
{
	sendHalfByte(data);							// Wysy�am g�rn� po�ow� bajtu
	_delay_us(2);								// Op�nienie w celu wykrycia stanu "0" na pinie ENABLE
	sendHalfByte(data << 4);					// Wysy�am doln� po�ow� bajtu
}

void sendCommand(char data)
{
	sendByte(data);								// Wysy�am komend�
	_delay_us(50);								// Czekam na przetworzenie komendy
}

void sendChar(char data)
{
	sendByte(data);								// Wysy�am znak
	_delay_us(1500);							// Czekam na wypisanie znaku
}

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

ISR (INT0_vect) 								// Przerwanie INT0 
{
	PORTA &= 0xFE;								// Prze��czam LCD w tryb wprowadzania komend
	_delay_us(2);								// Op�nienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x01);							// Czyszcz� wy�wietlacz
	write_counter = 0;							// Resetuj� licznik wpisywania na ekran
	PORTA |= 0x01;								// Prze��czam LCD w tryb wprowadzania danych
}

ISR (TIMER0_COMP_vect) {        								// Przerwanie TIMER0
	PORTB = (~_BV(multi_counter+4) & 0xF0) | (PORTB & 0x0F);	// Ustawiam 0 na dany bit w PORTD a reszt� starszych bit�w na 1
	if((PINB & 0x0F) != 0x0F)									// Sprawdzam czy dany klawisz jest naci�ni�ty
	{
		char code = ((debinary(~PINB & 0x0F)-1) * 4) + multi_counter;	// Dekoduj� znak z klawiatury
		if(write_counter < 16 && (code != last_character || no_entry))			// Sprawdzam czy mo�na wpisa� kolejny znak
		{
			sendChar(pgm_read_byte_near(transcode + code));		// wypisuj� zdekodowany znak klawisza
			write_counter++;
		}
		last_character = code;									// Zapami�tuj� kod klawisza
		was_char_pressed = 1;									// Zauwa�am �e wcisn��em jaki� klawisz
	}
	multi_counter++;											// zwi�kszam licznik multipleksacji i w razie czego wracam do 0
	if(multi_counter >= 4) 
	{
		if(was_char_pressed)									// sprawdzam czy w poprzedniej iteracji zosta� naci�ni�ty jaki� klawisz
		{
			no_entry = 0;										// ustawiam flag� braku wpisywania na warto�� fa�sz
		}
		else
		{
			no_entry = 1;
		}
		was_char_pressed = 0;									// resetuj� flag� sprawdzaj�c� czy nacisn��em jaki� klawisz
		multi_counter = 0;
	}
}

int main(void)
{
	_delay_ms(15); 								// Czekam a� wy�wietlacz LCD zostanie zainicjalizowany

	DDRA |= 0xF3;								// Ustawiam cz�� linii A jako wyj�cie
	DDRB |= 0xF0;								// Ustawiam kolumny jako wej�cie

	PORTD |= 0x04;								// podci�gam 2 PIND pod zasilanie
	PORTB |= 0x0F;								// Podci�gam wiersze pod zasilanie

	MCUCR |= 0x0A;								// Ustawienie aktywacji przerwania w tryb falling-edge;

	GICR |= 0x40;								// W��czenie przerwa� INT0

	OCR0 = 156;                    				// ustawienie momentu przerwania na 156 (0,01s)

    TIMSK |= 0x02;                 				// w��czenie przerwania TIMER0

    TCCR0 |= 0b01000100;            			// w��czam tryb CTC i ustawiam prescaler na 1/256

	
	sendHalfByte(0x30);							// Inicjalizacja standardowymi bajtami
	_delay_ms(5);								// Czekam zgodnie z dokumentacj�
	sendHalfByte(0x30);							
	_delay_us(101);
	sendCommand(0x32);
	sendCommand(0x28);							// Ustawiam tryb 2 linii i znak�w 5x8
	sendCommand(0x08);							// Wy��czam wy�wietlacz zgodnie z dokumentacj�
	sendCommand(0x01);							// Czyszcz� wy�wietlacz
	sendCommand(0x06);							// Ustawiam kierunek wyprowadzania tekstu i spos�b wyprowadzania na wy�wietlacz
	sendCommand(0x0F);							// W��czam wy�wietlacz i ustawiam znak na pozycji kursora na miganie
	PORTA |= 0x01;								// Prze��czam LCD w tryb wprowadzania danych

	sei();										// W��czam obs�uge przerwa�

	while(1) {}									// P�tla g��wna programu
}
