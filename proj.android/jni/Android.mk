LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
#cd /cygdrive/d/cocos2dx_example/workplace/network/proj.android/ && /cygdrive/c/Cocos/frameworks/android-ndk-windows/android-ndk-r10d/ndk-build NDK_PROJECT_PATH=. NDK_APPLICATION_MK=./jni/Application.mk NDK_MODULE_PATH=/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/

COCOS2DX_ROOT = "/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1"
#NDK_MODULE_PATH="/cygdrive/c/Cocos/frameworks/android-ndk-windows/android-ndk-r10d"
NDK_MODULE_PATH="/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos"
$(call import-add-path,  /cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/extensions)
$(call import-add-path,  /cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/external)
$(call import-add-path,  /cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos)
#APP_STL := gnustl_static

LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp

#LOCAL_MODULE := protobuf_static
#LOCAL_MODULE_FILENAME := libprotobuf

LOCAL_CPP_EXTENSION := .cc .cpp

LOCAL_LDLIBS:=-L$(SYSROOT)/usr/lib -llog

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/ODSocket.cpp \
                   ../../Classes/Pocket.cpp \
                   ../../Classes/Queue.cpp \
                   ../../Classes/TcpMsg.cpp \
                   ../../Classes/data/talkbox.cc \
                   ../../Classes/utils/CursorTextField.cpp \
                   ../../Classes/utils/MyCharSet.cpp \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/io/coded_stream.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/stubs/common.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/descriptor.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/descriptor.pb.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/descriptor_database.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/dynamic_message.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/extension_set.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/extension_set_heavy.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/generated_message_reflection.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/generated_message_util.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/io/gzip_stream.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/compiler/importer.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/message.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/message_lite.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/stubs/once.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/compiler/parser.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/io/printer.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/reflection_ops.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/repeated_field.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/service.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/stubs/structurally_valid.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/stubs/strutil.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/stubs/substitute.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/stubs/stringprintf.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/text_format.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/io/tokenizer.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/unknown_field_set.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/wire_format.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/wire_format_lite.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/io/zero_copy_stream.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/io/zero_copy_stream_impl.cc \
                    /cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/google/protobuf/io/zero_copy_stream_impl_lite.cc 


                    
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)../../Classes/data/ \
/cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/ \
/cygdrive/e/forthxu/download/protobuf-2.5.0-bz2/src/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/external/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/extensions/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos/2d/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos/2d/base/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos/network/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos/platform/ \
/cygdrive/c/Cocos/frameworks/cocos2d-x-3.8.1/cocos/platform/android/ \
/cygdrive/e/forthxu/download/protobuf-2.5.0/protobuf-2.5.0/vsprojects/Release/


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,./cocos)
#$(call import-module,./prebuilt-mk)


$(call import-module,cocos)
#$(call import-module,cocos/audio/android)
$(call import-module,extensions)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END