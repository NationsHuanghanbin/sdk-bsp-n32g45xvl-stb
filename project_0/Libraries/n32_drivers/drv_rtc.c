/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_rtc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "board.h"
#include <sys/time.h>
#include <rtdevice.h>

#ifdef BSP_USING_RTC

uint32_t SynchPrediv, AsynchPrediv;

static rt_err_t n32_rtc_get_timeval(struct timeval *tv)
{
    struct tm tm_new = {0};
    RTC_DateType  RTC_DateStructure;
    RTC_TimeType  RTC_TimeStructure;

    RTC_GetTime(RTC_FORMAT_BIN, &RTC_TimeStructure);
    RTC_GetDate(RTC_FORMAT_BIN, &RTC_DateStructure);

    tm_new.tm_sec  = RTC_TimeStructure.Seconds;
    tm_new.tm_min  = RTC_TimeStructure.Minutes;
    tm_new.tm_hour = RTC_TimeStructure.Hours;
    tm_new.tm_wday = RTC_DateStructure.WeekDay;
    tm_new.tm_mday = RTC_DateStructure.Date;
    tm_new.tm_mon  = RTC_DateStructure.Month - 1;
    tm_new.tm_year = RTC_DateStructure.Year + 100;

    tv->tv_sec     = timegm(&tm_new);

    return RT_EOK;
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
    struct tm time = {0};
    RTC_DateType  RTC_DateStructure={0};
    RTC_TimeType  RTC_TimeStructure={0};

    gmtime_r(&time_stamp, &time);
    if(time.tm_year < 100)
    {
        return -RT_ERROR;
    }

    RTC_TimeStructure.Seconds = time.tm_sec ;
    RTC_TimeStructure.Minutes = time.tm_min ;
    RTC_TimeStructure.Hours   = time.tm_hour;
    RTC_DateStructure.Date    = time.tm_mday;
    RTC_DateStructure.Month   = time.tm_mon + 1 ;
    RTC_DateStructure.Year    = time.tm_year - 100;
    RTC_DateStructure.WeekDay = time.tm_wday + 1;

    /* Configure the RTC date register */
    if(RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStructure) != SUCCESS)
    {
        return -RT_ERROR;
    }

    /* Configure the RTC time register */
    if(RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStructure) != SUCCESS)
    {
        return -RT_ERROR;
    }

    rt_kprintf("set rtc time.\n");

    return RT_EOK;
}

static rt_err_t rt_rtc_config(void)
{
    RTC_InitType  RTC_InitStructure;

    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv  = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat   = RTC_24HOUR_FORMAT;

    /* Check on RTC init */
    if(RTC_Init(&RTC_InitStructure) != SUCCESS)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t n32_rtc_init(void)
{
    /* Enable the PWR clock */
#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR | RCC_APB1_PERIPH_BKP, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
#endif
	
    /* Allow access to RTC */
    PWR_BackupAccessEnable(ENABLE);

#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    /* Reset Backup */
    BKP_DeInit();
#endif
	
    /* Disable RTC clock */
    RCC_EnableRtcClk(DISABLE);
	
#ifdef BSP_RTC_USING_HSE
    /* Enable the HSE OSC */
    RCC_EnableLsi(DISABLE);
    RCC_ConfigHse(RCC_HSE_ENABLE);
    while (RCC_WaitHseStable() == ERROR)
    {
    }
#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    rt_kprintf("rtc clock source is set hse/128!\n");
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV128);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    rt_kprintf("rtc clock source is set hse/32!\n");
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV32);
#endif
		
#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    SynchPrediv  = 0x1E8;  // 8M/128 = 62.5KHz
    AsynchPrediv = 0x7F;   // value range: 0-7F
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    SynchPrediv  = 0x7A0; // 8M/32 = 250KHz
    AsynchPrediv = 0x7F;  // value range: 0-7F
#endif
#endif /* BSP_RTC_USING_HSE */

#ifdef BSP_RTC_USING_LSE
    rt_kprintf("rtc clock source is set lse!\n");
    /* Enable the LSE OSC32_IN PC14 */
    RCC_EnableLsi(DISABLE); // LSI is turned off here to ensure that only one clock is turned on

#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    RCC_ConfigLse(RCC_LSE_ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSERD) == RESET)
    {
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    RCC_ConfigLse(RCC_LSE_ENABLE,0x28);
    while (RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD) == RESET)
    {
    }
#endif
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSE);

    SynchPrediv  = 0xFF; // 32.768KHz
    AsynchPrediv = 0x7F; // value range: 0-7F
#endif /* BSP_RTC_USING_LSE */

#ifdef BSP_RTC_USING_LSI
    rt_kprintf("rtc clock source is set lsi!\n");
    /* Enable the LSI OSC */
    RCC_EnableLsi(ENABLE);
#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
    {
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    while (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_LSIRD) == RESET)
    {
    }
#endif
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
		
#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    SynchPrediv  = 0x136; // 39.64928KHz
    AsynchPrediv = 0x7F;  // value range: 0-7F
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    SynchPrediv  = 0x14A; // 41828Hz
    AsynchPrediv = 0x7F;  // value range: 0-7F
#endif
#endif /* BSP_RTC_USING_LSI */

    /* Enable the RTC Clock */
    RCC_EnableRtcClk(ENABLE);
    RTC_WaitForSynchro();

    if(rt_rtc_config() != RT_EOK)
    {
        rt_kprintf("rtc init failed.\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t n32_rtc_get_secs(time_t *sec)
{
    struct timeval tv;

    n32_rtc_get_timeval(&tv);
    *(time_t *) sec = tv.tv_sec;

    rt_kprintf("RTC: get rtc_time %d.\n", *sec);

    return RT_EOK;
}

static rt_err_t n32_rtc_set_secs(time_t *sec)
{
    rt_err_t result = RT_EOK;

    if(set_rtc_time_stamp(*sec))
    {
        result = -RT_ERROR;
    }

    rt_kprintf("RTC: set rtc_time %d.\n", *sec);

    return result;
}

static const struct rt_rtc_ops n32_rtc_ops =
{
    n32_rtc_init,
    n32_rtc_get_secs,
    n32_rtc_set_secs,
    RT_NULL,
    RT_NULL,
    n32_rtc_get_timeval,
    RT_NULL,
};

static rt_rtc_dev_t n32_rtc_dev;

static int rt_hw_rtc_init(void)
{
    rt_err_t result;

    n32_rtc_dev.ops = &n32_rtc_ops;
    result = rt_hw_rtc_register(&n32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if(result != RT_EOK)
    {
        rt_kprintf("rtc register error code: %d.\n", result);
        return result;
    }
    else
    {
        rt_kprintf("rtc initialize success.\n");
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);
#endif /* BSP_USING_RTC */

