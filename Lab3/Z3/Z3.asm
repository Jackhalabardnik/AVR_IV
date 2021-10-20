

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

	
	SBI PORTB, 0				; podci¹gam przyciski pod zasilanie
	SBI PORTD, 0

restart:
	LDI R16, 1			;	restart animacji
loop:			; pocz¹tek pêtli g³ównej
	MOV R17, R16  		; zapisujê bie¿¹cy stan animacji
	
	SBIS PINB, 0			; je¿eli przycisk A jest wciœniêty to wy³¹czam LED 0 i 7 u¿ywaj¹c AND
	ANDI R17, 0b01111110		

	SBIS PIND, 0
	CALL negate
	
	OUT PORTA, R17		; ustawienie odpowiedniego leda jako w³¹czonego

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


negate:
	LDI R18, 0b00011000 ; ³adujê maskê
	EOR R17, R18	;wybiórczo negujê dwa œrodkowe bity
	ret	
