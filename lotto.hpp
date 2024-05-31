#pragma once

#include <stdint.h>

constexpr uint8_t LOTTO_SIZE{6}; ///< Liczba losowanych liczb.

/**
 * Wartość zwracana przez maszynę losującą.
 */
struct LottoResult {
	uint8_t buffer[LOTTO_SIZE]; ///< Tablica z wynikiem.
};

/**
 * Maszyna losująca.
 */
struct Lotto {
	/**
	 * Inicjalizuje maszynę losującą.
	 *
	 * Komora maszyny losującej jest pusta…
	 */
	void initialize() const;
	
	/**
	 * Losuje zestaw liczb.
	 *
	 * … następuje zwolnienie blokady i rozpoczynamy losowanie sześciu liczb.
	 *
	 * @return Wylosowane liczby.
	 */
	LottoResult shuffle() const;
};

extern const Lotto lotto; ///< Instancja maszyny losującej.
