//
// Created by clemente on 17/04/20.
//

#include "ticktack-jni.h"
#include "TickTackStore.h"

using namespace TickTack;

extern "C" {
JNIEXPORT jlong JNICALL
Java_com_ticktack_core_TickTackStore_open(JNIEnv *env, jobject thiz, jstring path) {
  auto charPath = env->GetStringUTFChars(path, nullptr);

  TickTackStore *keyStore = new TickTackStore(charPath);
  env->ReleaseStringUTFChars(path, charPath);

  return reinterpret_cast<jlong>(keyStore);
}

JNIEXPORT jlong JNICALL
Java_com_ticktack_core_TickTackStore_getOrCreate(JNIEnv *env, jobject thiz, jlong handler,
                                                 jstring key) {
  TickTackStore *tickTackStore = (TickTackStore *) reinterpret_cast<void *>(handler);

  if (tickTackStore == nullptr) {
    jclass Exception = env->FindClass("java/lang/Exception");
    env->ThrowNew(Exception, "Handler does not point to a TickTackStore");
    return 0;
  }

  auto charKey = env->GetStringUTFChars(key, nullptr);
  Counter &counter = tickTackStore->getOrCreate(charKey);
  env->ReleaseStringUTFChars(key, charKey);

  return reinterpret_cast<jlong>(&counter);
}

JNIEXPORT void JNICALL
Java_com_ticktack_core_TickTackStore_remove(JNIEnv *env, jobject thiz, jlong handler) {
  TickTackStore *tickTackStore = (TickTackStore *) reinterpret_cast<void *>(handler);

  if (tickTackStore == nullptr) {
    jclass Exception = env->FindClass("java/lang/Exception");
    env->ThrowNew(Exception, "Handler does not point to a TickTackStore");
    return;
  }

  tickTackStore->remove();
  delete tickTackStore;
}

JNIEXPORT jlong JNICALL
Java_com_ticktack_core_Counter_increment(JNIEnv *env, jobject thiz, jlong handler) {
  Counter *counter = (Counter *) reinterpret_cast<void *>(handler);

  if (counter == nullptr) {
    jclass Exception = env->FindClass("java/lang/Exception");
    env->ThrowNew(Exception, "Handler does not point to a Counter");
    return 0;
  }

  (*counter)++;

  auto clazz = env->FindClass("com/ticktack/core/TickTackStore");
  auto method = env->GetStaticMethodID(clazz,
                                       "onDataChange",
                                       "(Ljava/lang/String;J)V");

//  env->CallStaticVoidMethod(clazz, method,
//                            env->NewStringUTF("hello"),
//                            jlong((unsigned long) *counter));

  return (unsigned long) *counter;
}

JNIEXPORT jlong JNICALL
Java_com_ticktack_core_Counter_getValue(JNIEnv *env, jobject thiz, jlong handler) {
  // TODO: implement getValue()
  Counter *counter = (Counter *) reinterpret_cast<void *>(handler);

  if (counter == nullptr) {
    jclass Exception = env->FindClass("java/lang/Exception");
    env->ThrowNew(Exception, "Handler does not point to a Counter");
    return 0;
  }

  return (unsigned long) *counter;
}
}
