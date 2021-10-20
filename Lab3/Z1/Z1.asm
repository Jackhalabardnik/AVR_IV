
.include "m32def.inc"
	
	.org 0x00
	jmp main

	.org 0x100
main: 			; program g³ówny
	IN R16, DDRA
	ORI R16, 0x0F ; ustawiam pierwsze 4 bity portu A na wyjœcie
	OUT DDRA, R16

	SBI PORTB, 0 ; podci¹gam przycisk A pod liniê zasilania
	SBI PORTB, 1 ; podciagam przycisk B pod liniê zasilania
loop:			; pocz¹tek pêtli g³ównej

	IN R16, PINB ; pobieram informacje od szyny PIN B

	ANDI R16, 0x03 ; upewniam siê, ¿e pracujê na bitach 0 i 1 

	IN R17, PORTA   ; zapisujê stan portów
	MOV R18, R17 

	ANDI R18, 0xF0  ; zapamiêtujê tylko starsze bity PORTA

	CPI  R16, 0x03 ; sprawdzam czy wciœniête s¹ obydwa przyciski

	BREQ opcja ; je¿eli oba nie sa wciœniête to ide do wariantu 2
					; warinat 1
	ORI R17, 0x0C   ;	ustawiam maskê aby œwieci³y siê dwa ostatnie ledy
	ANDI R17, 0x0C	; ustawiam maskê aby œwieci³y siê tylko dwa ostatnie ledy
	OR R17, R18	; przywracam stan starszych bitów PORTA

	rjmp koniec	; skok do insturkcji koñcz¹cej pêtlê

opcja:				;wariant 2
	ORI R17, 0x03	; ustawiam maskê aby œwieci³y siê dwa pierwsze ledy
	ANDI R17, 0x03	; ustawiam maskê aby œwieci³y siê tylko dwa piwersze ledy
	OR R17, R18	; przywracam stan starszych bitów PORTA

koniec:

	OUT PORTA, R17 ; ustawiam stan led w PORTA

	rjmp loop	; wróæ na pocz¹tek pêtli g³ównej

