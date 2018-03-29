
#include <Motor/motor.h>

void Motor_Configure(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //���һ���GPIO����
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);     //1
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);     //2
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);     //3
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);     //4

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //��������GPIO����
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);     //1
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);     //2
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);     //3
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0);     //4
}


//Motor0 Setting
/**
 * ����ʱ��
 * һ��1.8�� 200��/Ȧ
 * A->B->C->D->A->B->����
 *��תΪ��D->...->A
             |   A     B     C     D
            _|________________________
        A    |   1     0     0     0
        A-   |   0     1     0     0
        B    |   0     0     1     0
        B-   |   0     0     0     1
**/
void SetMotor_Four_Motor0(uint8_t Direction)
{
    static uint8_t i = 0;
    if(Direction>0)     //˳��
    {
        switch(i)
           {
               case 0:
               {
                   A1(1);B1(0);A2(0);B2(0);
                   break;
               }

               case 1:
               {
                   A1(0);B1(1);A2(0);B2(0);
                   break;
               }

               case 2:
               {
                   A1(0);B1(0);A2(1);B2(0);
                   break;
               }

               case 3:
               {
                   A1(0);B1(0);A2(0);B2(1);
                   break;
               }
           }
    }
    else                //����
    {
        switch(i)
           {
               case 3:
               {
                   A1(1);B1(0);A2(0);B2(0);
                   break;
               }

               case 2:
               {
                   A1(0);B1(1);A2(0);B2(0);
                   break;
               }

               case 1:
               {
                   A1(0);B1(0);A2(1);B2(0);
                   break;
               }

               case 0:
               {
                   A1(0);B1(0);A2(0);B2(1);
                   break;
               }
           }
    }
    i++;
    if(i>3)
        i=0;

}

/**
 * ����ʱ��
 * һ��0.9�� 400��/Ȧ
 * A->B->C->D->E->F->G->H->A->B->����
 *��תΪ��H->...->A
             |   A     B     C     D     E     F     G     H
            _|_______________________________________________
        A    |   1     1     0     0     0     0     0     1
        A-   |   0     0     0     1     1     1     0     0
        B    |   0     1     1     1     0     0     0     0
        B-   |   0     0     0     0     0     1     1     1
**/
void SetMotor_Eight_Motor0(uint8_t Direction)
{
    static uint8_t i = 0;
    if (Direction>0)    //˳��
    {
        switch(i)
        {
            case 0:
            {
                A1(1);B1(0);A2(0);B2(0);
                break;
            }

            case 1:
            {
                A1(1);B1(1);A2(0);B2(0);
                break;
            }

            case 2:
            {
                A1(0);B1(1);A2(0);B2(0);
                break;
            }

            case 3:
            {
                A1(0);B1(1);A2(1);B2(0);
                break;
            }
            case 4:
            {
                A1(0);B1(0);A2(1);B2(0);
                break;
            }

            case 5:
            {
                A1(0);B1(0);A2(1);B2(1);
                break;
            }

            case 6:
            {
                A1(0);B1(0);A2(0);B2(1);
                break;
            }

            case 7:
            {
                A1(1);B1(0);A2(0);B2(1);
                break;
            }

        }
    }
    else                   //����
    {
        switch(i)
         {
             case 7:
             {
                 A1(1);B1(0);A2(0);B2(0);
                 break;
             }

             case 6:
             {
                 A1(1);B1(1);A2(0);B2(0);
                 break;
             }

             case 5:
             {
                 A1(0);B1(1);A2(0);B2(0);
                 break;
             }

             case 4:
             {
                 A1(0);B1(1);A2(1);B2(0);
                 break;
             }
             case 3:
             {
                 A1(0);B1(0);A2(1);B2(0);
                 break;
             }

             case 2:
             {
                 A1(0);B1(0);A2(1);B2(1);
                 break;
             }

             case 1:
             {
                 A1(0);B1(0);A2(0);B2(1);
                 break;
             }

             case 0:
             {
                 A1(1);B1(0);A2(0);B2(1);
                 break;
             }

         }
    }

    i++;
    if(i==8)i=0;
}

//Motor1 Setting
/**
 * ����ʱ��
 * һ��1.8�� 200��/Ȧ
 * A->B->C->D->A->B->����
 *��תΪ��D->...->A
             |   A     B     C     D
            _|________________________
        A    |   1     0     0     0
        A-   |   0     1     0     0
        B    |   0     0     1     0
        B-   |   0     0     0     1
**/
void SetMotor_Four_Motor1(uint8_t Direction)
{
    static uint8_t i = 0;
    if(Direction>0)     //˳��
    {
        switch(i)
           {
               case 0:
               {
                   C1(1);D1(0);C2(0);D2(0);
                   break;
               }

               case 1:
               {
                   C1(0);D1(1);C2(0);D2(0);
                   break;
               }

               case 2:
               {
                   C1(0);D1(0);C2(1);D2(0);
                   break;
               }

               case 3:
               {
                   C1(0);D1(0);C2(0);D2(1);
                   break;
               }
           }
    }
    else                //����
    {
        switch(i)
           {
               case 3:
               {
                   C1(1);D1(0);C2(0);D2(0);
                   break;
               }

               case 2:
               {
                   C1(0);D1(1);C2(0);D2(0);
                   break;
               }

               case 1:
               {
                   C1(0);D1(0);C2(1);D2(0);
                   break;
               }

               case 0:
               {
                   C1(0);D1(0);C2(0);D2(1);
                   break;
               }
           }
    }
    i++;
    if(i>3)
        i=0;

}

/**
 * ����ʱ��
 * һ��0.9�� 400��/Ȧ
 * A->B->C->D->E->F->G->H->A->B->����
 *��תΪ��H->...->A
             |   A     B     C     D     E     F     G     H
            _|_______________________________________________
        A    |   1     1     0     0     0     0     0     1
        A-   |   0     0     0     1     1     1     0     0
        B    |   0     1     1     1     0     0     0     0
        B-   |   0     0     0     0     0     1     1     1
**/
void SetMotor_Eight_Motor1(uint8_t Direction)
{
    static uint8_t i = 0;
    if (Direction>0)    //˳��
    {
        switch(i)
        {
            case 0:
            {
                C1(1);D1(0);C2(0);D2(0);
                break;
            }

            case 1:
            {
                C1(1);D1(1);C2(0);D2(0);
                break;
            }

            case 2:
            {
                C1(0);D1(1);C2(0);D2(0);
                break;
            }

            case 3:
            {
                C1(0);D1(1);C2(1);D2(0);
                break;
            }
            case 4:
            {
                C1(0);D1(0);C2(1);D2(0);
                break;
            }

            case 5:
            {
                C1(0);D1(0);C2(1);D2(1);
                break;
            }

            case 6:
            {
                C1(0);D1(0);C2(0);D2(1);
                break;
            }

            case 7:
            {
                C1(1);D1(0);C2(0);D2(1);
                break;
            }

        }
    }
    else                   //����
    {
        switch(i)
         {
             case 7:
             {
                 C1(1);D1(0);C2(0);D2(0);
                 break;
             }

             case 6:
             {
                 C1(1);D1(1);C2(0);D2(0);
                 break;
             }

             case 5:
             {
                 C1(0);D1(1);C2(0);D2(0);
                 break;
             }

             case 4:
             {
                 C1(0);D1(1);C2(1);D2(0);
                 break;
             }
             case 3:
             {
                 C1(0);D1(0);C2(1);D2(0);
                 break;
             }

             case 2:
             {
                 C1(0);D1(0);C2(1);D2(1);
                 break;
             }

             case 1:
             {
                 C1(0);D1(0);C2(0);D2(1);
                 break;
             }

             case 0:
             {
                 C1(1);D1(0);C2(0);D2(1);
                 break;
             }

         }
    }

    i++;
    if(i==8)i=0;
}

