#include "buzzer.h"
#include "timer.h"

uint8_t tone = 0;

void buzzerWork(void)
{
    static uint32_t workTick = 0;
    static uint8_t step = 0;
    
    if (uwTick - workTick > 100)
    {
        workTick = uwTick;
        
        if (tone == 0)
        {
            TIM3->CCR1 = 0;
        }
        else if (tone == 1)
        {
            switch (step)
            {
            case 0:
                TIM3->CCR1 = 100;
                break;
            
            case 1:
            case 2:
            case 3:
                TIM3->CCR1 = 0;
                break;
            }
            step = (step + 1) % 2;
        }
        else if (tone == 2)
        {
            switch (step)
            {
            case 0:
            case 1:
                TIM3->CCR1 = 100;
                break;
            
            case 2:
            case 3:
                TIM3->CCR1 = 0;
                break;
            }
            step = (step + 1) % 2;
        }
    }
}

/* end of file */
