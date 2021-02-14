#include <jni.h>

#ifndef DEMONDK_COMMON_H
#define DEMONDK_COMMON_H

static const char *IOException = "java/io/IOException";
static const char *RuntimeException = "java/io/RuntimeException";

void throwByName(JNIEnv *env, const char *name, const char *msg);

#endif //DEMONDK_COMMON_H
