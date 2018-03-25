#ifndef _USART_H
#define _USART_H

#define lenth 16

#include "head.h"

 uint8_t rx_buffer_0[lenth];
 uint8_t rx_buffer_2[lenth];

extern int temp;

void ConfigureUART0(void);
void UART0_Send(uint8_t *pui8Buffer, uint32_t ui32Count);
void UART0_IntHandler(void);

void ConfigureUART2(void);
void UART2_Send(const uint8_t *pucBuffer, uint32_t ulCount);
void UART2_IntHandler(void);


#endif
