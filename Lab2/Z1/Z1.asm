.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g³ówny
			; tutaj ci¹g instrukcji inicjalizacyjnych
	SBI DDRA, 0		; ustawienie pierwszego bitu DDRA jako 1 w celu umo¿liwienia wyjœcia dla LED
	SBI PORTA, 0	; ustawienie pierwszego bitu PORTA na stan wysoki (w celu "zaœwiecenia siê" diody LED)
	SBI PORTA, 1		; ustawienie drugiego bitu PINA na stan wysoki w celu podci¹gniêcia przycisku po liniê zasilania

loop:			; pocz¹tek pêtli g³ównej
	SBIS PINA, 1	; je¿eli przycisk jest wciœniêty to wy³¹cz diodê LED 
	CBI PORTA, 0

	SBIC PINA, 1	; je¿eli przycisk nie jest wciœniêty to zasil diodê LED
	SBI PORTA, 0

	rjmp loop 	; wróæ na pocz¹tek pêtli g³ównej

