.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x002					; adres wektora INT0
	jmp set_mode_1
	.org 0x004					; adres wektora INT1
	jmp change_mode
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
	out DDRB, R16

	sei							; w��czam obs�ug� przerwa� w SREG po sko�czonej inicjalizacji

loop:							; pocz�tek p�tli g��wnej

	ldi R16, 0xFF				; krok 1 animacji
	out PORTC, R16

	brtc mode_0					; je�eli flaga T jest ustawiona to zmieniam animacj�
	ldi R16, 0x3C
mode_0:
					
	out PORTB, R16

	call delay 					; 1 op�nienie

	ldi R16, 0x00				; krok 2 animacji
	out PORTC, R16				
	out PORTB, R16

	call delay 					; 2 op�nienie
	call delay
			
	rjmp loop 					; wr�� na pocz�tek p�tli g��wnej

delay:							; p�tla op�niaj�ca
    ldi  r18, 52
    ldi  r19, 242
L1: dec  r19
    brne L1
    dec  r18
    brne L1
	ret

set_mode_1:
	
	push R16 					; zapami�tanie warto�ci
	in R16, SREG
	push R16

	in R16, PORTA				; pobieram aktualny stan PORTA			
	andi R16, 0x3C				; wy��czam LED 0,1,6,7
	out PORTA, R16				; ustawiam stan PORTA

	pop R16						; przypomnienie warto�ci
	ori R16, 0x40				; ustawiam flag� T w SREG
	out SREG, R16
	pop R16

	reti						; wracam z przerwania

change_mode:
	push R17
	push R16 					; zapami�tanie warto�ci
	in R16, SREG	
	push R16
		
	in R16, PORTB 				; pobieram aktualny stan port�w	

	brts set_mode				; je�eli tryb 1 by� ustawiony to go wy��czam
	andi R16, 0x3C				; je�eli nie to w��czam tryb jeden
	
	rjmp end					; omijam wy��czanie trybu 1

set_mode:
	call synchronise				; synchronizuj� bity na ko�cach z bitami w �rodku
	
end:

	out PORTB, R16				; ustawiam stan portu odpowiedno do zmienionego trybu

	pop R16						; przypomnienie warto�ci

	LDI R17, 0x40				; ustawiam mask� dla EOR

	EOR R16, R17				; zmianiam stan bitu T w SREG wybi�rcz� negacj�

	out SREG, R16
	pop R16
	pop R17

	reti						; koniec przerwania

synchronise:
	sbrc R16, 3					; je�eli �rodkowe bity s� ustawione to ustawiam wszystkie bity
	ldi R16, 0xFF

	sbrs R16, 3					; je�eli �rodkowe bity s� wyczyszczone to czyszcz� wszystkie
	ldi R16, 0x00

	ret							; powr�t
