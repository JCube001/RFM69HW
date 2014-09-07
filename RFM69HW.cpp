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

#include <SPI.h>
#include "RFM69HW.h"

const uint16_t RFM69HW::FREQUENCY_MULTIPLIER = 16384;
const uint8_t RFM69HW::FSTEP_HZ = 61;
const uint32_t RFM69HW::FXOSC_HZ = 32 * 1000000;
const uint8_t RFM69HW::VERSION = 0x24;

RFM69HW::RFM69HW(const int8_t slaveSelectPin, const int8_t resetPin) :
    slaveSelectPin(slaveSelectPin),
    resetPin(resetPin)
{
    pinMode(slaveSelectPin, OUTPUT);
    if (resetPin >= 0)
    {
        pinMode(resetPin, OUTPUT);
    }
}

bool RFM69HW::begin()
{
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    digitalWrite(slaveSelectPin, HIGH);
    if (resetPin >= 0)
    {
        digitalWrite(resetPin, LOW);
    }
    delay(10);
    if (version() == VERSION)
    {
        return true;
    }
    return false;
}

uint32_t RFM69HW::bitRate()
{
    const uint16_t br = readRegister2(REG_BITRATEMSB);
    return (uint16_t)(((float)FXOSC_HZ / br) + 0.5f);
}

void RFM69HW::calibrateOscillator()
{
    standby();
    writeRegister1(REG_OSC1, OSC1_RC_CAL_START);
    while (!(readRegister1(REG_OSC1) & OSC1_RC_CAL_DONE));
}

uint16_t RFM69HW::carrierFrequency()
{
    const uint32_t frf = readRegister3(REG_FRFMSB);
    return frf / FREQUENCY_MULTIPLIER;
}

uint32_t RFM69HW::frequencyDeviation()
{
    const uint16_t fdev = readRegister2(REG_FDEVMSB);
    return fdev * FSTEP_HZ;
}

void RFM69HW::reset()
{
    if (resetPin >= 0)
    {
        digitalWrite(resetPin, HIGH);
        delayMicroseconds(100);
        digitalWrite(resetPin, LOW);
        delay(5);
    }
}

void RFM69HW::setBitRate(const uint32_t bps)
{
    if (1200 <= bps && bps <= 300000)
    {
        const uint16_t br = (uint16_t)(((float)FXOSC_HZ / bps) + 0.5f);
        writeRegister2(REG_BITRATEMSB, br);
    }
}

void RFM69HW::setCarrierFrequency(const uint16_t mhz)
{
    if (290 <= mhz && mhz <= 1020)
    {
        const uint32_t frf = (uint32_t)mhz * FREQUENCY_MULTIPLIER;
        writeRegister3(REG_FRFMSB, frf);
    }
}

void RFM69HW::setFrequencyDeviation(const uint32_t hz)
{
    if (2000 <= hz && hz <= 75000)
    {
        const uint16_t fdev = (uint16_t)(((float)hz / FSTEP_HZ) + 0.5f);
        writeRegister2(REG_FDEVMSB, fdev);
    }
}

void RFM69HW::sleep()
{
    writeRegister1(REG_OPMODE, OPMODE_MODE_SLEEP);
}

void RFM69HW::standby()
{
    writeRegister1(REG_OPMODE, OPMODE_MODE_STDBY);
}

int8_t RFM69HW::temperature()
{
    standby();
    writeRegister1(REG_TEMP1, TEMP1_TEMP_MEAS_START);
    while (readRegister1(REG_TEMP1) & TEMP1_TEMP_MEAS_RUNNING);
    return map(readRegister1(REG_TEMP2), 0xFF, 0x00, -40, 85) + 10;
}

uint8_t RFM69HW::version()
{
    return readRegister1(REG_VERSION);
}

uint8_t RFM69HW::readRegister1(const uint8_t reg)
{
    uint8_t value;
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg & 0x7F);
    value = SPI.transfer(0x00);
    digitalWrite(slaveSelectPin, HIGH);
    return value;
}

uint16_t RFM69HW::readRegister2(const uint8_t reg)
{
    uint16_t value = 0;
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg & 0x7F);
    value |= ((uint16_t)SPI.transfer(0x00) << 8) & 0xFF00;
    value |= (uint16_t)SPI.transfer(0x00) & 0x00FF;
    digitalWrite(slaveSelectPin, HIGH);
    return value;
}

uint32_t RFM69HW::readRegister3(const uint8_t reg)
{
    uint32_t value = 0;
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg & 0x7F);
    value |= ((uint32_t)SPI.transfer(0x00) << 16) & 0xFF0000;
    value |= ((uint32_t)SPI.transfer(0x00) << 8) & 0x00FF00;
    value |= (uint32_t)SPI.transfer(0x00) & 0x0000FF;
    digitalWrite(slaveSelectPin, HIGH);
    return value;
}

void RFM69HW::writeRegister1(const uint8_t reg, const uint8_t value)
{
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg | 0x80);
    SPI.transfer(value);
    digitalWrite(slaveSelectPin, HIGH);
}

void RFM69HW::writeRegister2(const uint8_t reg, const uint16_t value)
{
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg | 0x80);
    SPI.transfer((uint8_t)((value & 0xFF00) >> 8));
    SPI.transfer((uint8_t)(value & 0x00FF));
    digitalWrite(slaveSelectPin, HIGH);
}

void RFM69HW::writeRegister3(const uint8_t reg, const uint32_t value)
{
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg | 0x80);
    SPI.transfer((uint8_t)((value & 0xFF0000) >> 16));
    SPI.transfer((uint8_t)((value & 0x00FF00) >> 8));
    SPI.transfer((uint8_t)(value & 0x0000FF));
    digitalWrite(slaveSelectPin, HIGH);
}
