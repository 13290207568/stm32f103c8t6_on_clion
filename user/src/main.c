#include "stm32f10x_rcc.h"
#include "Delay.h"
#include "OLED.h"

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init.GPIO_Pin = GPIO_Pin_13;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &gpio_init);
    gpio_init.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOA, &gpio_init);
    /*模块初始化*/
    OLED_Init(); //OLED初始化
    /*OLED显示*/
    OLED_ShowChar(1, 1, 'A'); //1行1列显示字符A

    OLED_ShowString(1, 3, "HelloWorld!"); //1行3列显示字符串HelloWorld!

    //	OLED_ShowNum(2, 1, ioa, 5);			//2行1列显示十进制数字12345，长度为5

    //	OLED_ShowSignedNum(2, 7, -66, 2);		//2行7列显示有符号十进制数字-66，长度为2

    OLED_ShowHexNum(3, 1, 0xBA55, 4); //3行1列显示十六进制数字0xA5A5，长度为4

    //	OLED_ShowBinNum(4, 1, 0xAA55, 16);		//4行1列显示二进制数字0xA5A5，长度为16
    //											//C语言无法直接写出二进制数字，故需要用十六进制表示

    u16 ioa = 0x0001;
    while (1)
    {
        if (ioa == 0x0080)
        {
            ioa = 0x0001;
        }
        else
        {
            ioa <<= 1;
        }
        GPIO_Write(GPIOA, ~ioa);
        Delay_ms(100);
        GPIO_SetBits(GPIOC,GPIO_Pin_13);
        Delay_ms(100);
        GPIO_ResetBits(GPIOC,GPIO_Pin_13);
        //		OLED_ShowChar(3, 1, 'A');				//1行1列显示字符A
        //		OLED_ShowNum(2, 1, ioa, 5);
        OLED_ShowHexNum(3, 1, ioa, 4); //3行1列显示十六进制数字0xA5A5，长度为4
        //		OLED_ShowSignedNum(2, 7, -66, 2);
        OLED_ShowBinNum(4, 1, ioa, 8); //4行1列显示二进制数字0xA5A5，长度为16
        //C语言无法直接写出二进制数字，故需要用十六进制表示
    }
    return 0;
}
