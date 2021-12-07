/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */


#include <rtthread.h>
#include <rtdevice.h>
#include "n32g45x.h"
#include "n32_msp.h"

#ifdef BSP_USING_UART
void n32_msp_usart_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    USART_Module *USARTx = (USART_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_UART1
    if(USART1 == USARTx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_9;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_UART2
    if(USART2 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_2;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_3;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_UART3
    if(USART3 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USART3, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_UART4
    if(UART4 == USARTx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_UART4, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_10;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SERIAL */

#ifdef BSP_USING_SPI
void n32_msp_spi_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    SPI_Module *SPIx = (SPI_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_SPI1
    if(SPI1 == SPIx)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_4;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_SPI2
    if(SPI2 == SPIx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_13 | GPIO_PIN_15;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_14;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
    /* Add others */
}
#endif /* BSP_USING_SPI */

#ifdef BSP_USING_SDIO
void n32_msp_sdio_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStructure;
    SDIO_Module *SDIOx = (SDIO_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStructure);
    GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if(SDIO == SDIOx)
    {
        /* if used dma ... */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);

        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_SDIO, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD, ENABLE);
        GPIO_InitCtlStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStructure);

        GPIO_InitCtlStructure.Pin = GPIO_PIN_2;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitCtlStructure);
    }
}
#endif /* BSP_USING_SDIO */

#ifdef BSP_USING_PWM
void n32_msp_tim_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStructure;
    GPIO_InitStruct(&GPIO_InitCtlStructure);
    TIM_Module *TIMx = (TIM_Module *)Instance;

    if(TIMx == TIM1)
    {
        /* TIM1 clock enable */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
        /* GPIOA clock enable */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

        /* GPIOA Configuration:TIM1 Channel1 and Channel4 as alternate function push-pull */
        GPIO_InitCtlStructure.Pin = GPIO_PIN_8 | GPIO_PIN_11;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
    }

    if(TIMx == TIM2)
    {
        /* TIM2 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
        /* GPIOA clock enable */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

        /* GPIOA Configuration:TIM2 Channel1 and Channel2 as alternate function push-pull */
        GPIO_InitCtlStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);
    }

    if(TIMx == TIM3)
    {
        /* TIM3 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
        /* GPIOA clock enable */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_GPIOB, ENABLE);

        GPIO_InitCtlStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        GPIO_InitCtlStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStructure);

        GPIO_InitCtlStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStructure);
    }
}
#endif /* BSP_USING_PWM */

#ifdef BSP_USING_ADC
void n32_msp_adc_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    GPIO_InitStruct(&GPIO_InitCtlStruct);
    ADC_Module *ADCx = (ADC_Module *)Instance;

#ifdef BSP_USING_ADC1
    if(ADCx == ADC1)
    {
        /* ADC1 & GPIO clock enable */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);
        ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV8);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_InitCtlStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
        GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
    }
#endif

#ifdef BSP_USING_ADC2
    if(ADCx == ADC2)
    {
        /* ADC2 & GPIO clock enable */
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC2, ENABLE);
        ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB,RCC_ADCHCLK_DIV8);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

        /* Configure ADC Channel as analog input */
        GPIO_InitCtlStruct.Pin = GPIO_PIN_1;
        GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitCtlStruct);
    }
#endif
}
#endif /* BSP_USING_ADC */

#ifdef BSP_USING_HWTIMER
void n32_msp_hwtim_init(void *Instance)
{
    TIM_Module *TIMx = (TIM_Module *)Instance;

#ifdef BSP_USING_HWTIM3
    if(TIMx == TIM3)
    {
        /* TIM3 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM4
    if(TIMx == TIM4)
    {
        /* TIM4 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM5
    if(TIMx == TIM5)
    {
        /* TIM5 clock enable */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
    }
#endif

#ifdef BSP_USING_HWTIM6
        if(TIMx == TIM6)
        {
            /* TIM6 clock enable */
            RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
        }
#endif

#ifdef BSP_USING_HWTIM7
        if(TIMx == TIM7)
        {
            /* TIM7 clock enable */
            RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM7, ENABLE);
        }
#endif
}
#endif

#ifdef BSP_USING_CAN
void n32_msp_can_init(void *Instance)
{
    GPIO_InitType GPIO_InitCtlStruct;
    CAN_Module *CANx = (CAN_Module *)Instance;

    GPIO_InitStruct(&GPIO_InitCtlStruct);
    GPIO_InitCtlStruct.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef BSP_USING_CAN1
    if(CAN1 == CANx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN1, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_12;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_11;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitCtlStruct);
    }
#endif
#ifdef BSP_USING_CAN2
    if(CAN2 == CANx)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN2, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
        //        GPIO_PinsRemapConfig(AFIO_MAP6_CAN2_0001, ENABLE);
        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_6;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);

        GPIO_InitCtlStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitCtlStruct.Pin = GPIO_PIN_5;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitCtlStruct);
    }
#endif
}
#endif /* BSP_USING_CAN */

#ifdef RT_USING_FINSH
#include <finsh.h>
#if defined(BSP_USING_UART2) || defined(BSP_USING_UART3)
static void uart_test_rw(rt_device_t uartx, const char *name)
{
    if (uartx == NULL)
    {
        uartx = rt_device_find(name);
        rt_err_t err = rt_device_open(uartx, RT_DEVICE_FLAG_INT_RX|RT_DEVICE_FLAG_DMA_RX);
        RT_ASSERT(err == RT_EOK);
    }
    rt_device_write(uartx, 0, name, strlen(name));
    rt_device_write(uartx, 0, "\r\n", 2);
    uint8_t recv_buf[64] = {0x0};
    int ret = rt_device_read(uartx, 0, recv_buf, sizeof(recv_buf));
    if (ret != 0)
    {
        for (int i=0; i<ret; ++i)
            rt_kprintf("[%02x]", recv_buf[i]);
    }
    rt_device_write(uartx, 0, "\r\n", 2);
}
static void uart_test(void)
{
#ifdef BSP_USING_UART2
    static rt_device_t u2 = NULL;
    uart_test_rw(u2, "uart2");
#endif
#ifdef BSP_USING_UART2
    static rt_device_t u3 = NULL;
    uart_test_rw(u3, "uart3");
#endif
}
MSH_CMD_EXPORT(uart_test, uart_test)
#endif

#ifdef BSP_USING_ADC
#ifdef BSP_USING_ADC1
#define ADC_DEV_NAME        "adc1"
#else
#define ADC_DEV_NAME        "adc2"
#endif
#define REFER_VOLTAGE       3300
#define CONVERT_BITS        (1 << 12)
static int adc_vol_sample(int argc, char *argv[])
{
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;

    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    for (int i=6; i<=9; ++i)
    {
        ret = rt_adc_enable(adc_dev, i);
        value = rt_adc_read(adc_dev, i);
        rt_kprintf("ch=[%d] the value is :[%d] \n", i, value);
        vol = value * REFER_VOLTAGE / CONVERT_BITS;
        rt_kprintf("ch=[%d] the voltage is :[%d] \n", i, vol);
    }

    return ret;
}
MSH_CMD_EXPORT(adc_vol_sample, adc voltage convert sample);
#endif

#ifdef BSP_USING_HWTIMER
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("timer name is :%s.\n", dev->parent.name);
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}
static int hwtimer_init(const char *name)
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;
    hw_dev = rt_device_find(name);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", name);
        return RT_ERROR;
    }
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", name);
        return ret;
    }
    rt_device_set_rx_indicate(hw_dev, timeout_cb);
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }
    timeout_s.sec = 5;
    timeout_s.usec = 0;
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    rt_thread_mdelay(3500);

    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}

static int hwtimer_sample(int argc, char *argv[])
{
#ifdef BSP_USING_HWTIM6
    hwtimer_init("timer6");
#endif
#ifdef BSP_USING_HWTIM7
    hwtimer_init("timer7");
#endif
    return RT_EOK;
}
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
#endif

#ifdef RT_USING_PWM
static int pwm_set_test(const char *name, int ch,
                        rt_uint32_t period, rt_uint32_t pulse)
{
    struct rt_device_pwm *pwm_dev = (struct rt_device_pwm *)rt_device_find(name);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", name);
        return RT_ERROR;
    }
    rt_pwm_set(pwm_dev, ch, period, pulse);
    rt_pwm_enable(pwm_dev, ch);
    return RT_EOK;
}
#define PWM_TEST_NAME_CH_1 "tim3pwm1"
#define PWM_TEST_NAME_CH_2 "tim3pwm2"
#define PWM_TEST_NAME_CH_3 "tim3pwm3"
#define PWM_TEST_NAME_CH_4 "tim3pwm4"
static int pwm_led_sample(int argc, char *argv[])
{
    pwm_set_test(PWM_TEST_NAME_CH_1, 1, 1000, 200);
    pwm_set_test(PWM_TEST_NAME_CH_2, 2, 1000, 400);
    pwm_set_test(PWM_TEST_NAME_CH_3, 3, 1000, 600);
    pwm_set_test(PWM_TEST_NAME_CH_4, 4, 1000, 700);
    return RT_EOK;
}
MSH_CMD_EXPORT(pwm_led_sample, pwm sample);
static int pwm_led_sample_off(int argc, char *argv[])
{
    struct rt_device_pwm *pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_TEST_NAME_CH_1);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_TEST_NAME_CH_1);
        return RT_ERROR;
    }
    rt_pwm_disable(pwm_dev, 1);
    return RT_EOK;
}
MSH_CMD_EXPORT(pwm_led_sample_off, pwm sample off);
#endif

#endif


