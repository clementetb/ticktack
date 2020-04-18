//
// Created by clemente on 17/04/20.
//

#ifndef TESTING_COUNTER_LIB_H
#define TESTING_COUNTER_LIB_H

#include <jni.h>

extern "C" {
JNIEXPORT jlong JNICALL
Java_com_ticktack_core_TickTackStore_open(JNIEnv *env, jobject thiz, jstring path);

JNIEXPORT jlong JNICALL
Java_com_ticktack_core_TickTackStore_getOrCreate(JNIEnv *env, jobject thiz, jlong handler, jstring key);

JNIEXPORT void JNICALL
Java_com_ticktack_core_TickTackStore_remove(JNIEnv *env, jobject thiz, jlong handler);

JNIEXPORT jlong JNICALL
Java_com_ticktack_core_Counter_increment(JNIEnv *env, jobject thiz, jlong handler);

JNIEXPORT jlong JNICALL
Java_com_ticktack_core_Counter_getValue(JNIEnv *env, jobject thiz, jlong handler);
}


#endif //TESTING_COUNTER_LIB_H
