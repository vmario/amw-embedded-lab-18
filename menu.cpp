#include "menu.hpp"

#include "keypad.hpp"
#include "lotto.hpp"
#include "lcdDisplay.hpp"

#include <util/delay.h>
#include <avr/io.h>

#include <stdio.h>
#include <stdlib.h>

Menu menu;

void Menu::initialize() const
{
	lcdDisplay.clear();
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write(" Initializing   ");
	lcdDisplay.goTo(0, 13);
	lcdDisplay.write(DISPLAY_CODE_ELLIPSIS);

	showProgress();
	lcdDisplay.clear();
}

void Menu::handleKey() const
{
	switch (keypad.oneTimeKey()) {
	case KEY_RIGHT:
		showResult();
		break;
	default:
		break;
	}
}

void Menu::showProgress() const
{
	lcdDisplay.goTo(1, 0);
	for (int i{0}; i < DISPLAY_LENGTH; ++i) {
		lcdDisplay.write('\xff');
		_delay_ms(40);
	}
}

void Menu::showResult() const
{
	char buf[DISPLAY_LENGTH + 1];
	LottoResult result{lotto.shuffle()};

	lcdDisplay.goTo(0, 9);
	lcdDisplay.write('\x03');
	lcdDisplay.goTo(1, 9);
	lcdDisplay.write('\x03');
	lcdDisplay.goTo(0, 0);

	for (int i = 0; i < 3; i++) {
		snprintf(buf, sizeof(buf), "%2d ", result.buffer[i]);
		lcdDisplay.write(buf);
	}

	lcdDisplay.goTo(1, 0);
	for (int i = 3; i < 6; i++) {
		snprintf(buf, sizeof(buf), "%2d ", result.buffer[i]);
		lcdDisplay.write(buf);
	}
}
