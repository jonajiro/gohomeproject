/*
  gclock.cpp - GCLK Library for Microchip ATSAMD21 (Cortex®-M0+)
 
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
#include "gclock.h"
#include "IOBUS.h"
 
#define DIVIDER(sel, div) (uint8_t)((sel) ? 1 << ((div) + 1) : ((div) == 0 ? 1 : (div)))
#define NONE 0xFF
 
// for SAMD21GJ
static const uint8_t GCLK_IO[] =
{
  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 0x04, 0x05, NONE, NONE, 0x00, 0x01,
  0x02, 0x03, NONE, NONE, 0x04, 0x05, 0x06, 0x07, NONE, NONE, NONE, 0x00, 0x00, NONE, 0x00, NONE,
  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 0x04, 0x05, 0x06, 0x07, 0x00, 0x01,
  0x02, 0x03, NONE, NONE, NONE, NONE, 0x00, 0x01, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
};
 
static GCLOCK_GEN _gen[GCLOCK_ID_I2S_1 - GCLOCK_ID_DFLL48 + 1];
 
static void sync(void)
{
  while (GCLK->STATUS.bit.SYNCBUSY)
    continue;
}
 
void GClock::begin(void)
{
  for (uint32_t i = 0; i < sizeof(_gen) / sizeof(_gen[0]); ++i)
    _gen[i] = GCLOCK_GEN_GCLK0;
  select(GCLOCK_ID_WDT, GCLOCK_GEN_OSCULP32K);
  select(GCLOCK_ID_RTC, GCLOCK_GEN_XOSC32K  );
}
 
void GClock::select(GCLOCK_ID id, GCLOCK_GEN gen)
{
  _gen[id] = gen;
}
 
void GClock::control(GCLOCK_ID id, bool enable)
{
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(id) | GCLK_CLKCTRL_GEN(_gen[id]) | (enable ? GCLK_CLKCTRL_CLKEN : 0);
  sync();
}
 
GCLOCK_GEN GClock::config(GCLOCK_SRC src, uint8_t divider, bool divsel, bool idc, GCLOCK_GEN reqid)
{
  GCLOCK_GEN id = GCLOCK_GEN_NONE;
  for (uint32_t i = GCLOCK_GEN_GCLK0; i <= GCLOCK_GEN_GCLK7; ++i)
  {
    if ((reqid != GCLOCK_GEN_NONE) && (reqid != (GCLOCK_GEN)i))
      continue;
    *(volatile uint8_t *)&GCLK->GENCTRL.reg = i;
    if (GCLK->GENCTRL.bit.GENEN)
    {
      if (GCLK->GENCTRL.bit.SRC == src)
      {
        *(volatile uint8_t *)&GCLK->GENDIV.reg = i;
        if (DIVIDER(GCLK->GENCTRL.bit.DIVSEL, GCLK->GENDIV.bit.DIV) == DIVIDER(divsel, divider))
        {
          if (idc)
          {
            GCLK->GENCTRL.bit.IDC = 1;
            sync();
          }
          return (GCLOCK_GEN)i;
        }
      }
    }
    else if (id == GCLOCK_GEN_NONE)
      id = (GCLOCK_GEN)i;
  }
  if (id != GCLOCK_GEN_NONE)
  {
    GCLK->GENDIV.reg  = GCLK_GENDIV_ID(id) | GCLK_GENDIV_DIV(divider);
    sync();
    GCLK->GENCTRL.reg = GCLK_GENCTRL_ID(id)
        | GCLK_GENCTRL_SRC(src)
        | GCLK_GENCTRL_GENEN
        | (idc      ? GCLK_GENCTRL_IDC      : 0)
        | (divsel   ? GCLK_GENCTRL_DIVSEL   : 0);
    sync();
  }
  return id;
}
 
bool GClock::output(uint32_t pin, GCLOCK_SRC src, uint8_t divider, bool divsel, bool idc, bool runstdby, bool oov)
{
  GCLOCK_GEN id = (GCLOCK_GEN)(pin < sizeof(GCLK_IO) ? GCLK_IO[pin] : NONE);
  if (id == NONE)
    return false;
  if (src == GCLOCK_SRC_NONE)
  {
    IOBUS::pinMode(pin, DISABLE);
    *(volatile uint8_t *)&GCLK->GENCTRL.reg = id;
    GCLK->GENCTRL.bit.OE = 0;
    sync();
  }
  else
  {
    if ((id = config(src, divider, divsel, idc, id)) == GCLOCK_GEN_NONE)
      return false;
    *(volatile uint8_t *)&GCLK->GENCTRL.reg = id;
    GCLK->GENCTRL.reg |= GCLK_GENCTRL_OE | (oov ? GCLK_GENCTRL_OOV : 0) | (runstdby ? GCLK_GENCTRL_RUNSTDBY : 0);
    sync();
    IOBUS::pinMode(pin, OUTPUT, true);
    IOBUS::multiplexing(pin, IOBUS_PMUX_H);
  }
  return true;
}
