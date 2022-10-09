#ifndef _JL_IRQ_H
#define _JL_IRQ_H

// Put this in your function declaration!
//  e.g. void IRQ_HANDLER TheInterruptHandler(void) { };
#define IRQ_HANDLER		__attribute__((interrupt))

void irq_enable(int line);
void irq_disable(int line);
void irq_set_priority(int line, int priority);

void irq_attach(int line, void (*handler)());
void irq_detach(int line);

#endif
