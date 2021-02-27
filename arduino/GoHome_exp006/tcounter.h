/*
  tcounter.h - Timer/Counter Library for Microchip ATSAMD21 (Cortex®-M0+)
 
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
#ifndef __TCOUNTER_H
#define __TCOUNTER_H
 
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sam.h>
#include "gclock.h"
#include "eventsys.h"
#include "IOBUS.h"
 
//
// Port Define for Seeeduino XIAO
//
#ifdef SEEED_XIAO_M0
  #define TCOUNTER_TC3_WO0_PIN_RX_LED TCOUNTER_TC3_WO0_PIN_A18
  #define TCOUNTER_TC3_WO1_PIN_TX_LED TCOUNTER_TC3_WO1_PIN_A19
  #define TCOUNTER_TCC0_WO0_PIN_D1    TCOUNTER_TCC0_WO0_PIN_A04
  #define TCOUNTER_TCC1_WO0_PIN_D2    TCOUNTER_TCC1_WO0_PIN_A10
  #define TCOUNTER_TCC1_WO0_PIN_D3    TCOUNTER_TCC1_WO1_PIN_A11
  #define TCOUNTER_TCC0_WO1_PIN_D4    TCOUNTER_TCC0_WO0_PIN_A08
  #define TCOUNTER_TCC0_WO1_PIN_D5    TCOUNTER_TCC0_WO1_PIN_A09
  #define TCOUNTER_TC4_WO0_PIN_D6     TCOUNTER_TC4_WO0_PIN_B08
  #define TCOUNTER_TC4_WO1_PIN_D7     TCOUNTER_TC4_WO1_PIN_B09
  #define TCOUNTER_TCC0_WO1_PIN_D8    TCOUNTER_TCC1_WO1_PIN_A07
  #define TCOUNTER_TCC0_WO1_PIN_D9    TCOUNTER_TCC0_WO1_PIN_A05
  #define TCOUNTER_TCC0_WO1_PIN_D10   TCOUNTER_TCC1_WO0_PIN_A06
#endif
 
//
// MUX(E)
//
#define TCOUNTER_TCC2_WO0_PIN_A00 IOBUS_PIN('A',  0)
#define TCOUNTER_TCC2_WO1_PIN_A01 IOBUS_PIN('A',  1)
#define TCOUNTER_TCC0_WO0_PIN_A04 IOBUS_PIN('A',  4)
#define TCOUNTER_TCC0_WO1_PIN_A05 IOBUS_PIN('A',  5)
#define TCOUNTER_TCC1_WO0_PIN_A06 IOBUS_PIN('A',  6)
#define TCOUNTER_TCC1_WO1_PIN_A07 IOBUS_PIN('A',  7)
#define TCOUNTER_TCC0_WO0_PIN_A08 IOBUS_PIN('A',  8)
#define TCOUNTER_TCC0_WO1_PIN_A09 IOBUS_PIN('A',  9)
#define TCOUNTER_TCC1_WO0_PIN_A10 IOBUS_PIN('A', 10)
#define TCOUNTER_TCC1_WO1_PIN_A11 IOBUS_PIN('A', 11)
#define TCOUNTER_TCC2_WO0_PIN_A12 IOBUS_PIN('A', 12)
#define TCOUNTER_TCC2_WO1_PIN_A13 IOBUS_PIN('A', 13)
#define TCOUNTER_TCC2_WO0_PIN_A16 IOBUS_PIN('A', 16)
#define TCOUNTER_TCC2_WO1_PIN_A17 IOBUS_PIN('A', 17)
#define TCOUNTER_TC3_WO0_PIN_A14  IOBUS_PIN('A', 14)
#define TCOUNTER_TC3_WO1_PIN_A15  IOBUS_PIN('A', 15)
#define TCOUNTER_TC3_WO0_PIN_A18  IOBUS_PIN('A', 18)
#define TCOUNTER_TC3_WO1_PIN_A19  IOBUS_PIN('A', 19)
#define TCOUNTER_TC7_WO0_PIN_A20  IOBUS_PIN('A', 20)
#define TCOUNTER_TC7_WO1_PIN_A21  IOBUS_PIN('A', 21)
#define TCOUNTER_TC4_WO0_PIN_A22  IOBUS_PIN('A', 22)
#define TCOUNTER_TC4_WO1_PIN_A23  IOBUS_PIN('A', 23)
#define TCOUNTER_TC5_WO0_PIN_A24  IOBUS_PIN('A', 24)
#define TCOUNTER_TC5_WO1_PIN_A25  IOBUS_PIN('A', 25)
#define TCOUNTER_TCC1_WO0_PIN_A30 IOBUS_PIN('A', 30)
#define TCOUNTER_TCC1_WO1_PIN_A31 IOBUS_PIN('A', 31)
#define TCOUNTER_TC7_WO0_PIN_B00  IOBUS_PIN('B',  0)
#define TCOUNTER_TC7_WO1_PIN_B01  IOBUS_PIN('B',  1)
#define TCOUNTER_TC6_WO0_PIN_B02  IOBUS_PIN('B',  2)
#define TCOUNTER_TC6_WO1_PIN_B03  IOBUS_PIN('B',  3)
#define TCOUNTER_TC4_WO0_PIN_B08  IOBUS_PIN('B',  8)
#define TCOUNTER_TC4_WO1_PIN_B09  IOBUS_PIN('B',  9)
#define TCOUNTER_TC5_WO0_PIN_B10  IOBUS_PIN('B', 10)
#define TCOUNTER_TC5_WO1_PIN_B11  IOBUS_PIN('B', 11)
#define TCOUNTER_TC4_WO0_PIN_B12  IOBUS_PIN('B', 12)
#define TCOUNTER_TC4_WO1_PIN_B13  IOBUS_PIN('B', 13)
#define TCOUNTER_TC5_WO0_PIN_B14  IOBUS_PIN('B', 14)
#define TCOUNTER_TC5_WO1_PIN_B15  IOBUS_PIN('B', 15)
#define TCOUNTER_TC6_WO0_PIN_B16  IOBUS_PIN('B', 16)
#define TCOUNTER_TC6_WO1_PIN_B17  IOBUS_PIN('B', 17)
#define TCOUNTER_TC7_WO0_PIN_B22  IOBUS_PIN('B', 22)
#define TCOUNTER_TC7_WO1_PIN_B23  IOBUS_PIN('B', 23)
#define TCOUNTER_TCC0_WO0_PIN_B30 IOBUS_PIN('B', 30)
#define TCOUNTER_TCC0_WO1_PIN_B31 IOBUS_PIN('B', 31)
//
// MUX(F)
//
#define TCOUNTER_TCC3_WO0_PIN_A02 IOBUS_PIN('A',  2)
#define TCOUNTER_TCC3_WO1_PIN_A03 IOBUS_PIN('A',  3)
#define TCOUNTER_TCC3_WO2_PIN_A04 IOBUS_PIN('A',  4)
#define TCOUNTER_TCC3_WO3_PIN_A05 IOBUS_PIN('A',  5)
#define TCOUNTER_TCC3_WO4_PIN_A06 IOBUS_PIN('A',  6)
#define TCOUNTER_TCC3_WO5_PIN_A07 IOBUS_PIN('A',  7)
#define TCOUNTER_TCC1_WO2_PIN_A08 IOBUS_PIN('A',  8)
#define TCOUNTER_TCC1_WO3_PIN_A09 IOBUS_PIN('A',  9)
#define TCOUNTER_TCC0_WO2_PIN_A10 IOBUS_PIN('A', 10)
#define TCOUNTER_TCC0_WO3_PIN_A11 IOBUS_PIN('A', 11)
#define TCOUNTER_TCC0_WO6_PIN_A12 IOBUS_PIN('A', 12)
#define TCOUNTER_TCC0_WO7_PIN_A13 IOBUS_PIN('A', 13)
#define TCOUNTER_TCC0_WO4_PIN_A14 IOBUS_PIN('A', 14)
#define TCOUNTER_TCC0_WO5_PIN_A15 IOBUS_PIN('A', 15)
#define TCOUNTER_TCC0_WO6_PIN_A16 IOBUS_PIN('A', 16)
#define TCOUNTER_TCC0_WO7_PIN_A17 IOBUS_PIN('A', 17)
#define TCOUNTER_TCC0_WO2_PIN_A18 IOBUS_PIN('A', 18)
#define TCOUNTER_TCC0_WO3_PIN_A19 IOBUS_PIN('A', 19)
#define TCOUNTER_TCC0_WO6_PIN_A20 IOBUS_PIN('A', 20)
#define TCOUNTER_TCC0_WO7_PIN_A21 IOBUS_PIN('A', 21)
#define TCOUNTER_TCC0_WO2_PIN_A22 IOBUS_PIN('A', 22)
#define TCOUNTER_TCC0_WO3_PIN_A23 IOBUS_PIN('A', 23)
#define TCOUNTER_TCC1_WO2_PIN_A24 IOBUS_PIN('A', 24)
#define TCOUNTER_TCC1_WO3_PIN_A25 IOBUS_PIN('A', 25)
#define TCOUNTER_TCC3_WO6_PIN_A27 IOBUS_PIN('A', 27)
#define TCOUNTER_TCC3_WO7_PIN_A28 IOBUS_PIN('A', 28)
#define TCOUNTER_TCC3_WO4_PIN_A30 IOBUS_PIN('A', 30)
#define TCOUNTER_TCC3_WO5_PIN_A31 IOBUS_PIN('A', 31)
#define TCOUNTER_TCC3_WO2_PIN_B30 IOBUS_PIN('B',  2)
#define TCOUNTER_TCC3_WO3_PIN_B31 IOBUS_PIN('B',  3)
#define TCOUNTER_TCC3_WO6_PIN_B08 IOBUS_PIN('B',  8)
#define TCOUNTER_TCC3_WO7_PIN_B09 IOBUS_PIN('B',  9)
#define TCOUNTER_TCC0_WO4_PIN_B10 IOBUS_PIN('B', 10)
#define TCOUNTER_TCC0_WO5_PIN_B11 IOBUS_PIN('B', 11)
#define TCOUNTER_TCC0_WO6_PIN_B12 IOBUS_PIN('B', 12)
#define TCOUNTER_TCC0_WO7_PIN_B13 IOBUS_PIN('B', 13)
#define TCOUNTER_TCC0_WO4_PIN_B16 IOBUS_PIN('B', 16)
#define TCOUNTER_TCC0_WO5_PIN_B17 IOBUS_PIN('B', 17)
#define TCOUNTER_TCC3_WO0_PIN_B22 IOBUS_PIN('B', 22)
#define TCOUNTER_TCC3_WO1_PIN_B23 IOBUS_PIN('B', 23)
#define TCOUNTER_TCC1_WO2_PIN_B30 IOBUS_PIN('B', 30)
#define TCOUNTER_TCC1_WO3_PIN_B31 IOBUS_PIN('B', 31)
 
#define TCOUNTER_DUTY_BIT    16
#define TCOUNTER_DUTY_MAX    (1 << TCOUNTER_DUTY_BIT)
#define TCOUNTER_DUTY_PER(p) (TCOUNTER_DUTY_MAX * ((p) > 100 ? 100 : (p)) / 100)
 
typedef enum
{
  TCOUNTER_ID_TCC0 = 0,
  TCOUNTER_ID_TCC1 = 1,
  TCOUNTER_ID_TCC2 = 2,
  TCOUNTER_ID_TC3  = 3,
  TCOUNTER_ID_TC4  = 4,
  TCOUNTER_ID_TC5  = 5,
  TCOUNTER_ID_TC6  = 6,
  TCOUNTER_ID_TC7  = 7,
  TCOUNTER_ID_ANY = TCOUNTER_ID_TC7 + 1,
} TCOUNTER_ID;
 
typedef enum
{
  TCOUNTER_MODE8  = 0,
  TCOUNTER_MODE16 = 1,
  TCOUNTER_MODE24 = 2,
  TCOUNTER_MODE32 = 3,
} TCOUNTER_MODE;
 
typedef enum
{
  TCOUNTER_WAVEGEN_NFRQ = TC_CTRLA_WAVEGEN_NFRQ_Val,
  TCOUNTER_WAVEGEN_MFRQ = TC_CTRLA_WAVEGEN_MFRQ_Val,
  TCOUNTER_WAVEGEN_NPWM = TC_CTRLA_WAVEGEN_NPWM_Val,
  TCOUNTER_WAVEGEN_MPWM = TC_CTRLA_WAVEGEN_MPWM_Val,
} TCOUNTER_WAVEGEN;
 
typedef enum
{
  TCOUNTER_PRESCSYNC_GCLK   = TC_CTRLA_PRESCSYNC_GCLK_Val,
  TCOUNTER_PRESCSYNC_PRESC  = TC_CTRLA_PRESCSYNC_PRESC_Val,
  TCOUNTER_PRESCSYNC_RESYNC = TC_CTRLA_PRESCSYNC_RESYNC_Val,
} TCOUNTER_PRESCSYNC;
 
typedef enum
{
  TCOUNTER_PRESCALER_DIV1    = TC_CTRLA_PRESCALER_DIV1_Val,
  TCOUNTER_PRESCALER_DIV2    = TC_CTRLA_PRESCALER_DIV2_Val,
  TCOUNTER_PRESCALER_DIV4    = TC_CTRLA_PRESCALER_DIV4_Val,
  TCOUNTER_PRESCALER_DIV8    = TC_CTRLA_PRESCALER_DIV8_Val,
  TCOUNTER_PRESCALER_DIV16   = TC_CTRLA_PRESCALER_DIV16_Val,
  TCOUNTER_PRESCALER_DIV64   = TC_CTRLA_PRESCALER_DIV64_Val,
  TCOUNTER_PRESCALER_DIV256  = TC_CTRLA_PRESCALER_DIV256_Val,
  TCOUNTER_PRESCALER_DIV1024 = TC_CTRLA_PRESCALER_DIV1024_Val,
} TCOUNTER_PRESCALER;
 
typedef enum
{
  TCOUNTER_EVACT_OFF       = TC_EVCTRL_EVACT_OFF_Val,
  TCOUNTER_EVACT_RETRIGGER = TC_EVCTRL_EVACT_RETRIGGER_Val,
  TCOUNTER_EVACT_COUNT     = TC_EVCTRL_EVACT_COUNT_Val,
  TCOUNTER_EVACT_START     = TC_EVCTRL_EVACT_START_Val,
  TCOUNTER_EVACT_PPW       = TC_EVCTRL_EVACT_PPW_Val,
  TCOUNTER_EVACT_PWP       = TC_EVCTRL_EVACT_PWP_Val,
} TCOUNTER_EVACT;
 
typedef enum
{
  TCOUNTER_EVOSEL_MC0 = 0,
  TCOUNTER_EVOSEL_MC1 = 1,
  TCOUNTER_EVOSEL_OVF = 2,
} TCOUNTER_EVOSEL;
 
typedef enum
{
  TCOUNTER_MC0 = 0,
  TCOUNTER_MC1 = 1,
} TCOUNTER_MC;
 
typedef enum
{
  TCOUNTER_CMD_NONE      = TC_CTRLBCLR_CMD_NONE_Val,
  TCOUNTER_CMD_RETRIGGER = TC_CTRLBCLR_CMD_RETRIGGER_Val,
  TCOUNTER_CMD_STOP      = TC_CTRLBCLR_CMD_STOP_Val,
} TCOUNTER_CMD;
 
typedef enum
{
  TCOUNTER_INT_MC0 = TC_INTFLAG_MC0,
  TCOUNTER_INT_MC1 = TC_INTFLAG_MC1,
  TCOUNTER_INT_OVF = TC_INTFLAG_OVF,
  TCOUNTER_INT_ERR = TC_INTFLAG_ERR,
} TCOUNTER_INT;
 
class TCounter;
 
typedef void (*TCOUNTER_CALLBACK)(TCounter *obj, TCOUNTER_INT flag);
 
typedef struct
{
  TCOUNTER_ID       id;
  struct {
    TCOUNTER_MODE low;
    TCOUNTER_MODE high;
  } mode;
  void              *reg;    // (Tcc *) or (Tc *)
  uint32_t          apbmask;
  GCLOCK_ID         gclkid;
  IRQn_Type         irqid;
  EVENTSYS_USER     evuser[2];
  EVENTSYS_GEN      evgen[3];
  uint32_t          wo[2][3];
} TCOUNTER_T;
 
class TCounter
{
  protected:
 
    const TCOUNTER_T *_tc;
 
    static void release0(const TCOUNTER_T *tc);
    static bool valid(uint32_t id);
    static void setCallback(TCounter *obj, TCOUNTER_CALLBACK func);
 
    virtual uint32_t maxCount(void) = 0;
 
    void controlGCLK(bool enable)
    {
      GClock::control(_tc->gclkid, enable);
    }
 
    TCounter(const TCOUNTER_T *tc)
    : _tc(tc)
    {
    }
 
  public:
 
    virtual ~TCounter(void)
    {
      release();
    }
 
    virtual void release(void)
    {
    }
 
    void setCallback(TCOUNTER_CALLBACK func)
    {
      setCallback(this, func);
    }
 
    uint32_t pulsWidth(uint64_t us)
    {
      return period((F_CPU / 1000000) * us);
    }
 
    uint32_t frequency(uint32_t hz)
    {
      return period(F_CPU / hz);
    }
 
    virtual uint32_t period(uint64_t count) = 0;
    virtual uint32_t prescaler(TCOUNTER_PRESCALER ps) = 0;
    virtual uint32_t top(void) = 0;
    virtual bool dutyCycle(TCOUNTER_MC mc, uint32_t ratio = TCOUNTER_DUTY_MAX >> 1) = 0;
    virtual EVENTSYS_USER eventInput(TCOUNTER_EVACT evact, bool enable, bool invert = false) = 0;
    virtual EVENTSYS_GEN eventOutput(TCOUNTER_EVOSEL evosel, bool enable) = 0;
    virtual void direction(bool down) = 0;
    virtual void oneshot(bool enable) = 0;
    virtual void interrupt(TCOUNTER_INT flag, bool enable) = 0;
    virtual void capture(TCOUNTER_MC mc, bool enable) = 0;
    virtual bool output(TCOUNTER_MC mc, uint32_t pin, bool enable, bool invert = false) = 0;
    virtual void start(void) = 0;
    virtual void stop(void) = 0;
    virtual bool running(void) = 0;
    virtual void command(TCOUNTER_CMD cmd) = 0;
    virtual void debugControl(bool dgbrun) = 0;
    virtual void count(uint32_t value) = 0;
    virtual uint32_t count(void) = 0;
    virtual void cc(TCOUNTER_MC mc, uint32_t value) = 0;
    virtual uint32_t cc(TCOUNTER_MC mc) = 0;
    virtual void per(uint32_t value) = 0;
    virtual uint32_t per(void) = 0;
 
    TCOUNTER_ID id(void)
    {
      return _tc->id;
    }
};
 
class TCCImplement : public TCounter
{
  private:
 
    Tcc *_reg;
    bool _mpwm;
 
    void sync(uint32_t flags)
    {
      while (_reg->SYNCBUSY.reg & flags)
        continue;
    }
 
    uint32_t maxCount(void) override
    {
      switch (_tc->mode.high)
      {
        case TCOUNTER_MODE16: return 0xFFFF;
        case TCOUNTER_MODE24: return TCC_COUNT_MASK;
        default: break;
      }
      return 0;
    }
 
  public:
 
    TCCImplement(const TCOUNTER_T *tc, TCOUNTER_WAVEGEN wavegen, TCOUNTER_PRESCSYNC pssync, bool runstdby)
    : TCounter(tc)
    {
      _reg  = (Tcc *)tc->reg;
      _mpwm = (wavegen == TCOUNTER_WAVEGEN_MPWM);
      PM->APBCMASK.reg |= tc->apbmask;
      controlGCLK(true);
      _reg->CTRLA.reg = TCC_CTRLA_SWRST;
      sync(TCC_CTRLA_SWRST);
      _reg->WAVE.bit.WAVEGEN    = (_mpwm ? TCOUNTER_WAVEGEN_NPWM : wavegen);
      _reg->CTRLA.bit.PRESCSYNC = pssync;
      _reg->CTRLA.bit.RUNSTDBY  = runstdby;
      per(TCC_COUNT_MASK);
      cc(TCOUNTER_MC0, TCC_COUNT_MASK);
      NVIC_EnableIRQ(_tc->irqid);
      NVIC_SetPriority(_tc->irqid, 0);
    }
 
    void release(void) override
    {
      if (_tc)
      {
        _reg->CTRLA.reg = TCC_CTRLA_SWRST;
        sync(TCC_CTRLA_SWRST);
        NVIC_DisableIRQ(_tc->irqid);
        if (!valid(_tc->id ^ 1))
          controlGCLK(false);
        PM->APBCMASK.reg &= ~_tc->apbmask;
        release0(_tc);
        _reg = 0;
        _tc  = 0;
      }
    }
 
    uint32_t period(uint64_t count) override
    {
      static const uint8_t PS_SHIFT[] = {0, 1, 1, 1, 1, 2, 2, 2};
      uint32_t mc = maxCount();
      uint8_t  ps = 0;
      for (; ps < sizeof(PS_SHIFT); ++ps)
      {
        if ((count >>= PS_SHIFT[ps]) <= mc)
          break;
      }
      if (count > mc)
      {
        count = mc - 1;
        ps = sizeof(PS_SHIFT) - 1;
      }
      else if (count)
        --count;
      cc(TCOUNTER_MC0, count);
      if (_mpwm)
        per(count);
      return prescaler((TCOUNTER_PRESCALER)ps);
    }
 
    uint32_t prescaler(TCOUNTER_PRESCALER ps) override
    {
      switch (_reg->CTRLA.bit.PRESCALER = ps)
      {
        case TCOUNTER_PRESCALER_DIV1   : return F_CPU;
        case TCOUNTER_PRESCALER_DIV2   : return F_CPU / 2;
        case TCOUNTER_PRESCALER_DIV4   : return F_CPU / 4;
        case TCOUNTER_PRESCALER_DIV8   : return F_CPU / 8;
        case TCOUNTER_PRESCALER_DIV16  : return F_CPU / 16;
        case TCOUNTER_PRESCALER_DIV64  : return F_CPU / 64;
        case TCOUNTER_PRESCALER_DIV256 : return F_CPU / 256;
        case TCOUNTER_PRESCALER_DIV1024: return F_CPU / 1024;
      }
      return 0;
    }
 
    uint32_t top(void) override
    {
      if (_reg->WAVE.bit.WAVEGEN == TCOUNTER_WAVEGEN_MFRQ)
        return cc(TCOUNTER_MC0);
      else
        return per();
    }
 
    bool dutyCycle(TCOUNTER_MC mc, uint32_t ratio = TCOUNTER_DUTY_MAX >> 1) override
    {
      if ((_reg->WAVE.bit.WAVEGEN & 1) && (mc == TCOUNTER_MC0))
        return false;
      cc(mc, (((uint64_t)top() + 1) * (ratio > TCOUNTER_DUTY_MAX ? TCOUNTER_DUTY_MAX : ratio)) >> TCOUNTER_DUTY_BIT);
      return true;
    }
 
    EVENTSYS_USER eventInput(TCOUNTER_EVACT evact, bool enable, bool invert = false) override
    {
      switch (evact)
      {
        case TCOUNTER_EVACT_OFF:
        case TCOUNTER_EVACT_RETRIGGER:
        case TCOUNTER_EVACT_COUNT:
        case TCOUNTER_EVACT_START:
          _reg->EVCTRL.bit.EVACT0 = evact;
          _reg->EVCTRL.vec.TCINV  = invert ? 1 : 0;
          _reg->EVCTRL.vec.TCEI   = enable ? 1 : 0;
          return _tc->evuser[0];
        case TCOUNTER_EVACT_PPW:
        case TCOUNTER_EVACT_PWP:
          _reg->EVCTRL.bit.EVACT1 = evact;
          _reg->EVCTRL.vec.TCINV  = invert ? 2 : 0;
          _reg->EVCTRL.vec.TCEI   = enable ? 2 : 0;
          return _tc->evuser[1];
      }
      return EVENTSYS_USER_NONE;
    }
 
    EVENTSYS_GEN eventOutput(TCOUNTER_EVOSEL evosel, bool enable) override
    {
      switch (evosel)
      {
        case TCOUNTER_EVOSEL_MC0: _reg->EVCTRL.bit.MCEO0 = enable; break;
        case TCOUNTER_EVOSEL_MC1: _reg->EVCTRL.bit.MCEO1 = enable; break;
        case TCOUNTER_EVOSEL_OVF: _reg->EVCTRL.bit.OVFEO = enable; break;
      }
      return _tc->evgen[evosel];
    }
 
    void direction(bool down) override
    {
      if (down)
        _reg->CTRLBSET.reg = TCC_CTRLBSET_DIR;
      else
        _reg->CTRLBCLR.reg = TCC_CTRLBCLR_DIR;
      sync(TCC_SYNCBUSY_CTRLB);
    }
 
    void oneshot(bool enable) override
    {
      if (enable)
        _reg->CTRLBSET.reg = TCC_CTRLBSET_ONESHOT;
      else
        _reg->CTRLBCLR.reg = TCC_CTRLBCLR_ONESHOT;
      sync(TCC_SYNCBUSY_CTRLB);
    }
 
    void interrupt(TCOUNTER_INT flag, bool enable) override
    {
      switch (flag)
      {
        case TCOUNTER_INT_MC0:
          if (enable)
            _reg->INTENSET.reg = TCC_INTENSET_MC0;
          else
            _reg->INTENCLR.reg = TCC_INTENCLR_MC0;
          break;
        case TCOUNTER_INT_MC1:
          if (enable)
            _reg->INTENSET.reg = TCC_INTENSET_MC1;
          else
            _reg->INTENCLR.reg = TCC_INTENCLR_MC1;
          break;
        case TCOUNTER_INT_OVF:
          if (enable)
            _reg->INTENSET.reg = TCC_INTENSET_OVF;
          else
            _reg->INTENCLR.reg = TCC_INTENCLR_OVF;
          break;
        case TCOUNTER_INT_ERR:
          if (enable)
            _reg->INTENSET.reg = TCC_INTENSET_ERR;
          else
            _reg->INTENCLR.reg = TCC_INTENCLR_ERR;
          break;
      }
    }
 
    void capture(TCOUNTER_MC mc, bool enable) override
    {
      switch (mc)
      {
        case TCOUNTER_MC0: _reg->CTRLA.bit.CPTEN0 = _reg->EVCTRL.bit.MCEI0 = enable; break;
        case TCOUNTER_MC1: _reg->CTRLA.bit.CPTEN1 = _reg->EVCTRL.bit.MCEI1 = enable; break;
      }
    }
 
    bool output(TCOUNTER_MC mc, uint32_t pin, bool enable, bool invert = false) override
    {
      for (uint32_t i = 0; i < sizeof(_tc->wo[0]) / sizeof(_tc->wo[0][0]); ++i)
      {
        if (_tc->wo[mc][i] == pin)
        {
          if (enable)
          {
            switch (mc)
            {
              case TCOUNTER_MC0: _reg->DRVCTRL.bit.INVEN0 = invert; break;
              case TCOUNTER_MC1: _reg->DRVCTRL.bit.INVEN1 = invert; break;
            }
            IOBUS::pinMode(pin, OUTPUT, true);
            IOBUS::multiplexing(pin, IOBUS_PMUX_E);
          }
          else
            IOBUS::pinMode(pin, DISABLE);
          return true;
        }
      }
      return false;
    }
 
    void start(void) override
    {
      _reg->CTRLA.bit.ENABLE = 1;
      sync(TCC_SYNCBUSY_ENABLE);
    }
 
    void stop(void) override
    {
      _reg->CTRLA.bit.ENABLE = 0;
      sync(TCC_SYNCBUSY_ENABLE);
    }
 
    bool running(void) override
    {
      return !_reg->STATUS.bit.STOP;
    }
 
    void command(TCOUNTER_CMD cmd) override
    {
      _reg->CTRLBSET.reg = TCC_CTRLBSET_CMD(cmd);
      sync(TCC_SYNCBUSY_CTRLB);
    }
 
    void debugControl(bool dgbrun) override
    {
      _reg->DBGCTRL.bit.DBGRUN = dgbrun;
    }
 
    void count(uint32_t value) override
    {
      _reg->COUNT.reg = value;
      sync(TCC_SYNCBUSY_COUNT);
    }
 
    uint32_t count(void) override
    {
      _reg->CTRLBSET.reg = TCC_CTRLBSET_CMD_READSYNC;
      sync(TCC_SYNCBUSY_CTRLB | TCC_SYNCBUSY_COUNT);
      return _reg->COUNT.bit.COUNT;
    }
 
    void cc(TCOUNTER_MC mc, uint32_t value) override
    {
      _reg->CC[mc].reg = value;
      sync(TCC_SYNCBUSY_CC(1 << mc));
    }
 
    uint32_t cc(TCOUNTER_MC mc) override
    {
      return _reg->CC[mc].bit.CC;
    }
 
    void per(uint32_t value) override
    {
      _reg->PER.reg = value;
      sync(TCC_SYNCBUSY_PER);
    }
 
    uint32_t per(void) override
    {
      return _reg->PER.bit.PER;
    }
};
 
class TCImplement : public TCounter
{
  private:
 
    Tc *_reg;
 
    void sync(void)
    {
      while (_reg->COUNT16.CTRLA.bit.SWRST || _reg->COUNT16.STATUS.bit.SYNCBUSY)
        continue;
    }
 
    uint32_t maxCount(void) override
    {
      switch (_reg->COUNT16.CTRLA.bit.MODE)
      {
        case TC_CTRLA_MODE_COUNT32_Val: return TC_COUNT32_COUNT_MASK;
        case TC_CTRLA_MODE_COUNT16_Val: return TC_COUNT16_COUNT_MASK;
        case TC_CTRLA_MODE_COUNT8_Val : return TC_COUNT8_COUNT_MASK ;
      }
      return 0;
    }
 
  public:
 
    TCImplement(const TCOUNTER_T *tc, TCOUNTER_MODE mode, TCOUNTER_WAVEGEN wavegen, TCOUNTER_PRESCSYNC pssync, bool runstdby)
    : TCounter(tc)
    {
      _reg = (Tc *)tc->reg;
      controlGCLK(true);
      _reg->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
      sync();
      switch (mode)
      {
        default:
        case TCOUNTER_MODE32: _reg->COUNT16.CTRLA.bit.MODE = TC_CTRLA_MODE_COUNT32_Val; break;
        case TCOUNTER_MODE16: _reg->COUNT16.CTRLA.bit.MODE = TC_CTRLA_MODE_COUNT16_Val; break;
        case TCOUNTER_MODE8 : _reg->COUNT16.CTRLA.bit.MODE = TC_CTRLA_MODE_COUNT8_Val ; break;
      }
      _reg->COUNT16.CTRLA.bit.WAVEGEN   = wavegen;
      _reg->COUNT16.CTRLA.bit.PRESCSYNC = pssync;
      _reg->COUNT16.CTRLA.bit.RUNSTDBY  = runstdby;
      per(TC_COUNT32_COUNT_MASK);
      cc(TCOUNTER_MC0, TC_COUNT32_COUNT_MASK);
      NVIC_EnableIRQ(_tc->irqid);
      NVIC_SetPriority(_tc->irqid, 0);
    }
 
    void release(void) override
    {
      if (_tc)
      {
        _reg->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
        sync();
        NVIC_DisableIRQ(_tc->irqid);
        if ((_reg->COUNT16.CTRLA.bit.MODE == TC_CTRLA_MODE_COUNT32_Val) || !valid(_tc->id ^ 1))
          controlGCLK(false);
        release0(_tc);
        _reg = 0;
        _tc  = 0;
      }
    }
 
    uint32_t period(uint64_t count) override
    {
      static const uint8_t PS_SHIFT[] = {0, 1, 1, 1, 1, 2, 2, 2};
      uint32_t mc = maxCount();
      uint8_t  ps = 0;
      for (; ps < sizeof(PS_SHIFT); ++ps)
      {
        if ((count >>= PS_SHIFT[ps]) <= mc)
          break;
      }
      if (count > mc)
      {
        count = mc - 1;
        ps = sizeof(PS_SHIFT) - 1;
      }
      else if (count)
        --count;
      cc(TCOUNTER_MC0, count);
      return prescaler((TCOUNTER_PRESCALER)ps);
    }
 
    uint32_t prescaler(TCOUNTER_PRESCALER ps) override
    {
      switch (_reg->COUNT16.CTRLA.bit.PRESCALER = ps)
      {
        case TCOUNTER_PRESCALER_DIV1   : return F_CPU;
        case TCOUNTER_PRESCALER_DIV2   : return F_CPU / 2;
        case TCOUNTER_PRESCALER_DIV4   : return F_CPU / 4;
        case TCOUNTER_PRESCALER_DIV8   : return F_CPU / 8;
        case TCOUNTER_PRESCALER_DIV16  : return F_CPU / 16;
        case TCOUNTER_PRESCALER_DIV64  : return F_CPU / 64;
        case TCOUNTER_PRESCALER_DIV256 : return F_CPU / 256;
        case TCOUNTER_PRESCALER_DIV1024: return F_CPU / 1024;
      }
      return 0;
    }
 
    uint32_t top(void) override
    {
      if (_reg->COUNT16.CTRLA.bit.WAVEGEN & 1)
        return cc(TCOUNTER_MC0);
      if (_reg->COUNT16.CTRLA.bit.MODE == TC_CTRLA_MODE_COUNT8_Val)
        return per();
      return maxCount();
    }
 
    bool dutyCycle(TCOUNTER_MC mc, uint32_t ratio = TCOUNTER_DUTY_MAX >> 1) override
    {
      if ((_reg->COUNT16.CTRLA.bit.WAVEGEN & 1) && (mc == TCOUNTER_MC0))
        return false;
      cc(mc, (((uint64_t)top() + 1) * (ratio > TCOUNTER_DUTY_MAX ? TCOUNTER_DUTY_MAX : ratio)) >> TCOUNTER_DUTY_BIT);
      return true;
    }
 
    EVENTSYS_USER eventInput(TCOUNTER_EVACT evact, bool enable, bool invert = false) override
    {
      _reg->COUNT16.EVCTRL.bit.EVACT = evact;
      _reg->COUNT16.EVCTRL.bit.TCINV = invert;
      _reg->COUNT16.EVCTRL.bit.TCEI  = enable;
      return _tc->evuser[0];
    }
 
    EVENTSYS_GEN eventOutput(TCOUNTER_EVOSEL evosel, bool enable) override
    {
      switch (evosel)
      {
        case TCOUNTER_EVOSEL_MC0: _reg->COUNT16.EVCTRL.bit.MCEO0 = enable; break;
        case TCOUNTER_EVOSEL_MC1: _reg->COUNT16.EVCTRL.bit.MCEO1 = enable; break;
        case TCOUNTER_EVOSEL_OVF: _reg->COUNT16.EVCTRL.bit.OVFEO = enable; break;
      }
      return _tc->evgen[evosel];
    }
 
    void direction(bool down) override
    {
      if (down)
        _reg->COUNT16.CTRLBSET.reg = TC_CTRLBSET_DIR;
      else
        _reg->COUNT16.CTRLBCLR.reg = TC_CTRLBCLR_DIR;
      sync();
    }
 
    void oneshot(bool enable) override
    {
      if (enable)
        _reg->COUNT16.CTRLBSET.reg = TC_CTRLBSET_ONESHOT;
      else
        _reg->COUNT16.CTRLBCLR.reg = TC_CTRLBCLR_ONESHOT;
      sync();
    }
 
    void interrupt(TCOUNTER_INT flag, bool enable) override
    {
      switch (flag)
      {
        case TCOUNTER_INT_MC0:
          if (enable)
            _reg->COUNT16.INTENSET.reg = TC_INTENSET_MC0;
          else
            _reg->COUNT16.INTENCLR.reg = TC_INTENCLR_MC0;
          break;
        case TCOUNTER_INT_MC1:
          if (enable)
            _reg->COUNT16.INTENSET.reg = TC_INTENSET_MC1;
          else
            _reg->COUNT16.INTENCLR.reg = TC_INTENCLR_MC1;
          break;
        case TCOUNTER_INT_OVF:
          if (enable)
            _reg->COUNT16.INTENSET.reg = TC_INTENSET_OVF;
          else
            _reg->COUNT16.INTENCLR.reg = TC_INTENCLR_OVF;
          break;
        case TCOUNTER_INT_ERR:
          if (enable)
            _reg->COUNT16.INTENSET.reg = TC_INTENSET_ERR;
          else
            _reg->COUNT16.INTENCLR.reg = TC_INTENCLR_ERR;
          break;
      }
    }
 
    void capture(TCOUNTER_MC mc, bool enable) override
    {
      switch (mc)
      {
        case TCOUNTER_MC0: _reg->COUNT16.CTRLC.bit.CPTEN0 = enable; break;
        case TCOUNTER_MC1: _reg->COUNT16.CTRLC.bit.CPTEN1 = enable; break;
      }
      sync();
    }
 
    bool output(TCOUNTER_MC mc, uint32_t pin, bool enable, bool invert = false) override
    {
      for (uint32_t i = 0; i < sizeof(_tc->wo[0]) / sizeof(_tc->wo[0][0]); ++i)
      {
        if (_tc->wo[mc][i] == pin)
        {
          if (enable)
          {
            switch (mc)
            {
              case TCOUNTER_MC0: _reg->COUNT16.CTRLC.bit.INVEN0 = invert; break;
              case TCOUNTER_MC1: _reg->COUNT16.CTRLC.bit.INVEN1 = invert; break;
            }
            sync();
            IOBUS::pinMode(pin, OUTPUT, true);
            IOBUS::multiplexing(pin, IOBUS_PMUX_E);
          }
          else
          {
#ifdef SEEED_XIAO_M0
            if ((pin != TCOUNTER_TC3_WO0_PIN_RX_LED) && (pin != TCOUNTER_TC3_WO1_PIN_TX_LED))
#endif
              IOBUS::pinMode(pin, DISABLE);
          }
          return true;
        }
      }
      return false;
    }
 
    void start(void) override
    {
      _reg->COUNT16.CTRLA.bit.ENABLE = 1;
      sync();
    }
 
    void stop(void) override
    {
      _reg->COUNT16.CTRLA.bit.ENABLE = 0;
      sync();
    }
 
    bool running(void) override
    {
      return !_reg->COUNT16.STATUS.bit.STOP;
    }
 
    void command(TCOUNTER_CMD cmd) override
    {
      _reg->COUNT16.CTRLBSET.reg = TC_CTRLBSET_CMD(cmd);
      sync();
    }
 
    void debugControl(bool dgbrun) override
    {
      _reg->COUNT16.DBGCTRL.bit.DBGRUN = dgbrun;
    }
 
    void count(uint32_t value) override
    {
      switch (_reg->COUNT16.CTRLA.bit.MODE)
      {
        case TC_CTRLA_MODE_COUNT8_Val : _reg->COUNT8.COUNT.reg  = (uint8_t )value; break;
        case TC_CTRLA_MODE_COUNT16_Val: _reg->COUNT16.COUNT.reg = (uint16_t)value; break;
        case TC_CTRLA_MODE_COUNT32_Val: _reg->COUNT32.COUNT.reg = (uint32_t)value; break;
      }
      sync();
    }
 
    uint32_t count(void) override
    {
      if ((_reg->COUNT16.READREQ.reg & (TC_READREQ_RCONT | TC_READREQ_ADDR_Msk)) != (TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount16 *)0)->COUNT.reg)))
      {
        _reg->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount16 *)0)->COUNT.reg);
        sync();
      }
      switch (_reg->COUNT16.CTRLA.bit.MODE)
      {
        case TC_CTRLA_MODE_COUNT32_Val: return _reg->COUNT32.COUNT.bit.COUNT;
        case TC_CTRLA_MODE_COUNT16_Val: return _reg->COUNT16.COUNT.bit.COUNT;
        case TC_CTRLA_MODE_COUNT8_Val : return _reg->COUNT8.COUNT.bit.COUNT;
      }
      return 0;
    }
 
    void cc(TCOUNTER_MC mc, uint32_t value) override
    {
      switch (_reg->COUNT16.CTRLA.bit.MODE)
      {
        case TC_CTRLA_MODE_COUNT32_Val: _reg->COUNT32.CC[mc].reg = (uint32_t)value; break;
        case TC_CTRLA_MODE_COUNT16_Val: _reg->COUNT16.CC[mc].reg = (uint16_t)value; break;
        case TC_CTRLA_MODE_COUNT8_Val : _reg->COUNT8.CC[mc].reg  = (uint8_t )value; break;
      }
      sync();
    }
 
    uint32_t cc(TCOUNTER_MC mc) override
    {
      switch (_reg->COUNT16.CTRLA.bit.MODE)
      {
        case TC_CTRLA_MODE_COUNT32_Val:
          if ((_reg->COUNT32.READREQ.reg & (TC_READREQ_RCONT | TC_READREQ_ADDR_Msk)) != (TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount32 *)0)->CC[mc].reg)))
          {
            _reg->COUNT32.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount32 *)0)->CC[mc].reg);
            sync();
          }
          return _reg->COUNT32.CC[mc].bit.CC;
        case TC_CTRLA_MODE_COUNT16_Val:
          if ((_reg->COUNT16.READREQ.reg & (TC_READREQ_RCONT | TC_READREQ_ADDR_Msk)) != (TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount16 *)0)->CC[mc].reg)))
          {
            _reg->COUNT16.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount16 *)0)->CC[mc].reg);
            sync();
          }
          return _reg->COUNT16.CC[mc].bit.CC;
        case TC_CTRLA_MODE_COUNT8_Val:
          if ((_reg->COUNT8.READREQ.reg & (TC_READREQ_RCONT | TC_READREQ_ADDR_Msk)) != (TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount8 *)0)->CC[mc].reg)))
          {
            _reg->COUNT8.READREQ.reg = TC_READREQ_RREQ | TC_READREQ_RCONT | TC_READREQ_ADDR((int)&((TcCount8 *)0)->CC[mc].reg);
            sync();
          }
          return _reg->COUNT8.CC[mc].bit.CC;
      }
      return 0;
    }
 
    void per(uint32_t value) override
    {
      if (_reg->COUNT16.CTRLA.bit.MODE == TC_CTRLA_MODE_COUNT8_Val)
      {
        _reg->COUNT8.PER.reg = (uint8_t)value;
        sync();
      }
    }
 
    uint32_t per(void) override
    {
      return (_reg->COUNT16.CTRLA.bit.MODE == TC_CTRLA_MODE_COUNT8_Val ? _reg->COUNT8.PER.bit.PER : 0);
    }
};
 
class TCFactory
{
  private:
 
    static const TCOUNTER_T *alloc0(TCOUNTER_MODE mode, TCOUNTER_ID id);
 
    static TCounter *alloc(const TCOUNTER_T *tc, TCOUNTER_MODE mode, TCOUNTER_WAVEGEN wavegen, TCOUNTER_PRESCSYNC pssync, bool runstdby)
    {
      if (tc == 0)
        return 0;
      return tc->id <= TCOUNTER_ID_TCC2
        ? (TCounter *) new TCCImplement(tc, wavegen, pssync, runstdby)
        : (TCounter *) new TCImplement (tc, mode, wavegen, pssync, runstdby);
    }
 
  public:
 
    static TCounter *alloc(TCOUNTER_MODE mode, TCOUNTER_WAVEGEN wavegen, TCOUNTER_PRESCSYNC pssync = TCOUNTER_PRESCSYNC_RESYNC, bool runstdby = false)
    {
      return alloc(alloc0(mode, TCOUNTER_ID_ANY), mode, wavegen, pssync, runstdby);
    }
 
    static TCounter *alloc(TCOUNTER_ID id, TCOUNTER_MODE mode, TCOUNTER_WAVEGEN wavegen, TCOUNTER_PRESCSYNC pssync = TCOUNTER_PRESCSYNC_RESYNC, bool runstdby = false)
    {
      return alloc(alloc0(mode, id), mode, wavegen, pssync, runstdby);
    }
};
 
#endif
