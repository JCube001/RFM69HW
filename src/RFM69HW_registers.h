/*
The MIT License (MIT)

Copyright (c) 2014, 2016 Jacob McGladdery

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

#ifndef _RFM69HW_REGISTERS_H_
#define _RFM69HW_REGISTERS_H_

// Registers
#define RFM69HW_FIFO             0x00
#define RFM69HW_OPMODE           0x01
#define RFM69HW_DATAMODUL        0x02
#define RFM69HW_BITRATEMSB       0x03
#define RFM69HW_BITRATELSB       0x04
#define RFM69HW_FDEVMSB          0x05
#define RFM69HW_FDEVLSB          0x06
#define RFM69HW_FRFMSB           0x07
#define RFM69HW_FRFMID           0x08
#define RFM69HW_FRFLSB           0x09
#define RFM69HW_OSC1             0x0A
#define RFM69HW_AFCCTRL          0x0B
#define RFM69HW_RESERVED0C       0x0C
#define RFM69HW_LISTEN1          0x0D
#define RFM69HW_LISTEN2          0x0E
#define RFM69HW_LISTEN3          0x0F
#define RFM69HW_VERSION          0x10
#define RFM69HW_PALEVEL          0x11
#define RFM69HW_PARAMP           0x12
#define RFM69HW_OCP              0x13
#define RFM69HW_RESERVED14       0x14
#define RFM69HW_RESERVED15       0x15
#define RFM69HW_RESERVED16       0x16
#define RFM69HW_RESERVED17       0x17
#define RFM69HW_LNA              0x18
#define RFM69HW_RXBW             0x19
#define RFM69HW_AFCBW            0x1A
#define RFM69HW_OOKPEAK          0x1B
#define RFM69HW_OOKAVG           0x1C
#define RFM69HW_OOKFIX           0x1D
#define RFM69HW_AFCFEI           0x1E
#define RFM69HW_AFCMSB           0x1F
#define RFM69HW_AFCLSB           0x20
#define RFM69HW_FEIMSB           0x21
#define RFM69HW_FEILSB           0x22
#define RFM69HW_RSSICONFIG       0x23
#define RFM69HW_RSSIVALUE        0x24
#define RFM69HW_DIOMAPPING1      0x25
#define RFM69HW_DIOMAPPING2      0x26
#define RFM69HW_IRQFLAGS1        0x27
#define RFM69HW_IRQFLAGS2        0x28
#define RFM69HW_RSSITHRESH       0x29
#define RFM69HW_RXTIMEOUT1       0x2A
#define RFM69HW_RXTIMEOUT2       0x2B
#define RFM69HW_PREAMBLEMSB      0x2C
#define RFM69HW_PREAMBLELSB      0x2D
#define RFM69HW_SYNCCONFIG       0x2E
#define RFM69HW_SYNCVALUE1       0x2F
#define RFM69HW_SYNCVALUE2       0x30
#define RFM69HW_SYNCVALUE3       0x31
#define RFM69HW_SYNCVALUE4       0x32
#define RFM69HW_SYNCVALUE5       0x33
#define RFM69HW_SYNCVALUE6       0x34
#define RFM69HW_SYNCVALUE7       0x35
#define RFM69HW_SYNCVALUE8       0x36
#define RFM69HW_PACKETCONFIG1    0x37
#define RFM69HW_PAYLOADLENGTH    0x38
#define RFM69HW_NODEADRS         0x39
#define RFM69HW_BROADCASTADRS    0x3A
#define RFM69HW_AUTOMODES        0x3B
#define RFM69HW_FIFOTHRESH       0x3C
#define RFM69HW_PACKETCONFIG2    0x3D
#define RFM69HW_AESKEY1          0x3E
#define RFM69HW_AESKEY2          0x3F
#define RFM69HW_AESKEY3          0x40
#define RFM69HW_AESKEY4          0x41
#define RFM69HW_AESKEY5          0x42
#define RFM69HW_AESKEY6          0x43
#define RFM69HW_AESKEY7          0x44
#define RFM69HW_AESKEY8          0x45
#define RFM69HW_AESKEY9          0x46
#define RFM69HW_AESKEY10         0x47
#define RFM69HW_AESKEY11         0x48
#define RFM69HW_AESKEY12         0x49
#define RFM69HW_AESKEY13         0x4A
#define RFM69HW_AESKEY14         0x4B
#define RFM69HW_AESKEY15         0x4C
#define RFM69HW_AESKEY16         0x4D
#define RFM69HW_TEMP1            0x4E
#define RFM69HW_TEMP2            0x4F
#define RFM69HW_TESTLNA          0x58
#define RFM69HW_TESTPA1          0x5A
#define RFM69HW_TESTPA2          0x5C
#define RFM69HW_TESTDAGC         0x6F
#define RFM69HW_TESTAFC          0x71

// 0x01 - Op mode masks
#define RFM69HW_OPMODE_SEQUENCER_ON     (0 << 7) // Default
#define RFM69HW_OPMODE_SEQUENCER_OFF    (1 << 7)
#define RFM69HW_OPMODE_LISTEN_ON        (1 << 6)
#define RFM69HW_OPMODE_LISTEN_OFF       (0 << 6) // Default
#define RFM69HW_OPMODE_LISTEN_ABORT     (1 << 5)
#define RFM69HW_OPMODE_MODE_MASK        (0b111 << 2)
#define RFM69HW_OPMODE_MODE_SLEEP       (0b000 << 2)
#define RFM69HW_OPMODE_MODE_STANDBY     (0b001 << 2) // Default
#define RFM69HW_OPMODE_MODE_FS          (0b010 << 2)
#define RFM69HW_OPMODE_MODE_TX          (0b011 << 2)
#define RFM69HW_OPMODE_MODE_RX          (0b100 << 2)

// 0x0A - Oscillator masks
#define RFM69HW_OSC1_RC_CAL_START    (1 << 7)
#define RFM69HW_OSC1_RC_CAL_DONE     (1 << 6)

// 0x23 - RSSI config masks
#define RFM69HW_RSSICONFIG_RSSI_DONE     (1 << 1)
#define RFM69HW_RSSICONFIG_RSSI_START    (1 << 0)

// 0x26 - Digital IO mapping 2 masks
#define RFM69HW_DIOMAPPING2_DIO4_MASK     (0b11 << 6)
#define RFM69HW_DIOMAPPING2_DIO4_00       (0b00 << 6) // Default
#define RFM69HW_DIOMAPPING2_DIO4_01       (0b01 << 6)
#define RFM69HW_DIOMAPPING2_DIO4_10       (0b10 << 6)
#define RFM69HW_DIOMAPPING2_DIO4_11       (0b11 << 6)
#define RFM69HW_DIOMAPPING2_DIO5_MASK     (0b11 << 4)
#define RFM69HW_DIOMAPPING2_DIO5_00       (0b00 << 4) // Default
#define RFM69HW_DIOMAPPING2_DIO5_01       (0b01 << 4)
#define RFM69HW_DIOMAPPING2_DIO5_10       (0b10 << 4)
#define RFM69HW_DIOMAPPING2_DIO5_11       (0b11 << 4)
#define RFM69HW_DIOMAPPING2_CLKOUT_MASK   (0b111 << 0)
#define RFM69HW_DIOMAPPING2_CLKOUT_1      (0b000 << 0)
#define RFM69HW_DIOMAPPING2_CLKOUT_2      (0b001 << 0)
#define RFM69HW_DIOMAPPING2_CLKOUT_4      (0b010 << 0)
#define RFM69HW_DIOMAPPING2_CLKOUT_8      (0b011 << 0)
#define RFM69HW_DIOMAPPING2_CLKOUT_16     (0b100 << 0)
#define RFM69HW_DIOMAPPING2_CLKOUT_32     (0b101 << 0) // Reset value
#define RFM69HW_DIOMAPPING2_CLKOUT_RC     (0b110 << 0)
#define RFM69HW_DIOMAPPING2_CLKOUT_OFF    (0b111 << 0) // Recommended

// 0x27 - IRQ flags 1 masks
#define RFM69HW_IRQFLAGS1_MODE_READY         (1 << 7) // Default
#define RFM69HW_IRQFLAGS1_RX_READY           (1 << 6)
#define RFM69HW_IRQFLAGS1_TX_READY           (1 << 5)
#define RFM69HW_IRQFLAGS1_PLL_LOCK           (1 << 4)
#define RFM69HW_IRQFLAGS1_RSSI               (1 << 3)
#define RFM69HW_IRQFLAGS1_TIMEOUT            (1 << 2)
#define RFM69HW_IRQFLAGS1_AUTO_MODE          (1 << 1)
#define RFM69HW_IRQFLAGS1_SYNC_ADDR_MATCH    (1 << 0)

// 0x28 - IRQ flags 2 masks
#define RFM69HW_IRQFLAGS2_FIFO_FULL         (1 << 7)
#define RFM69HW_IRQFLAGS2_FIFO_NOT_EMPTY    (1 << 6)
#define RFM69HW_IRQFLAGS2_FIFO_LEVEL        (1 << 5)
#define RFM69HW_IRQFLAGS2_FIFO_OVERRUN      (1 << 4)
#define RFM69HW_IRQFLAGS2_PACKET_SENT       (1 << 3)
#define RFM69HW_IRQFLAGS2_PAYLOAD_READY     (1 << 2)
#define RFM69HW_IRQFLAGS2_CRC_OK            (1 << 1)

// 0x3C - FIFO threshold masks
#define RFM69HW_FIFOTHRESH_TX_START_FIFO_LEVEL        (0 << 7) // Reset value
#define RFM69HW_FIFOTHRESH_TX_START_FIFO_NOT_EMPTY    (1 << 7) // Recommended
#define RFM69HW_FIFOTHRESH_FIFO_THRESHOLD_MASK        (0b1111111 << 0)

// 0x4E - Temperature 1 masks
#define RFM69HW_TEMP1_MEAS_START      (1 << 3)
#define RFM69HW_TEMP1_MEAS_RUNNING    (1 << 2)

#endif // _RFM69HW_REGISTERS_H_
