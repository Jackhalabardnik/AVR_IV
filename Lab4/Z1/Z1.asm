.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x004					; adres wektora INT1
	jmp negate_port_B
main: 							; program g��wny

	cli							; blokuj� wykonywanie przerwa� na czas inicjalizacji
						
	ldi R16, low(RAMEND)		; inicjalizacja SP
	out SPL,R16
	ldi R16, high(RAMEND)
	out SPH,R16

	ldi R16, 0x80				; w��czam obs�ug� przerwania INT1
	out GICR, R16

	sbi PORTD, 3				; p�dci�gam przycisk pod zasilanie

    ldi R16, 0x08				; ustawiam �eby przerwanie INT1 w��czy�o si� tylko zaraz po naci�ni�ciu przycisku (falling edge)
	out MCUCR, R16 

	ldi R16, 0xFF				; ustawiam lini� B i C jako wyj�cie
	out DDRB, R16
	out DDRC, R16

	out PORTB, R16				; ustalam stany pocz�tkowe
	sbi PORTC, 7

	sei							; w��czam obs�ug� przerwa� w SREG po sko�czonej inicjalizacji

loop:							; pocz�tek p�tli g��wnej

	in R16, PORTC				; pobieram aktualny stan animacji
	ror R16						; przewijam animacj�
	out PORTC, R16				; ustawiam stan animacji

	call delay 
			
	rjmp loop 					; wr�� na pocz�tek p�tli g��wnej

delay:							; p�tla op�niaj�ca
	ldi  r18, 104
    ldi  r19, 229
L1: dec  r19
    brne L1
    dec  r18
    brne L1
	ret

negate_port_B:

	push R16					; zapami�tuj� warto�ci na stosie
	in R16, SREG
	push R16

	in R16, PORTB				; pobieram aktualny stan portu i go neguj�
	com R16
	out PORTB, R16

	pop R16						; przywracam warto�ci SREG i R16 z stosu
	out SREG, R16
	pop R16

	reti						; wracam z przerwania
