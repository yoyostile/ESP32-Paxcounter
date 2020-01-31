#ifndef _IRQHANDLER_H
#define _IRQHANDLER_H

#define DISPLAY_IRQ 0x001
#define BUTTON_IRQ 0x002
#define SENDCYCLE_IRQ 0x004
#define CYCLIC_IRQ 0x008
#define TIMESYNC_IRQ 0x010
#define MASK_IRQ 0x020
#define UNMASK_IRQ 0x040
#define BME_IRQ 0x080
#define DHT_IRQ 0x90
#define MATRIX_DISPLAY_IRQ 0x100
#define PMU_IRQ 0x200
#define SWITCH_IRQ 0x300

#include "globals.h"
#include "cyclic.h"
#include "senddata.h"
#include "timekeeper.h"
#include "bmesensor.h"
#include "dhtsensor.h"
#include "power.h"

void irqHandler(void *pvParameters);
void mask_user_IRQ();
void unmask_user_IRQ();

#ifdef HAS_DISPLAY
void IRAM_ATTR DisplayIRQ();
#endif

#ifdef HAS_MATRIX_DISPLAY
void IRAM_ATTR MatrixDisplayIRQ();
#endif

#ifdef HAS_BUTTON
void IRAM_ATTR ButtonIRQ();
#endif

#ifdef USE_SWITCH
void IRAM_ATTR SwitchIRQ();
#endif

#ifdef HAS_PMU
void IRAM_ATTR PMUIRQ();
#endif


#endif