#include <usart/usart.h>
#include "utils/uartstdio.h"

int  temp=0;

//*************************************UART0*****************************************************************
//                                UART0������Ϊ���⴮�ڣ���ʹ��UARTPrint();
void ConfigureUART0(void)
{
    //ʹ��GPIOA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //ʹ��UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //���ô���ģʽ
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);//ʹ���ڲ�������Ϊʱ��Դ
    UARTStdioConfig(0, 115200, 16000000);                                 //�����ںţ������ʣ�ʱ��ԴƵ�ʣ������ϵͳʱ�ӣ���ΪSysCtlClockGet()������

    //ʹ��FIFO
//  UARTFIFOEnable(UART0_BASE);
//  UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX4_8,UART_FIFO_RX1_8); //Ĭ�ϵķ���FIFO���Ϊ1/2�����ý���FIFOΪ1/8

      //ʹ��UART2 �ж�
  IntEnable(INT_UART0);
  UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
//                                                           �����ж�          ���ճ�ʱ�ж�

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
    //ȡ���жϱ�־λ
    ui32Status = UARTIntStatus(UART0_BASE, true);
   //����жϱ�־λ
    UARTIntClear(UART0_BASE, ui32Status);
               //�ж��Ƿ���������Ϣ
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
    //ʹ��GPIOD
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //ʹ��UART2
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    //unlock
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0x80;
    //���ô���ģʽ
    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    UARTConfigSetExpClk(UART2_BASE,SysCtlClockGet(), 115200,
                                    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                     UART_CONFIG_PAR_NONE));

    //ʹ��FIFO
        UARTFIFOEnable(UART2_BASE);
        UARTFIFOLevelSet(UART2_BASE,UART_FIFO_TX4_8,UART_FIFO_RX1_8); //Ĭ�ϵķ���FIFO���Ϊ1/2�����ý���FIFOΪ1/8

    //ʹ��UART2 �ж�
        IntEnable(INT_UART2);
        UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
}

void UART2_Send(const uint8_t *pucBuffer, uint32_t ulCount)              //���ڷ��ͺ���
{
    while(ulCount--)
    {
        //��Ҫ���͵��ַ�д��UART
        UARTCharPutNonBlocking(UART2_BASE, *pucBuffer++);

    }
}

void UART2_IntHandler(void)
{
    //uint8_t buffer=' ';
    uint8_t buffer;
    uint8_t a=0;
    uint32_t ui32Status;
    //ȡ���жϱ�־λ
    ui32Status = UARTIntStatus(UART2_BASE, true);
   //����жϱ�־λ
    UARTIntClear(UART2_BASE, ui32Status);
               //�ж��Ƿ���������Ϣ
    while(UARTCharsAvail(UART2_BASE))
    {
      buffer =(uint8_t)(UARTCharGetNonBlocking(UART2_BASE));
      rx_buffer_2[a]=buffer;
      a++;
    }
}
//****************************************************************************************************************

