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


#ifndef OPENESTIMCTRL_DGLABESTIM01_H
#define OPENESTIMCTRL_DGLABESTIM01_H
#define DGLabESTIM01ServiceBattUUID "955A180A-0FE2-F5AA-A094-84B8D4F3E8AD"
#define DGLabESTIM01CharacteristicBattUUID "955A1500-0FE2-F5AA-A094-84B8D4F3E8AD"
#define DGLabESTIM01ServiceEStimUUID "955A180B-0FE2-F5AA-A094-84B8D4F3E8AD"
#define DGLabESTIM01CharacteristicStrengthUUID "955A1504-0FE2-F5AA-A094-84B8D4F3E8AD"
#define DGLabESTIM01CharacteristicPWMAUUID "955A1506-0FE2-F5AA-A094-84B8D4F3E8AD"
#define DGLabESTIM01CharacteristicPWMBUUID "955A1505-0FE2-F5AA-A094-84B8D4F3E8AD"
#include "OpenEStimCtrl.h"


namespace OpenEStimCtrl::DGLabESTIM01 {
    enum DGLabESTIM01Channel: uint8_t {
        CHANNEL_A = 0,
        CHANNEL_B = 1
    };

    PACK(struct DGLabESTIM01BattData {
        uint8_t level;
    });

    PACK(union DGLabESTIM01EStimStrengthData {
        uint8_t data[3];
        PACK(struct{
            uint8_t reserved: 2;
            uint16_t strengthB: 11;
            uint16_t strengthA: 11;
        }) payload;
    });

    PACK(union DGLabESTIM01EStimWaveData {
        uint8_t data[3];
        PACK(struct {
            uint8_t reserved: 4;
            uint8_t z: 5;
            uint16_t y: 10;
            uint8_t x: 5;
        }) payload;
    });

    PACK(struct DGLabESTIM01EStimWave {
        uint8_t x; uint16_t y; uint8_t z;
    });


    typedef void (*onChannelStrengthChange)(const uint16_t &strengthA, const uint16_t &strengthB, void* userData);
    typedef void (*onBatteryChange)(const uint8_t &level, void* userData);


    class DGLabESTIM01 {
    public:
        [[maybe_unused]] explicit DGLabESTIM01(SendDataCallback sendDataCallback);
        virtual ~DGLabESTIM01() = default;

        [[maybe_unused]] void parseBLEData(const char* service, const char* characteristic, const uint8_t *data, int length);
        [[maybe_unused]] void setStrength(uint16_t strengthA, uint16_t strengthB);
        [[maybe_unused]] void sendWave(DGLabESTIM01Channel channel, uint8_t x, uint16_t y, uint8_t z);
        [[maybe_unused]] void sendWave(DGLabESTIM01Channel channel, DGLabESTIM01EStimWave wave);
        [[maybe_unused]] void setUserData(void* userData);
        [[maybe_unused]] void* getUserData();

        [[maybe_unused]] void setOnBatteryChange(onBatteryChange onBatteryChange);
        [[maybe_unused]] void setOnStrengthChange(onChannelStrengthChange onChannelStrengthChange);

        [[maybe_unused]] [[nodiscard]] uint8_t getBattery() const;
        [[maybe_unused]] [[nodiscard]] uint16_t getStrengthA() const;
        [[maybe_unused]] [[nodiscard]] uint16_t getStrengthB() const;


    private:
        SendDataCallback _sendDataCallback;
        onBatteryChange _onBatteryChange = nullptr;
        onChannelStrengthChange _onChannelStrengthChange = nullptr;
        uint8_t _battery = 0;
        uint16_t _strengthA = 0;
        uint16_t _strengthB = 0;
        void* _userData = nullptr;
    };

}

extern "C" void* DGLabESTIM01_new(SendDataCallback sendDataCallback);
extern "C" void DGLabESTIM01_delete(void* dglab);
extern "C" void DGLabESTIM01_parseBLEData(void* dglab, const char* service, const char* characteristic, const uint8_t *data, int length);
extern "C" void DGLabESTIM01_setStrength(void* dglab, uint16_t strengthA, uint16_t strengthB);
extern "C" void DGLabESTIM01_sendWave(void* dglab, OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01Channel channel, uint8_t x, uint8_t y, uint8_t z);
extern "C" void DGLabESTIM01_sendWaveStruct(void* dglab, OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01Channel channel, OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01EStimWave wave);
extern "C" void DGLabESTIM01_setOnBatteryChange(void* dglab, OpenEStimCtrl::DGLabESTIM01::onBatteryChange onBatteryChange);
extern "C" void DGLabESTIM01_setOnStrengthChange(void* dglab, OpenEStimCtrl::DGLabESTIM01::onChannelStrengthChange onChannelStrengthChange);
extern "C" uint8_t DGLabESTIM01_getBattery(void* dglab);
extern "C" uint16_t DGLabESTIM01_getStrengthA(void* dglab);
extern "C" uint16_t DGLabESTIM01_getStrengthB(void* dglab);
extern "C" void DGLabESTIM01_setUserData(void* dglab, void* userData);
extern "C" void* DGLabESTIM01_getUserData(void* dglab);

#endif //OPENESTIMCTRL_DGLABESTIM01_H
