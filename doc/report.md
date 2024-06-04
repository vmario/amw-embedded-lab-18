---
title: "Ćwiczenie 18: Generator pseudolosowy i wskaźniki na funkcje"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: no
colorlinks: yes
header-right: "\\faEdit"
footer-left: "Sprawozdanie z laboratorium"
header-includes: |
  \usepackage{awesomebox}
  \usepackage{tikz}
  \usepackage{xfrac}
  \usetikzlibrary{positioning}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
...

\lstset{language=[11]C++}

_W trosce o Państwa wyniki proszę o czytelne wpisywanie nazwisk._

**Data**: \dotfill

**Autorzy**: \dotfill

# Część praktyczna

## Zadanie podstawowe

**Ocena prowadzącego**: \dotfill

## Zadanie rozszerzone

**Ocena prowadzącego**: \dotfill

# Część teoretyczna

## Zadanie podstawowe

Do którego kanału ADC podłączony jest wewnętrzny termometr? Jakiego napięcia odniesienia wymaga?

\awesomebox[violet]{2pt}{\faBook}{violet}{Potrzebne informacje znajdziesz w sekcji \textit{Temperature Measurement} dokumentacji mikrokontrolera.}

\vspace{3cm}

Jakie jest typowe napięcie z termometru wewnętrznego w temperaturze pokojowej?

\vspace{3cm}

Przelicz to napięcie na wartość pomiaru w rejestrze ADC.

\awesomebox[violet]{2pt}{\faBook}{violet}{Potrzebne informacje znajdziesz w sekcji \textit{ADC Conversion Result} dokumentacji mikrokontrolera.}

\vspace{2.5cm}

## Zadanie rozszerzone

W bieżącym ćwiczeniu szum na przetworniku ADC jest dla nas zjawiskiem korzystnym, gdyż zwiększa entropię, ale podczas precyzyjnych pomiarów jest szkodliwym zakłóceniem. W jaki sposób mikrokontroler ATmega328P umożliwia zmniejszenie tego szumu?

\awesomebox[violet]{2pt}{\faBook}{violet}{Potrzebne informacje znajdziesz w sekcji \textit{ADC Noise Reduction Mode} dokumentacji mikrokontrolera.}

\vspace{4cm}

## \faCertificate&nbsp; Zadanie specjalne

_+1 pkt dla osoby, która jako pierwsza poda poprawną odpowiedź._

Jeżeli przy `RAND_MAX` równym 0x7fff losujemy liczbę z zakresu [1; 49] za pomocą wyrażenia:

```
uint8_t value = (rand() % 49) + 1;
```

to jakie liczby mają odrobinę większe prawdopodobieństwo wylosowania od pozostałych?
