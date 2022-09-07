#include <jl_regs.h>
#include <jl_irq.h>
#include "wallclk.h"

// hardcoded...
#define PERIOD_1MS		(48000000 / 1000)

volatile uint64_t msecs;

static void IRQ_HANDLER TickerTimer(void) {
	msecs++;
	reg32_wsmask(CORE_base+CORE_TTMR_CON_cpnd, 1);
};


void wallclk_init(void) {
	reg32_write(CORE_base+CORE_TTMR_CON, 0);
	reg32_write(CORE_base+CORE_TTMR_CNT, 0);
	reg32_write(CORE_base+CORE_TTMR_PRD, PERIOD_1MS);
	reg32_wsmask(CORE_base+CORE_TTMR_CON_enable, 1);
	irq_attach(3, TickerTimer);
}


uint64_t micros(void) {
	return (msecs * 1000ull) + (reg32_read(CORE_base+CORE_TTMR_CNT) / (PERIOD_1MS / 1000));
}

void usleep(uint64_t us) {
	for (uint64_t target = micros() + us; micros() < us; );
}


uint64_t millis(void) {
	return msecs;
}

void delay(uint64_t ms) {
	for (uint64_t target = millis() + ms; millis() < ms; );
}
