#include "version.h"

uint32_t chipUniqueID[3];

void versionInit(void)
{
    chipUniqueID[0] = *(volatile uint32_t *)(0X1ffff7e8);
    chipUniqueID[1] = *(volatile uint32_t *)(0X1ffff7ec);
    chipUniqueID[2] = *(volatile uint32_t *)(0X1ffff7f0);
}

/* end of file */
