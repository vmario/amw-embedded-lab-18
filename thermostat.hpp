#pragma once

constexpr double TARGET_DEFAULT{20}; ///< Domyślna wartość temperatury docelowej.
constexpr double HYSTERESIS_DEFAULT{1}; ///< Domyślna wartość histerezy.

/**
 * Logika termostatu i obsługa jego nastaw.
 */
struct Thermostat {
	/**
	 * Zapisuje nastawy do EEPROM.
	 */
	void save() const;

	/**
	 * Odczytuje nastawy z EEPROM.
	 */
	void restore();

	/**
	 * Określa stan grzałki na podstawie bieżącej temperatury.
	 *
	 * @param temperature Bieżąca temperatura.
	 * @return Stan grzałki.
	 */
	bool run(double temperature);

	double target{TARGET_DEFAULT}; ///< Temperatura docelowa.
	double hysteresis{HYSTERESIS_DEFAULT}; ///< Histereza.
private:
	bool heater; ///< Stan grzałki.
};

extern Thermostat thermostat; ///< Globalna instancja termostatu.
