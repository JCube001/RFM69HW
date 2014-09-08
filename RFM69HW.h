/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2014 Jacob McGladdery

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*******************************************************************************/

#ifndef RFM69HW_H
#define RFM69HW_H

#include <Arduino.h>

class RFM69HW
{
public:
    RFM69HW(const int8_t slaveSelectPin = SS, const int8_t resetPin = -1);
    bool begin(const uint32_t bps = 0);
    uint32_t bitRate();
    void calibrateOscillator();
    uint16_t carrierFrequency();
    uint32_t frequencyDeviation();
    void reset();
    void setBitRate(const uint32_t bps);
    void setCarrierFrequency(const uint16_t mhz);
    void setFrequencyDeviation(const uint32_t hz);
    void sleep();
    void standby();
    int8_t temperature();
    uint8_t version();

private:
    enum reg
    {
        REG_FIFO          = 0x00,
        REG_OPMODE        = 0x01,
        REG_DATAMODUL     = 0x02,
        REG_BITRATEMSB    = 0x03,
        REG_BITRATELSB    = 0x04,
        REG_FDEVMSB       = 0x05,
        REG_FDEVLSB       = 0x06,
        REG_FRFMSB        = 0x07,
        REG_FRFMID        = 0x08,
        REG_FRFLSB        = 0x09,
        REG_OSC1          = 0x0A,
        REG_AFCCTRL       = 0x0B,
        REG_RESERVED0C    = 0x0C,
        REG_LISTEN1       = 0x0D,
        REG_LISTEN2       = 0x0E,
        REG_LISTEN3       = 0x0F,
        REG_VERSION       = 0x10,
        REG_PALEVEL       = 0x11,
        REG_PARAMP        = 0x12,
        REG_OCP           = 0x13,
        REG_RESERVED14    = 0x14,
        REG_RESERVED15    = 0x15,
        REG_RESERVED16    = 0x16,
        REG_RESERVED17    = 0x17,
        REG_LNA           = 0x18,
        REG_RXBW          = 0x19,
        REG_AFCBW         = 0x1A,
        REG_OOKPEAK       = 0x1B,
        REG_OOKAVG        = 0x1C,
        REG_OOKFIX        = 0x1D,
        REG_AFCFEI        = 0x1E,
        REG_AFCMSB        = 0x1F,
        REG_AFCLSB        = 0x20,
        REG_FEIMSB        = 0x21,
        REG_FEILSB        = 0x22,
        REG_RSSICONFIG    = 0x23,
        REG_RSSIVALUE     = 0x24,
        REG_DIOMAPPING1   = 0x25,
        REG_DIOMAPPING2   = 0x26,
        REG_IRQFLAGS1     = 0x27,
        REG_IRQFLAGS2     = 0x28,
        REG_RSSITHRESH    = 0x29,
        REG_RXTIMEOUT1    = 0x2A,
        REG_RXTIMEOUT2    = 0x2B,
        REG_PREAMBLEMSB   = 0x2C,
        REG_PREAMBLELSB   = 0x2D,
        REG_SYNCCONFIG    = 0x2E,
        REG_SYNCVALUE1    = 0x2F,
        REG_SYNCVALUE2    = 0x30,
        REG_SYNCVALUE3    = 0x31,
        REG_SYNCVALUE4    = 0x32,
        REG_SYNCVALUE5    = 0x33,
        REG_SYNCVALUE6    = 0x34,
        REG_SYNCVALUE7    = 0x35,
        REG_SYNCVALUE8    = 0x36,
        REG_PACKETCONFIG1 = 0x37,
        REG_PAYLOADLENGTH = 0x38,
        REG_NODEADRS      = 0x39,
        REG_BROADCASTADRS = 0x3A,
        REG_AUTOMODES     = 0x3B,
        REG_FIFOTHRESH    = 0x3C,
        REG_PACKETCONFIG2 = 0x3D,
        REG_AESKEY1       = 0x3E,
        REG_AESKEY2       = 0x3F,
        REG_AESKEY3       = 0x40,
        REG_AESKEY4       = 0x41,
        REG_AESKEY5       = 0x42,
        REG_AESKEY6       = 0x43,
        REG_AESKEY7       = 0x44,
        REG_AESKEY8       = 0x45,
        REG_AESKEY9       = 0x46,
        REG_AESKEY10      = 0x47,
        REG_AESKEY11      = 0x48,
        REG_AESKEY12      = 0x49,
        REG_AESKEY13      = 0x4A,
        REG_AESKEY14      = 0x4B,
        REG_AESKEY15      = 0x4C,
        REG_AESKEY16      = 0x4D,
        REG_TEMP1         = 0x4E,
        REG_TEMP2         = 0x4F,
        REG_TESTLNA       = 0x58,
        REG_TESTPA1       = 0x5A,
        REG_TESTPA2       = 0x5C,
        REG_TESTDAGC      = 0x6F,
        REG_TESTAFC       = 0x71
    };

    enum opmode
    {
        OPMODE_SEQUENCER_OFF = 0x80,
        OPMODE_LISTEN_ON     = 0x40,
        OPMODE_LISTEN_ABORT  = 0x20,
        OPMODE_MODE          = 0x1C
    };

    enum opmode_mode
    {
        OPMODE_MODE_SLEEP = 0x00 << 2,
        OPMODE_MODE_STDBY = 0x01 << 2,
        OPMODE_MODE_FS    = 0x02 << 2,
        OPMODE_MODE_TX    = 0x03 << 2,
        OPMODE_MODE_RX    = 0x04 << 2
    };

    enum osc1
    {
        OSC1_RC_CAL_START = 0x80,
        OSC1_RC_CAL_DONE  = 0x40
    };

    enum temp1
    {
        TEMP1_TEMP_MEAS_START   = 0x08,
        TEMP1_TEMP_MEAS_RUNNING = 0x04
    };

    uint8_t readRegister1(const uint8_t reg);
    uint16_t readRegister2(const uint8_t reg);
    uint32_t readRegister3(const uint8_t reg);
    void writeRegister1(const uint8_t reg, const uint8_t value);
    void writeRegister2(const uint8_t reg, const uint16_t value);
    void writeRegister3(const uint8_t reg, const uint32_t value);

    static const uint32_t BITRATE_MAX_BPS;
    static const uint32_t BITRATE_MIN_BPS;
    static const uint32_t FDA_MAX_HZ;
    static const uint32_t FDA_MIN_HZ;
    static const uint16_t FR_MAX_MHZ;
    static const uint16_t FR_MIN_MHZ;
    static const uint16_t FREQUENCY_MULTIPLIER;
    static const uint8_t FSTEP_HZ;
    static const uint32_t FXOSC_HZ;
    static const uint8_t VERSION;
    const int8_t resetPin;
    const int8_t slaveSelectPin;
};

#endif // RFM69HW_H

