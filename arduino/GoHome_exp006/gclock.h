/*
  gclock.h - GCLK Library for Microchip ATSAMD21 (Cortex®-M0+)
 
  Copyright (c) 2020 Sasapea's Lab. All right reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef __GCLOCK_H
#define __GCLOCK_H
 
#include <stdint.h>
#include <stdbool.h>
#include <sam.h>
 
//
// Port Define for Seeeduino XIAO
//
#ifdef SEEED_XIAO_M0
  #define GCLOCK_PIN_D2 GCLOCK_PIN_PA10
  #define GCLOCK_PIN_D3 GCLOCK_PIN_PA11
#endif
 
#define GCLOCK_PIN_PA10 IOBUS_PIN('A', 10)
#define GCLOCK_PIN_PA11 IOBUS_PIN('A', 11)
#define GCLOCK_PIN_PA14 IOBUS_PIN('A', 14)
#define GCLOCK_PIN_PA15 IOBUS_PIN('A', 15)
#define GCLOCK_PIN_PA16 IOBUS_PIN('A', 16)
#define GCLOCK_PIN_PA17 IOBUS_PIN('A', 17)
#define GCLOCK_PIN_PA20 IOBUS_PIN('A', 20)
#define GCLOCK_PIN_PA21 IOBUS_PIN('A', 21)
#define GCLOCK_PIN_PA22 IOBUS_PIN('A', 22)
#define GCLOCK_PIN_PA23 IOBUS_PIN('A', 23)
#define GCLOCK_PIN_PA27 IOBUS_PIN('A', 27)
#define GCLOCK_PIN_PA28 IOBUS_PIN('A', 28)
#define GCLOCK_PIN_PA30 IOBUS_PIN('A', 30)
#define GCLOCK_PIN_PB10 IOBUS_PIN('B', 10)
#define GCLOCK_PIN_PB11 IOBUS_PIN('B', 11)
#define GCLOCK_PIN_PB12 IOBUS_PIN('B', 12)
#define GCLOCK_PIN_PB13 IOBUS_PIN('B', 13)
#define GCLOCK_PIN_PB14 IOBUS_PIN('B', 14)
#define GCLOCK_PIN_PB15 IOBUS_PIN('B', 15)
#define GCLOCK_PIN_PB16 IOBUS_PIN('B', 16)
#define GCLOCK_PIN_PB17 IOBUS_PIN('B', 17)
#define GCLOCK_PIN_PB22 IOBUS_PIN('B', 22)
#define GCLOCK_PIN_PB23 IOBUS_PIN('B', 23)
 
typedef enum
{
  GCLOCK_ID_DFLL48       = GCLK_CLKCTRL_ID_DFLL48_Val,
  GCLOCK_ID_FDPLL        = GCLK_CLKCTRL_ID_FDPLL_Val,
  GCLOCK_ID_FDPLL32K     = GCLK_CLKCTRL_ID_FDPLL32K_Val,
  GCLOCK_ID_WDT          = GCLK_CLKCTRL_ID_WDT_Val,
  GCLOCK_ID_RTC          = GCLK_CLKCTRL_ID_RTC_Val,
  GCLOCK_ID_EIC          = GCLK_CLKCTRL_ID_EIC_Val,
  GCLOCK_ID_USB          = GCLK_CLKCTRL_ID_USB_Val,
  GCLOCK_ID_EVSYS_0      = GCLK_CLKCTRL_ID_EVSYS_0_Val,
  GCLOCK_ID_EVSYS_1      = GCLK_CLKCTRL_ID_EVSYS_1_Val,
  GCLOCK_ID_EVSYS_2      = GCLK_CLKCTRL_ID_EVSYS_2_Val,
  GCLOCK_ID_EVSYS_3      = GCLK_CLKCTRL_ID_EVSYS_3_Val,
  GCLOCK_ID_EVSYS_4      = GCLK_CLKCTRL_ID_EVSYS_4_Val,
  GCLOCK_ID_EVSYS_5      = GCLK_CLKCTRL_ID_EVSYS_5_Val,
  GCLOCK_ID_EVSYS_6      = GCLK_CLKCTRL_ID_EVSYS_6_Val,
  GCLOCK_ID_EVSYS_7      = GCLK_CLKCTRL_ID_EVSYS_7_Val,
  GCLOCK_ID_EVSYS_8      = GCLK_CLKCTRL_ID_EVSYS_8_Val,
  GCLOCK_ID_EVSYS_9      = GCLK_CLKCTRL_ID_EVSYS_9_Val,
  GCLOCK_ID_EVSYS_10     = GCLK_CLKCTRL_ID_EVSYS_10_Val,
  GCLOCK_ID_EVSYS_11     = GCLK_CLKCTRL_ID_EVSYS_11_Val,
  GCLOCK_ID_SERCOMX_SLOW = GCLK_CLKCTRL_ID_SERCOMX_SLOW_Val,
  GCLOCK_ID_SERCOM0_CORE = GCLK_CLKCTRL_ID_SERCOM0_CORE_Val,
  GCLOCK_ID_SERCOM1_CORE = GCLK_CLKCTRL_ID_SERCOM1_CORE_Val,
  GCLOCK_ID_SERCOM2_CORE = GCLK_CLKCTRL_ID_SERCOM2_CORE_Val,
  GCLOCK_ID_SERCOM3_CORE = GCLK_CLKCTRL_ID_SERCOM3_CORE_Val,
  GCLOCK_ID_SERCOM4_CORE = GCLK_CLKCTRL_ID_SERCOM4_CORE_Val,
  GCLOCK_ID_SERCOM5_CORE = GCLK_CLKCTRL_ID_SERCOM5_CORE_Val,
  GCLOCK_ID_TCC0_TCC1    = GCLK_CLKCTRL_ID_TCC0_TCC1_Val,
  GCLOCK_ID_TCC2_TC3     = GCLK_CLKCTRL_ID_TCC2_TC3_Val,
  GCLOCK_ID_TC4_TC5      = GCLK_CLKCTRL_ID_TC4_TC5_Val,
  GCLOCK_ID_TC6_TC7      = GCLK_CLKCTRL_ID_TC6_TC7_Val,
  GCLOCK_ID_ADC          = GCLK_CLKCTRL_ID_ADC_Val,
  GCLOCK_ID_AC_DIG       = GCLK_CLKCTRL_ID_AC_DIG_Val,
  GCLOCK_ID_AC_ANA       = GCLK_CLKCTRL_ID_AC_ANA_Val,
  GCLOCK_ID_DAC          = GCLK_CLKCTRL_ID_DAC_Val,
  GCLOCK_ID_PTC          = GCLK_CLKCTRL_ID_PTC_Val,
  GCLOCK_ID_I2S_0        = GCLK_CLKCTRL_ID_I2S_0_Val,
  GCLOCK_ID_I2S_1        = GCLK_CLKCTRL_ID_I2S_1_Val,
} GCLOCK_ID;
 
typedef enum
{
  GCLOCK_GEN_GCLK0     = GCLK_CLKCTRL_GEN_GCLK0_Val, //  8 division factor bits - DIV[ 7:0]
  GCLOCK_GEN_GCLK1     = GCLK_CLKCTRL_GEN_GCLK1_Val, // 16 division factor bits - DIV[15:0]
  GCLOCK_GEN_GCLK2     = GCLK_CLKCTRL_GEN_GCLK2_Val, //  5 division factor bits - DIV[ 4:0]
  GCLOCK_GEN_GCLK3     = GCLK_CLKCTRL_GEN_GCLK3_Val, //  8 division factor bits - DIV[ 7:0]
  GCLOCK_GEN_GCLK4     = GCLK_CLKCTRL_GEN_GCLK4_Val, //  8 division factor bits - DIV[ 7:0]
  GCLOCK_GEN_GCLK5     = GCLK_CLKCTRL_GEN_GCLK5_Val, //  8 division factor bits - DIV[ 7:0]
  GCLOCK_GEN_GCLK6     = GCLK_CLKCTRL_GEN_GCLK6_Val, //  8 division factor bits - DIV[ 7:0]
  GCLOCK_GEN_GCLK7     = GCLK_CLKCTRL_GEN_GCLK7_Val, //  8 division factor bits - DIV[ 7:0]
  GCLOCK_GEN_NONE      = GCLOCK_GEN_GCLK7 + 1,
  //
  // for Seeeduino XIAO (see. startup.c)
  //
  GCLOCK_GEN_MAIN      = GCLK_CLKCTRL_GEN_GCLK0_Val,
  GCLOCK_GEN_XOSC32K   = GCLK_CLKCTRL_GEN_GCLK1_Val,
  GCLOCK_GEN_OSCULP32K = GCLK_CLKCTRL_GEN_GCLK2_Val,
  GCLOCK_GEN_OSC8M     = GCLK_CLKCTRL_GEN_GCLK3_Val,
} GCLOCK_GEN;
 
typedef enum
{
  GCLOCK_SRC_XOSC      = GCLK_GENCTRL_SRC_XOSC_Val,
  GCLOCK_SRC_GCLKIN    = GCLK_GENCTRL_SRC_GCLKIN_Val,
  GCLOCK_SRC_GCLKGEN1  = GCLK_GENCTRL_SRC_GCLKGEN1_Val,  // GCLOCK_GEN_XOSC32K->
  GCLOCK_SRC_OSCULP32K = GCLK_GENCTRL_SRC_OSCULP32K_Val, // ->GCLOCK_GEN_OSCULP32K
  GCLOCK_SRC_OSC32K    = GCLK_GENCTRL_SRC_OSC32K_Val,
  GCLOCK_SRC_XOSC32K   = GCLK_GENCTRL_SRC_XOSC32K_Val,   // ->GCLOCK_GEN_XOSC32K
  GCLOCK_SRC_OSC8M     = GCLK_GENCTRL_SRC_OSC8M_Val,     // ->GCLOCK_GEN_OSC8M
  GCLOCK_SRC_DFLL48M   = GCLK_GENCTRL_SRC_DFLL48M_Val,   // ->GCLOCK_GEN_MAIN
  GCLOCK_SRC_FDPLL     = GCLK_GENCTRL_SRC_FDPLL_Val,
  GCLOCK_SRC_NONE      = GCLOCK_SRC_FDPLL + 1,
} GCLOCK_SRC;
 
class GClock
{
  public:
 
    static void begin(void);
    static void select(GCLOCK_ID id, GCLOCK_GEN gen);
    static void control(GCLOCK_ID id, bool enable);
    static GCLOCK_GEN config(GCLOCK_SRC src, uint8_t divider = 0, bool divsel = false,
      bool idc = false, GCLOCK_GEN reqid = GCLOCK_GEN_NONE);
    static bool output(uint32_t pin, GCLOCK_SRC src, uint8_t divider = 0, bool divsel = false,
      bool idc = false, bool runstdby = false, bool oov = false);
};
 
#endif
