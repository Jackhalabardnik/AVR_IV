.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g��wny
	SBI DDRA, 0	; inicjalizacja port�w dla diod
	SBI DDRB, 0
	SBI DDRC, 0
	SBI DDRD, 0

	SBI PORTA, 7	; ustawianie przycisk�w w stan wysoki
	SBI PORTD, 7
loop:			; pocz�tek p�tli g��wnej
	
					;pierwszy krok animacji
	
	SBI PORTA, 0	
	SBI PORTB, 0
	CBI PORTC, 0
	SBIC PIND, 7	; je�eli przycisk B jest wci�ni�ty to nie nale�y wy��cza� diody LED w porcie D
	CBI PORTD, 0
	SBIS PIND, 7	; w pierwszym kroku p�tli chcemy �eby LED D by� zapalony je�eli przycisk B jest wci�ni�ty zaraz na pocz�tku programu
	SBI PORTD, 0

    ldi  r18, 3	;pierwsza p�tla op�niaj�ca
    ldi  r19, 8
    ldi  r20, 120
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1


					; drugi krok animacji
	SBIC PINA, 7	; je�eli przycisk A jest wci�ni�ty to nie nale�y wy��cza� diody LED w porcie A
	CBI PORTA, 0	
	CBI PORTB, 0
	SBI PORTC, 0
	SBI PORTD, 0
	
		
    ldi  r18, 3	; druga p�tla op�niaj�ca
    ldi  r19, 8
    ldi  r20, 120
L2: dec  r20
    brne L2
    dec  r19
    brne L2
    dec  r18
    brne L2

	rjmp loop 	; wr�� na pocz�tek p�tli g��wnej
