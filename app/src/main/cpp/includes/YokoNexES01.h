/*
OpenEStimCtrl
Copyright (C) 2023 Personal/SoundReload

This program is free software: you can redistribute it and/or modify
        it under the terms of the GNU Affero General Public License as published by
        the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
        along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef OPENESTIMCTRL_YOKONEXES01_H
#define OPENESTIMCTRL_YOKONEXES01_H

#define YokonexES01ServiceUUID "0000ff30-0000-1000-8000-00805f9b34fb"
#define YokonexES01CharacteristicSendUUID "0000ff31-0000-1000-8000-00805f9b34fb"
#define YokonexES01CharacteristicReceiveUUID "0000ff32-0000-1000-8000-00805f9b34fb"

#include "OpenEStimCtrl.h"

namespace OpenEStimCtrl::YokoNexES01 {

        enum YokoNexES01Channel: uint8_t {
            CHANNEL_A = 0x01, CHANNEL_B = 0x02, CHANNEL_BOTH = 0x03
        };

        enum YokoNexES01Mode: uint8_t {
            MODE_INTERNAL_1 = 0x01,
            MODE_INTERNAL_2 = 0x02,
            MODE_INTERNAL_3 = 0x03,
            MODE_INTERNAL_4 = 0x04,
            MODE_INTERNAL_5 = 0x05,
            MODE_INTERNAL_6 = 0x06,
            MODE_INTERNAL_7 = 0x07,
            MODE_INTERNAL_8 = 0x08,
            MODE_INTERNAL_9 = 0x09,
            MODE_INTERNAL_10 = 0x0A,
            MODE_INTERNAL_11 = 0x0B,
            MODE_INTERNAL_12 = 0x0C,
            MODE_INTERNAL_13 = 0x0D,
            MODE_INTERNAL_14 = 0x0E,
            MODE_INTERNAL_15 = 0x0F,
            MODE_INTERNAL_16 = 0x10,
            MODE_CUSTOM = 0x11,
        };

        enum YokoNexES01Motor: uint8_t {
            MOTOR_OFF = 0x00, MOTOR_ON = 0x01, MOTOR_INTERNAL_1 = 0x11, MOTOR_INTERNAL_2 = 0x12, MOTOR_INTERNAL_3 = 0x13
        };

        enum YokoNexES01Step: uint8_t {
            STEP_OFF = 0x00, STEP_ON = 0x01, STEP_CLEAR = 0x02, STEP_PAUSE = 0x03, STEP_RESUME = 0x04
        };

        enum YokoNexES01Angle: uint8_t {
            ANGLE_OFF = 0x01, ANGLE_ON = 0x01
        };

        enum YokoNexES01Query: uint8_t {
            QUERY_CHANNEL_A = 0x01, QUERY_CHANNEL_B = 0x02, QUERY_MOTOR = 0x03, QUERY_BATTERY = 0x04, QUERY_STEP = 0x05, QUERY_ANGLE = 0x06
        };
        enum YokoNexES01ChannelStatus: uint8_t {
            NOT_PLUG_IN = 0x00, PLUG_IN_RUNNING = 0x01, PLUG_IN_IDLE = 0x02
        };

        PACK(struct YokoNexES01Status {
            YokoNexES01ChannelStatus connection = YokoNexES01ChannelStatus::NOT_PLUG_IN;
            bool enabled = false;
            be_uint16_t strength;
            YokoNexES01Mode mode = YokoNexES01Mode::MODE_INTERNAL_1;
        });

        PACK(struct YokoNexES01Accel {
            be_uint16_t accX;
            be_uint16_t accY;
            be_uint16_t accZ;
            be_uint16_t gyroX;
            be_uint16_t gyroY;
            be_uint16_t gyroZ;
        });

        typedef void (*onChannelStatusChange)(const YokoNexES01Status status, void* userData);
        typedef void (*onMotorStatusChange)(const YokoNexES01Motor status, void* userData);
        typedef void (*onBatteryStatusChange)(const uint8_t battery, void* userData);
        typedef void (*onStepStatusChange)(const uint16_t step, void* userData);
        typedef void (*onAngleStatusChange)(const YokoNexES01Accel accel, void* userData);
        typedef void (*onException)(const uint8_t code, void* userData);

        class YokoNexES01 {
        public:
            [[maybe_unused]] explicit YokoNexES01(SendDataCallback sendCallback);
            virtual ~YokoNexES01() = default;

            [[maybe_unused]] void parseBLEData(uint8_t *data, int length);

            [[maybe_unused]] void setEStim(YokoNexES01Channel channel, bool enabled, uint16_t strength, YokoNexES01Mode mode, uint8_t frequency, uint8_t pulseWidth);
            [[maybe_unused]] void triggerMotor(YokoNexES01Motor mode);
            [[maybe_unused]] void setStep(YokoNexES01Step mode);
            [[maybe_unused]] void setAngle(YokoNexES01Angle mode);
            [[maybe_unused]] void query(YokoNexES01Query query);
            [[maybe_unused]] void setUserData(void* userData);
            [[maybe_unused]] void* getUserData();

            [[maybe_unused]] void setOnChannelAStatusChange(onChannelStatusChange callback);
            [[maybe_unused]] void setOnChannelBStatusChange(onChannelStatusChange callback);
            [[maybe_unused]] void setOnMotorStatusChange(onMotorStatusChange callback);
            [[maybe_unused]] void setOnBatteryStatusChange(onBatteryStatusChange callback);
            [[maybe_unused]] void setOnStepStatusChange(onStepStatusChange callback);
            [[maybe_unused]] void setOnAngleStatusChange(onAngleStatusChange callback);
            [[maybe_unused]] void setOnException(onException callback);


            [[maybe_unused]] [[nodiscard]] uint8_t getLastException() const;
            [[maybe_unused]] [[nodiscard]] uint8_t getBattery() const;
            [[maybe_unused]] [[nodiscard]] uint16_t getStep() const;
            [[maybe_unused]] [[nodiscard]] YokoNexES01Accel getAccel() const;
            [[maybe_unused]] [[nodiscard]] YokoNexES01Status getChannelA() const;
            [[maybe_unused]] [[nodiscard]] YokoNexES01Status getChannelB() const;
            [[maybe_unused]] [[nodiscard]] YokoNexES01Motor getMotor() const;

        private:
            SendDataCallback _sendCallback = nullptr;
            onChannelStatusChange _onChannelAStatusChange = nullptr;
            onChannelStatusChange _onChannelBStatusChange = nullptr;
            onMotorStatusChange _onMotorStatusChange = nullptr;
            onBatteryStatusChange _onBatteryStatusChange = nullptr;
            onStepStatusChange _onStepStatusChange = nullptr;
            onAngleStatusChange _onAngleStatusChange = nullptr;
            onException _onException = nullptr;
            void* _userData = nullptr;
            YokoNexES01Status channelA {
                YokoNexES01ChannelStatus::NOT_PLUG_IN,
                false,
                be_uint16_t(0x0000),
                YokoNexES01Mode::MODE_INTERNAL_1
            };
            YokoNexES01Status channelB {
                YokoNexES01ChannelStatus::NOT_PLUG_IN,
                false,
                be_uint16_t(0x0000),
                YokoNexES01Mode::MODE_INTERNAL_1
            };
            YokoNexES01Motor motor = YokoNexES01Motor::MOTOR_OFF;
            uint8_t battery = 0x0;
            uint16_t step = 0x0000;
            YokoNexES01Accel accel;
            uint8_t lastException = 0x0;
        };


        PACK(struct YokoNexES01DataChannel {
            uint8_t header = 0x35;
            uint8_t command = 0x11;
            uint8_t channel = 0x03;
            uint8_t enabled = 0x00;
            be_uint16_t strength;
            uint8_t mode = 0x01;
            uint8_t frequency = 0x00;
            uint8_t pulseWidth = 0x00;
            uint8_t checksum = 0x00;
        });

        PACK(struct YokoNexES01DataMotor {
            uint8_t header = 0x35;
            uint8_t command = 0x12;
            uint8_t mode = 0x00;
            uint8_t checksum = 0x00;
        });

        PACK(struct YokoNexES01DataStep {
            uint8_t header = 0x35;
            uint8_t command = 0x13;
            uint8_t mode = 0x00;
            uint8_t checksum = 0x00;
        });

        PACK(struct YokoNexES01DataAngle {
            uint8_t header = 0x35;
            uint8_t command = 0x14;
            uint8_t mode = 0x00;
            uint8_t checksum = 0x00;
        });

        PACK(struct YokoNexES01DataQuery {
            uint8_t header = 0x35;
            uint8_t command = 0x71;
            uint8_t query = 0x00;
            uint8_t checksum = 0x00;
        });

        enum YokoNexES01DataReceiveType: uint8_t {
            TYPE_CHANNEL_A = 0x01,TYPE_CHANNEL_B = 0x02, TYPE_MOTOR = 0x03, TYPE_BATTERY = 0x04, TYPE_STEP = 0x05, TYPE_ANGLE = 0x06, TYPE_EXCEPTION = 0x55
        };

        union YokoNexES01DataReceive {
            uint8_t data[16] = {0};
            PACK(struct {
                uint8_t header = 0x00;
                uint8_t command = 0x00;
                YokoNexES01DataReceiveType type;
                PACK(union {
                    uint8_t data[13] = {0};
                    PACK(struct {
                        YokoNexES01ChannelStatus connection;
                        uint8_t enabled;
                        be_uint16_t strength;
                        YokoNexES01Mode mode;
                        uint8_t checksum = 0x00;
                    }) channel;
                    PACK(struct {
                        YokoNexES01Motor mode;
                        uint8_t checksum = 0x00;
                    }) motor;
                    PACK(struct {
                        uint8_t level;
                        uint8_t checksum = 0x00;
                    }) battery;
                    PACK(struct {
                        be_uint16_t step;
                        uint8_t checksum = 0x00;
                    }) step;
                    PACK(struct {
                        be_uint16_t accX;
                        be_uint16_t accY;
                        be_uint16_t accZ;
                        be_uint16_t gyroX;
                        be_uint16_t gyroY;
                        be_uint16_t gyroZ;
                        uint8_t checksum = 0x00;
                    }) angle;
                    PACK(struct {
                        uint8_t code;
                        uint8_t checksum = 0x00;
                    }) exception;
                }) payload;
            }) packet;
        };
}


extern "C" void* YokoNexES01_new(SendDataCallback sendDataCallback);
extern "C" void YokoNexES01_delete(void* yokoNexES01);

extern "C" void YokoNexES01_parseBLEData(void* yokoNexES01, const char* data, int length);
extern "C" void YokoNexES01_setEStim(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Channel channel, bool enabled, uint16_t strength, OpenEStimCtrl::YokoNexES01::YokoNexES01Mode mode, uint8_t frequency, uint8_t pulseWidth);
extern "C" void YokoNexES01_triggerMotor(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Motor mode);
extern "C" void YokoNexES01_setStep(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Step mode);
extern "C" void YokoNexES01_setAngle(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Angle mode);
extern "C" void YokoNexES01_query(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Query query);
extern "C" void YokoNexES01_setUserData(void* yokoNexES01, void* userData);
extern "C" void* YokoNexES01_getUserData(void* yokoNexES01);

extern "C" void YokoNexES01_setOnChannelAStatusChange(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::onChannelStatusChange callback);
extern "C" void YokoNexES01_setOnChannelBStatusChange(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::onChannelStatusChange callback);
extern "C" void YokoNexES01_setOnMotorStatusChange(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::onMotorStatusChange callback);
extern "C" void YokoNexES01_setOnBatteryStatusChange(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::onBatteryStatusChange callback);
extern "C" void YokoNexES01_setOnStepStatusChange(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::onStepStatusChange callback);
extern "C" void YokoNexES01_setOnAngleStatusChange(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::onAngleStatusChange callback);
extern "C" void YokoNexES01_setOnException(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::onException callback);

extern "C" uint8_t YokoNexES01_getLastException(void* yokoNexES01);
extern "C" uint8_t YokoNexES01_getBattery(void* yokoNexES01);
extern "C" uint16_t YokoNexES01_getStep(void* yokoNexES01);
extern "C" void YokoNexES01_getAccel(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Accel* accel);
extern "C" void YokoNexES01_getChannelA(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Status* status);
extern "C" void YokoNexES01_getChannelB(void* yokoNexES01, OpenEStimCtrl::YokoNexES01::YokoNexES01Status* status);
extern "C" OpenEStimCtrl::YokoNexES01::YokoNexES01Motor YokoNexES01_getMotor(void* yokoNexES01);


#endif //OPENESTIMCTRL_YOKONEXES01_H
