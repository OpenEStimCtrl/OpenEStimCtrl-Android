package io.openestimctrl.android.openestimctrl

import java.io.Closeable

class DGLabESTIM01(val callback: (serviceUUID: String, characteristicUUID: String, data: ByteArray, length: Int)->Unit) : Closeable {
    private val id = OpenEStimCtrlNative.newID()
    private val ptr: Long = OpenEStimCtrlNative.DGLabESTIM01_new(id, this)
    private var onBatteryStatusChanged: ((Int) -> Unit) = { _ -> }
    private var onStrengthChanged: ((Int, Int) -> Unit) = { _, _ -> }

    enum class Channel(val value: Int) {
        CHANNEL_A(0),
        CHANNEL_B(1)
    }

    override fun close() {
        OpenEStimCtrlNative.DGLabESTIM01_delete(ptr)
    }

    fun parseBLEData(serviceUUID: String, characteristicUUID: String, data: ByteArray) {
        OpenEStimCtrlNative.DGLabESTIM01_parseBLEData(ptr, serviceUUID, characteristicUUID, data, data.size)
    }

    fun setOnBatteryStatusChanged(callback: ((Int) -> Unit)?) {
        onBatteryStatusChanged = if (callback == null) {
            { _ -> }
        } else {
            callback
        }
    }

    fun setOnStrengthChanged(callback: ((Int, Int) -> Unit)?) {
        onStrengthChanged = if (callback == null) {
            { _, _ -> }
        } else {
            callback
        }
    }

    // API
    fun setStrength(strengthA: Int, strengthB: Int) {
        OpenEStimCtrlNative.DGLabESTIM01_setStrength(ptr, strengthA, strengthB)
    }

    fun sendWave(channel: Channel, x: Int, y: Int, z: Int) {
        OpenEStimCtrlNative.DGLabESTIM01_sendWave(ptr, channel.value, x, y, z)
    }


    // Native callbacks
    fun nativeSendCallback(serviceUUID: String, characteristicUUID: String, data: ByteArray) =
        callback(serviceUUID, characteristicUUID, data, data.size)

    fun nativeOnBatteryChangedCallback(battery: Int) =
        onBatteryStatusChanged(battery)

    fun nativeOnStrengthChangedCallback(strengthA: Int, strengthB: Int) =
        onStrengthChanged(strengthA, strengthB)
}