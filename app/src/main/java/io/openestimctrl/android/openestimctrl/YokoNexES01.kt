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

import io.openestimctrl.android.findOrThrowBy
import java.io.Closeable

class YokoNexES01(val callback: (serviceUUID: String, characteristicUUID: String, data: ByteArray, length: Int)->Unit): Closeable {
    private val id = OpenEStimCtrlNative.newID()
    private val ptr: Long = OpenEStimCtrlNative.YokoNexES01_new(id, this)
    private var onException: ((Int) -> Unit) = { _ -> }
    private var onChannelStatusChanged: ((Channel, ChannelStatus, Boolean, Int, ChannelMode) -> Unit) = { _,_, _, _, _ -> }
    private var onMotorStatusChanged: ((MotorMode) -> Unit) = { _ -> }
    private var onBatteryStatusChanged: ((Int) -> Unit) = { _ -> }
    private var onStepChanged: ((Int) -> Unit) = { _ -> }
    private var onAngleChanged: ((Int, Int, Int, Int, Int, Int) -> Unit) = { _,_,_,_,_,_ -> }

    enum class MotorMode(val value: Int) {
        OFF(0x00),
        ON(0x01),
        MOTOR_INTERNAL_1(0x11),
        MOTOR_INTERNAL_2(0x12),
        MOTOR_INTERNAL_3(0x13)
    }
    enum class Channel(val value: Int) {
        CHANNEL_A(0x01),
        CHANNEL_B(0x02),
        CHANNEL_AB(0x03)
    }
    enum class ChannelMode(val value: Int) {
        MODE_INTERNAL_1(0x01),
        MODE_INTERNAL_2(0x02),
        MODE_INTERNAL_3(0x03),
        MODE_INTERNAL_4(0x04),
        MODE_INTERNAL_5(0x05),
        MODE_INTERNAL_6(0x06),
        MODE_INTERNAL_7(0x07),
        MODE_INTERNAL_8(0x08),
        MODE_INTERNAL_9(0x09),
        MODE_INTERNAL_10(0x0A),
        MODE_INTERNAL_11(0x0B),
        MODE_INTERNAL_12(0x0C),
        MODE_INTERNAL_13(0x0D),
        MODE_INTERNAL_14(0x0E),
        MODE_INTERNAL_15(0x0F),
        MODE_INTERNAL_16(0x10),
        MODE_CUSTOM(0x11),
    }
    enum class ChannelStatus(val value: Int) {
        NOT_PLUG_IN(0x00), PLUG_IN_RUNNING(0x01), PLUG_IN_IDLE(0x02)
    }
    enum class Query(val value: Int) {
        QUERY_CHANNEL_A(0x01),
            QUERY_CHANNEL_B(0x02),
            QUERY_MOTOR(0x03),
            QUERY_BATTERY(0x04),
            QUERY_STEP(0x05),
            QUERY_ANGLE(0x06)
    }

    override fun close() {
        OpenEStimCtrlNative.YokoNexES01_delete(ptr)
    }

    fun setOnException(callback: ((Int) -> Unit)?) {
        onException = if (callback == null) {
            { _ -> }
        } else {
            callback
        }
    }

    fun setOnChannelStatusChanged(callback: ((Channel, ChannelStatus, Boolean, Int, ChannelMode) -> Unit)?) {
        onChannelStatusChanged = if (callback == null) {
            { _,_,_,_,_ -> }
        } else {
            callback
        }
    }

    fun setOnMotorStatusChanged(callback: ((MotorMode) -> Unit)?) {
        onMotorStatusChanged = if (callback == null) {
            { _ -> }
        } else {
            callback
        }
    }

    fun setOnBatteryStatusChanged(callback: ((Int) -> Unit)?) {
        onBatteryStatusChanged = if (callback == null) {
            { _ -> }
        } else {
            callback
        }
    }

    fun setOnStepChanged(callback: ((Int) -> Unit)?) {
        onStepChanged = if (callback == null) {
            { _ -> }
        } else {
            callback
        }
    }

    fun setOnAngleChanged(callback: ((Int, Int, Int, Int, Int, Int) -> Unit)?) {
        onAngleChanged = if (callback == null) {
            { _,_,_,_,_,_ -> }
        } else {
            callback
        }
    }

    fun parseBLEData(data: ByteArray) {
        OpenEStimCtrlNative.YokoNexES01_parseBLEData(ptr, data, data.size)
    }

    // API

    fun triggerMotor(mode: MotorMode) {
        OpenEStimCtrlNative.YokoNexES01_triggerMotor(ptr, mode.value)
    }

    fun setEStim(channel: Channel, enabled: Boolean, strength: Int, mode: ChannelMode, frequency: Int, pulseWidth: Int) {
        OpenEStimCtrlNative.YokoNexES01_setEStim(ptr, channel.value, enabled, strength, mode.value, frequency, pulseWidth)
    }

    fun setAngle(enabled: Boolean) {
        OpenEStimCtrlNative.YokoNexES01_setAngle(ptr, enabled)
    }

    fun query(query: Query) {
        OpenEStimCtrlNative.YokoNexES01_query(ptr, query.value)
    }


    // Native callbacks
    fun nativeSendCallback(serviceUUID: String, characteristicUUID: String, data: ByteArray) =
        callback(serviceUUID, characteristicUUID, data, data.size)


    fun nativeOnChannelAStatusChangeCallback(connection: Int, enabled: Boolean, strength: Int, mode: Int) =
        onChannelStatusChanged(Channel.CHANNEL_A, ChannelStatus::value findOrThrowBy connection, enabled, strength, ChannelMode::value findOrThrowBy mode)


    fun nativeOnChannelBStatusChangeCallback(connection: Int, enabled: Boolean, strength: Int, mode: Int, pulseWidth: Int) =
        onChannelStatusChanged(Channel.CHANNEL_B, ChannelStatus::value findOrThrowBy connection, enabled, strength, ChannelMode::value findOrThrowBy mode)


    fun nativeOnMotorStatusChangeCallback(status: Int) =
        onMotorStatusChanged(MotorMode::value findOrThrowBy status)


    fun nativeOnBatteryStatusChangeCallback(battery: Int) =
        onBatteryStatusChanged(battery)


    fun nativeOnStepStatusChangeCallback(step: Int) =
        onStepChanged(step)


    fun nativeOnAngleStatusChangeCallback(accX: Int, accY: Int, accZ: Int, gyroX: Int, gyroY: Int, gyroZ: Int) =
        onAngleChanged(accX, accY, accZ, gyroX, gyroY, gyroZ)


    fun nativeOnExceptionCallback(code: Int) = onException(code)
}