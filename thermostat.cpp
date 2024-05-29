#include "thermostat.hpp"

#include <avr/eeprom.h>
#include <util/atomic.h>

#include <stdio.h>
#include <string.h>

Thermostat thermostat;

/**
 * Adresy nastaw w EEPROM.
 */
enum EEPROM_ADDRESS {
	EEPROM_ADDRESS_TARGET = 0, ///< Adres temperatury zadanej.
	EEPROM_ADDRESS_HYSTERESIS = EEPROM_ADDRESS_TARGET + sizeof(float), ///< Adres histerezy.
};

void Thermostat::save() const
{
}

void Thermostat::restore()
{
}

bool Thermostat::run(double temperature)
{
	if (heater && temperature > target + hysteresis) {
		heater = false;
	}

	if (!heater && temperature < target - hysteresis) {
		heater = true;
	}

	return heater;
}
