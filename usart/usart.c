#include <usart/usart.h>
#include "utils/uartstdio.h"

int  temp=0;

//*************************************UART0*****************************************************************
//                                UART0仅仅作为虚拟串口，仅使用UARTPrint();
void ConfigureUART0(void)
{
    //使能GPIOA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //使能UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //设置串口模式
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);//使用内部晶振作为时钟源
    UARTStdioConfig(0, 115200, 16000000);                                 //（串口号，波特率，时钟源频率，如果用系统时钟，则为SysCtlClockGet()函数）

    //使能FIFO
//  UARTFIFOEnable(UART0_BASE);
//  UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX4_8,UART_FIFO_RX1_8); //默认的发送FIFO深度为1/2，设置接受FIFO为1/8

      //使能UART2 中断
  IntEnable(INT_UART0);
  UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
//                                                           接收中断          接收超时中断

}
void
UART0_Send(uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
uint8_t ReciveData[16];
uint8_t ReciveData_i = 0;
void UART0_IntHandler(void)
{
    uint32_t ui32Status;
    //取得中断标志位
    ui32Status = UARTIntStatus(UART0_BASE, true);
   //清楚中断标志位
    UARTIntClear(UART0_BASE, ui32Status);
               //判断是否有有用信息
    ReciveData_i = 0;
    while(UARTCharsAvail(UART0_BASE))
    {
//        if((UARTCharGetNonBlocking(UART0_BASE))=='R')
//        {
//            ReciveData_i=0;
//            ReciveData[0] = 'R';
//        }
        ReciveData[ReciveData_i] =(UARTCharGetNonBlocking(UART0_BASE));
        ReciveData_i++;
    }
    if((ReciveData[0]=='R')&&(ReciveData[1]=='T'))
    {

       if(ReciveData[2]=='F')
       {
           temp =  (ReciveData[3]-48)*100+(ReciveData[4]-48)*10+(ReciveData[5]-48);
       }
       if(ReciveData[2]=='B')
      {
          temp =  (ReciveData[3]-48)*100+(ReciveData[4]-48)*10+(ReciveData[5]-48);
          temp = -temp;
      }
    }
  //  UART0_Send(ReciveData, 8);
}

//*************************************************************************************************************



//*****************************************UART1*************************************************************

//*************************************************************************************************************



//****************************************UART2****************************************************************
void ConfigureUART2(void)
{
    //使能GPIOD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //使能UART2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    //unlock
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0x80;
    //设置串口模式
    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    UARTConfigSetExpClk(UART2_BASE,SysCtlClockGet(), 115200,
                                    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                     UART_CONFIG_PAR_NONE));

    //使能FIFO
        UARTFIFOEnable(UART2_BASE);
        UARTFIFOLevelSet(UART2_BASE,UART_FIFO_TX4_8,UART_FIFO_RX1_8); //默认的发送FIFO深度为1/2，设置接受FIFO为1/8

    //使能UART2 中断
        IntEnable(INT_UART2);
        UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
}

void UART2_Send(const uint8_t *pucBuffer, uint32_t ulCount)              //串口发送函数
{
    while(ulCount--)
    {
        //将要发送的字符写进UART
        UARTCharPutNonBlocking(UART2_BASE, *pucBuffer++);

    }
}

void UART2_IntHandler(void)
{
    //uint8_t buffer=' ';
    uint8_t buffer;
    uint8_t a=0;
    uint32_t ui32Status;
    //取得中断标志位
    ui32Status = UARTIntStatus(UART2_BASE, true);
   //清楚中断标志位
    UARTIntClear(UART2_BASE, ui32Status);
               //判断是否有有用信息
    while(UARTCharsAvail(UART2_BASE))
    {
      buffer =(uint8_t)(UARTCharGetNonBlocking(UART2_BASE));
      rx_buffer_2[a]=buffer;
      a++;
    }
}
//****************************************************************************************************************

