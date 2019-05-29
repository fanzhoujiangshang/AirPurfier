/**
*******************************************************************************
* @file      serial.h
* @version   V1.0
* @date      2016.11.23
* @brief     ´®¿ÚÇý¶¯
*******************************************************************************
* @copy
*
* @author	R&D @ AEE Enterprise
*
* Eone Flight Controler 
*******************************************************************************
*/

/*---------------------------- Include ---------------------------------------*/
#ifndef __serial_h
#define __serial_h

#include "stm32f4xx.h"

#define SERIAL_DEFAULT_RX_BUFSIZE	128

typedef void serialTxDMACallback_t(void *s);

typedef struct
{
    unsigned int baudRate;
    uint16_t flowControl;
    uint16_t parity;
    uint16_t stopBits;

    unsigned int txBufSize;
    volatile unsigned char *txBuf;
    volatile unsigned int txHead, txTail;

    unsigned int rxBufSize;
    volatile unsigned char *rxBuf;
    volatile unsigned int rxHead, rxTail;
    volatile unsigned int rxPos;

    USART_TypeDef *USARTx;
    DMA_Stream_TypeDef *rxDMAStream;
    DMA_Stream_TypeDef *txDMAStream;
    uint32_t rxDMAChannel;
    uint32_t txDMAChannel;
    uint32_t rxDmaFlags, txDmaFlags;
    volatile unsigned char txDmaRunning;
    serialTxDMACallback_t *txDMACallback;
    void *txDMACallbackParam;

    uint8_t waitFlag;
} serialPort_t;

serialPort_t *serialOpen(USART_TypeDef *USARTx, unsigned int baud, uint16_t flowControl, unsigned int rxBufSize, unsigned int txBufSize);
void serialChangeBaud(serialPort_t *s, unsigned int baud);
void serialChangeParity(serialPort_t *s, uint16_t parity);
void serialChangeStopBits(serialPort_t *s, uint16_t stopBits);
void serialSetSTDIO(serialPort_t *s);
void serialWrite(serialPort_t *s, unsigned char ch);
void serialWriteBlock(serialPort_t *s, const unsigned char *buf, unsigned char len);
void serialWatch(void);
unsigned char serialAvailable(serialPort_t *s);
uint8_t serialRead(serialPort_t *s);
int serialReadBlock(serialPort_t *s);
void serialPrint(serialPort_t *s, const char *str);
int _serialStartTxDMA(serialPort_t *s, void *buf, int size, serialTxDMACallback_t *txDMACallback, void *txDMACallbackParam);
int __putchar(int ch);
int __getchar(void);

extern serialPort_t *serialSTDIO;

#endif /* __serial_h */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************** (C) COPYRIGHT AEE Technology ******END OF FILE*****/
