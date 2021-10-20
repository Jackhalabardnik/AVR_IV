

#define F_CPU 4000000

#include <avr/io.h>
#include <util/delay.h>

void sendByte(char data)
{
	PORTB |= 0x02;								// Wysy�am flag� ENABLE
    PORTA = data;								// Wysy�am bajt
    PORTB &= 0xFD;								// Usuwam flag� ENABLE
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

int main(void)
{
	_delay_ms(15); 								// Czekam a� wy�wietlacz LCD zostanie zainicjalizowany

	DDRA = 0xFF;								// Ustawiam ca�� lini� A i cz�� linii B jako wyj�cie
	DDRB |= 0x03;
	
	sendCommand(0x30);							// Inicjalizacja standardowymi bajtami
	_delay_ms(5);								// Czekam zgodnie z dokumentacj�
	sendCommand(0x30);							
	_delay_us(101);
	sendCommand(0x30);
	sendCommand(0x38);							// Ustawiam tryb 2 linii i znak�w 5x8
	sendCommand(0x08);							// Wy��czam wy�wietlacz zgodnie z dokumentacj�
	sendCommand(0x01);							// Czyszcz� wy�wietlacz
	sendCommand(0x07);							// Ustawiam kierunek wyprowadzania tekstu i spos�b wyprowadzania na wy�wietlacz
	sendCommand(0x0F);							// W��czam wy�wietlacz i ustawiam znak na pozycji kursora na miganie
	sendCommand(0x8F);							// Ustawiam kursor na odpowiedniej pozycji
	PORTB |= 0x01;								// Prze��czam LCD w tryb wyprowadzania danych;

	
	char *nazwisko = "Wojcik";
	while(*nazwisko)
	{
		sendChar(*nazwisko++);	
	}
}
