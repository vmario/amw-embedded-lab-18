---
title: "Ćwiczenie 18: Generator pseudolosowy i wskaźniki na funkcje"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
  \usepackage{tikz}
  \usetikzlibrary{automata, positioning, arrows, shapes, patterns}
  \usepackage{tikz-timing}
  \usepackage{xfrac}
  \usepackage{ellipsis}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
  \usepackage{lcd}
  \LCDcolors[MidnightBlue]{MidnightBlue!10}{MidnightBlue!80}
...

\lstset{language=[11]C++}
\tikzset{
    >=stealth',
    node distance=2.8cm,
    every state/.style={thick, fill=gray!20, align=center, text width=1.1cm},
    auto,
    font=\footnotesize,
}

> Code never lies, comments sometimes do.
>
> — _Ron Jeffries_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* sposobem działania generatora pseudolosowego,
* metodami pozyskiwania entropii w systemach mikroprocesorowych,
* wykorzystaniem implementacji podstawowych algorytmów z biblioteki standardowej,
* wykorzystaniem wskaźników na funkcje.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _LCD Keypad Shield_ do _Arduino Uno_.
1. W lewej części wyświetlacza widocznych jest 6 liczb wybranych przez generator pseudolosowy, symulujący losowanie Lotto.
1. Po kliknięciu przycisku _RIGHT_ losowane są nowe liczby.
1. W prawej części wyświetlacza widoczne jest ziarno losowości.

\DefineLCDchar{verticalLine}{0010000100001000010000100001000010000100}
\begin{center}
\LCD{2}{16}
    | 1 19 16 {verticalLine} Seed:|
    |36 40 14 {verticalLine}     1|
\captionof{figure}{Wyjściowy stan wyświetlacza}
\end{center}

Program wyjściowy symuluje losowanie liczb w grze Lotto — wybiera w funkcji `Lotto::shuffle()` 6 niepowtarzających się liczb z przedziału [1; 49], dokonując za pomocą algorytmu Fishera-Yatesa permutacji tablicy `numbersPool`, wypełnionej wstępnie kolejnymi liczbami naturalnymi od 1 do 49. Na koniec wybieranych jest 6 pierwszych liczb z tak przemieszanej tablicy.

Algorytm Fishera-Yatesa nie zapewnia losowania sam w sobie, ale wymaga użycia zewnętrznej funkcji losującej. W języku C mamy do dyspozycji funkcję `rand()`, która zwraca wartości z zakresu [0;&nbsp;`RAND_MAX`], gdzie w naszym przypadku `RAND_MAX` wynosi 32767.

\awesomebox[teal]{2pt}{\faCode}{teal}{Język C++ od wersji C++11 posiada bibliotekę \lstinline{random}, która zawiera bogaty zestaw narzędzi do generowania wartości pseudolosowych zgodnych z różnymi rozkładami prawdopodobieństwa i z użyciem różnych implementacji generatorów. Ze względu na złożoność nie jest ona dostępna dla platformy AVR.}

Należy jednak pamiętać, że żaden generator pseudolosowy, czyli PRNG (_Pseudorandom Number Generator_), nie generuje liczb losowych! Mikroprocesor jest urządzeniem deterministycznym zaprojektowanym z założeniem, że lepiej, by nie działał w ogóle niż działał w sposób nieprzewidywalny[^1]. Nie istnieje zatem algorytm, który byłby w stanie wygenerować prawdziwie losowe liczby[^2]. Algorytmy PRNG zaprojektowane są w sposób, który zapewnia odpowiedni rozkład generowanych liczb, przypominający losowy, ale wiele z nich jest do tego stopnia deterministycznych, że po zebraniu kilku wygenerowanych liczb można przewidzieć następne. Stąd po każdym włączeniu urządzenia, widoczne są te same liczby — algorytm zaczyna pracę od tej samej wartości.

[^1]: _Vide_ BOR (_Brown-out Detector_), czyli obwód wyłączający mikrokontroler przy zbyt niskim napięciu zasilania, kiedy część procesora może jeszcze pracować, ale błędnie.

[^2]: &bdquo;Anyone who considers arithmetical methods of producing random digits is, of course, in a state of sin&rdquo; — John von Neumann.

# Zadanie podstawowe

Celem zadania podstawowego jest inicjalizacja PRNG wartością o charakterze losowym, a przynajmniej bardzo trudnym do przewidzenia i mało powtarzalnym. Idealnym źródłem byłyby zjawiska kwantowe, które z założenia są czysto losowe, co wykazano w wielu złożonych eksperymentach, wykazując brak korelacji z jakimkolwiek czynnikiem, włączając w to sygnały sprzed 10 miliardów lat[^3]. Przykładami źródeł o takim charakterze są szumy śrutowe złącza p-n czy rozpad promieniotwórczy.

[^3]: Ewentualnie wyniki eksperymentów zostały z góry ustalone u zarania dziejów Wszechświata, ale dla nas jest to nieodróżnialne.

Na nasze potrzeby w zupełności wystarczające jest wykorzystanie jakiegoś procesu o trudnym do przewidzenia przebiegu, np. szumu termicznego, parametrów pogodowych, zjawisk chaotycznych czy interakcji z&nbsp;użytkownikiem. Tym ostatnim rozwiązaniem mógłby być precyzyjny pomiar czasu wciśnięcia przycisku przez użytkownika, ale zakładamy, że chcemy, by urządzenie wyświetlało losowe liczby bez żadnej interakcji. W tym celu użyjemy termometru. Wprawdzie temperatura otoczenia może być bardzo stabilna, jednak na pomiar wykonany z odpowiednią rozdzielczością nałoży się szum termometru i ADC. Analizując więc nie tylko samą temperaturę, ale biorąc pod uwagę jej chaotyczne oscylacje, możemy uzyskać wystarczająco dobre źródło losowości (entropii).

Mikrokontroler ATmega328P wyposażony jest we wbudowany termometr, dzięki czemu nie ma potrzeby uzupełniania urządzenia o dodatkowy sensor.

## Wymagania funkcjonalne

1. Po każdym uruchomieniu urządzenie stosuje inne ziarno losowości i wyświetla inne liczby.

## Modyfikacja programu

### Konfiguracja ADC

Odczytaj z dokumentacji mikrokontrolera numer kanału ADC oraz wymagane napięcie referencyjne dla termometru wewnętrznego i skonfiguruj odpowiednio rejestr `ADMUX` w metodzie `Lotto::initialize()`.

\awesomebox[violet]{2pt}{\faBook}{violet}{Potrzebne informacje znajdziesz w sekcji \textit{Temperature Measurement} dokumentacji mikrokontrolera.}

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Nieprawidłowa konfiguracja ADC niekoniecznie uniemożliwi działanie algorytmu zbierania entropii (bo nieużywane kanały ADC mogą również generować szum), ale proces zbierania entropii może być dużo dłuższy.}

Skonfiguruj preskaler ADC i włącz przetwornik:

```
ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
```

Teraz możesz uruchomić pomiar, ustawiając bit `ADSC` (_ADC Start Conversion_) i odczytać wynik z pary rejestrów `ADC` po wyczyszczeniu tego bitu przez przetwornik. Ze względu na zmianę napięcia referencyjnego oraz kondensator podłączony do pinu _AREF_ pierwszy pomiar będzie znacząco zaniżony. Należy odczekać kilka milisekund i wykonać drugi pomiar:

```
ADCSRA |= _BV(ADSC);
while (bit_is_set(ADCSRA, ADSC)) ;
_delay_ms(10);
ADCSRA |= _BV(ADSC);
while (bit_is_set(ADCSRA, ADSC)) ;
uint16_t seed = ADC;
```

Odczytaną wartość można wyświetlić na wyświetlaczu i porównać z dokumentacją celem oceny poprawności konfiguracji ADC.

### Algorytm zbierania entropii

Zaimplementuj algorytm zbierania entropii według poniższego wzoru. Sumujemy tutaj pomiary z ADC tak długo, aż zarejestrujemy 256 zmian wartości temperatury.

\begin{algorithm}
\caption{Algorytm zbierania entropii}
\begin{algorithmic}
    \Repeat
        \State wykonaj pomiar ADC
        \State $seed \gets seed + ADC$
        \If{$ADC \neq poprzedniADC$}
            \State $poprzedniADC \gets ADC$
            \State $liczbaZmian \gets liczbaZmian + 1$
        \EndIf
    \Until{$liczbaZmian < 256$}
\end{algorithmic}
\end{algorithm}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest sortowanie wylosowanych liczb za pomocą algorytmu z biblioteki standardowej.

## Wymagania funkcjonalne

1. Losowane liczby wyświetlane są w kolejności rosnącej.

## Modyfikacja programu

Użyj algorytmu `qsort()` z biblioteki standardowej. Znajdź w Internecie dokumentację tej funkcji i użyj jej na tablicy `result.buffer` w metodzie `Lotto::shuffle()` przed zwróceniem danych. Zwróć uwagę, że ostatnim argumentem funkcji `qsort()` jest wskaźnik na funkcję, która odpowiada za porównywanie danych. Napisz odpowiednią funkcję.
