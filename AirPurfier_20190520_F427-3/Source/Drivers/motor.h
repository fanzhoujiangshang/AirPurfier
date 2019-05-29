#ifndef __motor_h
#define __motor_h

#include "afx.h"

typedef struct
{
    uint32_t lastCalTick;
    uint32_t rpm;
    uint32_t pulseCount;
    uint8_t setSpeedLevel;
    uint32_t setPoint;
    float output;
		float outputreal;
    uint8_t autoModeEnable;
    
    uint8_t setTimeLevel;
    uint32_t timeLeft;
		uint32_t timeLeftHours;
		float    air_quality;
		u32      settimes;
		u32      raisingHDTick1;
		u32      raisingHDTick2;
		u8       seq;
		signed short error;
} motorStruct_t;

typedef struct 
{
	float kp;
	float ki;
	float kd;

	signed short _last_input;
	float _last_derivative;

	float _integrator;

	float _imax;

	float p_out;
	float i_out;
	float d_out;
}pid_para;

void motorSensorInit(void);
void motorSensorUpdate(void);
void motorControl(void);
void pid_Init(void);
extern motorStruct_t motorData;

#endif /* __motor_h */

/* end of file */
