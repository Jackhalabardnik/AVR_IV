.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g³ówny
	SBI DDRA, 0	; inicjalizacja portów dla diod
	SBI DDRB, 0
	SBI DDRC, 0
	SBI DDRD, 0
loop:			; pocz¹tek pêtli g³ównej
	
	SBI PORTA, 0	;pierwszy krok animacji
	SBI PORTB, 0
	CBI PORTC, 0


    ldi  r18, 3	;pierwsza pêtla opóŸniaj¹ca
    ldi  r19, 8
    ldi  r20, 120
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1


	CBI PORTA, 0	; drugi krok animacji
	CBI PORTB, 0
	SBI PORTC, 0
	SBI PORTD, 0	


    ldi  r18, 9		; druga pêtla opóŸniaj¹ca
    ldi  r19, 30
    ldi  r20, 229
L2: dec  r20
    brne L2
    dec  r19
    brne L2
    dec  r18
    brne L2
    nop

	SBI PORTB, 0	; trzeci krok animacji
	CBI PORTD, 0


	ldi  r18, 3	; trzecia pêtla opóŸniaj¹ca
    ldi  r19, 8
    ldi  r20, 120
L3: dec  r20
    brne L3
    dec  r19
    brne L3
    dec  r18
    brne L3

	rjmp loop 	; wróæ na pocz¹tek pêtli g³ównej
