LOCAL_PATH := $(call my-dir)

# These makefiles are here instead of being Android.mk files in the
# respective crypto, ssl, and apps directories so
# that import_openssl.sh import won't remove them.
include $(LOCAL_PATH)/build-config.mk
include $(LOCAL_PATH)/Crypto.mk
