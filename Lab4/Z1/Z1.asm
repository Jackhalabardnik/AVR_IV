.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x004					; adres wektora INT1
	jmp negate_port_B
main: 							; program g³ówny

	cli							; blokujê wykonywanie przerwañ na czas inicjalizacji
						
	ldi R16, low(RAMEND)		; inicjalizacja SP
	out SPL,R16
	ldi R16, high(RAMEND)
	out SPH,R16

	ldi R16, 0x80				; w³¹czam obs³ugê przerwania INT1
	out GICR, R16

	sbi PORTD, 3				; p¹dci¹gam przycisk pod zasilanie

    ldi R16, 0x08				; ustawiam ¿eby przerwanie INT1 w³¹czy³o siê tylko zaraz po naciœniêciu przycisku (falling edge)
	out MCUCR, R16 

	ldi R16, 0xFF				; ustawiam liniê B i C jako wyjœcie
	out DDRB, R16
	out DDRC, R16

	out PORTB, R16				; ustalam stany pocz¹tkowe
	sbi PORTC, 7

	sei							; w³¹czam obs³ugê przerwañ w SREG po skoñczonej inicjalizacji

loop:							; pocz¹tek pêtli g³ównej

	in R16, PORTC				; pobieram aktualny stan animacji
	ror R16						; przewijam animacjê
	out PORTC, R16				; ustawiam stan animacji

	call delay 
			
	rjmp loop 					; wróæ na pocz¹tek pêtli g³ównej

delay:							; pêtla opóŸniaj¹ca
	ldi  r18, 104
    ldi  r19, 229
L1: dec  r19
    brne L1
    dec  r18
    brne L1
	ret

negate_port_B:

	push R16					; zapamiêtujê wartoœci na stosie
	in R16, SREG
	push R16

	in R16, PORTB				; pobieram aktualny stan portu i go negujê
	com R16
	out PORTB, R16

	pop R16						; przywracam wartoœci SREG i R16 z stosu
	out SREG, R16
	pop R16

	reti						; wracam z przerwania
