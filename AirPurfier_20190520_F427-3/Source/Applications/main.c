#include "afx.h"
#include "afx_init.h"

int main(void)
{
	/* 新建系统初始化任务 */
    xTaskCreate(afxInitTask, "InitTask", configMINIMAL_STACK_SIZE * 4, \
        NULL, tskIDLE_PRIORITY, NULL);
	
	/* FreeRTOS调度器开始工作 */
	vTaskStartScheduler();
	
	/* 此处不会执行到 */
	while (1);
}

/* end of file */                                                                                             
