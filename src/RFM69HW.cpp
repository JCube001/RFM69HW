/*
The MIT License (MIT)

Copyright (c) 2014-2016 Jacob McGladdery

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

#include "RFM69HW.h"

#include <SPI.h>
#include "RFM69HW_registers.h"

// Utilities
#define MILLION  (1000000)

// Device info
#define VERSION  (0x24)

// Clocks
#define FXOSC_HZ  (32 * MILLION)
#define FSTEP_HZ  (61)
#define SPI_SPEED_HZ  (10 * MILLION)

class SPIGuard {
public:
    SPIGuard(const uint8_t slaveSelectPin) :
        slaveSelectPin(slaveSelectPin)
    {
        SPI.beginTransaction(SPISettings(SPI_SPEED_HZ, MSBFIRST, SPI_MODE0));
        digitalWrite(slaveSelectPin, LOW);
    }

    ~SPIGuard() {
        digitalWrite(slaveSelectPin, HIGH);
        SPI.endTransaction();
    }

private:
    const uint8_t slaveSelectPin;
};

RFM69HW::RFM69HW(const int8_t slaveSelectPin, const int8_t resetPin) :
    Stream(),
    slaveSelectPin(slaveSelectPin),
    resetPin(resetPin)
{
}

bool RFM69HW::begin() {
    // Initialize SPI
    SPI.begin();

    // Setup and deassert the slave select pin
    pinMode(slaveSelectPin, OUTPUT);
    digitalWrite(slaveSelectPin, HIGH);

    // Setup and deassert the reset pin, if it was specified. Note that if the
    // reset pin was not left floating on the board, then the user must specify
    // the reset pin in order to ensure correct operation.
    if (resetPin >= 0) {
        pinMode(resetPin, OUTPUT);
        digitalWrite(resetPin, LOW);
    }

    // The RFM69HW module performs an automatic power-on reset at power up.
    // Need to wait for 10 ms before commencing communication on SPI.
    delay(10);

    // Sanity check to make sure we're really communicating with a RFM69HW
    if (version() != VERSION)
        return false;

    // Disable the CLKOUT signal. It shouldn't be needed for anything and
    // disabling it reduces current consumption.
    write8(RFM69HW_DIOMAPPING2, RFM69HW_DIOMAPPING2_CLKOUT_OFF);

    // Set the TX start condition to be whenever data has been written into the
    // FIFO. This will cause the transmit function to transmit data immediatly.
    write8(RFM69HW_FIFOTHRESH, RFM69HW_FIFOTHRESH_TX_START_FIFO_NOT_EMPTY);

    return true;
}

bool RFM69HW::begin(const uint32_t baudRate, const uint32_t frequency) {
    if (!begin())
        return false;

    // Set the frequency and baud rate to use
    setBaudRate(baudRate);
    setCarrierFrequencyMHz(frequency);

    return true;
}

void RFM69HW::reset() {
    if (resetPin < 0)
        return;

    // The manual reset sequence is:
    //   1) Pull the reset pin high for 100 us
    //   2) Pull the reset pin back to low
    //   3) Wait for 5 ms before using the device again
    digitalWrite(resetPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(resetPin, LOW);
    delay(5);
}

#if 0
void RFM69HW::transmit(const void* payload, uint8_t size) {
    // Change the op mode to standby. This will prevent the radio from
    // receiving anything and therefore overwriting the FIFO while we are still
    // sending the current payload out.
    standby();

    // Write the payload to the device FIFO
    {
        volatile SPIGuard guard(slaveSelectPin);
        SPI.transfer(RFM69HW_FIFO | 0x80);
        for (uint8_t i = 0; i < size; ++i)
            SPI.transfer(((uint8_t*)payload)[i]);
    }

    // Change the op mode to TX. As long as the TX start condition has been set
    // to FIFO not empty, then the transmission will occur immediatly.
    setOpMode(RFM69HW_OPMODE_MODE_TX);

    // Wait until the transmission has completed
    while (~read8(RFM69HW_IRQFLAGS2) & RFM69HW_IRQFLAGS2_PACKET_SENT);

    // Transmission complete. Change the op mode to standby.
    standby();
}
#endif

int RFM69HW::available() {
    // TODO
}

int RFM69HW::peek() {
    // TODO
}

void RFM69HW::flush() {
    // TODO
}

int RFM69HW::read() {
    // TODO
}

size_t RFM69HW::write(uint8_t value) {
    // TODO
}

size_t RFM69HW::write(const uint8_t* buffer, size_t size) {
    // TODO
}

void RFM69HW::standby() {
    setOpMode(RFM69HW_OPMODE_MODE_STANDBY);
}

void RFM69HW::sleep() {
    setOpMode(RFM69HW_OPMODE_MODE_SLEEP);
}

uint32_t RFM69HW::baudRate() {
    return FXOSC_HZ / read16(RFM69HW_BITRATEMSB);
}

void RFM69HW::setBaudRate(const uint32_t value) {
    write16(RFM69HW_BITRATEMSB, FXOSC_HZ / value);
}

uint32_t RFM69HW::carrierFrequency() {
    return FSTEP_HZ * read24(RFM69HW_FRFMSB);
}

void RFM69HW::setCarrierFrequency(const uint32_t value) {
    const uint32_t frf = value / FSTEP_HZ;

    // Handle hopping under different op modes
    switch (read8(RFM69HW_OPMODE) & RFM69HW_OPMODE_MODE_MASK) {
    case RFM69HW_OPMODE_MODE_TX:
        // Transmitter channel hop sequence:
        //   1) Set the op mode to RX
        //   2) Change the carrier frequency
        //   3) Set the op mode back to TX
        //   4) Wait for the TX start procedure to finish
        setOpMode(RFM69HW_OPMODE_MODE_RX);
        write24(RFM69HW_FRFMSB, frf);
        setOpMode(RFM69HW_OPMODE_MODE_TX);
        while (~read8(RFM69HW_IRQFLAGS1) & RFM69HW_IRQFLAGS1_TX_READY);
        break;
    case RFM69HW_OPMODE_MODE_RX:
        // Receiver channel hop sequence:
        //   1) Change the carrier frequency
        //   2) Set the op mode to FS
        //   3) Set the op mode back to RX
        //   4) Wait for the RX start procedure to finish
        write24(RFM69HW_FRFMSB, frf);
        setOpMode(RFM69HW_OPMODE_MODE_FS);
        setOpMode(RFM69HW_OPMODE_MODE_RX);
        while (~read8(RFM69HW_IRQFLAGS1) & RFM69HW_IRQFLAGS1_RX_READY);
        break;
    default:
        // Change the carrier frequency. It can take up to 80 us before the
        // channel hop is completed
        write24(RFM69HW_FRFMSB, frf);
        delayMicroseconds(80);
        break;
    }
}

uint32_t RFM69HW::carrierFrequencyMHz() {
    return carrierFrequency() / MILLION;
}

void RFM69HW::setCarrierFrequencyMHz(const uint32_t value) {
    setCarrierFrequency(value * MILLION);
}

int8_t RFM69HW::receivedSignalStrength() {
    // Take the measurement
    write8(RFM69HW_RSSICONFIG, RFM69HW_RSSICONFIG_RSSI_START);
    while (~read8(RFM69HW_RSSICONFIG) & RFM69HW_RSSICONFIG_RSSI_DONE);

    // Convert the measured value to decibal-milliwatts. The equation used is:
    // y = -x / 2. This equation comes from the RSSI value register
    // documentation in the datasheet.
    return -((int16_t)read8(RFM69HW_RSSIVALUE)) / 2;
}

uint8_t RFM69HW::version() {
    return read8(RFM69HW_VERSION);
}

int8_t RFM69HW::temperature() {
    // This procedure can only be run in standby or FS op mode
    standby();

    // Take the measurement. According to the datasheet, this should finish in
    // less then 100 us.
    write8(RFM69HW_TEMP1, RFM69HW_TEMP1_MEAS_START);
    while (read8(RFM69HW_TEMP1) & RFM69HW_TEMP1_MEAS_RUNNING);

    // Convert the measured value to degrees Celsius. The conversion involves
    // taking the measurement and passing it through the equation:
    // y = -x + 170. This equation does not come from the datasheet. It was
    // found through testing where a value of 150 was found to be equal to a
    // temperature of 20 C, and 140 was found to be equal to 30 C. The
    // temperature sensor measures temperature using an ADC as -1 C per LSB, so
    // the equation is obviously linear.
    return -((int16_t)read8(RFM69HW_TEMP2)) + 170;
}

void RFM69HW::calibrateOscillator() {
    // This procedure can only be run in standby mode
    standby();

    // Trigger calibration and wait for it to finish. Unknown exactly how long
    // this may take. Worst case time would be 500 us.
    write8(RFM69HW_OSC1, RFM69HW_OSC1_RC_CAL_START);
    while (~read8(RFM69HW_OSC1) & RFM69HW_OSC1_RC_CAL_DONE);
}

void RFM69HW::setOpMode(const uint8_t value) {
    // Set the operating mode. Wait until the mode ready interrupt occurs
    // before continuing.
    write8(RFM69HW_OPMODE, value);
    while (~read8(RFM69HW_IRQFLAGS1) & RFM69HW_IRQFLAGS1_MODE_READY);
}

uint8_t RFM69HW::read8(const uint8_t reg) {
    volatile SPIGuard guard(slaveSelectPin);
    SPI.transfer(reg);
    return SPI.transfer(0x00);
}

uint16_t RFM69HW::read16(const uint8_t reg) {
    uint16_t value = 0;
    volatile SPIGuard guard(slaveSelectPin);
    SPI.transfer(reg);
    value |= (uint16_t)SPI.transfer(0x00) << 8;
    value |= (uint16_t)SPI.transfer(0x00);
    return value;
}

uint32_t RFM69HW::read24(const uint8_t reg) {
    uint32_t value = 0;
    volatile SPIGuard guard(slaveSelectPin);
    SPI.transfer(reg);
    value |= (uint32_t)SPI.transfer(0x00) << 16;
    value |= (uint32_t)SPI.transfer(0x00) << 8;
    value |= (uint32_t)SPI.transfer(0x00);
    return value;
}

void RFM69HW::write8(const uint8_t reg, const uint8_t value) {
    volatile SPIGuard guard(slaveSelectPin);
    SPI.transfer(reg | 0x80);
    SPI.transfer(value);
}

void RFM69HW::write16(const uint8_t reg, const uint16_t value) {
    volatile SPIGuard guard(slaveSelectPin);
    SPI.transfer(reg | 0x80);
    SPI.transfer((value & 0xFF00) >> 8);
    SPI.transfer((value & 0x00FF));
}

void RFM69HW::write24(const uint8_t reg, const uint32_t value) {
    volatile SPIGuard guard(slaveSelectPin);
    SPI.transfer(reg | 0x80);
    SPI.transfer((value & 0xFF0000) >> 16);
    SPI.transfer((value & 0x00FF00) >> 8);
    SPI.transfer((value & 0x0000FF));
}
