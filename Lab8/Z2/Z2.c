

#define F_CPU 4000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

volatile int counter = 0;						// Licznik

const char imie[] PROGMEM = "Jacek";			// Umieszczam imiê w pamiêci programu

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

ISR (INT0_vect) 								// Przerwanie INT0 
{
	char byte = pgm_read_byte_near(imie + counter); // Pobieram dane z pamiêci programu
	
	if(byte)							// Je¿eli nie napotka³em koñca imienia to wypisujê kolejn¹ literê
	{
		sendChar(byte);
		counter++;
	}
}

ISR (INT1_vect) 								// Przerwanie INT1
{
	PORTA &= 0xFE;								// Prze³¹czam LCD w tryb wprowadzania komend
	_delay_us(2);								// OpóŸnienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x01);							// Czyszczê wyœwietlacz
	sendCommand(0x90);							// Ustawiam kursor na odpowiedniej pozycji
	counter = 0;								// Resetujê licznik
	PORTA |= 0x01;								// Prze³¹czam LCD w tryb wprowadzania danych
}

int main(void)
{
	_delay_ms(15); 								// Czekam a¿ wyœwietlacz LCD zostanie zainicjalizowany

	DDRA |= 0xF3;								// Ustawiam ca³¹ liniê C i czêœæ linii A jako wyjœcie
	DDRC |= 0xFF;

	PORTD |= 0x0C;								// podci¹gam 2 i 3 PIND pod zasilanie

	MCUCR |= 0x0A;								// Ustawienie aktywacji obu przerwañ w tryb falling-edge;

	GICR |= 0xC0;								// W³¹czenie przerwañ INT0 i INT1

	
	sendHalfByte(0x30);							// Inicjalizacja standardowymi bajtami
	_delay_ms(5);								// Czekam zgodnie z dokumentacj¹
	sendHalfByte(0x30);							
	_delay_us(101);
	sendCommand(0x32);
	sendCommand(0x28);							// Ustawiam tryb 2 linii i znaków 5x8
	sendCommand(0x08);							// Wy³¹czam wyœwietlacz zgodnie z dokumentacj¹
	sendCommand(0x01);							// Czyszczê wyœwietlacz
	sendCommand(0x07);							// Ustawiam kierunek wyprowadzania tekstu i sposób wyprowadzania na wyœwietlacz
	sendCommand(0x0D);							// W³¹czam wyœwietlacz i ustawiam znak na pozycji kursora na miganie
	sendCommand(0x90);							// Ustawiam kursor na odpowiedniej pozycji
	PORTA |= 0x01;								// Prze³¹czam LCD w tryb wprowadzania danych

	sei();										// W³¹czam obs³uge przerwañ

	while(1)
	{
		PORTC ^= 0xFF;
		_delay_ms(50);
	}
}
