#include "jl_irq.h"
#include "jl_regs.h"

extern void *InterruptVectorTable[];

void irq_enable(int line) {
	if (line < 0 || line > 63) return;
	reg32_wsmask(CORE_base+CORE_ICFGi_enable(line), 1);
}

void irq_disable(int line) {
	if (line < 0 || line > 63) return;
	reg32_wsmask(CORE_base+CORE_ICFGi_enable(line), 0);
}

void irq_set_priority(int line, int priority) {
	if (line < 0 || line > 63) return;
	reg32_wsmask(CORE_base+CORE_ICFGi_priority(line), priority);
}

void irq_attach(int line, void (* handler)()) {
	if (line < 0 || line > 63) return;
	InterruptVectorTable[line] = handler;
	irq_enable(line);
}

void irq_detach(int line) {
	if (line < 0 || line > 63) return;
	irq_disable(line);
	InterruptVectorTable[line] = 0;
}
