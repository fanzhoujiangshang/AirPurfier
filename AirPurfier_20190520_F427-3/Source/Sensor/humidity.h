#ifndef __humidity_h
#define __humidity_h

#include "sht3x.h"

void humidityInit(void);
void humidityUpdate(void);

extern ft temperature; // temperature [°„C]
extern ft humidity; // relative humidity [%RH]

#endif /* __humidity_h */

/* end of file */
