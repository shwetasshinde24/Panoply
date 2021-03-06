/*
 * Copyright (C) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef _AESM_LOGIC_H
#define _AESM_LOGIC_H

#include <stdlib.h>
#include <stdint.h>
#include "IAESMLogic.h"
#include <aesm_logic.h>

class AESMLogicWrapper :public IAESMLogic {
    public:
        AESMLogicWrapper() {
        }

        ae_error_t service_start(){
            return AESMLogic::service_start();
        }

        void service_stop();

        virtual aesm_error_t initQuote(uint8_t    *target_info,
                uint32_t   target_info_length,
                uint8_t    *gid,
                uint32_t   gid_length);

        virtual aesm_error_t getQuote(uint32_t reportLength, const uint8_t* report,
                uint32_t quoteType,
                uint32_t spidLength, const uint8_t* spid,
                uint32_t nonceLength, const uint8_t* nonce,
                uint32_t sig_rlLength, const uint8_t* sig_rl,
                uint32_t bufferSize, uint8_t* quote,
                uint32_t qe_reportSize, uint8_t* qe_report);

        virtual aesm_error_t closeSession(uint32_t sessionId);

        virtual aesm_error_t createSession(uint32_t *session_id,
                uint8_t *se_dh_msg1,
                uint32_t se_dh_msg1_size);

        virtual aesm_error_t exchangeReport(uint32_t session_id,
                const uint8_t* se_dh_msg2,
                uint32_t se_dh_msg2_size,
                uint8_t* se_dh_msg3,
                uint32_t se_dh_msg3_size);

        virtual aesm_error_t getLaunchToken(const uint8_t *measurement,
                uint32_t        measurement_size,
                const uint8_t   *public_key,
                uint32_t        public_key_size,
                const uint8_t   *se_attributes,
                uint32_t        se_attributes_size,
                uint8_t         **launch_token,
                uint32_t        *launch_token_size);

        virtual aesm_error_t invokeService(const uint8_t  *pse_message_req,
                uint32_t pse_message_req_size,
                uint8_t  *pse_message_resp,
                uint32_t pse_message_resp_size);

        virtual aesm_error_t getPsCap(uint64_t* ps_cap);
        virtual aesm_error_t reportAttestationStatus(uint8_t* platform_info, uint32_t platform_info_size,
                uint32_t attestation_error_code,
                uint8_t* update_info, uint32_t update_info_size);

    private:
        AESMLogicWrapper& operator=(const AESMLogicWrapper&);
        AESMLogicWrapper(const AESMLogicWrapper&);
};

#endif
