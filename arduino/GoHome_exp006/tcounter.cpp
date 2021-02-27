/*
  tcounter.cpp - Timer/Counter Library for Microchip ATSAMD21 (Cortex®-M0+)
 
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
#include "tcounter.h"
 
#define WO_NONE (uint32_t)-1
 
static const TCOUNTER_T _TCC0_ =
{
  .id       = TCOUNTER_ID_TCC0,
  .mode     = { .low = TCOUNTER_MODE24, .high = TCOUNTER_MODE24 },
  .reg      = TCC0,
  .apbmask  = PM_APBCMASK_TCC0,
  .gclkid   = GCLOCK_ID_TCC0_TCC1,
  .irqid    = TCC0_IRQn,
  .evuser   = { EVENTSYS_USER_TCC0_EV_0, EVENTSYS_USER_TCC0_EV_1 },
  .evgen    = { EVENTSYS_GEN_TCC0_MCX_0, EVENTSYS_GEN_TCC0_MCX_1, EVENTSYS_GEN_TCC0_OVF },
  .wo       = { { TCOUNTER_TCC0_WO0_PIN_A04, TCOUNTER_TCC0_WO0_PIN_A08, TCOUNTER_TCC0_WO0_PIN_B30 },
                { TCOUNTER_TCC0_WO1_PIN_A05, TCOUNTER_TCC0_WO1_PIN_A09, TCOUNTER_TCC0_WO1_PIN_B31 } },
};
 
static const TCOUNTER_T _TCC1_ =
{
  .id       = TCOUNTER_ID_TCC1,
  .mode     = { .low = TCOUNTER_MODE24, .high = TCOUNTER_MODE24 },
  .reg      = TCC1,
  .apbmask  = PM_APBCMASK_TCC1,
  .gclkid   = GCLOCK_ID_TCC0_TCC1,
  .irqid    = TCC1_IRQn,
  .evuser   = { EVENTSYS_USER_TCC1_EV_0, EVENTSYS_USER_TCC1_EV_1 },
  .evgen    = { EVENTSYS_GEN_TCC1_MCX_0, EVENTSYS_GEN_TCC1_MCX_1, EVENTSYS_GEN_TCC1_OVF },
  .wo       = { { TCOUNTER_TCC1_WO0_PIN_A06, TCOUNTER_TCC1_WO0_PIN_A10, TCOUNTER_TCC1_WO0_PIN_A30 },
                { TCOUNTER_TCC1_WO1_PIN_A07, TCOUNTER_TCC1_WO1_PIN_A11, TCOUNTER_TCC1_WO1_PIN_A31 } },
};
 
static const TCOUNTER_T _TCC2_ =
{
  .id       = TCOUNTER_ID_TCC2,
  .mode     = { .low = TCOUNTER_MODE16, .high = TCOUNTER_MODE16 },
  .reg      = TCC2,
  .apbmask  = PM_APBCMASK_TCC2,
  .gclkid   = GCLOCK_ID_TCC2_TC3,
  .irqid    = TCC2_IRQn,
  .evuser   = { EVENTSYS_USER_TCC2_EV_0, EVENTSYS_USER_TCC2_EV_1 },
  .evgen    = { EVENTSYS_GEN_TCC2_MCX_0, EVENTSYS_GEN_TCC2_MCX_1, EVENTSYS_GEN_TCC2_OVF },
  .wo       = { { TCOUNTER_TCC2_WO0_PIN_A00, TCOUNTER_TCC2_WO0_PIN_A12, TCOUNTER_TCC2_WO0_PIN_A16 },
                { TCOUNTER_TCC2_WO1_PIN_A01, TCOUNTER_TCC2_WO1_PIN_A13, TCOUNTER_TCC2_WO1_PIN_A17 } },
};
 
static const TCOUNTER_T _TC3_ =
{
  .id       = TCOUNTER_ID_TC3,
  .mode     = { .low = TCOUNTER_MODE8, .high = TCOUNTER_MODE16 },
  .reg      = TC3,
  .apbmask  = PM_APBCMASK_TC3,
  .gclkid   = GCLOCK_ID_TCC2_TC3,
  .irqid    = TC3_IRQn,
  .evuser   = { EVENTSYS_USER_TC3, EVENTSYS_USER_TC3 },
  .evgen    = { EVENTSYS_GEN_TC3_MCX_0, EVENTSYS_GEN_TC3_MCX_1, EVENTSYS_GEN_TC3_OVF },
  .wo       = { { TCOUNTER_TC3_WO0_PIN_A14, TCOUNTER_TC3_WO0_PIN_A18, WO_NONE },
                { TCOUNTER_TC3_WO1_PIN_A15, TCOUNTER_TC3_WO1_PIN_A19, WO_NONE } },
};
 
static const TCOUNTER_T _TC4_ =
{
  .id       = TCOUNTER_ID_TC4,
  .mode     = { .low = TCOUNTER_MODE8, .high = TCOUNTER_MODE32 },
  .reg      = TC4,
  .apbmask  = PM_APBCMASK_TC4,
  .gclkid   = GCLOCK_ID_TC4_TC5,
  .irqid    = TC4_IRQn,
  .evuser   = { EVENTSYS_USER_TC4, EVENTSYS_USER_TC4 },
  .evgen    = { EVENTSYS_GEN_TC4_MCX_0, EVENTSYS_GEN_TC4_MCX_1, EVENTSYS_GEN_TC4_OVF },
  .wo       = { { TCOUNTER_TC4_WO0_PIN_A22, TCOUNTER_TC4_WO0_PIN_B08, TCOUNTER_TC4_WO0_PIN_B12 },
                { TCOUNTER_TC4_WO1_PIN_A23, TCOUNTER_TC4_WO1_PIN_B09, TCOUNTER_TC4_WO1_PIN_B13 } },
};
 
static const TCOUNTER_T _TC5_ =
{
  .id       = TCOUNTER_ID_TC5,
  .mode     = { .low = TCOUNTER_MODE8, .high = TCOUNTER_MODE16 },
  .reg      = TC5,
  .apbmask  = PM_APBCMASK_TC5,
  .gclkid   = GCLOCK_ID_TC4_TC5,
  .irqid    = TC5_IRQn,
  .evuser   = { EVENTSYS_USER_TC5, EVENTSYS_USER_TC5 },
  .evgen    = { EVENTSYS_GEN_TC5_MCX_0, EVENTSYS_GEN_TC5_MCX_1, EVENTSYS_GEN_TC5_OVF },
  .wo       = { { TCOUNTER_TC5_WO0_PIN_A24, TCOUNTER_TC5_WO0_PIN_B10, TCOUNTER_TC5_WO0_PIN_B14 },
                { TCOUNTER_TC5_WO1_PIN_A25, TCOUNTER_TC5_WO1_PIN_B11, TCOUNTER_TC5_WO1_PIN_B15 } },
};
 
static const TCOUNTER_T *_TC_[] = {&_TCC0_, &_TCC1_, &_TCC2_, &_TC3_, &_TC4_, &_TC5_, 0, 0 };
 
typedef struct
{
  TCounter *obj;
  TCOUNTER_CALLBACK func;
} CALLBACK;
 
static CALLBACK _callback[sizeof(_TC_) / sizeof(_TC_[0])];
 
static uint32_t _counters;
 
static void TCCx_Handler(Tcc *tcc, CALLBACK *cb)
{
  if (tcc->INTFLAG.bit.MC0)
  {
    tcc->INTFLAG.bit.MC0 = 1;
    if (tcc->INTENSET.bit.MC0 && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_MC0);  
  }
  if (tcc->INTFLAG.bit.MC1)
  {
    tcc->INTFLAG.bit.MC1 = 1;
    if (tcc->INTENSET.bit.MC1 && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_MC1);  
  }
  if (tcc->INTFLAG.bit.OVF)
  {
    tcc->INTFLAG.bit.OVF = 1;
    if (tcc->INTENSET.bit.OVF && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_OVF);  
  }
  if (tcc->INTFLAG.bit.ERR)
  {
    tcc->INTFLAG.bit.ERR = 1;
    if (tcc->INTENSET.bit.ERR && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_ERR);  
  }
}
 
static void TCx_Handler(Tc *tc, CALLBACK *cb)
{
  if (tc->COUNT16.INTFLAG.bit.MC0)
  {
    tc->COUNT16.INTFLAG.bit.MC0 = 1;
    if (tc->COUNT16.INTENSET.bit.MC0 && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_MC0);  
  }
  if (tc->COUNT16.INTFLAG.bit.MC1)
  {
    tc->COUNT16.INTFLAG.bit.MC1 = 1;
    if (tc->COUNT16.INTENSET.bit.MC1 && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_MC1);  
  }
  if (tc->COUNT16.INTFLAG.bit.OVF)
  {
    tc->COUNT16.INTFLAG.bit.OVF = 1;
    if (tc->COUNT16.INTENSET.bit.OVF && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_OVF);  
  }
  if (tc->COUNT16.INTFLAG.bit.ERR)
  {
    tc->COUNT16.INTFLAG.bit.ERR = 1;
    if (tc->COUNT16.INTENSET.bit.ERR && cb->func)
      cb->func(cb->obj, TCOUNTER_INT_ERR);  
  }
}
 
void TCC0_Handler(void)
{
  TCCx_Handler(TCC0, &_callback[0]);
}
 
void TCC1_Handler(void)
{
  TCCx_Handler(TCC1, &_callback[1]);
}
 
void TCC2_Handler(void)
{
  TCCx_Handler(TCC2, &_callback[2]);
}
 
void TC3_Handler(void)
{
  TCx_Handler(TC3, &_callback[3]);
}
 
void TC4_Handler(void)
{
  TCx_Handler(TC4, &_callback[4]);
}
 
void TC5_Handler(void)
{
  TCx_Handler(TC5, &_callback[5]);
}
 
static void init0(void)
{
  if (_counters == 0)
  {
    _counters = (uint32_t)-1;
    for (uint32_t i = 0; i < sizeof(_TC_) / sizeof(_TC_[0]); ++i)
    {
      if (_TC_[i])
        _counters &= ~(1 << i);
    }
    memset(_callback, 0, sizeof(_callback));
  }
}
 
static TCOUNTER_MODE high(TCOUNTER_MODE mode)
{
  if (mode == TCOUNTER_MODE32)
  {
    if (_counters & (3 << TCOUNTER_ID_TC4))
      return TCOUNTER_MODE16;
  }
  return mode;
}
 
const TCOUNTER_T *TCFactory::alloc0(TCOUNTER_MODE mode, TCOUNTER_ID id)
{
  init0();
  const TCOUNTER_T *sel[TCOUNTER_MODE32 + 1] = {0};
  uint32_t mask = (mode == TCOUNTER_MODE32 ? 3 : 1);
  for (uint32_t i = 0; i < sizeof(_TC_) / sizeof(_TC_[0]); ++i)
  {
    if (((id == TCOUNTER_ID_ANY) || (id == i)) && ((_counters & (mask << i)) == 0))
    {
      const TCOUNTER_T *tc = _TC_[i];
      TCOUNTER_MODE hi = high(tc->mode.high);
      if (hi >= mode)
      {
        if (sel[hi] == 0)
          sel[hi] = tc;
        else
        {
          if ((high(sel[hi]->mode.high) != mode) && (sel[hi]->mode.low != mode))
          {
            if (sel[hi]->mode.low > tc->mode.low)
              sel[hi] = tc;
          }
        }
      }
    }
  }
  for (uint32_t i = 0; i < sizeof(sel) / sizeof(sel[0]); ++i)
  {
    const TCOUNTER_T *tc = sel[i];
    if (tc && (tc->mode.high >= mode))
    {
      _counters |= mask << tc->id;
      return _TC_[tc->id];
    }
  }
  return 0;
}
 
void TCounter::release0(const TCOUNTER_T *tc)
{
  _counters &= ~((tc->mode.high == TCOUNTER_MODE32 ? 3 : 1) << tc->id);
}
 
bool TCounter::valid(uint32_t id)
{
  return _counters & (1 << id);
}
 
void TCounter::setCallback(TCounter *obj, TCOUNTER_CALLBACK func)
{
  _callback[obj->_tc->id] = { .obj = obj, .func = func };
}
