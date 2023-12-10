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


#include <jni.h>
#include "includes/YokoNexES01.h"
#include "includes/DGLabESTIM01.h"
#include <map>

std::map<long, jobject> instances;
JNIEnv *savedEnv = nullptr;

void sendCallback(const char* serviceUuid, const char* characteristicUuid, uint8_t* data, int length, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeSendCallback", "(Ljava/lang/String;Ljava/lang/String;[B)V");
    jstring serviceUuidStr = savedEnv->NewStringUTF(serviceUuid);
    jstring characteristicUuidStr = savedEnv->NewStringUTF(characteristicUuid);
    jbyteArray dataArr = savedEnv->NewByteArray(length);
    savedEnv->SetByteArrayRegion(dataArr, 0, length, (jbyte*)data);
    savedEnv->CallVoidMethod(instance, method, serviceUuidStr, characteristicUuidStr, dataArr);
    savedEnv->DeleteLocalRef(serviceUuidStr);
    savedEnv->DeleteLocalRef(characteristicUuidStr);
    savedEnv->DeleteLocalRef(dataArr);
}

void onYokoNexES01ChannelAStatusChange(const OpenEStimCtrl::YokoNexES01::YokoNexES01Status status, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnChannelAStatusChangeCallback", "(IIII)V");
    savedEnv->CallVoidMethod(instance, method, status.connection, status.enabled, status.strength, status.mode);
}

void onYokoNexES01ChannelBStatusChange(const OpenEStimCtrl::YokoNexES01::YokoNexES01Status status, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnChannelBStatusChangeCallback", "(IIII)V");
    savedEnv->CallVoidMethod(instance, method, status.connection, status.enabled, status.strength, status.mode);
}

void onYokoNexES01MotorStatusChange(const OpenEStimCtrl::YokoNexES01::YokoNexES01Motor status, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnMotorStatusChangeCallback", "(I)V");
    savedEnv->CallVoidMethod(instance, method, status);
}

void onYokoNexES01BatteryStatusChange(const uint8_t battery, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnBatteryStatusChangeCallback", "(I)V");
    savedEnv->CallVoidMethod(instance, method, battery);
}

void onYokoNexES01StepStatusChange(const uint16_t step, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnStepStatusChangeCallback", "(I)V");
    savedEnv->CallVoidMethod(instance, method, step);
}

void onYokoNexES01AngleStatusChange(const OpenEStimCtrl::YokoNexES01::YokoNexES01Accel accel, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnAngleStatusChangeCallback", "(IIIIII)V");
    savedEnv->CallVoidMethod(instance, method, accel.accX, accel.accY, accel.accZ, accel.gyroX, accel.gyroY, accel.gyroZ);
}

void onYokoNexES01Exception(const uint8_t code, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnExceptionCallback", "(I)V");
    savedEnv->CallVoidMethod(instance, method, code);
}

extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_YokoNexES01_1delete(JNIEnv *env, jobject thiz,
                                                                      jlong ptr) {
    if (savedEnv == nullptr) {
        savedEnv = env;
    }
    long id = (long)YokoNexES01_getUserData((void*)ptr);
    env->DeleteGlobalRef(instances[id]);
    instances.erase(id);
    YokoNexES01_delete((void*)ptr);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_YokoNexES01_1new(JNIEnv *env,
                                                                                 jobject thiz,
                                                                                 jlong id,
                                                                                 jobject clazz) {
    if (savedEnv == nullptr) {
        savedEnv = env;
    }
    long uid = (long)id;
    auto instance = new OpenEStimCtrl::YokoNexES01::YokoNexES01(sendCallback);
    instance->setUserData((void*)id);
    instance->setOnChannelAStatusChange(onYokoNexES01ChannelAStatusChange);
    instance->setOnChannelBStatusChange(onYokoNexES01ChannelBStatusChange);
    instance->setOnMotorStatusChange(onYokoNexES01MotorStatusChange);
    instance->setOnBatteryStatusChange(onYokoNexES01BatteryStatusChange);
    instance->setOnStepStatusChange(onYokoNexES01StepStatusChange);
    instance->setOnAngleStatusChange(onYokoNexES01AngleStatusChange);
    instance->setOnException(onYokoNexES01Exception);
    instances[uid] = env->NewGlobalRef(clazz);
    return (jlong)instance;
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_YokoNexES01_1parseBLEData(
        JNIEnv *env, jobject thiz, jlong ptr, jbyteArray data, jint len) {
    if (savedEnv == nullptr) {
        savedEnv = env;
    }
    auto instance = (OpenEStimCtrl::YokoNexES01::YokoNexES01*)ptr;
    jbyte* dataPtr = env->GetByteArrayElements(data, nullptr);
    instance->parseBLEData((uint8_t*)dataPtr, len);
}

extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_YokoNexES01_1triggerMotor(
        JNIEnv *env, jobject thiz, jlong ptr, jint mode) {
    auto instance = (OpenEStimCtrl::YokoNexES01::YokoNexES01*)ptr;
    instance->triggerMotor((OpenEStimCtrl::YokoNexES01::YokoNexES01Motor)mode);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_YokoNexES01_1setEStim(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                      jlong ptr,
                                                                                      jint channel,
                                                                                      jboolean enabled,
                                                                                      jint strength,
                                                                                      jint mode,
                                                                                      jint frequency,
                                                                                      jint pulse_width) {
    auto instance = (OpenEStimCtrl::YokoNexES01::YokoNexES01*)ptr;
    instance->setEStim((OpenEStimCtrl::YokoNexES01::YokoNexES01Channel)channel, enabled, strength, (OpenEStimCtrl::YokoNexES01::YokoNexES01Mode)mode, frequency, pulse_width);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_YokoNexES01_1setAngle(JNIEnv *env,
                                                                                      jobject thiz,
                                                                                      jlong ptr,
                                                                                      jboolean setting) {
    auto instance = (OpenEStimCtrl::YokoNexES01::YokoNexES01*)ptr;
    if (setting) {
        instance->setAngle(OpenEStimCtrl::YokoNexES01::YokoNexES01Angle::ANGLE_ON);
    } else {
        instance->setAngle(OpenEStimCtrl::YokoNexES01::YokoNexES01Angle::ANGLE_OFF);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_YokoNexES01_1query(JNIEnv *env,
                                                                                   jobject thiz,
                                                                                   jlong ptr,
                                                                                   jint query) {
    auto instance = (OpenEStimCtrl::YokoNexES01::YokoNexES01*)ptr;
    instance->query((OpenEStimCtrl::YokoNexES01::YokoNexES01Query)query);
}

void onDGLabESTIM01BatteryChange(const uint8_t &level, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnBatteryChangedCallback", "(I)V");
    savedEnv->CallVoidMethod(instance, method, level);
}

void onDGLabESTIM01StrengthChange(const uint16_t &strengthA, const uint16_t &strengthB, void* userData) {
    long id = (long)userData;
    jobject instance = instances[id];
    jclass clazz = savedEnv->GetObjectClass(instance);
    jmethodID method = savedEnv->GetMethodID(clazz, "nativeOnStrengthChangedCallback", "(II)V");
    savedEnv->CallVoidMethod(instance, method, strengthA, strengthB);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_DGLabESTIM01_1new(JNIEnv *env,
                                                                                  jobject thiz,
                                                                                  jlong id,
                                                                                  jobject clazz) {
    if (savedEnv == nullptr) {
        savedEnv = env;
    }
    long uid = (long)id;
    auto instance = new OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01(sendCallback);
    instance->setUserData((void*)id);
    instance->setOnBatteryChange(onDGLabESTIM01BatteryChange);
    instance->setOnStrengthChange(onDGLabESTIM01StrengthChange);
    instances[uid] = env->NewGlobalRef(clazz);
    return (jlong)instance;
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_DGLabESTIM01_1delete(JNIEnv *env,
                                                                                     jobject thiz,
                                                                                     jlong ptr) {
    if (savedEnv == nullptr) {
        savedEnv = env;
    }
    long id = (long)DGLabESTIM01_getUserData((void*)ptr);
    env->DeleteGlobalRef(instances[id]);
    instances.erase(id);
    DGLabESTIM01_delete((void*)ptr);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_DGLabESTIM01_1parseBLEData(
        JNIEnv *env, jobject thiz, jlong ptr, jstring service_uuid, jstring characteristic_uuid,
        jbyteArray data, jint len) {
    if (savedEnv == nullptr) {
        savedEnv = env;
    }

    auto instance = (OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01*)ptr;
    const char* serviceUuidStr = env->GetStringUTFChars(service_uuid, nullptr);
    const char* characteristicUuidStr = env->GetStringUTFChars(characteristic_uuid, nullptr);
    jbyte* dataPtr = env->GetByteArrayElements(data, nullptr);
    instance->parseBLEData(serviceUuidStr, characteristicUuidStr, (uint8_t*)dataPtr, len);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_DGLabESTIM01_1setStrength(
        JNIEnv *env, jobject thiz, jlong ptr, jint strength_a, jint strength_b) {
    auto instance = (OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01*)ptr;
    instance->setStrength(strength_a, strength_b);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_openestimctrl_android_openestimctrl_OpenEStimCtrlNative_DGLabESTIM01_1sendWave(JNIEnv *env,
                                                                                       jobject thiz,
                                                                                       jlong ptr,
                                                                                       jint channel,
                                                                                       jint x,
                                                                                       jint y,
                                                                                       jint z) {
    auto instance = (OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01*)ptr;
    instance->sendWave((OpenEStimCtrl::DGLabESTIM01::DGLabESTIM01Channel)channel, x, y, z);
}