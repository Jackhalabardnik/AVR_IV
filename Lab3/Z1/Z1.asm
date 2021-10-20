
.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g��wny
	IN R16, DDRA
	ORI R16, 0x0F ; ustawiam pierwsze 4 bity portu A na wyj�cie
	OUT DDRA, R16

	SBI PORTB, 0 ; podci�gam przycisk A pod lini� zasilania
	SBI PORTB, 1 ; podciagam przycisk B pod lini� zasilania
loop:			; pocz�tek p�tli g��wnej

	IN R16, PINB ; pobieram informacje od szyny PIN B

	ANDI R16, 0x03 ; upewniam si�, �e pracuj� na bitach 0 i 1 

	IN R17, PORTA   ; zapisuj� stan port�w
	MOV R18, R17 

	ANDI R18, 0xF0  ; zapami�tuj� tylko starsze bity PORTA

	CPI  R16, 0x03 ; sprawdzam czy wci�ni�te s� obydwa przyciski

	BREQ opcja ; je�eli oba nie sa wci�ni�te to ide do wariantu 2
					; warinat 1
	ORI R17, 0x0C   ;	ustawiam mask� aby �wieci�y si� dwa ostatnie ledy
	ANDI R17, 0x0C	; ustawiam mask� aby �wieci�y si� tylko dwa ostatnie ledy
	OR R17, R18	; przywracam stan starszych bit�w PORTA

	rjmp koniec	; skok do insturkcji ko�cz�cej p�tl�

opcja:				;wariant 2
	ORI R17, 0x03	; ustawiam mask� aby �wieci�y si� dwa pierwsze ledy
	ANDI R17, 0x03	; ustawiam mask� aby �wieci�y si� tylko dwa piwersze ledy
	OR R17, R18	; przywracam stan starszych bit�w PORTA

koniec:

	OUT PORTA, R17 ; ustawiam stan led w PORTA

	rjmp loop	; wr�� na pocz�tek p�tli g��wnej

