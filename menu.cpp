#include "menu.hpp"

#include "keypad.hpp"
#include "lcdDisplay.hpp"
#include "thermostat.hpp"

#include <util/delay.h>
#include <avr/eeprom.h>

Menu menu;

void Menu::initialize() const
{
	thermostat.restore();

	lcdDisplay.clear();
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write(" Initializing   ");
	lcdDisplay.goTo(0, 13);
	lcdDisplay.write(DISPLAY_CODE_ELLIPSIS);

	showProgress();
	lcdDisplay.clear();

	lcdDisplay.goTo(0, 0);
	lcdDisplay.write("T:     C");
	lcdDisplay.goTo(0, 6);
	lcdDisplay.write(DISPLAY_CODE_DEGREE);

	lcdDisplay.goTo(0, 9);
	lcdDisplay.write("H:    C");
	lcdDisplay.goTo(0, 14);
	lcdDisplay.write(DISPLAY_CODE_DEGREE);

	lcdDisplay.goTo(1, 6);
	lcdDisplay.write(DISPLAY_CODE_DEGREE);
	lcdDisplay.goTo(1, 7);
	lcdDisplay.write('C');

	lcdDisplay.goTo(1, 9);
	lcdDisplay.write("[    ]");
}

void Menu::run() const
{
	switch (state) {
	case MENU_STATE_TARGET:
		menu.editTarget();
		break;
	case MENU_STATE_HYSTERESIS:
		menu.editHysteresis();
		break;
	default:
		menu.main();
		break;
	}
}

void Menu::showProgress() const
{
	lcdDisplay.goTo(1, 0);
	for (int i{0}; i < DISPLAY_LENGTH; ++i) {
		lcdDisplay.write('\xff');
		_delay_ms(80);
	}
}

void Menu::erase()
{
	for (int address{0}; address < 1024; ++address) {
		eeprom_update_byte(reinterpret_cast<uint8_t*>(address), 0xFF);
	}
}

void Menu::main()
{
	switch (keypad.oneTimeKey()) {
	case KEY_SELECT:
		state = MENU_STATE_TARGET;
		break;
	case KEY_RIGHT:
		lcdDisplay.clear();
		lcdDisplay.goTo(0, 0);
		lcdDisplay.write("    Erasing     ");
		lcdDisplay.goTo(0, 11);
		lcdDisplay.write(DISPLAY_CODE_ELLIPSIS);
		erase();
		showProgress();
		initialize();
		break;
	default:
		break;
	}
}

void Menu::editTarget()
{
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write(DISPLAY_CODE_NEGATIVE_ARROW);
	lcdDisplay.write(' ');

	switch (keypad.oneTimeKey()) {
	case KEY_SELECT:
		lcdDisplay.goTo(0, 0);
		lcdDisplay.write("T:");
		state = MENU_STATE_HYSTERESIS;
		break;
	case KEY_UP:
		if (thermostat.target < 40) {
			thermostat.target += 0.5;
		}
		break;
	case KEY_DOWN:
		if (thermostat.target > 10) {
			thermostat.target -= 0.5;
		}
		break;
	default:
		break;
	}
}

void Menu::editHysteresis()
{
	lcdDisplay.goTo(0, 9);
	lcdDisplay.write(DISPLAY_CODE_NEGATIVE_ARROW);
	lcdDisplay.write(' ');

	switch (keypad.oneTimeKey()) {
	case KEY_SELECT:
		lcdDisplay.goTo(0, 9);
		lcdDisplay.write("H:");
		thermostat.save();
		state = MENU_STATE_DEFAULT;
		break;
	case KEY_UP:
		if (thermostat.hysteresis < 5) {
			thermostat.hysteresis += 0.5;
		}
		break;
	case KEY_DOWN:
		if (thermostat.hysteresis > 0.0) {
			thermostat.hysteresis -= 0.5;
		}
		break;
	default:
		break;
	}
}
