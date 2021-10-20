

#define F_CPU 4000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

volatile int counter = 0;

const char data[] = { 0x02, 0xF1, 0x38, 0xBA, 0x97 };

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

ISR (INT0_vect) 								// Przerwanie INT0 
{
	if(counter < 5)								// Je�eli nie napotka�em ko�ca tablicy to wypisuj� kolejn� liter�
	{
		if(counter > 0)
		{
			sendChar(' ');						// Je�eli trzeba wypisuj� spacj�
		}								
																						// Pobieram dane z pami�ci programu
		sendChar(pgm_read_byte_near(transcode + (data[counter] >> 4)));					// Wypisuj� g�rn� po�ow� 
		sendChar(pgm_read_byte_near(transcode + (data[counter] & 0x0F)));				// Wypisuj� doln� po�ow� 
		counter++;
	}
}

ISR (INT1_vect) 								// Przerwanie INT1
{
	PORTA &= 0xFE;								// Prze��czam LCD w tryb wprowadzania komend
	_delay_us(2);								// Op�nienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x01);							// Czyszcz� wy�wietlacz
	sendCommand(0x90);							// Ustawiam kursor na odpowiedniej pozycji
	counter = 0;								// Resetuj� licznik
	PORTA |= 0x01;								// Prze��czam LCD w tryb wprowadzania danych
}

int main(void)
{
	_delay_ms(15); 								// Czekam a� wy�wietlacz LCD zostanie zainicjalizowany

	DDRA |= 0xF3;								// Ustawiam ca�� lini� C i cz�� linii A jako wyj�cie
	DDRC |= 0xFF;

	PORTD |= 0x0C;								// podci�gam 2 i 3 PIND pod zasilanie

	MCUCR |= 0x0A;								// Ustawienie aktywacji obu przerwa� w tryb falling-edge;

	GICR |= 0xC0;								// W��czenie przerwa� INT0 i INT1

	
	sendHalfByte(0x30);							// Inicjalizacja standardowymi bajtami
	_delay_ms(5);								// Czekam zgodnie z dokumentacj�
	sendHalfByte(0x30);							
	_delay_us(101);
	sendCommand(0x32);
	sendCommand(0x28);							// Ustawiam tryb 2 linii i znak�w 5x8
	sendCommand(0x08);							// Wy��czam wy�wietlacz zgodnie z dokumentacj�
	sendCommand(0x01);							// Czyszcz� wy�wietlacz
	sendCommand(0x07);							// Ustawiam kierunek wyprowadzania tekstu i spos�b wyprowadzania na wy�wietlacz
	sendCommand(0x0D);							// W��czam wy�wietlacz i ustawiam znak na pozycji kursora na miganie
	sendCommand(0x90);							// Ustawiam kursor na odpowiedniej pozycji
	PORTA |= 0x01;								// Prze��czam LCD w tryb wprowadzania danych

	sei();										// W��czam obs�uge przerwa�

	while(1)
	{
		PORTC ^= 0xFF;
		_delay_ms(50);
	}
}
