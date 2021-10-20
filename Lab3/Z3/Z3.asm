

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

	
	SBI PORTB, 0				; podci�gam przyciski pod zasilanie
	SBI PORTD, 0

restart:
	LDI R16, 1			;	restart animacji
loop:			; pocz�tek p�tli g��wnej
	MOV R17, R16  		; zapisuj� bie��cy stan animacji
	
	SBIS PINB, 0			; je�eli przycisk A jest wci�ni�ty to wy��czam LED 0 i 7 u�ywaj�c AND
	ANDI R17, 0b01111110		

	SBIS PIND, 0
	CALL negate
	
	OUT PORTA, R17		; ustawienie odpowiedniego leda jako w��czonego

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


negate:
	LDI R18, 0b00011000 ; �aduj� mask�
	EOR R17, R18	;wybi�rczo neguj� dwa �rodkowe bity
	ret	
