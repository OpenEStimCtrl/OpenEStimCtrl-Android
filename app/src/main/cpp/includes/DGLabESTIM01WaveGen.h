/*
OpenEStimCtrl
Copyright (C) 2023  Personal/SoundReload

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

#ifndef OPENESTIMCTRLSTATIC_DGLABESTIM01WAVEGEN_H
#define OPENESTIMCTRLSTATIC_DGLABESTIM01WAVEGEN_H

#include <cmath>
#include "../src/DGLabESTIM01.h"

namespace OpenEStimCtrl {
    namespace DGLabESTIM01WaveGen {
        PACK(struct DGLabESTIM01EStimTouchWave {
                 uint8_t x;
                 uint16_t y;
                 uint8_t z;
        });

        PACK(struct DGLabESTIM01EStimAutoWaveState {

        });

        static DGLabESTIM01::DGLabESTIM01EStimWave calcXYZByFrequency(double frequency, int z);
        static DGLabESTIM01::DGLabESTIM01EStimWave calcTouchWaveByPosition(double x, double y);
        static DGLabESTIM01::DGLabESTIM01EStimWave calcTouchWaveByTimeSpan(int timeSpan, DGLabESTIM01EStimTouchWave* touchWave, size_t length);
        static DGLabESTIM01::DGLabESTIM01EStimWave calcAutoWave(DGLabESTIM01EStimAutoWaveState* state);
    };

} // OpenEStimCtrl

extern "C" void DGLabESTIM01WaveGen_calcXYZByFrequency(double frequency, int z, OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01EStimWave* wave);
extern "C" void DGLabESTIM01WaveGen_calcTouchWaveByPosition(double x, double y, OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01EStimWave* wave);
extern "C" void DGLabESTIM01WaveGen_calcTouchWaveByTimeSpan(int timeSpan, OpenEStimCtrl::DGLabESTIM01WaveGen::DGLabESTIM01EStimTouchWave* touchWave, size_t length, OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01EStimWave* wave);
extern "C" void DGLabESTIM01WaveGen_calcAutoWave(OpenEStimCtrl::DGLabESTIM01WaveGen::DGLabESTIM01EStimAutoWaveState* state, OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01EStimWave* wave);

#endif //OPENESTIMCTRLSTATIC_DGLABESTIM01WAVEGEN_H
