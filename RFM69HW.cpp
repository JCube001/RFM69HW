/*
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
*/

/**
 * @file  RFM69HW.cpp
 * @brief Implementation for the RFM69HW driver.
 */

#include <SPI.h>
#include "RFM69HW.h"
#include "RFM69HW_config.h"

/**
 * @addtogroup RFM69HW
 * @{
 */

const uint8_t RFM69HW::AESKEY_NUM_BYTES = 16;
const uint32_t RFM69HW::BITRATE_MAX_BPS = 300 * 1000;
const uint32_t RFM69HW::BITRATE_MIN_BPS = 1200;
const uint32_t RFM69HW::FDA_MAX_HZ = 500 * 1000;
const uint32_t RFM69HW::FDA_MIN_HZ = 600;
#if RFM69HW_MODULE_FR_MHZ == 315
const uint16_t RFM69HW::FR_MAX_MHZ = 340;
const uint16_t RFM69HW::FR_MIN_MHZ = 290;
#elif RFM69HW_MODULE_FR_MHZ == 433
const uint16_t RFM69HW::FR_MAX_MHZ = 510;
const uint16_t RFM69HW::FR_MIN_MHZ = 424;
#elif RFM69HW_MODULE_FR_MHZ == 868
const uint16_t RFM69HW::FR_MAX_MHZ = 890;
const uint16_t RFM69HW::FR_MIN_MHZ = 862;
#elif RFM69HW_MODULE_FR_MHZ == 915
const uint16_t RFM69HW::FR_MAX_MHZ = 1020;
const uint16_t RFM69HW::FR_MIN_MHZ = 890;
#else
#error RFM69HW_MODULE_FR_MHZ must be defined as either 315, 433, 868, or 915
#endif // RFM69HW_MODULE_FR_MHZ
const uint16_t RFM69HW::FREQUENCY_MULTIPLIER = 16384;
const uint8_t RFM69HW::FSTEP_HZ = 61;
const uint32_t RFM69HW::FXOSC_HZ = 32 * 1000000;
const uint8_t RFM69HW::SYNCVALUE_NUM_BYTES = 8;
const float RFM69HW::TEMP_MAX_C = 85.0f;
const float RFM69HW::TEMP_MIN_C = -40.0f;
const uint8_t RFM69HW::VERSION = 0x24;

/**
 * @brief   Constructor.
 * @details Initializes the RFM69HW radio driver with the values of the SPI
 *          slave select pin and the reset pin.
 *
 * @param[in] slaveSelectPin The GPIO pin to use for slave select with the
 *                           radio. If not specified, then this value defaults
 *                           to using the Arduino macro SS.
 * @param[in] resetPin       The GPIO pin to use for reseting the radio. If not
 *                           specified, then the manual reset feature will be
 *                           disabled.
 */
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

/**
 * @brief   Initializes the SPI bus, GPIO, and some common parameters.
 * @details Starts the SPI bus and sets its bit order, data mode, and clock
 *          divider so as to be suitable for use with the RFM69HW. The initial
 *          bit rate and carrier frequency of the radio can also be set.
 *
 * @param[in] bps   The radio bit rate in bits per second.
 * @param[in] mhz   The radio carrier frequency in megahertz.
 * @retval    true  If the radio module can be communicated with.
 * @retval    false If the radio module can not be communicated with.
 * @return          Whether or not the radio started successfully.
 */
bool RFM69HW::begin(const uint32_t bps, const uint16_t mhz)
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
        setBitRate(bps);
        setCarrierFrequency(mhz);
        return true;
    }
    return false;
}

/**
 * @brief   Gets the current bit rate.
 * @details Reads the bit rate of the radio and converts to bits per second.
 * @f[
 *   \text{BitRate} = \frac{\text{FXOSC}}{\text{BitRate}_{\text{Register}}}
 * @f]
 *
 * @return The bit rate of the radio in bits per second.
 */
uint32_t RFM69HW::bitRate()
{
    const uint16_t br = read16(RFM69HW_BITRATEMSB);
    return (uint32_t)(((float)FXOSC_HZ / br) + 0.5f);
}

/**
 * @brief   Gets the current broadcast address.
 * @details Reads the broadcast address of the radio.
 *
 * @return The numeric broadcast address.
 */
uint8_t RFM69HW::broadcastAddress()
{
    return read8(RFM69HW_BROADCASTADRS);
}

void RFM69HW::calibrateOscillator()
{
    standby();
    write8(RFM69HW_OSC1, RFM69HW_OSC1_RC_CAL_START);
    while (!(read8(RFM69HW_OSC1) & RFM69HW_OSC1_RC_CAL_DONE));
}

uint16_t RFM69HW::carrierFrequency()
{
    const uint32_t frf = read24(RFM69HW_FRFMSB);
    return frf / FREQUENCY_MULTIPLIER;
}

uint32_t RFM69HW::frequencyDeviation()
{
    const uint16_t fdev = read16(RFM69HW_FDEVMSB);
    return fdev * FSTEP_HZ;
}

uint8_t RFM69HW::nodeAddress()
{
    return read8(RFM69HW_NODEADRS);
}

uint8_t RFM69HW::payloadLength()
{
    return read8(RFM69HW_PAYLOADLENGTH);
}

/**
 * @brief   Gets the preamble size.
 * @details Reads the preamble size from the radio.
 *
 * @return The preamble size in bytes.
 */
uint16_t RFM69HW::preambleSize()
{
    return read16(RFM69HW_PREAMBLEMSB);
}

/**
 * @brief   Gets the received signal strength.
 * @details Reads the Received Signal Strength Indicator (RSSI) on the radio.
 * @f[
 *   \text{RSSI} = \frac{-\text{RssiValue}_{\text{Register}}}{2}
 * @f]
 *
 * @return The signal strength in Decibel-milliwatts.
 */
float RFM69HW::signalStrength()
{
    write8(RFM69HW_RSSICONFIG, RFM69HW_RSSICONFIG_START);
    while (!(read8(RFM69HW_RSSICONFIG) & RFM69HW_RSSICONFIG_DONE));
    return -((float)read8(RFM69HW_RSSIVALUE)) / 2.0f;
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
    if ((BITRATE_MIN_BPS <= bps) && (bps <= BITRATE_MAX_BPS))
    {
        const uint16_t br = (uint16_t)(((float)FXOSC_HZ / bps) + 0.5f);
        write16(RFM69HW_BITRATEMSB, br);
    }
}

void RFM69HW::setBroadcastAddress(const uint8_t address)
{
    write8(RFM69HW_BROADCASTADRS, address);
}

/**
 * @brief   Sets the carrier frequency.
 * @details Writes a new carrier frequency value to radio module. This switches
 *          the channel the radio is operating on.
 * @note    This function will step through different operating modes while
 *          changing the channel in order to avoid spectral splatter. Therefore
 *          this function is safe to use in rapid frequency hopping
 *          applications.
 * @warning The caller of this function must respect either the Rx or Tx start
 *          procedures, depending on what mode they were in. This means waiting
 *          for either the Rx ready or Tx ready interrupt to fire before
 *          attempting to use the radio after a channel switch. If listening
 *          for those interrupts is not possible, then the calling code should
 *          have a delay or at least one millisecond after the call to this
 *          function. 
 *
 * @param[in] mhz The carrier frequency to set in megahertz.
 */
void RFM69HW::setCarrierFrequency(const uint16_t mhz)
{
    if ((FR_MIN_MHZ <= mhz) && (mhz <= FR_MAX_MHZ))
    {
        const uint32_t frf = (uint32_t)mhz * FREQUENCY_MULTIPLIER;
        const uint8_t mode = read8(RFM69HW_OPMODE);
        switch (mode & RFM69HW_OPMODE_MODE)
        {
        case RFM69HW_OPMODE_MODE_TX:
            write8(RFM69HW_OPMODE, RFM69HW_OPMODE_MODE_RX);
            write24(RFM69HW_FRFMSB, frf);
            write8(RFM69HW_OPMODE, RFM69HW_OPMODE_MODE_TX);
            break;
        case RFM69HW_OPMODE_MODE_RX:
            write24(RFM69HW_FRFMSB, frf);
            write8(RFM69HW_OPMODE, RFM69HW_OPMODE_MODE_FS);
            write8(RFM69HW_OPMODE, RFM69HW_OPMODE_MODE_RX);
            break;
        default:
            write24(RFM69HW_FRFMSB, frf);
            break;
        }
    }
}

void RFM69HW::setEncryptionKey(const char *key, const uint8_t length)
{
    if ((NULL != key) && ((0 < length) && (length <= AESKEY_NUM_BYTES)))
    {
        digitalWrite(slaveSelectPin, LOW);
        SPI.transfer(RFM69HW_AESKEY1 | 0x80);
        for (uint8_t i = 0; i < length; ++i)
        {
            SPI.transfer(key[i]);
        }
        // Fill in any remaining bytes with 0
        for (uint8_t i = 0; i < (AESKEY_NUM_BYTES - length); ++i)
        {
            SPI.transfer(0x00);
        }
        digitalWrite(slaveSelectPin, HIGH);
    }
}

void RFM69HW::setFrequencyDeviation(const uint32_t hz)
{
    if ((FDA_MIN_HZ <= hz) && (hz <= FDA_MAX_HZ))
    {
        const uint16_t fdev = (uint16_t)(((float)hz / FSTEP_HZ) + 0.5f);
        write16(RFM69HW_FDEVMSB, fdev);
    }
}

void RFM69HW::setNodeAddress(const uint8_t address)
{
    write8(RFM69HW_NODEADRS, address);
}

void RFM69HW::setPayloadLength(const uint8_t length)
{
    write8(RFM69HW_PAYLOADLENGTH, length);
}

/**
 * @brief   Sets the preamble size.
 * @details Writes a new preamble size to the radio.
 *
 * @param[in] size The new size of the preamble in bytes.
 */
void RFM69HW::setPreambleSize(const uint16_t size)
{
    write16(RFM69HW_PREAMBLEMSB, size);
}

void RFM69HW::setSyncWord(const char *word, const uint8_t length)
{
    if ((NULL != word) && ((0 < length) && (length <= SYNCVALUE_NUM_BYTES)))
    {
        digitalWrite(slaveSelectPin, LOW);
        SPI.transfer(RFM69HW_SYNCVALUE1 | 0x80);
        for (uint8_t i = 0; i < length; ++i)
        {
            SPI.transfer(word[i]);
        }
        digitalWrite(slaveSelectPin, HIGH);
        // Update the sync size value in the sync config register
        const uint8_t config = (read8(RFM69HW_SYNCCONFIG) & 0xC7)
                | ((length - 1) << 3);
        write8(RFM69HW_SYNCCONFIG, config);
    }
}

void RFM69HW::sleep()
{
    write8(RFM69HW_OPMODE, RFM69HW_OPMODE_MODE_SLEEP);
}

void RFM69HW::standby(const bool listen)
{
    const uint8_t mode = read8(RFM69HW_OPMODE);
    if (listen)
    {
        write8(RFM69HW_OPMODE,
               RFM69HW_OPMODE_LISTEN_ON | RFM69HW_OPMODE_MODE_STDBY);
    }
    else if (mode & RFM69HW_OPMODE_LISTEN_ON)
    {
        write8(RFM69HW_OPMODE,
               RFM69HW_OPMODE_LISTEN_ABORT | RFM69HW_OPMODE_MODE_STDBY);
        write8(RFM69HW_OPMODE, RFM69HW_OPMODE_MODE_STDBY);
    }
    else
    {
        write8(RFM69HW_OPMODE, RFM69HW_OPMODE_MODE_STDBY);
    }
}

/**
 * @brief   Gets the temperature of the radio module.
 * @details Reads the temperature of the radio and converts it to degrees
 *          Celsius.
 * @warning The CMOS temperature sensor on the RFM69HW is known to be wildly
 *          inaccurate. If you really wish to make use of this sensor, then
 *          you will need to take an initial reading and compare it against
 *          the known ambient temperature. The difference between the two
 *          values can then be used as an offset for estimating the actual
 *          temperature based on future return values from this function.
 *
 * @return The temperature of the radio module in degrees Celsius.
 */
float RFM69HW::temperature()
{
    standby();
    write8(RFM69HW_TEMP1, RFM69HW_TEMP1_MEAS_START);
    while (read8(RFM69HW_TEMP1) & RFM69HW_TEMP1_MEAS_RUNNING);
    return mapTemperature(read8(RFM69HW_TEMP2));
}

/**
 * @brief   Gets the entire numeric version ID from the radio module.
 * @details Reads the version register of the radio as-is.
 *
 * @retval 0x24 The expected version number of the RFM69HW.
 * @return      The full version number of the radio module.
 */
uint8_t RFM69HW::version()
{
    return read8(RFM69HW_VERSION);
}

/**
 * @brief   Linear mapping function for computing temperature.
 * @details Function for computing the temperature read from the CMOS sensor on
 *          the radio module to degrees Celsius. Uses hard-coded values to
 *          speed up computation.
 *
 * @param[in] value The raw temperature value read from the device register.
 * @return          The computed temperature in degrees Celsius.
 */
float RFM69HW::mapTemperature(const uint8_t value)
{
    return ((((float)value - 255.0f) / -255.0f) * (TEMP_MAX_C - TEMP_MIN_C))
            + TEMP_MIN_C;
}

/**
 * @brief   Reads one register.
 * @details Performs a read-only SPI transfer of the register @p reg.
 *
 * @param[in] reg The register to read.
 * @return        The 8-bit value read from the register.
 */
uint8_t RFM69HW::read8(const uint8_t reg)
{
    uint8_t value;
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg & 0x7F);
    value = SPI.transfer(0x00);
    digitalWrite(slaveSelectPin, HIGH);
    return value;
}

/**
 * @brief   Reads two registers.
 * @details Performs a burst mode read-only SPI transfer of the register @p reg
 *          and the register at the next address.
 *
 * @param[in] reg The register to start reading at.
 * @return        The 16-bit value read from the two registers.
 */
uint16_t RFM69HW::read16(const uint8_t reg)
{
    uint16_t value = 0;
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg & 0x7F);
    value |= ((uint16_t)SPI.transfer(0x00) << 8) & 0xFF00;
    value |= (uint16_t)SPI.transfer(0x00) & 0x00FF;
    digitalWrite(slaveSelectPin, HIGH);
    return value;
}

/**
 * @brief   Reads three registers.
 * @details Performs a burst mode read-only SPI transfer of the register @p reg
 *          and the registers at the next two addresses.
 *
 * @param[in] reg The register to start reading at.
 * @return        The 24-bit value read from the three registers.
 */
uint32_t RFM69HW::read24(const uint8_t reg)
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

/**
 * @brief   Writes one register.
 * @details Performs a write-only SPI transfer of the register @p reg.
 *
 * @param[in] reg   The register to write.
 * @param[in] value The 8-bit value to write to the register.
 */
void RFM69HW::write8(const uint8_t reg, const uint8_t value)
{
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg | 0x80);
    SPI.transfer(value);
    digitalWrite(slaveSelectPin, HIGH);
}

/**
 * @brief   Writes two registers.
 * @details Performs a burst mode write-only SPI transfer of the register
 *          @p reg and the register at the next address.
 *
 * @param[in] reg   The register to start writing at.
 * @param[in] value The 16-bit value to write to the registers.
 */
void RFM69HW::write16(const uint8_t reg, const uint16_t value)
{
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg | 0x80);
    SPI.transfer((uint8_t)((value & 0xFF00) >> 8));
    SPI.transfer((uint8_t)(value & 0x00FF));
    digitalWrite(slaveSelectPin, HIGH);
}

/**
 * @brief   Writes three registers.
 * @details Performs a burst mode write-only SPI transfer of the register
 *          @p reg and the registers at the next two addresses.
 *
 * @param[in] reg   The register to start writing at.
 * @param[in] value The 24-bit value to write to the registers.
 */
void RFM69HW::write24(const uint8_t reg, const uint32_t value)
{
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(reg | 0x80);
    SPI.transfer((uint8_t)((value & 0xFF0000) >> 16));
    SPI.transfer((uint8_t)((value & 0x00FF00) >> 8));
    SPI.transfer((uint8_t)(value & 0x0000FF));
    digitalWrite(slaveSelectPin, HIGH);
}

/** @} */

