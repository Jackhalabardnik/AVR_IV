

.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g³ówny
	LDI R16, low(RAMEND)		; inicjalizacja SP
	OUT SPL,R16
	LDI R16, high(RAMEND)
	OUT SPH,R16

	LDI R16, 0xFF    			; inicjalizacja linii A jako wyjœcie
	OUT DDRA, R16

restart:
	LDI R16, 3			;	restart animacji
loop:			; pocz¹tek pêtli g³ównej
	OUT PORTA, R16		; ustawienie odpowiedniego leda jako w³¹czonego

	call delay		;wywo³anie funkcji opóŸniaj¹cej

	LSL R16			; przesuniêcie w lewo do kolejnego leda
	
	BREQ restart	; je¿eli skoñczy³y nam siê ledy to wracamy po kolejnego

	rjmp loop 	; w przeciwnym przypadku wykonujemy kolejny krok pêtli

delay:			; prêtla opóŸniaj¹ca
    ldi  r18, 104
    ldi  r19, 229
L1: dec  r19
    brne L1
    dec  r18
    brne L1

	ret
