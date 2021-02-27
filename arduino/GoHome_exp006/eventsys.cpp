/*
  eventsys.cpp - Event System Library for Microchip ATSAMD21 (Cortex®-M0+)
 
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
#include <string.h>
#include "eventsys.h"
 
static uint32_t _channels;
static EVENTSYS_CALLBACK _callback[EVSYS_CHANNELS];
 
#define INTFLAG_MASK (EVSYS_INTFLAG_EVD_Msk | EVSYS_INTFLAG_EVDp8_Msk | EVSYS_INTFLAG_OVR_Msk | EVSYS_INTFLAG_OVRp8_Msk)
 
void EVSYS_Handler(void)
{
  for (EVENTSYS_CHANNEL i = 0; (i < EVSYS_CHANNELS) && (EVSYS->INTFLAG.reg & INTFLAG_MASK); ++i)
  {
    uint32_t evd = EVENTSYS_EVD(i);
    uint32_t ovr = EVENTSYS_OVR(i);
    if (EVSYS->INTFLAG.reg & evd)
    {
      EVSYS->INTFLAG.reg = evd;
      if (_callback[i])
      _callback[i]((EVENTSYS_CHANNEL)(i + 1), EVENTSYS_INT_EVENTDETECTION);
    }
    if (EVSYS->INTFLAG.reg & ovr)
    {
      EVSYS->INTFLAG.reg = ovr;
      if (_callback[i])
        _callback[i]((EVENTSYS_CHANNEL)(i + 1), EVENTSYS_INT_OVERRUN);
    }
  }
}
 
void EventSys::setCallback(uint8_t no, EVENTSYS_CALLBACK cb)
{
  _callback[no] = cb;
}
 
void EventSys::begin(bool gclkreq)
{
  PM->APBCMASK.bit.EVSYS_ = 1;
  EVSYS->CTRL.reg = EVSYS_CTRL_SWRST;
  if (gclkreq)
    EVSYS->CTRL.reg = EVSYS_CTRL_GCLKREQ;
  NVIC_EnableIRQ(EVSYS_IRQn);
  NVIC_SetPriority(EVSYS_IRQn, 0);
  memset(_callback, 0, sizeof(_callback));
  _channels = 0;
}
 
void EventSys::end(void)
{
  if (PM->APBCMASK.bit.EVSYS_)
  {
    NVIC_DisableIRQ(EVSYS_IRQn);
    EVSYS->CTRL.reg = EVSYS_CTRL_SWRST;
    PM->APBCMASK.bit.EVSYS_ = 0;
  }
}
 
EVENTSYS_CHANNEL EventSys::allocChannel(void)
{
  uint32_t b = 1;
  for (EVENTSYS_CHANNEL i = 0; i < EVSYS_CHANNELS; ++i, b <<= 1)
  {
    if ((_channels & b) == 0)
    {
      _channels |= b;
      return i + 1;
    }
  }
  return 0;
}
 
void EventSys::releaseChannel(EVENTSYS_CHANNEL ch)
{
  if (ch)
  {
    interrupt(ch, 0);
    setEventGen(ch, EVENTSYS_GEN_NONE, EVENTSYS_PATH_SYNCHRONOUS, EVENTSYS_EDGSEL_NO_EVT_OUTPUT);
    // release users
    for (uint32_t user = EVENTSYS_USER_DMAC_CH_0; user <= EVENTSYS_USER_PTC_STCONV; ++user)
    {
      *(volatile uint8_t *)&EVSYS->USER.reg = EVSYS_USER_USER(user);
      if (EVSYS->USER.bit.CHANNEL == ch)
        EVSYS->USER.reg = EVSYS_USER_USER(user) | EVSYS_USER_CHANNEL(0);
    }
    controlGCLK(ch - 1, false);
    setCallback(ch, 0);
    _channels &= ~(1 << (ch - 1));
  }
}
