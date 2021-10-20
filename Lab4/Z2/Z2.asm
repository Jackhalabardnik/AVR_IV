.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x002					; adres wektora INT0
	jmp set_LED
	.org 0x004					; adres wektora INT1
	jmp change_LED
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
	SBI DDRA, 0

	sbi PORTC, 7				; ustalam stany pocz¹tkowe

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

set_LED:

	SBI PORTA, 0				; w³¹czam LED0, SBI nie narusza SREG a zatem nie muszê go zapamiêtywaæ
	
	reti						; wracam z przerwania

change_LED:						; negujê LED0
		
	SBIS PORTA, 0				; je¿eli LED0 jest wy³¹czony to skaczê do instrukcji w³¹czenia
	rjmp LED_on					; je¿eli bym nie skoczy³ to w nastêpnej instrukcji wy³¹czy³bym LED0, pomimo ¿e dopiero go w³¹czy³em

	SBIC PORTA, 0				; je¿eli LED0 jest w³¹czony to go wy³¹czam
	CBI PORTA, 0

	reti						; wracam z przerwania

LED_on:
	SBI PORTA, 0				; w³¹czam LED0
	reti						; wracam z przerwania
