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
 * @file  RFM69HW.h
 * @brief Definitions for the RFM69HW driver.
 */

#ifndef RFM69HW_H
#define RFM69HW_H

#include <Arduino.h>

/**
 * @addtogroup RFM69HW
 * @{
 */

/**
 * @defgroup Exported_Types
 * @{
 */

/**
 * @defgroup Register_Mapping
 * @{
 */
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
/** @} */

/**
 * @defgroup Operation_Mode
 * @{
 */
#define RFM69HW_OPMODE_SEQUENCER_OFF    ((uint8_t)0x80)
#define RFM69HW_OPMODE_LISTEN_ON        ((uint8_t)0x40)
#define RFM69HW_OPMODE_LISTEN_ABORT     ((uint8_t)0x20)
#define RFM69HW_OPMODE_SLEEP            ((uint8_t)0x00)
#define RFM69HW_OPMODE_STDBY            ((uint8_t)0x04)
#define RFM69HW_OPMODE_FS               ((uint8_t)0x08)
#define RFM69HW_OPMODE_TX               ((uint8_t)0x0C)
#define RFM69HW_OPMODE_RX               ((uint8_t)0x10)
/** @} */

/**
 * @defgroup Data_Modulation
 * @{
 */
#define RFM69HW_DATAMODUL_PACKET_MODE                 ((uint8_t)0x00)
#define RFM69HW_DATAMODUL_CONTINUOUS_MODE             ((uint8_t)0x40)
#define RFM69HW_DATAMODUL_CONTINUOUS_MODE_NO_BSYNC    ((uint8_t)0x60)
#define RFM69HW_DATAMODUL_FSK                         ((uint8_t)0x00)
#define RFM69HW_DATAMODUL_OOK                         ((uint8_t)0x08)
#define RFM69HW_DATAMODUL_SHAPING_0                   ((uint8_t)0x00)
#define RFM69HW_DATAMODUL_SHAPING_1                   ((uint8_t)0x01)
#define RFM69HW_DATAMODUL_SHAPING_2                   ((uint8_t)0x02)
#define RFM69HW_DATAMODUL_SHAPING_3                   ((uint8_t)0x03)
/** @} */

/**
 * @defgroup Oscillator
 * @{
 */
#define RFM69HW_OSC1_RC_CAL_START    ((uint8_t)0x80)
#define RFM69HW_OSC1_RC_CAL_DONE     ((uint8_t)0x40)
/** @} */

/**
 * @defgroup Automatic_Frequency_Control
 * @{
 */
#define RFM69HW_AFCCTRL_AFC_LOW_BETA_ON    ((uint8_t)0x20)
/** @} */

/**
 * @defgroup Listen_Mode
 * @{
 */
#define RFM69HW_LISTEN1_RESOL_IDLE_64_US     ((uint8_t)0x40)
#define RFM69HW_LISTEN1_RESOL_IDLE_4_1_MS    ((uint8_t)0x80)
#define RFM69HW_LISTEN1_RESOL_IDLE_262_MS    ((uint8_t)0xC0)
#define RFM69HW_LISTEN1_RESOL_RX_64_US       ((uint8_t)0x10)
#define RFM69HW_LISTEN1_RESOL_RX_4_1_MS      ((uint8_t)0x20)
#define RFM69HW_LISTEN1_RESOL_RX_262_MS      ((uint8_t)0x30)
#define RFM69HW_LISTEN1_CRITERIA             ((uint8_t)0x08)
#define RFM69HW_LISTEN1_END_0                ((uint8_t)0x00)
#define RFM69HW_LISTEN1_END_1                ((uint8_t)0x02)
#define RFM69HW_LISTEN1_END_2                ((uint8_t)0x04)
/** @} */

/**
 * @defgroup Version
 * @{
 */
#define RFM69HW_VERSION_REVISION      ((uint8_t)0xF0)
#define RFM69HW_VERSION_METAL_MASK    ((uint8_t)0x0F)
/** @} */

/**
 * @defgroup Power_Amplifier_Level
 * @{
 */
#define RFM69HW_PALEVEL_PA0_ON             ((uint8_t)0x80)
#define RFM69HW_PALEVEL_PA1_ON             ((uint8_t)0x40)
#define RFM69HW_PALEVEL_PA2_ON             ((uint8_t)0x60)
#define RFM69HW_PALEVEL_OUTPUT_POWER_0     ((uint8_t)0x00)
#define RFM69HW_PALEVEL_OUTPUT_POWER_1     ((uint8_t)0x01)
#define RFM69HW_PALEVEL_OUTPUT_POWER_2     ((uint8_t)0x02)
#define RFM69HW_PALEVEL_OUTPUT_POWER_3     ((uint8_t)0x03)
#define RFM69HW_PALEVEL_OUTPUT_POWER_4     ((uint8_t)0x04)
#define RFM69HW_PALEVEL_OUTPUT_POWER_5     ((uint8_t)0x05)
#define RFM69HW_PALEVEL_OUTPUT_POWER_6     ((uint8_t)0x06)
#define RFM69HW_PALEVEL_OUTPUT_POWER_7     ((uint8_t)0x07)
#define RFM69HW_PALEVEL_OUTPUT_POWER_8     ((uint8_t)0x08)
#define RFM69HW_PALEVEL_OUTPUT_POWER_9     ((uint8_t)0x09)
#define RFM69HW_PALEVEL_OUTPUT_POWER_10    ((uint8_t)0x0A)
#define RFM69HW_PALEVEL_OUTPUT_POWER_11    ((uint8_t)0x0B)
#define RFM69HW_PALEVEL_OUTPUT_POWER_12    ((uint8_t)0x0C)
#define RFM69HW_PALEVEL_OUTPUT_POWER_13    ((uint8_t)0x0D)
#define RFM69HW_PALEVEL_OUTPUT_POWER_14    ((uint8_t)0x0E)
#define RFM69HW_PALEVEL_OUTPUT_POWER_15    ((uint8_t)0x0F)
#define RFM69HW_PALEVEL_OUTPUT_POWER_16    ((uint8_t)0x10)
#define RFM69HW_PALEVEL_OUTPUT_POWER_17    ((uint8_t)0x11)
#define RFM69HW_PALEVEL_OUTPUT_POWER_18    ((uint8_t)0x12)
#define RFM69HW_PALEVEL_OUTPUT_POWER_19    ((uint8_t)0x13)
#define RFM69HW_PALEVEL_OUTPUT_POWER_20    ((uint8_t)0x14)
#define RFM69HW_PALEVEL_OUTPUT_POWER_21    ((uint8_t)0x15)
#define RFM69HW_PALEVEL_OUTPUT_POWER_22    ((uint8_t)0x16)
#define RFM69HW_PALEVEL_OUTPUT_POWER_23    ((uint8_t)0x17)
#define RFM69HW_PALEVEL_OUTPUT_POWER_24    ((uint8_t)0x18)
#define RFM69HW_PALEVEL_OUTPUT_POWER_25    ((uint8_t)0x19)
#define RFM69HW_PALEVEL_OUTPUT_POWER_26    ((uint8_t)0x1A)
#define RFM69HW_PALEVEL_OUTPUT_POWER_27    ((uint8_t)0x1B)
#define RFM69HW_PALEVEL_OUTPUT_POWER_28    ((uint8_t)0x1C)
#define RFM69HW_PALEVEL_OUTPUT_POWER_29    ((uint8_t)0x1D)
#define RFM69HW_PALEVEL_OUTPUT_POWER_30    ((uint8_t)0x1E)
#define RFM69HW_PALEVEL_OUTPUT_POWER_31    ((uint8_t)0x1F)
/** @} */

/**
 * @defgroup Power_Amplifier_Ramp
 * @{
 */
#define RFM69HW_PARAMP_3_4_MS    ((uint8_t)0x00)
#define RFM69HW_PARAMP_2_MS      ((uint8_t)0x01)
#define RFM69HW_PARAMP_1_MS      ((uint8_t)0x02)
#define RFM69HW_PARAMP_500_US    ((uint8_t)0x03)
#define RFM69HW_PARAMP_250_US    ((uint8_t)0x04)
#define RFM69HW_PARAMP_125_US    ((uint8_t)0x05)
#define RFM69HW_PARAMP_100_US    ((uint8_t)0x06)
#define RFM69HW_PARAMP_62_US     ((uint8_t)0x07)
#define RFM69HW_PARAMP_50_US     ((uint8_t)0x08)
#define RFM69HW_PARAMP_40_US     ((uint8_t)0x09)
#define RFM69HW_PARAMP_31_US     ((uint8_t)0x0A)
#define RFM69HW_PARAMP_25_US     ((uint8_t)0x0B)
#define RFM69HW_PARAMP_20_US     ((uint8_t)0x0C)
#define RFM69HW_PARAMP_15_US     ((uint8_t)0x0D)
#define RFM69HW_PARAMP_12_US     ((uint8_t)0x0E)
#define RFM69HW_PARAMP_10_US     ((uint8_t)0x0F)
/** @} */

/**
 * @defgroup Overload_Current_Protection
 * @{
 */
#define RFM69HW_OCP_ON      ((uint8_t)0x10)
#define RFM69HW_OCP_TRIM    ((uint8_t)0x0F)
/** @} */

/**
 * @defgroup Low_Noise_Amplifier
 * @{
 */
#define RFM69HW_LNA_ZIN_50_OHM                   ((uint8_t)0x00)
#define RFM69HW_LNA_ZIN_200_OHM                  ((uint8_t)0x80)
#define RFM69HW_LNA_CURRENT_GAIN                 ((uint8_t)0x38)
#define RFM69HW_LNA_GAIN_SELECT_INTERNAL_AGC     ((uint8_t)0x00)
#define RFM69HW_LNA_GAIN_SELECT_G1               ((uint8_t)0x01)
#define RFM69HW_LNA_GAIN_SELECT_G2               ((uint8_t)0x02)
#define RFM69HW_LNA_GAIN_SELECT_G3               ((uint8_t)0x03)
#define RFM69HW_LNA_GAIN_SELECT_G4               ((uint8_t)0x04)
#define RFM69HW_LNA_GAIN_SELECT_G5               ((uint8_t)0x05)
#define RFM69HW_LNA_GAIN_SELECT_G6               ((uint8_t)0x06)
/** @} */

/**
 * @defgroup Receiver_Bandwidth
 * @{
 */
#define RFM69HW_RXBW_DCC_FREQ    ((uint8_t)0xE0)
#define RFM69HW_RXBW_MANT_16     ((uint8_t)0x00)
#define RFM69HW_RXBW_MANT_20     ((uint8_t)0x08)
#define RFM69HW_RXBW_MANT_24     ((uint8_t)0x10)
#define RFM69HW_RXBW_EXP         ((uint8_t)0x07)
/** @} */

/**
 * @defgroup Automatic_Frequency_Control_Bandwidth
 * @{
 */
#define RFM69HW_AFCBW_DCC_FREQ_AFC     ((uint8_t)0xE0)
#define RFM69HW_AFCBW_RXBW_MANT_AFC    ((uint8_t)0x18)
#define RFM69HW_AFCBW_RXBW_EXP_AFC     ((uint8_t)0x07)
/** @} */

/**
 * @defgroup On_Off_Keying_Peak
 * @{
 */
#define RFM69HW_OOKPEAK_THRESH_TYPE_FIXED       ((uint8_t)0x00)
#define RFM69HW_OOKPEAK_THRESH_TYPE_PEAK        ((uint8_t)0x40)
#define RFM69HW_OOKPEAK_THRESH_TYPE_AVERAGE     ((uint8_t)0x80)
#define RFM69HW_OOKPEAK_THRESH_STEP_0_5_DB      ((uint8_t)0x00)
#define RFM69HW_OOKPEAK_THRESH_STEP_1_0_DB      ((uint8_t)0x08)
#define RFM69HW_OOKPEAK_THRESH_STEP_1_5_DB      ((uint8_t)0x10)
#define RFM69HW_OOKPEAK_THRESH_STEP_2_0_DB      ((uint8_t)0x18)
#define RFM69HW_OOKPEAK_THRESH_STEP_3_0_DB      ((uint8_t)0x20)
#define RFM69HW_OOKPEAK_THRESH_STEP_4_0_DB      ((uint8_t)0x28)
#define RFM69HW_OOKPEAK_THRESH_STEP_5_0_DB      ((uint8_t)0x30)
#define RFM69HW_OOKPEAK_THRESH_STEP_6_0_DB      ((uint8_t)0x38)
#define RFM69HW_OOKPEAK_THRESH_DEC_1_CHIP       ((uint8_t)0x00)
#define RFM69HW_OOKPEAK_THRESH_DEC_0_5_CHIP     ((uint8_t)0x01)
#define RFM69HW_OOKPEAK_THRESH_DEC_0_25_CHIP    ((uint8_t)0x02)
#define RFM69HW_OOKPEAK_THRESH_DEC_0_2_CHIP     ((uint8_t)0x03)
#define RFM69HW_OOKPEAK_THRESH_DEC_2_CHIP       ((uint8_t)0x04)
#define RFM69HW_OOKPEAK_THRESH_DEC_4_CHIP       ((uint8_t)0x05)
#define RFM69HW_OOKPEAK_THRESH_DEC_8_CHIP       ((uint8_t)0x06)
#define RFM69HW_OOKPEAK_THRESH_DEC_16_CHIP      ((uint8_t)0x07)
/** @} */

/**
 * @defgroup On_Off_Keying_Average
 * @{
 */
#define RFM69HW_OOKAVG_THRESH_FILT_32    ((uint8_t)0x00)
#define RFM69HW_OOKAVG_THRESH_FILT_8     ((uint8_t)0x40)
#define RFM69HW_OOKAVG_THRESH_FILT_4     ((uint8_t)0x80)
#define RFM69HW_OOKAVG_THRESH_FILT_2     ((uint8_t)0xC0)
/** @} */

/**
 * @defgroup Automatic_Frequency_Control_Frequency_Error_Indicator
 * @{
 */
#define RFM69HW_AFCFEI_FEI_DONE             ((uint8_t)0x40)
#define RFM69HW_AFCFEI_FEI_START            ((uint8_t)0x20)
#define RFM69HW_AFCFEI_AFC_DONE             ((uint8_t)0x10)
#define RFM69HW_AFCFEI_AFC_AUTOCLEAR_ON     ((uint8_t)0x08)
#define RFM69HW_AFCFEI_AFC_AUTO_ON          ((uint8_t)0x04)
#define RFM69HW_AFCFEI_AFC_CLEAR            ((uint8_t)0x02)
#define RFM69HW_AFCFEI_AFC_START            ((uint8_t)0x01)
/** @} */

/**
 * @defgroup Received_Signal_Strength_Indicator
 * @{
 */
#define RFM69HW_RSSICONFIG_DONE     ((uint8_t)0x02)
#define RFM69HW_RSSICONFIG_START    ((uint8_t)0x01)
/** @} */

/**
 * @defgroup DIO_Mapping_1
 * @{
 */
#define RFM69HW_DIOMAPPING1_DIO0_CONTINUOUS_SYNC_OR_PLL      ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO0_CONTINUOUS_TIMEOUT_OR_TX    ((uint8_t)0x40)
#define RFM69HW_DIOMAPPING1_DIO0_CONTINUOUS_RSSI             ((uint8_t)0x80)
#define RFM69HW_DIOMAPPING1_DIO0_CONTINUOUS_READY            ((uint8_t)0xC0)
#define RFM69HW_DIOMAPPING1_DIO0_PACKET_CRC_OR_SENT          ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO0_PACKET_PAYLOAD_OR_TX        ((uint8_t)0x40)
#define RFM69HW_DIOMAPPING1_DIO0_PACKET_SYNC                 ((uint8_t)0x80)
#define RFM69HW_DIOMAPPING1_DIO0_PACKET_RSSI_PLL             ((uint8_t)0xC0)
#define RFM69HW_DIOMAPPING1_DIO1_CONTINUOUS_DCLK             ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO1_CONTINUOUS_RX_OR_TX         ((uint8_t)0x10)
#define RFM69HW_DIOMAPPING1_DIO1_CONTINUOUS_SYNC_OR_PLL      ((uint8_t)0x30)
#define RFM69HW_DIOMAPPING1_DIO1_PACKET_FIFO_LEVEL           ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO1_PACKET_FIFO_FULL            ((uint8_t)0x10)
#define RFM69HW_DIOMAPPING1_DIO1_PACKET_FIFO_NOT_EMPTY       ((uint8_t)0x20)
#define RFM69HW_DIOMAPPING1_DIO1_PACKET_TIMEOUT_OR_PLL       ((uint8_t)0x30)
#define RFM69HW_DIOMAPPING1_DIO2_CONTINUOUS_DATA             ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO2_PACKET_FIFO_NOT_EMPTY       ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO2_PACKET_DATA                 ((uint8_t)0x04)
#define RFM69HW_DIOMAPPING1_DIO2_PACKET_AUTO_MODE            ((uint8_t)0x0C)
#define RFM69HW_DIOMAPPING1_DIO3_CONTINUOUS_RSSI_OR_TX       ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO3_CONTINUOUS_RX_OR_TX         ((uint8_t)0x01)
#define RFM69HW_DIOMAPPING1_DIO3_CONTINUOUS_AUTO_MODE        ((uint8_t)0x02)
#define RFM69HW_DIOMAPPING1_DIO3_CONTINUOUS_TIMEOUT_OR_TX    ((uint8_t)0x03)
#define RFM69HW_DIOMAPPING1_DIO3_PACKET_FIFO_FULL            ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING1_DIO3_PACKET_RSSI_OR_TX           ((uint8_t)0x01)
#define RFM69HW_DIOMAPPING1_DIO3_PACKET_SYNC                 ((uint8_t)0x02)
#define RFM69HW_DIOMAPPING1_DIO3_PACKET_PLL                  ((uint8_t)0x03)
/** @} */

/**
 * @defgroup DIO_Mapping_2
 * @{
 */
#define RFM69HW_DIOMAPPING2_DIO4_CONTINUOUS_TIMEOUT_OR_TX     ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING2_DIO4_CONTINUOUS_RX_OR_TX          ((uint8_t)0x40)
#define RFM69HW_DIOMAPPING2_DIO4_CONTINUOUS_SYNC              ((uint8_t)0x80)
#define RFM69HW_DIOMAPPING2_DIO4_CONTINUOUS_PLL               ((uint8_t)0xC0)
#define RFM69HW_DIOMAPPING2_DIO4_PACKET_TIMEOUT_OR_READY      ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING2_DIO4_PACKET_RSSI_OR_TX            ((uint8_t)0x40)
#define RFM69HW_DIOMAPPING2_DIO4_PACKET_RX                    ((uint8_t)0x80)
#define RFM69HW_DIOMAPPING2_DIO4_PACKET_PLL                   ((uint8_t)0xC0)
#define RFM69HW_DIOMAPPING2_DIO5_CONTINUOUS_CLKOUT            ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING2_DIO5_CONTINUOUS_RSSI_OR_CLKOUT    ((uint8_t)0x10)
#define RFM69HW_DIOMAPPING2_DIO5_CONTINUOUS_READY             ((uint8_t)0x30)
#define RFM69HW_DIOMAPPING2_DIO5_PACKET_CLKOUT                ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING2_DIO5_PACKET_DATA                  ((uint8_t)0x10)
#define RFM69HW_DIOMAPPING2_DIO5_PACKET_READY                 ((uint8_t)0x30)
#define RFM69HW_DIOMAPPING2_CLKOUT_FXOSC                      ((uint8_t)0x00)
#define RFM69HW_DIOMAPPING2_CLKOUT_FXOSC_OVER_2               ((uint8_t)0x01)
#define RFM69HW_DIOMAPPING2_CLKOUT_FXOSC_OVER_4               ((uint8_t)0x02)
#define RFM69HW_DIOMAPPING2_CLKOUT_FXOSC_OVER_8               ((uint8_t)0x03)
#define RFM69HW_DIOMAPPING2_CLKOUT_FXOSC_OVER_16              ((uint8_t)0x04)
#define RFM69HW_DIOMAPPING2_CLKOUT_FXOSC_OVER_32              ((uint8_t)0x05)
#define RFM69HW_DIOMAPPING2_CLKOUT_RC                         ((uint8_t)0x06)
#define RFM69HW_DIOMAPPING2_CLKOUT_OFF                        ((uint8_t)0x07)
/** @} */

/**
 * @defgroup Interrupt_Request_Flags_1
 * @{
 */
#define RFM69HW_IRQFLAGS1_MODE_READY            ((uint8_t)0x80)
#define RFM69HW_IRQFLAGS1_RX_READY              ((uint8_t)0x40)
#define RFM69HW_IRQFLAGS1_TX_READY              ((uint8_t)0x20)
#define RFM69HW_IRQFLAGS1_PLL_LOCK              ((uint8_t)0x10)
#define RFM69HW_IRQFLAGS1_RSSI                  ((uint8_t)0x08)
#define RFM69HW_IRQFLAGS1_TIMEOUT               ((uint8_t)0x04)
#define RFM69HW_IRQFLAGS1_AUTO_MODE             ((uint8_t)0x02)
#define RFM69HW_IRQFLAGS1_SYNC_ADDRESS_MATCH    ((uint8_t)0x01)
/** @} */

/**
 * @defgroup Interrupt_Request_Flags_2
 * @{
 */
#define RFM69HW_IRQFLAGS2_FIFO_FULL         ((uint8_t)0x80)
#define RFM69HW_IRQFLAGS2_FIFO_NOT_EMPTY    ((uint8_t)0x40)
#define RFM69HW_IRQFLAGS2_FIFO_LEVEL        ((uint8_t)0x20)
#define RFM69HW_IRQFLAGS2_FIFO_OVERRUN      ((uint8_t)0x10)
#define RFM69HW_IRQFLAGS2_PACKET_SENT       ((uint8_t)0x08)
#define RFM69HW_IRQFLAGS2_PAYLOAD_READY     ((uint8_t)0x04)
#define RFM69HW_IRQFLAGS2_CRC_OK            ((uint8_t)0x02)
/** @} */

/**
 * @defgroup Sync_Configuration
 * @{
 */
#define RFM69HW_SYNCCONFIG_SYNC_ON                ((uint8_t)0x80)
#define RFM69HW_SYNCCONFIG_FIFO_FILL_CONDITION    ((uint8_t)0x40)
#define RFM69HW_SYNCCONFIG_SYNC_SIZE              ((uint8_t)0x38)
#define RFM69HW_SYNCCONFIG_SYNC_TOL               ((uint8_t)0x07)
/** @} */

/**
 * @defgroup Packet_Configuration_1
 * @{
 */
#define RFM69HW_PACKETCONFIG1_PACKET_FORMAT_FIXED                    ((uint8_t)0x00)
#define RFM69HW_PACKETCONFIG1_PACKET_FORMAT_VARIABLE                 ((uint8_t)0x80)
#define RFM69HW_PACKETCONFIG1_DC_FREE_NONE                           ((uint8_t)0x00)
#define RFM69HW_PACKETCONFIG1_DC_FREE_MANCHESTER                     ((uint8_t)0x20)
#define RFM69HW_PACKETCONFIG1_DC_FREE_WHITENING                      ((uint8_t)0x40)
#define RFM69HW_PACKETCONFIG1_CRC_ON                                 ((uint8_t)0x10)
#define RFM69HW_PACKETCONFIG1_CRC_AUTO_CLEAR_OFF                     ((uint8_t)0x08)
#define RFM69HW_PACKETCONFIG1_ADDRESS_FILTERING_NONE                 ((uint8_t)0x00)
#define RFM69HW_PACKETCONFIG1_ADDRESS_FILTERING_NODE                 ((uint8_t)0x02)
#define RFM69HW_PACKETCONFIG1_ADDRESS_FILTERING_NODE_OR_BROADCAST    ((uint8_t)0x04)
/** @} */

/**
 * @defgroup Auto_Modes
 * @{
 */
#define RFM69HW_AUTOMODES_ENTER_CONDITION_NONE              ((uint8_t)0x00)
#define RFM69HW_AUTOMODES_ENTER_CONDITION_FIFO_NOT_EMPTY    ((uint8_t)0x20)
#define RFM69HW_AUTOMODES_ENTER_CONDITION_FIFO_LEVEL        ((uint8_t)0x40)
#define RFM69HW_AUTOMODES_ENTER_CONDITION_CRC_OK            ((uint8_t)0x60)
#define RFM69HW_AUTOMODES_ENTER_CONDITION_PAYLOAD_READY     ((uint8_t)0x80)
#define RFM69HW_AUTOMODES_ENTER_CONDITION_SYNC_ADDRESS      ((uint8_t)0xA0)
#define RFM69HW_AUTOMODES_ENTER_CONDITION_PACKET_SENT       ((uint8_t)0xC0)
#define RFM69HW_AUTOMODES_ENTER_CONDITION_FIFO_EMPTY        ((uint8_t)0xE0)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_NONE               ((uint8_t)0x00)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_FIFO_EMPTY         ((uint8_t)0x04)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_FIFO_LEVEL         ((uint8_t)0x08)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_CRC_OK             ((uint8_t)0x0C)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_PAYLOAD_READY      ((uint8_t)0x10)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_SYNC_ADDRESS       ((uint8_t)0x14)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_PACKET_SENT        ((uint8_t)0x18)
#define RFM69HW_AUTOMODES_EXIT_CONDITION_TIMEOUT            ((uint8_t)0x1C)
#define RFM69HW_AUTOMODES_INTERMEDIATE_SLEEP                ((uint8_t)0x00)
#define RFM69HW_AUTOMODES_INTERMEDIATE_STDBY                ((uint8_t)0x01)
#define RFM69HW_AUTOMODES_INTERMEDIATE_RX                   ((uint8_t)0x02)
#define RFM69HW_AUTOMODES_INTERMEDIATE_TX                   ((uint8_t)0x03)
/** @} */

/**
 * @defgroup FIFO_Threshold
 * @{
 */
#define RFM69HW_FIFOTHRESH_TX_START_CONDITION_FIFO_LEVEL        ((uint8_t)0x00)
#define RFM69HW_FIFOTHRESH_TX_START_CONDITION_FIFO_NOT_EMPTY    ((uint8_t)0x80)
#define RFM69HW_FIFOTHRESH_FIFO_THRESHOLD                       ((uint8_t)0x7F)
/** @} */

/**
 * @defgroup Packet_Configuration_2
 * @{
 */
#define RFM69HW_PACKETCONFIG2_INTER_PACKET_RX_DELAY    ((uint8_t)0xF0)
#define RFM69HW_PACKETCONFIG2_RESTART_RX               ((uint8_t)0x04)
#define RFM69HW_PACKETCONFIG2_AUTO_RX_RESTART_ON       ((uint8_t)0x02)
#define RFM69HW_PACKETCONFIG2_AES_ON                   ((uint8_t)0x01)
/** @} */

/**
 * @defgroup Temperature_1
 * @{
 */
#define RFM69HW_TEMP1_MEAS_START      ((uint8_t)0x08)
#define RFM69HW_TEMP1_MEAS_RUNNING    ((uint8_t)0x04)
/** @} */

/**
 * @defgroup Test_Low_Noise_Amplifier
 * @{
 */
#define RFM69HW_TESTLNA_SENSITIVITY_BOOST_NORMAL    ((uint8_t)0x1B)
#define RFM69HW_TESTLNA_SENSITIVITY_BOOST_HIGH      ((uint8_t)0x2D)
/** @} */

/**
 * @defgroup Test_Power_Amplifier_1
 * @{
 */
#define RFM69HW_TESTPA1_PA_20_DBM_NORMAL    ((uint8_t)0x55)
#define RFM69HW_TESTPA1_PA_20_DBM_HIGH      ((uint8_t)0x5D)
/** @} */

/**
 * @defgroup Test_Power_Amplifier_2
 * @{
 */
#define RFM69HW_TESTPA2_PA_20_DBM_NORMAL    ((uint8_t)0x70)
#define RFM69HW_TESTPA2_PA_20_DBM_HIGH      ((uint8_t)0x7C)
/** @} */

/**
 * @defgroup Test_Digital_Gain_Adjustment
 * @{
 */
#define RFM69HW_TESTDAGC_NORMAL                       ((uint8_t)0x00)
#define RFM69HW_TESTDAGC_IMPROVED_AFC_LOW_BETA_ON     ((uint8_t)0x20)
#define RFM69HW_TESTDAGC_IMPROVED_AFC_LOW_BETA_OFF    ((uint8_t)0x30)
/** @} */

/**
 * @brief   RFM69HW driver.
 * @details Driver for the RFM69HW radio transceiver.
 */
class RFM69HW
{
public:
    RFM69HW(const int8_t slaveSelectPin = SS, const int8_t resetPin = -1);
    bool begin(const uint32_t bps = 0, const uint16_t mhz = 0);
    uint32_t bitRate();
    uint8_t broadcastAddress();
    void calibrateOscillator();
    uint16_t carrierFrequency();
    uint32_t frequencyDeviation();
    uint8_t nodeAddress();
    uint8_t payloadLength();
    void reset();
    void setBitRate(const uint32_t bps);
    void setBroadcastAddress(const uint8_t address);
    void setCarrierFrequency(const uint16_t mhz);
    void setEncryptionKey(const char *key, const uint8_t length);
    void setFrequencyDeviation(const uint32_t hz);
    void setNodeAddress(const uint8_t address);
    void setPayloadLength(const uint8_t length);
    void setSyncWord(const char *word, const uint8_t length);
    void sleep();
    void standby();
    float temperature();
    uint8_t version();

private:
    float mapTemperature(const uint8_t value);
    uint8_t read8(const uint8_t reg);
    uint16_t read16(const uint8_t reg);
    uint32_t read32(const uint8_t reg);
    void write8(const uint8_t reg, const uint8_t value);
    void write16(const uint8_t reg, const uint16_t value);
    void write32(const uint8_t reg, const uint32_t value);

    static const uint8_t AESKEY_NUM_BYTES;
    static const uint32_t BITRATE_MAX_BPS;
    static const uint32_t BITRATE_MIN_BPS;
    static const uint32_t FDA_MAX_HZ;
    static const uint32_t FDA_MIN_HZ;
    static const uint16_t FR_MAX_MHZ;
    static const uint16_t FR_MIN_MHZ;
    static const uint16_t FREQUENCY_MULTIPLIER;
    static const uint8_t FSTEP_HZ;
    static const uint32_t FXOSC_HZ;
    static const uint8_t SYNCVALUE_NUM_BYTES;
    static const float TEMP_MAX_C;
    static const float TEMP_MIN_C;
    static const uint8_t VERSION;
    const int8_t resetPin;
    const int8_t slaveSelectPin;
};

/** @} */

/** @} */

#endif // RFM69HW_H

