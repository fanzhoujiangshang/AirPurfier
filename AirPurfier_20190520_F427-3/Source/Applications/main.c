#include "afx.h"
#include "afx_init.h"

int main(void)
{
	/* �½�ϵͳ��ʼ������ */
    xTaskCreate(afxInitTask, "InitTask", configMINIMAL_STACK_SIZE * 4, \
        NULL, tskIDLE_PRIORITY, NULL);
	
	/* FreeRTOS��������ʼ���� */
	vTaskStartScheduler();
	
	/* �˴�����ִ�е� */
	while (1);
}

/* end of file */                                                                                             
