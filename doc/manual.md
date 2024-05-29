---
title: "Ćwiczenie 17: Przechowywanie danych użytkownika w pamięci EEPROM"
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

> Programming is learned by writing programs.
>
> — _Brian Kernighan_

# Cel ćwiczenia

Celem ćwiczenia jest zapoznanie się z:

* obsługą pamięci EEPROM za pomocą biblioteki \texttt{libc},
* obsługą pamięci EEPROM za pomocą bezpośrednich operacji na rejestrach.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _LCD Keypad Shield_ do _Arduino Uno_.
1. Podłącz termometr LM35DZ do linii _A5_.
1. W pierwszej linii wyświetlacza widoczne są dwie nastawy: _T_ — temperatura zadana $T_t$ i _H_ — histereza $T_h$.
1. Nastawy można zmieniać za pomocą przycisków _UP_ i _DOWN_, wybierając je wcześniej przyciskiem _SELECT_.
1. W drugiej linii wyświetlacza widoczna jest bieżąca temperatura i stan grzałki.

Program wyjściowy symuluje termostat, który włącza grzałkę po obniżeniu temperatury poniżej $T_t - T_h$ i wyłącza po  prekroczeniu $T_t + T_h$.

![Histereza w termostacie sterującym grzałką](hysteresis.svg){width=400px}

Zadaniem histerezy jest zmniejszenie częstotliwości przełączania elementu wykonawczego, kosztem zmniejszenia precyzji regulowanego parametru.

W naszym przypadku, gdy mierzona temperatura oscyluje wokół temperatury zadanej $T_t$ np. z powodu ruchu powietrza w pomieszczeniu albo szumu pomiarowego, może dojść do sytuacji, gdy element wykonywaczy byłby przełączany w bardzo krótkich odcinkach czasu. Jest to zjawisko, które może być szkodliwe dla elementu sterującego (np. w przekaźniku może dojść do wypalenia styków), jak i dla elementu wykonawczego (np. kompresor w lodówce może ulec szybkiemu zużyciu).

Histereza zazwyczaj jest jednym z parametrów, które są dostępne dla użytkownika jako nastawa, co pozwala mu ustalić kompromis między precyzją sterowania a częstotliwością przełączania.

\DefineLCDchar{degree}{00010001010001000000000000000000000}
\begin{center}
\LCD{2}{16}
    |T:25.0{degree}C H:1.0{degree}C|
    |  24.0{degree}C [HEAT] |
\captionof{figure}{Przykładowy stan wyświetlacza}
\end{center}

# Zadanie podstawowe

Celem zadania podstawowego jest zapisywanie nastaw urządzenia w pamięci nieulotnej EEPROM.

## Wymagania funkcjonalne

1. Po wyjściu z edycji nastaw ustawione wartości zapisywane są w pamięci EEPROM mikrokontrolera.
1. Po zresetowaniu mikrokontrolera wczytywana jest zapamiętana temperatura.
1. Urządzenie wykrywa niezainicjalizowaną pamięć i używa wówczas domyślnych nastaw.

## Modyfikacja programu

### Zapis nastaw

Uzupełnij metodę `Thermostat::save()` tak, by zapisywała obie nastawy w pamięci EEPROM pod adresami `EEPROM_ADDRESS_TARGET` i `EEPROM_ADDRESS_HYSTERESIS`.

### Odczyt nastaw

Uzupełnij metodę `Thermostat::restore()` tak, by odczytywała obie nastawy w pamięci EEPROM pod adresami `EEPROM_ADDRESS_TARGET` i `EEPROM_ADDRESS_HYSTERESIS`. Odczyt odbywa się automatycznie przy inicjalizacji urządzenia.

### Rozpoznanie niezainicjalizowanej pamięci

Po wciśnięciu przycisku _RIGHT_ uruchamiana jest procedura czyszczenia pamięci EEPROM, tj.&nbsp;wypełniania jej wartościami \lstinline{0xFF}, które prowadzą do interpretacji wartości zadanej temperatury i&nbsp;histerezy jako _nie-liczb_.

\begin{center}
\LCD{2}{16}
    |T: nan{degree}C H:nan{degree}C|
    |  24.0{degree}C [----] |
\captionof{figure}{Odczyt niezainicjalizowanej pamięci}
\end{center}

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Wyczyszczona pamięć EEPROM nie jest wypełniona bajtami \lstinline{0x00}, ale \lstinline{0xFF}. Jest to częsta cecha pamięci nieulotnych.}

\awesomebox[teal]{2pt}{\faCode}{teal}{Liczba zmiennoprzecinkowa, w której wszystkie bity wykładnika są ustawione (co ma miejsce w wyczyszczonej pamięci EEPROM), nie jest poprawną wartością, ale \textit{nie-liczbą} (ang. \textit{NaN} — \textit{Not a Number}).}

Wartość `NaN` można wykryć za pomocą makra \lstinline{isnan()} zdefiniowanego w bibliotece \lstinline{math.h}. Po wykryciu takiej wartości należy użyć wartości domyślnych dla nastaw: `TARGET_DEFAULT` i&nbsp;`HYSTERESIS_DEFAULT`.

# Zadanie rozszerzone

Celem zadania rozszerzonego jest samodzielna implementacja funkcji odczytującej i zapisującej wartość w pamięci EEPROM.

## Wymagania funkcjonalne

1. Funkcjonowanie urządenia nie zmienia się.

## Modyfikacja programu

### Implementacja odczytu wartości `float` z EEPROM

Napisz własną funkcję odczytującą zmienną typu `float` z EEPROM (oczywiście, możesz posłużyć się inną nazwą):

```
float eeprom_read_float(const float* address)
```

\awesomebox[violet]{2pt}{\faBook}{violet}{Przykłady procedur odczytu i zapisu do EEPROM znajdziesz w opisie rejestru \texttt{EECR} (\textit{EEPROM Control Register}) w dokumentacji mikrokontrolera.}

Zwróć uwagę, że należy odczytać liczbę bajtów równą rozmiarowi typu `float`. W tym celu możesz zdefiniować tablicę, do której w pętli przepiszesz kolejne bajty z EEPROM:

```
uint8_t buffer[sizeof(float)];
```

Bufor można przepisać do zmiennej typu `float` za pomocą funkcji `memcpy()` z biblioteki `string.h`:

```
float value;
memcpy(&value, buffer, sizeof(float));
```

\awesomebox[teal]{2pt}{\faCode}{teal}{Argument funkcji jest typu \lstinline{const float*}, gdyż jest adresem w pamięci, a więc wskaźnikiem. Aby operować na nim jak na liczbie 16-bitowej, w szczególności móc wpisać do pary rejestrów EEAR, można rzutować go na typ \lstinline{uint16_t} za pomocą \lstinline{reinterpret_cast<uint16_t>(address)}.}

### Implementacja odczytu wartości `float` z EEPROM

Analogicznie zaimplementuj funkcję zapisującą zmienną typu `float` do EEPROM:

```
void eeprom_write_float(float* address, float value)
```

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Zwróć uwagę na zależności czasowe przy ustawianiu bitów \lstinline{EEMPE} i \lstinline{EEPE}. Zabezpiecz te operacje blokiem \lstinline{ATOMIC_BLOCK()}.}
