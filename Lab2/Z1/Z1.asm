.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g��wny
			; tutaj ci�g instrukcji inicjalizacyjnych
	SBI DDRA, 0		; ustawienie pierwszego bitu DDRA jako 1 w celu umo�liwienia wyj�cia dla LED
	SBI PORTA, 0	; ustawienie pierwszego bitu PORTA na stan wysoki (w celu "za�wiecenia si�" diody LED)
	SBI PORTA, 1		; ustawienie drugiego bitu PINA na stan wysoki w celu podci�gni�cia przycisku po lini� zasilania

loop:			; pocz�tek p�tli g��wnej
	SBIS PINA, 1	; je�eli przycisk jest wci�ni�ty to wy��cz diod� LED 
	CBI PORTA, 0

	SBIC PINA, 1	; je�eli przycisk nie jest wci�ni�ty to zasil diod� LED
	SBI PORTA, 0

	rjmp loop 	; wr�� na pocz�tek p�tli g��wnej

