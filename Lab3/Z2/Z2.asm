

.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g��wny
	LDI R16, low(RAMEND)		; inicjalizacja SP
	OUT SPL,R16
	LDI R16, high(RAMEND)
	OUT SPH,R16

	LDI R16, 0xFF    			; inicjalizacja linii A jako wyj�cie
	OUT DDRA, R16

restart:
	LDI R16, 3			;	restart animacji
loop:			; pocz�tek p�tli g��wnej
	OUT PORTA, R16		; ustawienie odpowiedniego leda jako w��czonego

	call delay		;wywo�anie funkcji op�niaj�cej

	LSL R16			; przesuni�cie w lewo do kolejnego leda
	
	BREQ restart	; je�eli sko�czy�y nam si� ledy to wracamy po kolejnego

	rjmp loop 	; w przeciwnym przypadku wykonujemy kolejny krok p�tli

delay:			; pr�tla op�niaj�ca
    ldi  r18, 104
    ldi  r19, 229
L1: dec  r19
    brne L1
    dec  r18
    brne L1

	ret
