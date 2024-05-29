#include "adc.hpp"

#include <avr/io.h>
#include <avr/interrupt.h>

const Adc adc;

volatile uint16_t temperatureAdc;
volatile uint16_t keyboardAdc{UINT16_MAX};

/**
 * Obsługa przerwania pomiaru ADC.
 */
ISR(ADC_vect)
{
	static uint8_t iteration;

	if (bit_is_clear(ADMUX, REFS1)) {
		if (iteration++ > 0) {
			keyboardAdc = adc.measure();
		}
		if (iteration > 100) {
			iteration = 0;
			ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX2) | _BV(MUX0);
		}
	} else {
		if (iteration++ > 0) {
			temperatureAdc = adc.measure();
			iteration = 0;
			ADMUX = _BV(REFS0);
		}
	}

	TIFR1 |= _BV(TOV1);
}

void Adc::initialize() const
{
	TCCR1B = _BV(CS10);
	ADMUX = _BV(REFS0);
	ADCSRB = _BV(ADTS2) | _BV(ADTS1);
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

uint16_t Adc::measure() const
{
	uint16_t value = ADCL;
	return value + (ADCH << 8);
}
