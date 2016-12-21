/**
 *
 * Copyright(c) 2011-2016 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to
 * the source code ("Material") are owned by Intel Corporation or its suppliers
 * or licensors. Title to the Material remains with Intel Corporation or its
 * suppliers and licensors. The Material contains trade secrets and proprietary
 * and confidential information of Intel or its suppliers and licensors. The
 * Material is protected by worldwide copyright and trade secret laws and treaty
 * provisions. No part of the Material may be used, copied, reproduced, modified,
 * published, uploaded, posted, transmitted, distributed, or disclosed in any
 * way without Intel's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or delivery
 * of the Materials, either expressly, by implication, inducement, estoppel or
 * otherwise. Any license under such intellectual property rights must be
 * express and approved by Intel(R) in writing.
 *
 */



#pragma once

#ifndef _SGX_STATUS_H_
#define _SGX_STATUS_H_

#include "sgx_error.h"

typedef enum _sgx_device_status_t {
    SGX_ENABLED,
    SGX_DISABLED_REBOOT_REQUIRED,
    SGX_DISABLED_LEGACY_OS,
    SGX_DISABLED
} sgx_device_status_t;

#ifdef _MSC_VER
#include <windows.h>
#ifdef  __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
#ifdef UNICODE
#define sgx_register_wl_cert_chain  sgx_register_wl_cert_chainw
#else
#define sgx_register_wl_cert_chain  sgx_register_wl_cert_chaina
#endif /* !UNICODE */
#endif

/*
 * Function used to query and enable SGX device.
 *
 * @param sgx_device_status[out] The status of SGX device. Can be one of the following values:
            SGX_ENABLED, SGX_DISABLED_REBOOT_REQUIRED, SGX_DISABLED_LEGACY_OS, SGX_DISABLED
 * @return If the function succeeds, return SGX_SUCCESS, any other value indicates an error.
 */
sgx_status_t sgx_enable_device(sgx_device_status_t* sgx_device_status);

/*
 * Function used to register white list cert chain
 *
 * @param CertChainPath[in] The full path of the cert chain.
 * @return If the function succeeds, return SGX_SUCCESS, any other value indicates an error.
 */
sgx_status_t sgx_register_wl_cert_chainw(const LPCWSTR CertChainPath);
sgx_status_t sgx_register_wl_cert_chaina(const LPCSTR CertChainPath);

#ifdef  __cplusplus
}
#endif

#endif

#endif
