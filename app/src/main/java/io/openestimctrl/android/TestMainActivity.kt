package io.openestimctrl.android

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import io.openestimctrl.android.openestimctrl.YokoNexES01

class TestMainActivity : AppCompatActivity() {
    val yokoNexES01 = YokoNexES01 { serviceUuid, characteristicUuid, data, len ->
        println("serviceUuid: $serviceUuid, characteristicUuid: $characteristicUuid, data: ${data.contentToString()}, len: $len")
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_test_main)
        yokoNexES01.query(YokoNexES01.Query.QUERY_CHANNEL_A)
    }
}