.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x002					; adres wektora INT0
	jmp set_LED
	.org 0x004					; adres wektora INT1
	jmp change_LED
main: 							; program g��wny

	cli							; blokuj� wykonywanie przerwa� na czas inicjalizacji
						
	ldi R16, low(RAMEND)		; inicjalizacja SP
	out SPL,R16
	ldi R16, high(RAMEND)
	out SPH,R16

	ldi R16, 0xC0				; w��czam obs�ug� przerwania INT1 i INT0
	out GICR, R16

	sbi PORTD, 3				; p�dci�gam przyciski pod zasilanie
	sbi PORTD, 2

    ldi R16, 0x0A				; ustawiam �eby przerwanie INT1 i INT0 w��czy�o si� tylko zaraz po naci�ni�ciu przycisku (falling edge)
	out MCUCR, R16 

	ldi R16, 0xFF				; ustawiam odpowiednie bity na liniach A i C jako wyj�cie
	out DDRC, R16
	SBI DDRA, 0

	sbi PORTC, 7				; ustalam stany pocz�tkowe

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

set_LED:

	SBI PORTA, 0				; w��czam LED0, SBI nie narusza SREG a zatem nie musz� go zapami�tywa�
	
	reti						; wracam z przerwania

change_LED:						; neguj� LED0
		
	SBIS PORTA, 0				; je�eli LED0 jest wy��czony to skacz� do instrukcji w��czenia
	rjmp LED_on					; je�eli bym nie skoczy� to w nast�pnej instrukcji wy��czy�bym LED0, pomimo �e dopiero go w��czy�em

	SBIC PORTA, 0				; je�eli LED0 jest w��czony to go wy��czam
	CBI PORTA, 0

	reti						; wracam z przerwania

LED_on:
	SBI PORTA, 0				; w��czam LED0
	reti						; wracam z przerwania
