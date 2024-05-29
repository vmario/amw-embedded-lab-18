---
title: "Ćwiczenie 17: Przechowywanie danych użytkownika w pamięci EEPROM"
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

Jaki jest rozmiar pamięci EEPROM dostępnej w mikrokontrolerze ATmega328P?

\vspace{1.5cm}

Ile cyklów zapisu/czyszczenia jest gwarantowane dla pamięci Flash, a ile dla pamięci EEPROM w&nbsp;mikrokontrolerze ATmega328P?

\vspace{1.5cm}

Jaka jest gwarantowana retencja danych w pamięciach nieulotnych w temperaturze pokojowej, a jaka w temperaturze 85&deg;C?

\vspace{1.5cm}

\awesomebox[violet]{2pt}{\faBook}{violet}{Odpowiedzi na powyższe pytania znajdziesz na pierwszej stronie dokumentacji mikrokontrolera.}

## Zadanie rozszerzone

Ile zajmuje zapis jednego bajtu w pamięci EEPROM?

\vspace{1.5cm}

Ile zajmie zapis całej dostępnej pamięci EEPROM?

\vspace{1.5cm}

\awesomebox[violet]{2pt}{\faBook}{violet}{Stałe czasowe przedstawione są w tabeli \textit{EEPROM Programming Time} w rozdziale \textit{AVR Memories} dokumentacji mikrokontrolera.}

## \faCertificate&nbsp; Zadanie specjalne

_+1 pkt dla osoby, która jako pierwsza poda poprawną odpowiedź._

Czym się różni operacja czyszczenia i zapisu komórki pamięci EEPROM? Po co sterownik EEPROM przewiduje rozdzielenie tych operacji?
