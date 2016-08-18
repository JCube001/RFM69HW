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

#ifndef _RFM69HW_H_
#define _RFM69HW_H_

#include <Arduino.h>
#include <stdint.h>

class RFM69HW : public Stream {
public:
    RFM69HW(const int8_t interruptPin, const int8_t slaveSelectPin=SS, const int8_t resetPin=-1);

    bool begin();
    bool begin(const uint32_t baudRate, const uint32_t frequency);
    void reset();

    int available();
    int peek();
    void flush();

    int read();
    size_t write(uint8_t value);
    size_t write(const uint8_t* buffer, size_t size);

    void standby();
    void sleep();

    uint32_t baudRate();
    void setBaudRate(const uint32_t value);

    uint32_t carrierFrequency();
    void setCarrierFrequency(const uint32_t value);

    uint32_t carrierFrequencyMHz();
    void setCarrierFrequencyMHz(const uint32_t value);

    int8_t receivedSignalStrength();

    uint8_t version();
    int8_t temperature();
    void calibrateOscillator();

private:
    void setOpMode(const uint8_t value);

    uint8_t read8(const uint8_t reg);
    uint16_t read16(const uint8_t reg);
    uint32_t read24(const uint8_t reg);

    void write8(const uint8_t reg, const uint8_t value);
    void write16(const uint8_t reg, const uint16_t value);
    void write24(const uint8_t reg, const uint32_t value);

    const int8_t interruptPin;
    const int8_t slaveSelectPin;
    const int8_t resetPin;
};

#endif // _RFM69HW_H_
