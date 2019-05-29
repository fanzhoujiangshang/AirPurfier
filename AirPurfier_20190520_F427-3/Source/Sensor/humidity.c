#include "humidity.h"
#include "i2c.h"
#include "timer.h"
#include "sht3x.h"

etError error; // error code
u32t serialNumber;// serial number
regStatus status; // sensor status
ft temperature; // temperature [°„C]
ft humidity; // relative humidity [%RH]
bt heater; // heater, false: off, true: on

void humidityUpdate(void)
{
    static uint32_t lastUpdateTick = 0;
	
    if (uwTick - lastUpdateTick > 100)
    {
        lastUpdateTick = uwTick;
        
        // read measurment buffer 
//        __disable_irq();
        
        error = SHT3X_ReadMeasurementBuffer(&temperature, &humidity);
        
//        __enable_irq();
//        
//        if(error == NO_ERROR)
//        {
//            // flash blue LED to signalise new temperature and humidity values
//            DelayMicroSeconds(10000);
//        }
//        else if (error == ACK_ERROR)
//        {
//            // there were no new values in the buffer -> ignore this error
//            error = NO_ERROR;
//        } else return;

//        // read heater status 
//        heater = status.bit.HeaterStatus ? TRUE : FALSE;

//        // if the user button is not pressed ... 
//        if(0)
//        {
//            // ... and the heater is on
//            if(heater)
//            {
//                // switch off the sensor internal heater 
//                error |= SHT3X_DisableHeater();
//                if(error != NO_ERROR) return; 
//            } 
//        }
//        else
//        // if the user button is pressed ... 
//        {
//            // ... and the heater is off 
//            if(!heater)
//            { 
//                // switch on the sensor internal heater 
//                error |= SHT3X_EnableHeater(); 
//                if(error != NO_ERROR) return; 
//            } 
//        }
    }
}

void humidityInit(void)
{
    /* RF-MSV30 SHT30 */
    SHT3X_Init(0x44); // Address: 0x44 = Sensor on EvalBoard connector 
	                           // 0x45 = Sensor on EvalBoard
    
    // ... try first a soft reset ... 
    error = SHT3X_SoftReset();

	// wait 50ms after power on
	DelayMicroSeconds(50000);

	error = SHT3x_ReadSerialNumber(&serialNumber);
	if(error != NO_ERROR){} // do error handling here
        
//    // demonstrate a single shot measurement with clock-stretching 
//    error = SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_CLKSTRETCH, 50);
//    if(error != NO_ERROR){} // do error handling here    

//	// demonstrate a single shot measurement with clock-stretching
//	error = SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_POLLING, 50);
//	if(error != NO_ERROR){} // do error handling here
        
//    // read status register 
//    error |= SHT3X_ReadStatus(&status.u16); 
//    if(error != NO_ERROR) return;

//    // check if the reset bit is set after a reset or power-up
//    if(status.bit.ResetDetected)
//    {
//        //override default temperature and humidity alert limits (red LED)
//        error = SHT3X_SetAlertLimits( 70.0f, 50.0f, // high set: RH [%], T [°„C] 
//            68.0f, 48.0f, // high clear: RH [%], T [°„C] 
//            32.0f, -2.0f, // low clear: RH [%], T [°„C] 
//            30.0f, -4.0f); // low set: RH [%], T [°„C] 
//        if(error != NO_ERROR) return;
//            
//        // clear reset and alert flags 
//        error = SHT3X_ClearAllAlertFlags();
//        if(error != NO_ERROR) return;

//        //start periodic measurement, with high repeatability and 1 measurements per second
//        error = SHT3X_StartPeriodicMeasurment(REPEATAB_HIGH, FREQUENCY_1HZ);
//        if(error != NO_ERROR) return;
//    }
    
    error = SHT3X_StartPeriodicMeasurment(REPEATAB_HIGH, FREQUENCY_1HZ);
    if(error != NO_ERROR) return;
}
