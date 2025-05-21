LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ssl
LOCAL_SRC_FILES := prebuilt/lib/$(TARGET_ARCH_ABI)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := crypto
LOCAL_SRC_FILES := prebuilt/lib/$(TARGET_ARCH_ABI)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := curl
LOCAL_SRC_FILES := prebuilt/lib/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libz
LOCAL_SRC_FILES := prebuilt/lib/$(TARGET_ARCH_ABI)/libz.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := shoujocrypt
LOCAL_SRC_FILES := \
    shoujocrypt.c \
    shoujocrypt/utils/cryptutils.c \
    shoujocrypt/utils/device.c \
    shoujocrypt/utils/errr.c \
    shoujocrypt/utils/walk.c \
    shoujocrypt/utils/web.c \
    shoujocrypt/utils/lock.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_STATIC_LIBRARIES := curl ssl crypto libz
LOCAL_CFLAGS := -DNDEBUG -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wall -Wformat -Werror=format-security -O3 -std=c23 -flto
LOCAL_LDFLAGS := -flto -Wl,-z,now,-z,relro
LOCAL_LDLIBS := -ldl
include $(BUILD_EXECUTABLE)