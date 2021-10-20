.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x002					; adres wektora INT0
	jmp set_mode_1
	.org 0x004					; adres wektora INT1
	jmp change_mode
main: 							; program g³ówny

	cli							; blokujê wykonywanie przerwañ na czas inicjalizacji
						
	ldi R16, low(RAMEND)		; inicjalizacja SP
	out SPL,R16
	ldi R16, high(RAMEND)
	out SPH,R16

	ldi R16, 0xC0				; w³¹czam obs³ugê przerwania INT1 i INT0
	out GICR, R16

	sbi PORTD, 3				; p¹dci¹gam przyciski pod zasilanie
	sbi PORTD, 2

    ldi R16, 0x0A				; ustawiam ¿eby przerwanie INT1 i INT0 w³¹czy³o siê tylko zaraz po naciœniêciu przycisku (falling edge)
	out MCUCR, R16 

	ldi R16, 0xFF				; ustawiam odpowiednie bity na liniach A i C jako wyjœcie
	out DDRC, R16
	out DDRB, R16

	sei							; w³¹czam obs³ugê przerwañ w SREG po skoñczonej inicjalizacji

loop:							; pocz¹tek pêtli g³ównej

	ldi R16, 0xFF				; krok 1 animacji
	out PORTC, R16

	brtc mode_0					; je¿eli flaga T jest ustawiona to zmieniam animacjê
	ldi R16, 0x3C
mode_0:
					
	out PORTB, R16

	call delay 					; 1 opóŸnienie

	ldi R16, 0x00				; krok 2 animacji
	out PORTC, R16				
	out PORTB, R16

	call delay 					; 2 opóŸnienie
	call delay
			
	rjmp loop 					; wróæ na pocz¹tek pêtli g³ównej

delay:							; pêtla opóŸniaj¹ca
    ldi  r18, 52
    ldi  r19, 242
L1: dec  r19
    brne L1
    dec  r18
    brne L1
	ret

set_mode_1:
	
	push R16 					; zapamiêtanie wartoœci
	in R16, SREG
	push R16

	in R16, PORTA				; pobieram aktualny stan PORTA			
	andi R16, 0x3C				; wy³¹czam LED 0,1,6,7
	out PORTA, R16				; ustawiam stan PORTA

	pop R16						; przypomnienie wartoœci
	ori R16, 0x40				; ustawiam flagê T w SREG
	out SREG, R16
	pop R16

	reti						; wracam z przerwania

change_mode:
	push R17
	push R16 					; zapamiêtanie wartoœci
	in R16, SREG	
	push R16
		
	in R16, PORTB 				; pobieram aktualny stan portów	

	brts set_mode				; je¿eli tryb 1 by³ ustawiony to go wy³¹czam
	andi R16, 0x3C				; je¿eli nie to w³¹czam tryb jeden
	
	rjmp end					; omijam wy³¹czanie trybu 1

set_mode:
	call synchronise				; synchronizujê bity na koñcach z bitami w œrodku
	
end:

	out PORTB, R16				; ustawiam stan portu odpowiedno do zmienionego trybu

	pop R16						; przypomnienie wartoœci

	LDI R17, 0x40				; ustawiam maskê dla EOR

	EOR R16, R17				; zmianiam stan bitu T w SREG wybiórcz¹ negacj¹

	out SREG, R16
	pop R16
	pop R17

	reti						; koniec przerwania

synchronise:
	sbrc R16, 3					; je¿eli œrodkowe bity s¹ ustawione to ustawiam wszystkie bity
	ldi R16, 0xFF

	sbrs R16, 3					; je¿eli œrodkowe bity s¹ wyczyszczone to czyszczê wszystkie
	ldi R16, 0x00

	ret							; powrót
