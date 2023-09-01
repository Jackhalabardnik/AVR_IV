<h1>Treści tych labów, które zapisałem</h1>
<h1>L2 </h1>
Poniższe zadania przeznaczone są do samodzielnego wykonania przez Studentów.
Wszystkie programy mają być napisane w języku asemblera dla procesora AVR,
uruchomione i przetestowane na AVR Studio 4.19 z użyciem symulatora HAPSIM.

Treści zadań:

We wszystkich poniższych zadaniach uwzględnia się, że w rzeczywistym układzie jeden z zacisków każdego z używanych przycisków dołączony jest do odpowiedniej linii portu,
a drugi do masy układu. W konsekwencji przyciśnięcie przycisku powoduje zwarcie linii portu do masy (wymuszenie 0 na linii wejściowej). 
W symulatorze HAPSIM ustawienie takiego sposobu działania przycisku wymaga wybrania opcji "active low" w konfiguracji przycisku.
Gdy przycisk pozostaje niewciśnięty linia wejściowa portu jest niespolaryzowana i rozpoznawany jej stan logiczny jest nieokreślony. W celu spowodowania, że w tym stanie przycisku stan linii wejściowej
jest 1 należy programowo taką linię wejściową "podciągnąć do zasilania". 

UWAGA!!!
Należy zapoznać się z rozwiązaniem problemu początkowego braku współpracy modeli przycisków i klawiatury HAPSIM z AVR Studio przedstawionym w pliku "Narzędzia.txt"
(Zakładka "Pliki", katalog "Materiały do zajęć/Informacje i polecenia"). 

UWAGA! Dla celów programowej realizacji opóźnienia założyć, że mikrokontroler taktowany jest zegarem systemowym o częstotliwości 4MHz

1) Opracować, uruchomić i przetestować program powodujący, że w trakcie, gdy przycisk (button) dołączony do linii PA.1 jest niewciśnięty, dioda LED dołączona do linii
 PA.0 świeci. Gdy gdy przycisk dołączony do linii PA.1 jest wciśnięty, dioda LED dołączona do linii PA.0 nie świeci. Użyć rozkazów operujących na pojedynczych bitach.


2) Opracować i uruchomić program, który powoduje cykliczną (pętla nieskończona) animację świecenia diod LED dołączonych do mikrokontrolera w nastepujący sposób:
LED0|LED1|LED2|LED3	-	PA0(PortA)|PB0(PortB)|PC0(PortC)|PD0(PortD).
Sekwencja w animacji jest następująca:
a) ON|ON|OFF|OFF - 100ms
b) OFF|OFF|ON|ON - 400ms
c) OFF|ON|ON|OFF - 100ms
Do realizacji opóźnienia użyć pętli opóźniających umieszczonych w odpowiednch miejscach w kodzie programu.
Przykładowy generator pętli opóźniającej dla AVR można znaleźć pod adresem: http://darcy.rsgc.on.ca/ACES/TEI4M/AVRdelay.html
Poza pętlami opóźnienia używać (w miarę możliwości) rozkazów operujących na pojedynczych bitach.

3) Diody podłączone do mikrokontrolera jak w zadaniu 2. Do linii 7  w Port A dołączony jest przycisk "A", natomiast do linii 7 w Port D dołączony jest przycisk "B".
Opracować program powodujący, że świecenie diod LED wykonuje następującą cykliczną animację w zależności od stanu przycisków:
a) przyciski nieprzyciśnięte:
	a) ON|ON|OFF|OFF - 100ms
	b) OFF|OFF|ON|ON - 100ms
b) przycisk A przyciśnięty (niezależnie od stanu przycisku B)
	animacja jak w pkt a) z tym, że dioda podłączona do PA0 pozostaje w stanie ON
b) przycisk B przyciśnięty (niezależnie od stanu przycisku A)
	animacja jak w pkt a) z tym, że dioda podłączona do PD0 pozostaje w stanie ON
Użyć rozkazów operujących na pojedynczych bitach. Użyć pętli opóźniających, identycznie jak wymaga tego zadanie 2.
Konstruując program o wariantowym sposobie działania nie używać oddzielnych bloków kodu na realizację poszczególnych wariantów, ponieważ skutkiem takiego sposobu
jest niedopuszczalna multiplikacja znaczącej częsci kodu takich bloków!
<h1>L3 </h1>
﻿Poniższe zadania przeznaczone są do samodzielnego wykonania przez Studentów.
Wszystkie programy mają być napisane w języku asemblera dla procesora AVR,
uruchomione i przetestowane na AVR Studio 4.19 z użyciem symulatora HAPSIM.

Treści zadań:

We wszystkich poniższych zadaniach uwzględnia się, że w rzeczywistym układzie jeden z zacisków każdego z używanych przycisków dołączony jest do odpowiedniej linii portu,
a drugi do masy układu. W konsekwencji przyciśnięcie przycisku powoduje zwarcie linii portu do masy (wymuszenie 0 na linii wejściowej). 
W symulatorze HAPSIM ustawienie takiego sposobu działania przycisku wymaga wybrania opcji "active low" w konfiguracji przycisku.
Gdy przycisk pozostaje niewciśnięty linia wejściowa portu jest niespolaryzowana i rozpoznawany jej stan logiczny jest nieokreślony. W celu spowodowania, że w tym stanie przycisku stan linii wejściowej
jest 1 należy programowo taką linię wejściową "podciągnąć do zasilania". 

UWAGA!!!
Należy zapoznać się z rozwiązaniem problemu początkowego braku współpracy modeli przycisków i klawiatury HAPSIM z AVR Studio przedstawionym w pliku "Narzędzia.txt"
(zakładka "Pliki", katalog "Materiały do zajęć/Laboratorium/Informacje i polecenia"). 

1) Do linii 0 i linii 1 Portu B mikrokontrolera dołączone są przyciski. Przyciski działają tak, że wciśnięcie zwiera linię do 0, a w stanie niewciśniętym
pozostawia linię portu rozwartą. Do linii PA0-3 Portu A dołączona jest linijka LED (4 diody).
Opracować program powodujący, że gdy niewciśnięte są obydwa przyciski stan świecenia diod LED jest następujący  ON|ON|OFF|OFF| (lewa skrajna pozycja w zapisie obok
odpowiada diodzie umieszczonej w najwyższej cześci panela LED w modelu HAPSIM, itd).  W każdym innym przypadku stan świecenia diod LED jest następujący 
OFF|OFF|ON|ON|. 
Użyć rozkazów operujących na bajtach typu MOV, AND, OR, EOR, COM, ew rozkazu porównania CP. Do stwierdzenia, że przyciśnięte są dwa przyciski użyć operacji maskowania, 
a do rozgałęzienia rozkazów typu BREQ/BRNE. Działania na rejestrach portów mają być zaprogramowane w taki sposób, żeby stan bitów odpowiadających niewykorzystanym liniiom
pozostał bez zmiany.


2) Do Portu A mikrokontrolera dołączona jest "linijka" czerwonych diod LED. Opracować, uruchomić i przetestować program powodujący animację świecenia diod LED. 
Animacja polega na tym, że w każdej chwili świeci pojedyncza dioda LED przy czym, pozycja świecącej się diody cyklicznie się zmienia począwszy od dołączonej do PA.0,  
do diody dołączonej do PA.7, po czym sekwencja powtarza się w pętli nieskończonej. Czas świecenia na każdej pozycji wynosi 20ms. 
Użyć procedury zawierającej programową pętlę opóźnienia czasowego do wytworzenia opóźnienia. Należy przyjąć, że częstotliwość taktowania AVR wynosi 4 MHz.
Przykładowy generator pętli opóźniającej dla AVR można znaleźć pod adresem: http://darcy.rsgc.on.ca/ACES/TEI4M/AVRdelay.html
Użyć rozkazów operujących na bajtach typu MOV, AND, OR, EOR, rozkazów rotacji/przesunięć a także ewentualnie rozkazów operujących na pojedynczych bitach tak, żeby 
zminimalizować rozmiar i czas wykonywania kodu.

UWAGA! Należy pamiętać, że - jeżeli w AVR używane są procedury (także procedury obsługi przerwań), względnie rozkazy operujące na stosie, należy w części
inicjalizacyjnej programu zainicjalizować wskaźnik stosu. Właściwa sekwencja kroków podana jest w "ATMEGA32 Datasheet.pdf" (patrz pliki/Materiały informacyjne).

3) Jak w zadaniu 2 z tym, że do linii 0 w porcie B dołączony jest przycisk "LED0/7 - OFF", a do linii 0 w porcie D przycisk "LED3/4 - NEG". 
Gdy przyciski są zwolnione, animacja trwa, jak w zadaniu 2.
Przyciśnięcie ktorego kolwiek przycisku nie ma wpływu na sekwencję animacji (np. nie skraca sekwencji), lecz w czasie, gdy przycisk "LED0/7 - OFF" jest wcisnięty 
na diodach LED0 i LED7 nie widać efektu animacji - pozostają WYŁĄCZONE.  Gdy przycisk "LED3/4 - NEG" jest wcisnięty na diodach LED3 i LED4 efekt animacji
jest ODWRÓCONY (dioda, która powinna świecić - nie świeci, i odwrotnie).
Użyć rozkazów operujących na bajtach typu MOV, AND, OR, EOR, itp. Efekt "wyłączenia LED z wizualizacji animacji" uzyskać metodą maskowania.
Konstruując program o wariantowym sposobie działania nie używać oddzielnych bloków kodu na realizację poszczególnych wariantów, ponieważ skutkiem takiego sposobu
jest niedopuszczalna multiplikacja znaczącej częsci kodu takich bloków!
<h1>L4 </h1>
Poniższe zadania przeznaczone są do samodzielnego wykonania przez Studentów.
Wszystkie programy powinny byc kodowane w języku asemblera dla AVR oraz uruchomione i przetestowane na AVR Studio 4.19 i symulatorze HAPSIM.

UWAGA!!!
Należy zapoznać się z rozwiązaniem problemu początkowego braku współpracy modeli przycisków i klawiatury HAPSIM z AVR Studio przedstawionym w pliku "Narzędzia.txt"
(zakładka "Pliki", katalog "Materiały do zajęć/Informacje i polecenia"). 

Informacje dodatkowe:
a) Adresy wektorów przerwań w ATMEGA32 patrz "Atmega32 Datasheet.pdf" (str 44).
b) Opis przerwań zewnętrznych patrz tamże (str 66).

WAŻNE!
W związku z użytą w AVR koncepcją wektorów przerwań struktura programu w asemblerze, w którym używa się przerwania(ń) jest następująca
(w przypadku wielu przerwań por. "Atmega32 Datasheet.pdf" (str 45)):

	.include "m32def.inc"
	.org 00
	JMP main

	.org <tutaj wpisać adres wektora przerwań używanego przerwania
	JMP proc_interrupt

main:			//początek programu głównego
	<inicjalizacje, konfiguracje>
	.........
work:		
	<kod programu głównego, zgodnie z wymaganiami, co ten program ma wykonywać>
	.........
	JMP work	/jeżeli działania programu głównego mają być realizowane w nieskończonej pętli
	
//STOP:	RJMP STOP	// w miejsce powyższej linii, jeżeli po wykonaniu w/w kodu działania programu głównego mają byc zakończone


proc_interrupt:
	<kod wymagany do prawidłowej obsługi przerwania (ew. także zamierzonej interakcji z programem głównym)>
	RETI		//powrót z procedury obsługi przerwania



Wymagania szczególne:
a) jak w poprzednich ćwiczeniach
b) procedury obsługi przerwań muszą być tak skonstruowane, żeby były jak najkrótsze i najszybciej się wykonywały
c) niedopuszczalna jest niezamierzona interakcja pomiędzy obsługą przerwań a programem głównym! jeżeli wykonanie kodu procedury obsługi przerwania modyfikuje wartości
 zmiennych/rejestrów, które w programie nie mają charakteru zmiennych globalnych (wspólnych dla obsługi przerwania i programu głównego), w szczególności modyfikuje 
bity warunkowe w rejestrze SREG - należy w prologu procedury obsługi zapisać je na stos a w epilogu przywrócić. 
UWAGA! AVR posiada pewną grupę rozkazów, których wykonanie nie modyfikuje SREG. Należy to wykorzystać do minimalizacji rozmiaru (czasu wykonania) kodu obsługi 
przerwania.

Treści zadań:


1)	Do portu B  dołączona jest "linijka" diod. Do portu C dołączona jest druga "linijka" diod. 
Po starcie programu stan świecenia diod dołączonych do Port B jest następujący ON|ON|ON|ON|ON|ON|ON|ON|. 
Po starcie programu stan świecenia diod dołączonych do Port C (od lewej dioda podłączona do linii 7 w Port C, itd.) jest następujący ON|OFF|OFF|OFF|OFF|OFF|OFF|OFF. 
Do linii 3 w porcie D (linia zgłaszania przerwania zewnętrznego INT1) dołączony jest przycisk (button). Wciśnięcie przycisku oznacza zwarcie linii do masy (logiczne 0).
Działanie programu: pętla główna programu  steruje portem C w ten sposób, że pozycja na której świeci się dioda zmienia się cyklicznie w kierunku od diody dołączonej 
do PC7 do PC0, co 20 ms. Port B sterowany jest w procedurze obsługi przerwania zewnętrznego INT1. Każdorazowo po przycisnięciu 
przycisku stan świecenia linijki diod LED podłączonej do PortB zmienia się na przeciwny (te, które świeciły, nie świecą i odwrotnie). Do realizacji opóźnienia 
wykorzystać procedurę zawierającą pętlę opóźnienia programowego. Przyjąć, że częstotliwość zegara systemowego wynosi 4MHz. Do realizacji przesuwania użyć
rozkazów przesunięć (ROR).


2)	Do Portu C podłączona jest linijka diod i sterowana jak w zadaniu 1. Do linii 0 Portu A podłączona jest pojedyncza dioda z linijki diod.
Do linii INT0 (PD2) i do linii INT1 (PD3) podłączone są przyciski o właściwościach, jak w Zadaniu 1.
Po starcie programu dioda podłączona do Portu A jest WYŁĄCZONA. Każdorazowo, gdy nastąpi przyciśnięcie przycisku podłączonego do PD2 
dioda dołączona do Port A zaświeca. Dioda zmienia stan (jeśli świeciła - gaśnie, gdy nie świeciła - zapala się) kiedy przycisnąć przycisk podłączony do PD3. 
Sterowanie linią PA.0 w obsłudze przerwań. Sterowanie linią PA.0 nie może modyfikować stanu pozostałych linii Port A.


3)	Linijki LED podłączone do mikrokontrolera jak w zadaniu 1. Podłączenia przycisków do mikrokontrolera jak w zadaniu 2.
Po starcie programu obydwie linijki pulsują w rytmie: ON|ON|ON|ON|ON|ON|ON|ON| przez 10ms i OFF|OFF|OFF|OFF|OFF|OFF|OFF|OFF| przez 20ms (tryb 0 animacji). 
Sterowanie portami do których podłączono diody - w pętli głównej programu. Opóźnienia czasowe zrealizować, jak w zadaniu 1.
Przyciśnięcie przycisku podłączonego do PD2 powoduje, że diody podłączone do PB.7-6 i PB.1-0 są trwale zgaszone (tryb 1 animacji), a świecenie pozostałych diod
poddane jest identycznej animacji jak w trybie 0.  Przyciśnięcie przycisku podłączonego do PD3 powoduje zmianę trybu 0->1 i 1->0. 
Przyciśnięcia przycisków nie mają wpływu na animację diod podłączonych do Port C.
W wyniku przyciśnięcia któregokolwiek z klawiszy wymagana zmiana wzoru świecenia LED na zestawie LED dołączonym do Portu B następuje bez zwłoki ("natychmiast" - 
bez oczekiwania na koniec okresu czasu przewidzianego dla bieżącego kroku animacji).
Użyć jednobitowego parametru, którego wartość zmieniana jest w procedurach obsługi przerwań zewnętrznych (INT0/INT1), a który używany jest w pętli głównej programu 
do modyfikacji animacji (zmiany trybu). 

<h1>L5</h1>

1)	Do PA.0 dołączona jest dioda LED. Do PD2 dołączony jest przycisk (button). Wciśnięcie powoduje zwarcie PD2 do masy (stan 0). 
Zwolnienie przycisku pozostawia linię niepodłączoną. Do Port C dołączona jest linijka diod.
Program działa tak, że:
a) Na linijce diod LED dołączonej do Port C w pętli nieskończonej trwa animacja: ON|ON|ON|ON|ON|ON|ON|ON| przez 50ms i OFF|OFF|OFF|OFF|OFF|OFF|OFF|OFF| przez 50ms.
Czas odmierzany za pomocą opóźnienia programowego (biblioteka delay).
b) wciśnięcie przycisku włącza LED i inicjuje odmierzanie czasu w timerze. LED gaśnie po upływie 0,5 sekundy (każde wciśnięcie w czasie odmierzania czasu
powoduje przedłużenie włączenia LED o w/w czas). Przed odmierzaniem czasu i po odmierzeniu czasu timer ma być zastopowany. 
Obsługa linii PA.0 w procedurach obsługi przerwań. Użyj trybu normal


2)	Opracować program, który po starcie na wyjściu linii OC1A generuje przebieg, w którym czas trwania 1 wynosi 19ms (faza 1 cyklu), czas trwania 0 wynosi 38ms
(faza 2 cyklu). Czas odmierza timer. Użyć trybu PWM. Do sterowania linią OC1A nie używać obsługi przerwań. Faza 1 rozpoczyna się z minimalnym opoźnieniem
w stosunku do startu programu, potrzebnym na wykonanie niebędnych konfiguracji.
UWAGA! Symulację działania należy przeprowadzić z użyciem symulatora "AVR Simulator 2", bez symulatora HAPSIM (nie współpracuje z AVR Simulator 2).
Jeżeli szkielet projektu do zadania 2 zawiera inne ustawienia, należy je odpowiednio zmienić.
Weryfikację działania programu należy wykonać w trybie "auto-step" obserwując stan rejestru PIN portu, w którym znajduje się linia OC1A.
Dla celów testowania zwiększyć 1024 krotnie częstotliwość zliczaną przez timer. W wersji finalnej programu przywrócić ustawienia wymagane przez zadanie.


3)	Podłączenia urządzeń zewnętrznych jak w Zadaniu 1. Dodatkowo do PA.7 dołączona skrajna dolna dioda z linijki, której górna skrajna dioda dołączona jest
do PA.0. Opracować program, który na PA.0 generuje powtarzalny przebieg, w którym czas trwania 1 wynosi 0,16s, czas trwania 0 początkowo wynosi 0,32s. 
Czas odmierza timer. Każdorazowe wciśnięcie przycisku dolączonego do PD2 powoduje skrócenie czasu trwania o 0,08s przy czym okres powtarzania przebiegu nie może 
być krótszy, niż 0,192s. Ponadto, wciśnięcie przycisku powoduje zaświecenie diody dołączonej do PA.7. Po wykonaniu operacji skrócenia czasu trwania 0 (bądź po stwierdzeniu,
że dalsze skracanie jest nidozwolone) dioda ta jest gaszona.
Użyć timera 1 i trybu CTC z wartością szczytową w OCR1A. Należy tak skonstruować zmianę w OCR1A (w odpowiedzi na przyciśnięcie klawisza), że wyeliminowana jest szkodliwa 
możliwość zmniejszenia wartości OCR1A w warunkach, gdy nowa wartość < TCNT1 (bieżącej wartości w liczniku timera). W przeciwnym razie po takiej zmianie
timer nie zarejestruje przekroczenia wartości zawartej w OCR1A i będzie zliczał aż do 2^16.
W procedurze main wykonywana jest identyczna animacja, jak w zadaniu 1, że czasy włączenia i wyłaczenia LED mają wynosić po 25ms.

<h1>L7 </h1>
Poniższe zadania przeznaczone są do samodzielnego wykonania przez Studentów.

UWAGA! W klawiaturze zorganizowanej matrycowo linie wierszy dołączone są do wejść portu obsługującego klawiaturę, a linie kolumn do wyjść tego portu.
Gdy klawisze w wierszu nie są przyciśnięte, linia wejściowa portu do, której dołączony jest ten wiersz, pozostaje rozwarta (brak polaryzacji - brak zdefiniowanego stanu logicznego).
Dlatego linie wejściowe portu do których dołączone są wiersze należy "podciągnąć do zasilania" powodując w ten sposób to, że gdy klawisze w wierszu nie są przyciśnięte
stan linii wejściowej odpowiada wartości logicznej 1. Żeby wciśnięcie klawisza zmieniło ten stan (rozpoznanie faktu wciśnięcia klawisza), na kolumnie, w której znajduje
 się ten klawisz, musi być stan logiczny 0. Stąd algorytm multipleksowego przeglądania klawiatury, jak poniżej

=>Algorytm multipleksowego przeglądania klawiatury martycowej o 1 wierszu i N kolumnach. Linia wiersza dołączona do wejścia portu. Linie kolumn do wyjść portu.
Krok#1) Kolumna#0=0, pozostałe 1; czytaj stan linii wiersza; jeżeli 0 -> nr klawisza=nr kolumny(ew. +1), BREAK, jeżeli 1 kontynuuj
Krok#2) Kolumna#1=0, pozostałe 1; czytaj stan linii wiersza; jeżeli 0 -> nr klawisza=nr kolumny(ew. +1), BREAK, jeżeli 1 kontynuuj
..
Krok#N) jak powyższe.

W przypadku klawiatury matrycowej o M wierszach i N kolumnach w każdym kroku należy czytać stan rejestru PIN portu, do którego dołączone są linie wierszy, a następnie
operacją maskowania wyodrębnić ze stanu PIN bit(y) odpowiadający(e) wierszowi(wierszom)m. Jeżeli nie jest prawdą, że wszyskie linie wierszy mają stan 1 -> 
któryś z klawiszy został przyciśnięty. W zależności od zastosowania (w ćwiczeniu warunki zadania) może być konieczne zdekodowanie numeru wiersza, w którym jest 0.
 W ćwiczeniu można założyć, że w danym momencie tylko 1 klawisz może być wciśnięty. Może być konieczne wyznaczenie kodu (numeru) klawisza (na podstawie numeru wiersza 
i numeru kolumny). Algorytm dekodowania, algorytm wyznaczenia numeru klawisza por. "Algorytmy Lab.pdf" w materiałach pomocniczych.

W przypadku, gdy multipleksowa obsługa klawiatury odbywa się "na żądanie" (przerwanie zewnętrzne), realizację należy wykonać w jednokrotnie wykonywanej pętli.
Należy uwzględnić konieczność pewnej zwłoki (rzędu mikrosekund!!!) po "aktywowaniu" kolumny a przed sprawdzaniem linii wejściowej, ze względu potrzebę przeczekania
stanów przejściowych
W przypadku, gdy obsługa multipleksowa klawiatury odbywa się poprzez cykliczne odpytywanie (Zadanie 3), realizacja każdego z kolejnych kroków ma być wykonana w odrębnym (kolejnym)
wywołaniu procedury obsługi przerwania kończącego odmierzenie czasu pomiędzy krokami.

=>Algorytm odczytu klawiatury z odwracaniem kierunków linii w porcie. Klawiatura M wierszy i N kolumn.
Początkowo linie portu, do którego dołączone są wiersze - na wejście, kolumny - na wyjście. Wszystkie linie kolumn aktywne (w ćwiczeniu wymagany stan 0).
Co ustalony okres czasu (timer, procedura obsługi przerwania od timera) czytany PIN portu obsługującego klawiaturę.
Operacją maskowania wyodrębniane ze stanu PIN bity odpowiadające wierszom. Jeżeli nie jest prawdą, że wszystkie linie wierszy mają stan 1 -> 
któryś z klawiszy został przyciśnięty (zapamiętaj stan bitów odpowiadających wierszom) -> zamiana kierunków linii portu (wejścia->wyjścia i odwrotnie), 
linie wejść podciągnięte -> podanie na wszystkie linie wierszy 0 -> czytany PIN portu obsługującego klawiaturę. Operacją maskowania wyodrębniane ze stanu PIN 
bity odpowiadające kolumnom. Powrót do stanu początkowego (kierunki linii, podciągnięcie linii wejściowych, aktywacja kolumn).

Dekodowanie numeru klawisza, jeżeli wymagane, na identycznej zasadzie, jak opisano wcześniej.




Treści zadań:

1)	Klawiatura składa się z 8-tu klawiszy zorganizowanych w 2 wiersze i 4 kolumny. Każdy z wierszy dołączony jest do pojedynczej wejściowej linii portu D 
będącej linią wejściową przerwania zewnętrznego: wiersz 0 do INT0, wiersz 1 do INT1. Kolumny klawiatury dołączone są do 4-ech wyjściowych linii portu D (PD7-4). 
Do portów A, B i C dołączone są linijki LED.
Opracować program, który rozpoznaje numer wciśniętego klawisza z pojedynego wiersza klawiatury.
Program w celu zidentyfkowania, który klawisz został wciśnięty, po rozpoznaniu zdarzenia wciśnięcia jednorazowo wykonuje algorytm multipleksowego (sekwencyjnego)
obsługiwania klawiatury.
Numer klawisza liczony od lewej od 1 ( liczba w zakresie od 1 do 8, zgodnie z opisem na modelu klawiatury w HAPSIM; należy załadowac plik konfiguracyjny) 
wyświetlany na 4 dolnych diodach linijki LED (LED1) za pośrednictwem 4-ech starszych bitów w PORTA. 
Ponadto, zliczane są wywołania każdej z procedur obsługujących zgłoszenie wcisnięcia klawisza. Numer wciśnięcia wyświetlany jest odpowiednio:
a) na linijce LED2 za pośrednictwem portu B - dla klawiszy w wierszu dołączonym do INT0,
b) na linijce LED3 za pośrednictwem portu C - dla klawiszy w wierszu dołączonym do INT1.
Dodatkowo, w procedurze main animacja wyświetlania na górnych diodach linijki LED1 za pośrednictwem 4-ech młodszych bitów Portu A.
Animacja polega na cyklicznym przełączaniu stanu świecenia co 50 ms pomiędzy stanem ON|ON|ON|ON| a stanem OFF|OFF|OFF|OFF|.
Obsługa klawiatury (WYŁĄCZNIE!) w procedurach obsługi przerwania zewnętrznego.

UWAGA! Należy uwzględnić, że w czasie obsługi klawiatury wykonywanej w w/w sposób może dochodzić do kolejnych (pasożytniczych) zgłoszeń zdarzeń przerwania zewnętrznego.
Należy zadbać, żeby te zgłoszenia nie skutkowały ponownym (niepotrzebnym) wywołaniem procedury obsługi przerwania


2)	Klawiatura składa się z 16 klawiszy umieszczonych na skrzyżowianiach 4 linii kolumn z 4-ema liniami wierszy. 
Kolumny klawiatury dołączone są do 4-ech linii portu D (PD7-4). Wiersze dołączone są do 4-ech linii portu D (PD3-0). 
Ponadto do portu A dołączona linijka LED.
Należy opracować program, który obsługuje klawiaturę zgodnie z algorytmem "z odwracaniem kierunków linii w porcie" oraz, jeżeli stwierdzone zostanie wciśnięcie klawisza,
za pośrednictwem portu A wyświetla na linijce LED kod o postaci: "kod aktywnej kolumny (kod 1z4, 4 starsze bity PortA)|kod aktywnego wiersza (kod 1z4, młodsze bity PortA)" 
Kod wyświetla się do czasu przyciśnięcia innego klawisza. Dodatkowo w procedurze main odbywa się animacja wyświetlania za pośrednictwem Portu C.
Animacja polega na cyklicznym przełączaniu stanu świecenia co 50 ms pomiędzy stanem ON|ON|ON|ON|ON|ON|ON|ON| a stanem OFF|OFF|OFF|OFF|OFF|OFF|OFF|OFF|.
Czas reakcji na przyciśnięcie klawisza na klawiaturze nie dłuższy niż 50 ms. 
Obsługa klawiatury w procedurze obsługi przerwania (WYŁĄCZNIE!) od timera. Użyć timera 0. 


3)	Klawiatura i zestawy diod LED podłączone są do mikrokontrolera jak w zadaniu 2. 
Należy opracować program, który obsługuje klawiaturę metodą multipleksacji z cyklicznym odpytywaniem klawiatury. Czas pomiędzy krokami wykonania algorytmu
odmierzany timerem.  Program, jeżeli stwierdzone zostanie wciśnięcie klawisza, za pośrednictwem portu A wyświetla na linijce LED numer wciśniętego klawisza, 
zgodny z opisem na modelu klawiatury HAPSIM (wczytać plik konfiguracyjny CW4Z3.xml). Kod wyświetla się do czasu przyciśnięcia innego klawisza. 
Dodatkowo w procedurze main odbywa się animacja wyświetlania za pośrednictwem Portu C, jak w zadaniu 1.
Czas reakcji na przyciśnięcie klawisza na klawiaturze nie dłuższy niż 50 ms. 
Obsługa klawiatury w procedurze obsługi przerwania (WYŁĄCZNIE!) od timera. Użyć timera 0. 


wektory przerwań:
https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html



<h1>L8 </h1>
Poniższe zadania przeznaczone są do samodzielnego wykonania przez Studentów.



Inicjalizacja LCD do pracy w trybie 4-bitowym:
inicjalizacja musi rozpocząć się od sekwencji komend 
		0x33
		0x32
(po restarcie LCD czyta w trybie 8 bitowym, 33 wysłane w dwóch krokach na 4 starsze bity oznacza wysłanie 2 razy
kodu 0x30; wysłanie w tym trybie 0x32 odczytywane jest przez LCD jako sekwencja 0x30 i 0x20; nie można wysłać 0x20 /przełącz w tyb 4 bitowy/, bo to zostanie odczytane
jako sekwencja 0x20 i 0x00, a ten drugi kod jest nieznaną komendą)


Kody sterujące wyświetlacza:

0x80 | 0b00(A6)(A5)(A4)(A3)(A2)(A1)(A0)		- set RAM addr (cursor position)

0x20 | 0b000(DL)NFXX				-	Function set
		DL=1 - 8 bits interface
		DL=0 - 4 bits interface
		N=1 - 2 lines
		N=0 - 1 line
		F=1 - 5x10 dots
		B=0 - 5x8 dots
		X  - don't care

0x10 | 0b0000(S/C)(R/L)XX
		S/C=1 - display shift
		S/C=0 - cursor shift
		R/L=1 - shift right
		R/L=0 - shift left


0x08 | 0b00000DCB				-	włacz/wyłącz wyświetlacz, wyświetlanie kursora
		D=1 - display is on
		D=0 - display is off
		C=1 - cursor displayed
		C=0 - cursor not displayed
		B=1 - blink at cursor position
		B=0 - don't blink at cursor position

0x04 | 0b000000(I/D)S				-	Entry mode tryb wprowadzania do RAM i wyprawadzania na wyświetlacz 
		I=1 - increment RAM addr (move cursor to right)
		I=0 - decrement RAM addr (move cursor to left)
		S=1 - char write<->display shift


Metoda zamiany naturalnego kodu binarnego (liczby) na inny kod z użyciem tablicy transkodowania:
W tablicy transkodowania indeks elementu odpowiada liczbie przeznaczonej do zakodowania (w nowym kodzie), a wartość pozycji o tym indeksie jest kodem tej liczby.
Zatem, pod pozycją 0 umieszcza się kod liczby 0, pod pozycją 1 - kod liczby 1, itd. Zamiana kodu odbywa się poprzez odczytanie z tablicy transkodowania 
wartości pozycji o indeksie, który jest liczbą wymagającą zakodowania
 

UWAGA! Należy pamiętać o sposobie rozwiązania problemu początkowego braku współpracy modeli przycisków i klawiatury HAPSIM z AVR Studio przedstawionym w pliku "Narzędzia.txt"
(Zakładka "Pliki", katalog "Materiały do zajęć/Informacje i polecenia"). 



Treści zadań:


1)	Wyświetlacz LCD programowany jest do pracy w trybie 8bitowym, tryb wyświetlania: 2 linie, format znaku 5x8 pikseli, 
	a następnie na wyświetlaczu wyświetla się nazwisko studenta. W celu wyświetlenia łańcucha tekstowego nazwiska należy w programie umieścić sekwencję
	wywołań funkcji przesyłającej pojedynczy znak do LCD tak, żeby każda kolejna litera pojedynczo wpisywana była do LCD zaczynając od pierwszej
	litery nazwiska, a kończąc na ostatniej. LCD obsługiwany przez PORTA - przesyłanie kodów, i 2 linie z portu B (EN-Enable bit PB1, RS-register select bit PB0). 
	W modelu wyświetlacza LCD w HAPSIM ustawić "Write Only Mode". 
	Opcja wykonania programu: znak wyświetla się z prawej strony wyświetlacza, widoczny kursor, znak na pozycji kursora pulsuje

2) 	Wyświetlacz LCD pracuje w trybie 4 bitowym. Obsługa LCD poprzez PortA: komunikacja - bity 4-7, EN(Enable) - bit 1, RS(register select) - bit 0.
W modelu wyświetlacza LCD w HAPSIM ustawić "Write Only Mode". Do PD.2 i PD.3 dołączone są przyciski (po przyciśnięciu zwarcie do masy - logiczne 0). 
Przycisk A do PD.2, przycisk B do PD.3.
Po starcie programu wyświelacz nic nie wyświetla. Każde wciśnięcie przycisku A wyświetla na LCD pojedynczy kolejny znak z imienia studenta. Tekst imienia
 zapisany w tablicy umieszczonej w pamięci programu. Sposób utworzenia tablicy z tekstem musi zapewniać, że końcowym elementem tablicy jest bajt=0x00.
Po osiągnięciu końca napisu, dalsze przyciśnięcia przycisku A nie powodują żadnego skutku. Do stwierdzenia osiągnięcia końca napisu należy wykorzystać
wiedzę o wartości ostatniego elementu tablicy. Każde wciśnięcie przycisku B czyści LCD. Obsługa przycisków w przerwaniach zewnętrznych. 
Ponadto, w procedurze main świecenie zestawu diod dołączonych do PortC poddawane jest animacji, w której co 50ms na przemian wszystkie diody zapalają się 
albo gasną.
	Opcja wykonania programu: napis pojawia się z prawej strony wyświetlacza


3)	Konfiguracja LCD jak powyżej. Do PD.2 i PD.3 dołączone są przyciski (po przyciśnięciu zwarcie do masy - logiczne 0). 
Przycisk A do PD.2, przycisk B do PD.3. W PAMIĘCI DANYCH umieszczono 5-bajtową tablicę zawierającą następującą sekwencję bajtów: 02 F1 38 BA 97.
Po starcie programu wyświelacz nic nie wyświetla. Każde wciśnięcie przycisku A wyświetla na LCD (po zamianie na odpowiadający kod ASCII) parę znaków
reprezentujących obydwa półbajty kolejnego bajtu z tablicy. Do zamiany należy użyć tablicy transkodującej z kodu szestnastkowego na  kod ASCII (cyfry 0-F, 
cyfry symbolizowane literami używają wielkich liter). Tablica transkodująca w PAMIĘCI PROGRAMU. Bajty tablicy mają być wyświetlone tak, 
żeby pomiędzy parami cyfr kolejnych bajtów występowały spacje, a układ napisu zgodny był z powyżej umieszczonym zapisem zawartości tablicy bajtów (od lewej do prawej).
Każde wciśnięcie przycisku B czyści LCD i przygotowuje do wyświetlenia zawartości tablicy od początku.Obsługa przycisków w przerwaniach zewnętrznych. P
onadto, w procedurze main świecenie zestawu diod dołączonych do PortC poddawane jest animacji, w której co 50ms na przemian wszystkie diody zapalają się albo gasną.
	Opcja wykonania programu: napis pojawia się z prawej strony wyświetlacza

	

Kody ASCII: http://www.asciitable.com/



<h1>L9 </h1>

Poniższe zadania przeznaczone są do samodzielnego wykonania przez Studentów.

W zadaniach uwzględnić, że gdy klawisz klawiatury pozostaje niewciśnięty, linia portu, do której jest dołączony, pozostaje w stanie nieokreślonym.
Należy zastosować właściwe rozwiązanie eliminujące ten problem.

Dla potrzeb symulacji działania systemu z użuciem symulatora HAPSIM zastosować podane wcześniej rozwiązanie problemu początkowej współpracy HAPSIM
z AVR Simulator występującym w przypadku użycia modelu przycisków lub/i klawiatury.

Treści zadań:

1)	Wyświetlacz LCD skonfigurowany jest do wyświetlania 2 linii, format znaku 5x8. Interfejs 4-bitowy. Program przyjmuje z klawiatury matrycowej liczbę składająca 
się z max 16 cyfr szestanstkowych (blokada pobierania, przy próbie wprowadzenia większej liczby cyfr). Wyświetla liczbę, w miarę wprowadzania kolejnych cyfr, 
na wyświetlaczu LCD. Wyświetlana liczba jest numerem klawisza zgodnie z opisem na modelu klawiatury HAPSIM (wczytać plik konfiguracyjny CW5Z3.xml).
Ponadto, przyciśnięcie klawisza dołączonego do linii PD2 "Clear" czyści wyświetlacz (kursor do lewego rogu). Zamiany binarnego/integer numeru klawisza na
kod ASCII (wymagany przez LCD) dokonać używając tablicy transkodowania. Tablica transkodowania ma być umieszczona w pamięci programu. 
Czas reakcji na przyciśnięcie klawisza na klawiaturze nie dłuższy niż 40 ms. Czas odmierzany timerem. Odczyt klawiatury realizowany multipleksowo w obsłudze 
przerwania od timera. Klawiatura dołączona do portu B. 
Kody ASCII: http://www.asciitable.com/


2) 	Wyświetlacz LCD skonfigurowany jest do wyświetlania 2 linii, format znaku 5x8. Interfejs 4-bitowy. Program przyjmuje z klawiatury matrycowej liczbę dziesiętną
 i tę wyświetla liczbę, w miarę wprowadzania kolejnych cyfr, na wyświetlaczu LCD. Cyfry (i funkcje) odpowiadające poszczególnym klawiszom ,jak w opisie modelu
 klawiatury w HAPSIM po załadowaniu pliku konfiguracyjnego CW9Z2.xml. Program reaguje na przyciśnięcie klawisza "Clear" wyczyszczeniem wyświetlacza (kursor do 
pozycji początkowej, jak po starcie programu). Przyciśnięcia pozostałych klawiszy klawiatury są ignorowane. 
Po starcie program wyświetli pobierane znaki w górnej linii zaczynając od:
wer a) lewej,
wer b) prawej.
Po osiągnięciu przez kursor ostatniej wyświetlanej pozycji w górnej linii kursor zatrzymuje się, natomiast każde wprowadzenie kolejnego znaku przesuwa dotychczasową 
treść (całą zawartość wyświetlacza) o 1 pozycję w kierunku przeciwnym niż kierunek, w którym dotąd następowało wprowadzanie znaków.
Ponadto, przytrzymywanie klawisza "Clear" ponad 1s (dla testowania na emulatorze skrócić 10 krotnie) czyści wyświetlacz i przełącza do wyświetlania w 2-iej linii.
Zamiana kodu binarnego/integer na ASCII, jak w zadaniu 1. Czas reakcji na przyciśnięcie klawisza na klawiaturze nie dłuższy niż 40 ms. Czas odmierzany timerem. 
Odczyt klawiatury realizowany multipleksowo w obsłudze przerwania od timera. Klawiatura dołączona do portu B. 


3)	Program, jak w zadaniu 2. Dodatkowo: 
	a) przycisnięcie klawisza "Up" powoduje przeniesienie wprowadzania tekstu do górnej linii (chyba, że obecnie już jest ustawione wprowadzanie do górnej linii);
	kursor na pierwszej, dotąd niezapisanej, pozycji w linii
	b) przycisnięcie klawisza "Down" powoduje przeniesienie wprowadzania tekstu do dolnej linii (chyba, że obecnie już jest ustawione wprowadzanie do dolnej linii);
	kursor na pierwszej, dotąd niezapisanej, pozycji w linii
	c) przycisnięcia klawisza "Left" powoduje przesunięcie treści obecnie aktywnej linii w lewo o 1 pozycję
	d) przycisnięcia klawisza "Right" powoduje przesunięcie treści obecnie aktywnej linii w prawo o 1 pozycję
	e) na przyciśnięcie klawisza "Enter" program nie reaguje
	

