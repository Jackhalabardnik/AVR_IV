.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g³ówny
	SBI DDRA, 0	; inicjalizacja portów dla diod
	SBI DDRB, 0
	SBI DDRC, 0
	SBI DDRD, 0

	SBI PORTA, 7	; ustawianie przycisków w stan wysoki
	SBI PORTD, 7
loop:			; pocz¹tek pêtli g³ównej
	
					;pierwszy krok animacji
	
	SBI PORTA, 0	
	SBI PORTB, 0
	CBI PORTC, 0
	SBIC PIND, 7	; je¿eli przycisk B jest wciœniêty to nie nale¿y wy³¹czaæ diody LED w porcie D
	CBI PORTD, 0
	SBIS PIND, 7	; w pierwszym kroku pêtli chcemy ¿eby LED D by³ zapalony je¿eli przycisk B jest wciœniêty zaraz na pocz¹tku programu
	SBI PORTD, 0

    ldi  r18, 3	;pierwsza pêtla opóŸniaj¹ca
    ldi  r19, 8
    ldi  r20, 120
L1: dec  r20
    brne L1
    dec  r19
    brne L1
    dec  r18
    brne L1


					; drugi krok animacji
	SBIC PINA, 7	; je¿eli przycisk A jest wciœniêty to nie nale¿y wy³¹czaæ diody LED w porcie A
	CBI PORTA, 0	
	CBI PORTB, 0
	SBI PORTC, 0
	SBI PORTD, 0
	
		
    ldi  r18, 3	; druga pêtla opóŸniaj¹ca
    ldi  r19, 8
    ldi  r20, 120
L2: dec  r20
    brne L2
    dec  r19
    brne L2
    dec  r18
    brne L2

	rjmp loop 	; wróæ na pocz¹tek pêtli g³ównej
