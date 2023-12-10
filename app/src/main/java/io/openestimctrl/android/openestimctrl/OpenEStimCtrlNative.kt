/*
OpenEStimCtrl Android
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

package io.openestimctrl.android.openestimctrl

object OpenEStimCtrlNative {
    init {
        System.loadLibrary("OpenEStimCtrlAndroid")
    }

    private var lastID: Long = 0

    fun newID() = lastID++

    external fun YokoNexES01_new(id: Long, clazz: YokoNexES01): Long
    external fun YokoNexES01_delete(ptr: Long)
    external fun YokoNexES01_parseBLEData(ptr: Long, data: ByteArray, len: Int)
    external fun YokoNexES01_triggerMotor(ptr: Long, mode: Int)
    external fun YokoNexES01_setEStim(ptr: Long, channel: Int, enabled: Boolean, strength: Int, mode: Int, frequency: Int, pulseWidth: Int)
    external fun YokoNexES01_setAngle(ptr: Long, setting: Boolean)
    external fun YokoNexES01_query(ptr: Long, query: Int)

    external fun DGLabESTIM01_new(id: Long, clazz: DGLabESTIM01): Long
    external fun DGLabESTIM01_delete(ptr: Long)
    external fun DGLabESTIM01_parseBLEData(ptr: Long, serviceUUID: String, characteristicUUID: String, data: ByteArray, len: Int)
    external fun DGLabESTIM01_setStrength(ptr: Long, strengthA: Int, strengthB: Int)
    external fun DGLabESTIM01_sendWave(ptr: Long, channel: Int, x: Int, y: Int, z: Int)
}