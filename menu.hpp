#pragma once

#include <stdint.h>

constexpr uint8_t DISPLAY_LENGTH{16}; ///< Szerokość wyświetlacza.
constexpr char DISPLAY_CODE_DEGREE{0}; ///< Kod symbolu stopnia.
constexpr char DISPLAY_CODE_NEGATIVE_ARROW{1}; ///< Kod strzałki wskazującej edytowaną nastawę.
constexpr char DISPLAY_CODE_ELLIPSIS{2}; ///< Kod wielokropka.
constexpr char DISPLAY_CODE_VERTICAL_LINE{3}; ///< Pionowa linia przez całą wysokość pola.

/**
 * Stany menu.
 */
enum MENU_STATE {
	MENU_STATE_DEFAULT, ///< Domyślny stan (wyświetlanie nastaw).
	MENU_STATE_TARGET, ///< Edycja temperatury zadanej.
	MENU_STATE_HYSTERESIS, ///< Edycja histerezy.
};

/**
 * Menu wyświetlacza.
 */
struct Menu {
	/**
	 * Inicjalizacja menu.
	 */
	void initialize() const;

	/**
	 * Obsługa klawiatury.
	 */
	void handleKey() const;

	/**
	 * Wyświetla wynik losowania.
	 */
	void showResult() const;

	/**
	 * Pasek postępu.
	 */
	void showProgress() const;
private:
	MENU_STATE state; ///< Bieżący stan menu.
};

extern Menu menu; ///< Globalna instancja menu.
