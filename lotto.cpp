#include "lotto.hpp"

#include "menu.hpp"
#include "lcdDisplay.hpp"

#include <avr/io.h>
#include <util/delay.h>

#include <stdlib.h>
#include <stdio.h>

const Lotto lotto;

enum {
	LOTTO_MIN = 1, ///< Najmniejsza z losowanych liczb.
	LOTTO_MAX = 49, ///< Największa z losowanych liczb.
};

/**
 * Miesza tablicę.
 *
 * @param array Tablica do pomieszania.
 * @param size Rozmiar tablicy.
 */
void arrayShuffle(uint8_t *array, size_t size) {
	if (size < 2) {
		return;
	}

	for (size_t i{0}; i < size - 1; i++) {
		size_t j = i + (rand() % (size - i));
		int temp = array[j];
		array[j] = array[i];
		array[i] = temp;
	}
}

void Lotto::initialize() const
{
	lcdDisplay.goTo(0, 0);
	lcdDisplay.write("Getting entropy");
	lcdDisplay.goTo(0, 15);
	lcdDisplay.write(DISPLAY_CODE_ELLIPSIS);

	lcdDisplay.clear();
	lcdDisplay.goTo(0, 11);
	lcdDisplay.write("Seed:");

	char buf[DISPLAY_LENGTH + 1];
	snprintf(buf, sizeof(buf), "%5u", 1);
	lcdDisplay.goTo(1, 11);
	lcdDisplay.write(buf);
}

LottoResult Lotto::shuffle() const
{
	LottoResult result;
	uint8_t numbersPool[LOTTO_MAX];

	// Inicjalizacja liczb lotto
	for (int i = 0; i < LOTTO_MAX; i++) {
		numbersPool[i] = LOTTO_MIN + i;
	}

	// Tasowanie liczb
	arrayShuffle(numbersPool, LOTTO_MAX);

	// Wybieranie wylosowanych liczb
	for (uint8_t i = 0; i < LOTTO_SIZE; i++) {
		result.buffer[i] = numbersPool[i];
	}

	return result;
}
