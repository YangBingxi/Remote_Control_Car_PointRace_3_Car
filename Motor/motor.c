
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
}


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
void SetMotor_Four(uint8_t Direction)
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
void SetMotor_Eight(uint8_t Direction)
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

