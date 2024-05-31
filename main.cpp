#include "adc.hpp"
#include "keypad.hpp"
#include "lcdDisplay.hpp"
#include "menu.hpp"
#include "lotto.hpp"

#include <util/atomic.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

/**
 * Obsługuje wyświetlacz i logikę termostatu.
 */
void mainLoop()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		keypad.measure(keyboardAdc);
	}
	menu.handleKey();
}

/**
 * Funkcja główna.
 */
int main()
{
	constexpr uint8_t DEGREE[] = {
		0b00000010,
		0b00000101,
		0b00000010,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
	};

	constexpr uint8_t NEGATIVE_ARROW[] = {
		0b00011111,
		0b00011011,
		0b00011101,
		0b00000000,
		0b00011101,
		0b00011011,
		0b00011111,
		0b00000000,
	};

	constexpr uint8_t ELLIPSIS[] = {
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00010101,
		0b00000000,
	};

	constexpr uint8_t VERTICAL_LINE[] = {
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
		0b00000100,
	};

	lcdDisplay.initialize();
	lcdDisplay.addSymbol(DEGREE, DISPLAY_CODE_DEGREE);
	lcdDisplay.addSymbol(NEGATIVE_ARROW, DISPLAY_CODE_NEGATIVE_ARROW);
	lcdDisplay.addSymbol(ELLIPSIS, DISPLAY_CODE_ELLIPSIS);
	lcdDisplay.addSymbol(VERTICAL_LINE, DISPLAY_CODE_VERTICAL_LINE);

	menu.initialize();
	lotto.initialize();
	menu.showResult();
	adc.initialize();
	sei();

	while (true) {
		mainLoop();
	}
}
