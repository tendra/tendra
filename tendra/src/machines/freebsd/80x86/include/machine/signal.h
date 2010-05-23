#ifndef __HACKED_MACHINE_SIGNAL_H
#define __HACKED_MACHINE_SIGNAL_H

/* disable gcc specific alignment instruction */
#define __aligned(arg1)

#include_next <machine/signal.h>

#endif /* __HACKED_MACHINE_SIGNAL_H */
