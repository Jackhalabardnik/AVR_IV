

#define F_CPU 4000000

#include <avr/io.h>
#include <util/delay.h>

void sendByte(char data)
{
	PORTB |= 0x02;								// Wysy³am flagê ENABLE
    PORTA = data;								// Wysy³am bajt
    PORTB &= 0xFD;								// Usuwam flagê ENABLE
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

int main(void)
{
	_delay_ms(15); 								// Czekam a¿ wyœwietlacz LCD zostanie zainicjalizowany

	DDRA = 0xFF;								// Ustawiam ca³¹ liniê A i czêœæ linii B jako wyjœcie
	DDRB |= 0x03;
	
	sendCommand(0x30);							// Inicjalizacja standardowymi bajtami
	_delay_ms(5);								// Czekam zgodnie z dokumentacj¹
	sendCommand(0x30);							
	_delay_us(101);
	sendCommand(0x30);
	sendCommand(0x38);							// Ustawiam tryb 2 linii i znaków 5x8
	sendCommand(0x08);							// Wy³¹czam wyœwietlacz zgodnie z dokumentacj¹
	sendCommand(0x01);							// Czyszczê wyœwietlacz
	sendCommand(0x07);							// Ustawiam kierunek wyprowadzania tekstu i sposób wyprowadzania na wyœwietlacz
	sendCommand(0x0F);							// W³¹czam wyœwietlacz i ustawiam znak na pozycji kursora na miganie
	sendCommand(0x8F);							// Ustawiam kursor na odpowiedniej pozycji
	PORTB |= 0x01;								// Prze³¹czam LCD w tryb wyprowadzania danych;

	
	char *nazwisko = "Wojcik";
	while(*nazwisko)
	{
		sendChar(*nazwisko++);	
	}
}
