/**
*   Copyright(C) 2011-2015 Intel Corporation All Rights Reserved.
*
*   The source code, information  and  material ("Material") contained herein is
*   owned  by Intel Corporation or its suppliers or licensors, and title to such
*   Material remains  with Intel Corporation  or its suppliers or licensors. The
*   Material  contains proprietary information  of  Intel or  its  suppliers and
*   licensors. The  Material is protected by worldwide copyright laws and treaty
*   provisions. No  part  of  the  Material  may  be  used,  copied, reproduced,
*   modified, published, uploaded, posted, transmitted, distributed or disclosed
*   in any way  without Intel's  prior  express written  permission. No  license
*   under  any patent, copyright  or  other intellectual property rights  in the
*   Material  is  granted  to  or  conferred  upon  you,  either  expressly,  by
*   implication, inducement,  estoppel or  otherwise.  Any  license  under  such
*   intellectual  property  rights must  be express  and  approved  by  Intel in
*   writing.
*
*   *Third Party trademarks are the property of their respective owners.
*
*   Unless otherwise  agreed  by Intel  in writing, you may not remove  or alter
*   this  notice or  any other notice embedded  in Materials by Intel or Intel's
*   suppliers or licensors in any way.
*/

// MainEnclave.cpp : Defines the exported functions for the DLL application
#include "sgx_eid.h"
// #include "../H2oEnclave.h"
// #include "NeverbleedEnclave.h"
#include "sgx_stdio_util.h"
#ifdef _MSC_VER
#include "NeverbleedEnclave.c"
#endif
#include "EnclaveMessageExchange.h"
#include "error_codes.h"
#include "Utility_E3.h"
#include "sgx_thread.h"
#include "sgx_dh.h"
#include <string.h>
// #include "tls.h"
#include <map>

// #include <openssl/x509.h>
// #include <openssl/pem.h>
// #include <openssl/err.h>
// #include "../vrfcert/vrfcert.h"

// #define fread(A,B,C,D) inline_fread(A,B,C,D)

//This is a test root CA for cert chain file intel/certlists.txt in binary format
//The root CA is hardcoded inside the Enclave which is trusted
const unsigned char root_ca_array[797]={
    0x30,0x82,0x03,0x19,0x30,0x82,0x02,0xc4,0xa0,0x03,0x02,0x01,0x02,0x02,0x01,0x00,
    0x30,0x0a,0x06,0x08,0x2a,0x86,0x48,0xce,0x3d,0x04,0x03,0x04,0x30,0x7f,0x31,0x0b,
    0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x31,0x0b,0x30,0x09,0x06,
    0x03,0x55,0x04,0x08,0x0c,0x02,0x43,0x41,0x31,0x1a,0x30,0x18,0x06,0x03,0x55,0x04,
    0x0a,0x0c,0x11,0x49,0x6e,0x74,0x65,0x6c,0x20,0x43,0x6f,0x72,0x70,0x6f,0x72,0x61,
    0x74,0x69,0x6f,0x6e,0x31,0x2f,0x30,0x2d,0x06,0x03,0x55,0x04,0x0b,0x0c,0x26,0x53,
    0x65,0x63,0x75,0x72,0x65,0x20,0x45,0x6e,0x63,0x6c,0x61,0x76,0x65,0x73,0x20,0x4c,
    0x69,0x63,0x65,0x6e,0x73,0x69,0x6e,0x67,0x20,0x52,0x6f,0x6f,0x74,0x20,0x53,0x69,
    0x67,0x6e,0x69,0x6e,0x67,0x31,0x16,0x30,0x14,0x06,0x03,0x55,0x04,0x03,0x0c,0x0d,
    0x77,0x77,0x77,0x2e,0x69,0x6e,0x74,0x65,0x6c,0x2e,0x63,0x6f,0x6d,0x30,0x1e,0x17,
    0x0d,0x31,0x35,0x30,0x39,0x31,0x36,0x32,0x31,0x30,0x39,0x34,0x37,0x5a,0x17,0x0d,
    0x33,0x35,0x30,0x39,0x31,0x31,0x32,0x31,0x30,0x39,0x34,0x37,0x5a,0x30,0x7f,0x31,
    0x0b,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x55,0x53,0x31,0x0b,0x30,0x09,
    0x06,0x03,0x55,0x04,0x08,0x0c,0x02,0x43,0x41,0x31,0x1a,0x30,0x18,0x06,0x03,0x55,
    0x04,0x0a,0x0c,0x11,0x49,0x6e,0x74,0x65,0x6c,0x20,0x43,0x6f,0x72,0x70,0x6f,0x72,
    0x61,0x74,0x69,0x6f,0x6e,0x31,0x2f,0x30,0x2d,0x06,0x03,0x55,0x04,0x0b,0x0c,0x26,
    0x53,0x65,0x63,0x75,0x72,0x65,0x20,0x45,0x6e,0x63,0x6c,0x61,0x76,0x65,0x73,0x20,
    0x4c,0x69,0x63,0x65,0x6e,0x73,0x69,0x6e,0x67,0x20,0x52,0x6f,0x6f,0x74,0x20,0x53,
    0x69,0x67,0x6e,0x69,0x6e,0x67,0x31,0x16,0x30,0x14,0x06,0x03,0x55,0x04,0x03,0x0c,
    0x0d,0x77,0x77,0x77,0x2e,0x69,0x6e,0x74,0x65,0x6c,0x2e,0x63,0x6f,0x6d,0x30,0x82,
    0x01,0x38,0x30,0x81,0xf5,0x06,0x07,0x2a,0x86,0x48,0xce,0x3d,0x02,0x01,0x30,0x81,
    0xe9,0x02,0x01,0x01,0x30,0x29,0x06,0x07,0x2a,0x86,0x48,0xce,0x3d,0x01,0x01,0x02,
    0x1e,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xff,
    0xff,0xff,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0x30,
    0x57,0x04,0x1e,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,
    0xff,0xff,0xff,0xff,0xff,0x80,0x00,0x00,0x00,0x00,0x00,0x7f,0xff,0xff,0xff,0xff,
    0xfc,0x04,0x1e,0x25,0x57,0x05,0xfa,0x2a,0x30,0x66,0x54,0xb1,0xf4,0xcb,0x03,0xd6,
    0xa7,0x50,0xa3,0x0c,0x25,0x01,0x02,0xd4,0x98,0x87,0x17,0xd9,0xba,0x15,0xab,0x6d,
    0x3e,0x03,0x15,0x00,0x7d,0x73,0x74,0x16,0x8f,0xfe,0x34,0x71,0xb6,0x0a,0x85,0x76,
    0x86,0xa1,0x94,0x75,0xd3,0xbf,0xa2,0xff,0x04,0x3d,0x04,0x67,0x68,0xae,0x8e,0x18,
    0xbb,0x92,0xcf,0xcf,0x00,0x5c,0x94,0x9a,0xa2,0xc6,0xd9,0x48,0x53,0xd0,0xe6,0x60,
    0xbb,0xf8,0x54,0xb1,0xc9,0x50,0x5f,0xe9,0x5a,0x16,0x07,0xe6,0x89,0x8f,0x39,0x0c,
    0x06,0xbc,0x1d,0x55,0x2b,0xad,0x22,0x6f,0x3b,0x6f,0xcf,0xe4,0x8b,0x6e,0x81,0x84,
    0x99,0xaf,0x18,0xe3,0xed,0x6c,0xf3,0x02,0x1e,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0x7f,0xff,0xff,0x97,0x5d,0xeb,0x41,0xb3,0xa6,0x05,0x7c,
    0x3c,0x43,0x21,0x46,0x52,0x65,0x51,0x02,0x01,0x01,0x03,0x3e,0x00,0x04,0x24,0x72,
    0xc1,0xb0,0xbc,0x1f,0x8c,0x76,0x43,0xfc,0xcf,0x4d,0x5e,0x67,0x19,0x91,0x7b,0x12,
    0xe0,0xdc,0xc2,0xa4,0x09,0xca,0xb4,0xeb,0xd4,0x6a,0xe4,0x17,0x25,0x9e,0x15,0xa6,
    0xf9,0x11,0x69,0x4a,0x95,0xe7,0x94,0x46,0xfb,0x37,0x0c,0x0f,0x1a,0xe1,0x60,0x7e,
    0xf6,0xf0,0x98,0x62,0x8f,0x8d,0x36,0xd9,0xc1,0x3c,0xa3,0x50,0x30,0x4e,0x30,0x1d,
    0x06,0x03,0x55,0x1d,0x0e,0x04,0x16,0x04,0x14,0xa6,0xb0,0x2e,0x96,0x9d,0x63,0x24,
    0x05,0x18,0x3e,0xf3,0x0c,0x29,0x81,0xeb,0x8a,0xa8,0x1a,0x21,0x3b,0x30,0x1f,0x06,
    0x03,0x55,0x1d,0x23,0x04,0x18,0x30,0x16,0x80,0x14,0xa6,0xb0,0x2e,0x96,0x9d,0x63,
    0x24,0x05,0x18,0x3e,0xf3,0x0c,0x29,0x81,0xeb,0x8a,0xa8,0x1a,0x21,0x3b,0x30,0x0c,
    0x06,0x03,0x55,0x1d,0x13,0x04,0x05,0x30,0x03,0x01,0x01,0xff,0x30,0x0a,0x06,0x08,
    0x2a,0x86,0x48,0xce,0x3d,0x04,0x03,0x04,0x03,0x43,0x00,0x30,0x40,0x02,0x1e,0x6f,
    0x2a,0x4d,0x70,0x89,0x59,0xe4,0x74,0x3b,0x8d,0x13,0x29,0xd9,0x5a,0x76,0x39,0xc0,
    0xe6,0xd1,0x81,0xce,0xfd,0x16,0x76,0x07,0x86,0xf4,0x4f,0x93,0xa9,0x02,0x1e,0x60,
    0x1d,0xb4,0x43,0xb2,0x1f,0xf8,0x28,0x59,0xdc,0xa9,0x05,0x31,0x11,0xbb,0x4f,0x02,
    0x74,0x2d,0x73,0x45,0x4b,0x6c,0xce,0x81,0xa9,0xc4,0x47,0x11,0x54
};

sgx_enclave_id_t tds_enclave_id;
sgx_enclave_id_t vrfcert_enclave_id;

// //Function to load the root ca
// static int read_root_ca(X509 **root_ca)
// {
//     const unsigned char *p = root_ca_array;

//     if(d2i_X509(root_ca, &p, sizeof(root_ca_array)) == NULL)
//         return -1;
//     return 0;
// }

// //function to read in ca chain in PEM format
// static vrf_cert_error_code_t read_ca(const uint8_t *ca, uint32_t ca_in_size, 
//                                      STACK_OF(X509) **pcerts, 
//                                      STACK_OF(X509_CRL) **pcrls)
// {
//     //printf("\n read_ca \n ");
//     vrf_cert_error_code_t ret = VCE_UNKNOWN;
//     BIO *memBIO = NULL;
//     STACK_OF(X509_INFO) *xis = NULL;
//     X509_INFO *xi;

//     //create an memory BIO so that we could transform data format via BIO
//     memBIO = BIO_new(BIO_s_mem());
//     if(memBIO == NULL)
//     {
//         ret = VCE_OUT_OF_MEMORY;
//         goto ret_point;
//     }
//     if(BIO_write(memBIO, ca, ca_in_size)==NULL)
//         goto ret_point;
//     *pcerts = sk_X509_new_null();
//     *pcrls = sk_X509_CRL_new_null();
//     if(*pcerts == NULL || *pcrls == NULL)
//     {
//         ret = VCE_OUT_OF_MEMORY;
//         goto ret_point;
//     }
//     //decode certs and crls from memory BIO
//     xis = PEM_X509_INFO_read_bio(memBIO, NULL, NULL, NULL);
//     if(xis == NULL)//unkown error
//         goto ret_point;
//     BIO_free(memBIO);
//     memBIO = NULL;
//     //create list of certs and list of crls respectively
//     for(int i = 0; i < sk_X509_INFO_num(xis); i++)
//     {
//         xi = sk_X509_INFO_value (xis, i);
//         if (xi->x509)
//         {
//             if (!sk_X509_push(*pcerts, xi->x509))
//                 goto ret_point;
//             //clear the cert from original list to avoid free the memory twice 
//             //  since the memory will be release when we release the list
//             xi->x509 = NULL;
//         }
//         if (xi->crl)
//         {
//             if (!sk_X509_CRL_push(*pcrls, xi->crl))
//                 goto ret_point;
//             //clear the cert from original list to avoid free the memory twice
//             //  since the memory will be release when we release the list
//             xi->crl = NULL;
//         }
//     }
//     if(sk_X509_CRL_num(*pcrls)==0)
//     {
//         //set it to NULL for special case: empty crl lists
//         sk_X509_CRL_pop_free(*pcrls, X509_CRL_free);
//         *pcrls = NULL;
//     }
//     ret = VCE_SUCCESS;
// ret_point:
//     if(memBIO!=NULL)BIO_free(memBIO);
//     if(xis!=NULL)sk_X509_INFO_pop_free(xis, X509_INFO_free);
//     if(ret!=VCE_SUCCESS)
//     {
//         //the pcerts and pcrls will be return to caller only when the function is successful
//         if(*pcerts!=NULL)
//         {
//             sk_X509_pop_free(*pcerts, X509_free);
//             *pcerts = NULL;
//         }
//         if(*pcrls!=NULL)
//         {
//             sk_X509_CRL_pop_free(*pcrls, X509_CRL_free);
//             *pcrls = NULL;
//         }
//     }
//     return ret;
// }

// //Function to verify the certificate chain pcerts
// vrf_cert_error_code_t verify_certs(X509 *root_ca, 
//                                    STACK_OF(X509) *pcerts, 
//                                    STACK_OF(X509_CRL) *pcrls)
// {
//     // printf("\n verify_certs \n ");
//     X509_STORE *store = NULL;
//     X509_STORE_CTX *ctx = NULL;
//     STACK_OF(X509) *trusted_cert_chain = NULL;
//     int i;
//     vrf_cert_error_code_t ret = VCE_UNKNOWN;

//     if(pcerts == NULL||
//         sk_X509_num(pcerts)==0)//at least one cert should be provided
//         return VCE_PARAM_INVALID;

//     trusted_cert_chain = sk_X509_new_null();
//     if(trusted_cert_chain == NULL)
//     {
//         ret = VCE_OUT_OF_MEMORY;
//         goto ret_point;
//     }
//     //First put the root ca into the trusted cert chain.
//     //The root ca is hard-coded into the enclave 
//     //  so that it could not be modified by attacker
//     if(!sk_X509_push(trusted_cert_chain, root_ca))
//     {
//         ret = VCE_UNKNOWN;
//         goto ret_point;
//     }

//     store = X509_STORE_new();
//     if(store == NULL)
//     {
//         ret = VCE_OUT_OF_MEMORY;
//         goto ret_point;
//     }

//     ctx = X509_STORE_CTX_new();
//     if(ctx == NULL)
//     {
//         ret = VCE_OUT_OF_MEMORY;
//         goto ret_point;
//     }

//     //Now verify the certs in the cert chain one by one
//     for(i=0; i<sk_X509_num(pcerts);++i)
//     {
//         X509 *cur_cert = sk_X509_value(pcerts, i);
//         X509_STORE_set_flags(store, X509_V_FLAG_IGNORE_CRITICAL);
//         if(pcrls!=NULL)
//         {
//             X509_STORE_set_flags(store, X509_V_FLAG_CRL_CHECK);
//         }
//         if(!X509_STORE_CTX_init(ctx, store, cur_cert, NULL))
//         {
//             ret = VCE_UNKNOWN;
//             goto ret_point;
//         }
//         if(pcrls != NULL)
//         {
//             //The crls should be used if it is provided
//             X509_STORE_CTX_set0_crls(ctx, pcrls);
//         }
//         X509_STORE_CTX_trusted_stack(ctx, trusted_cert_chain);

//         if( X509_verify_cert(ctx) == 1)
//         {
//             //verify success
//             //put the current cert into trusted cert chain 
//             //  since it will be used to verify the next level's cert
//             if(!sk_X509_push(trusted_cert_chain, cur_cert))
//             {
//                 ret = VCE_UNKNOWN;
//                 goto ret_point;
//             }
//         }
//         else
//         {
//             //decode error code
//             int err = X509_STORE_CTX_get_error(ctx);
//             switch(err){
//             case X509_V_ERR_CERT_HAS_EXPIRED:
//                 ret = VCE_LICENSE_EXPIRE;
//                 break;
//             case X509_V_ERR_CRL_HAS_EXPIRED:
//                 ret = VCE_CRL_EXPIRE;
//                 break;
//             case X509_V_ERR_CERT_REVOKED:
//                 ret = VCE_CERT_REVOKED;
//                 break;
//             default:
//                 ret = VCE_UNKNOWN;
//                 break;
//             }
//             goto ret_point;
//         }
//         X509_STORE_CTX_cleanup(ctx);
//     }
//     ret = VCE_SUCCESS;
// ret_point:
//     if(ctx != NULL)
//     {
//         X509_STORE_CTX_free(ctx);
//     }
//     if(store != NULL)
//     {
//         X509_STORE_free(store);
//     }
//     if(trusted_cert_chain!=NULL)
//     {
//         for(i=0;i<sk_X509_num(trusted_cert_chain); ++i)
//         {
//             //unlink all certs from the sk to avoid it is freed here. 
//             //   There'll be freed later in pcerts
//             sk_X509_set(trusted_cert_chain, i, NULL);
//         }
//         sk_X509_pop_free(trusted_cert_chain, X509_free);
//     }
//     return ret;
// }

// int verify_cert_in_perm(const uint8_t* cert, uint32_t cert_in_size)
// {
//     printf("\n verify_cert_in_perm \n ");
//     X509 *root_ca = NULL;
//     int ret = -1;
//     STACK_OF(X509) *pcerts = NULL;
//     STACK_OF(X509_CRL) *pcrls = NULL;

//     OpenSSL_add_all_algorithms();//initialize required algrithm

//     if(cert==NULL||cert_in_size==0)
//         goto ret_point;//invalid input parameter
//     if(read_root_ca(&root_ca)!=0)
//         goto ret_point;
//     if(read_ca(cert, cert_in_size, &pcerts, &pcrls)!=0)
//         goto ret_point;
//     ret = verify_certs(root_ca, pcerts, pcrls);
// ret_point:
//     if(root_ca != NULL)
//     {
//         X509_free(root_ca);
//     }
//     if(pcerts!=NULL)
//     {
//         sk_X509_pop_free(pcerts, X509_free);
//     }
//     if(pcrls!=NULL)
//     {
//         sk_X509_CRL_pop_free(pcrls, X509_CRL_free);
//     }
//     //clean potential memory usages
//     OBJ_cleanup();
//     EVP_cleanup();
//     CRYPTO_cleanup_all_ex_data();
//     ERR_remove_thread_state(NULL);
//     ERR_free_strings();
//     return ret;
// }


#define UNUSED(val) (void)(val)
#define TCHAR char
#define fprintf_s fprintf

std::map<sgx_enclave_id_t, dh_session_t>g_src_session_info_map;

static uint32_t e3_foo1_wrapper(ms_in_msg_exchange_t *ms, size_t param_lenth, char** resp_buffer, size_t* resp_length);

#ifdef _MSC_VER
#pragma warning( push )
//warning C4200: nonstandard extension used : zero-sized array in struct/union
#pragma warning( disable : 4200 )
#endif
//Function pointer table containing the list of functions that the enclave exposes
const struct {
    size_t num_funcs;
    const void* table[1];
} func_table = {
    1,
    {
        (const void*)e3_foo1_wrapper,
    }
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif



//Makes use of the sample code function to establish a secure channel with the destination enclave
uint32_t test_create_session(sgx_enclave_id_t src_enclave_id,
                          sgx_enclave_id_t dest_enclave_id)
{
    sgx_wrapper_printf("Call test_create_session \n");
    ATTESTATION_STATUS ke_status = SUCCESS;
    dh_session_t dest_session_info;
    //Core reference code function for creating a session
    ke_status = create_session(src_enclave_id, dest_enclave_id,&dest_session_info);
    if(ke_status == SUCCESS)
    {
        //Insert the session information into the map under the corresponding destination enclave id
        g_src_session_info_map.insert(std::pair<sgx_enclave_id_t, dh_session_t>(dest_enclave_id, dest_session_info));
    }
    memset(&dest_session_info, 0, sizeof(dh_session_t));
    sgx_wrapper_printf("return test_create_session %x \n", ke_status);
    return ke_status;
}

uint32_t test_encalve_to_enclave_verify_cert(sgx_enclave_id_t src_enclave_id,
                                          sgx_enclave_id_t dest_enclave_id, uint8_t* data, long len_data)
{
    ATTESTATION_STATUS ke_status = ATTESTATION_ERROR;
    verify_cert_param_struct_t *p_struct_var, struct_var;
    uint32_t target_fn_id, msg_type;
    char* marshalled_inp_buff;
    size_t marshalled_inp_buff_len;
    char* out_buff;
    size_t out_buff_len;
    dh_session_t *dest_session_info;
    size_t max_out_buff_size;
    uint32_t retval;

    max_out_buff_size = len_data + 2*sizeof(uint32_t);
    msg_type = ENCLAVE_TO_ENCLAVE_CALL;
    target_fn_id = 1;
    struct_var.len_data = len_data;
    struct_var.data = data;
    p_struct_var = &struct_var;
    verify_cert_param_struct_t *p_ret_struct_var, ret_struct_var;
    p_ret_struct_var = &ret_struct_var;

    //Marshals the input parameters for calling function verify_cert in vercert_enclave into a input buffer
    ke_status = marshal_input_parameters_e1_verfycert(target_fn_id, msg_type, p_struct_var, len_data, &marshalled_inp_buff, &marshalled_inp_buff_len);

    if(ke_status != SUCCESS)
    {
        return ke_status;
    }

    //Search the map for the session information associated with the destination enclave id passed in
    std::map<sgx_enclave_id_t, dh_session_t>::iterator it = g_src_session_info_map.find(dest_enclave_id);
    if(it != g_src_session_info_map.end())
    {
        dest_session_info = &it->second;
    }
    else
    {
        SAFE_FREE(marshalled_inp_buff);
        return INVALID_SESSION;
    }

    //Core Reference Code function
    ke_status = send_request_receive_response(src_enclave_id, dest_enclave_id, dest_session_info,
                  marshalled_inp_buff, marshalled_inp_buff_len, max_out_buff_size+2*sizeof(uint32_t), &out_buff, &out_buff_len);

    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    ////Un-marshal the return value and output parameters from verify_cert of vrfcert_enclave
    ke_status = unmarshal_retval_and_output_parameters_e1_verify(out_buff, p_ret_struct_var, &retval);
    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    if (p_ret_struct_var->len_data!=len_data)
        return ENCRYPT_DECRYPT_ERROR;

    if (memcmp(p_ret_struct_var->data, p_struct_var->data, len_data)!=0)
    {
        sgx_wrapper_printf("\nReturn certificate mismatch");
        return ENCRYPT_DECRYPT_ERROR;
    }

    if(retval == 0)
    {
        sgx_wrapper_printf("\nIn MainEnclave return result is: Verify passed");
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return SUCCESS;        
    }
    else
    {
        sgx_wrapper_printf("\nMainEnclave return result is: Verify failed \n");
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ATTESTATION_ERROR;           
    }  
}

//Makes use of the sample code function to do an enclave to enclave call (Test Vector)
uint32_t test_enclave_to_enclave_call(sgx_enclave_id_t src_enclave_id,
                                          sgx_enclave_id_t dest_enclave_id)
{
    ATTESTATION_STATUS ke_status = SUCCESS;
    external_param_struct_t *p_struct_var, struct_var;
    internal_param_struct_t internal_struct_var;
    uint32_t target_fn_id, msg_type;
    char* marshalled_inp_buff;
    size_t marshalled_inp_buff_len;
    char* out_buff;
    size_t out_buff_len;
    dh_session_t *dest_session_info;
    size_t max_out_buff_size;
    char* retval;

    max_out_buff_size = 50;
    msg_type = ENCLAVE_TO_ENCLAVE_CALL;
    target_fn_id = 0;
    internal_struct_var.ivar1 = 0x5;
    internal_struct_var.ivar2 = 0x6;
    struct_var.var1 = 0x3;
    struct_var.var2 = 0x4;
    struct_var.p_internal_struct = &internal_struct_var;
    p_struct_var = &struct_var;

    size_t len_data = sizeof(struct_var) - sizeof(struct_var.p_internal_struct);
    size_t len_ptr_data = sizeof(internal_struct_var);

    //Marshals the input parameters for calling function foo1 in Enclave1 into a input buffer
    ke_status = marshal_input_parameters_e1_foo1(target_fn_id, msg_type, p_struct_var, len_data,
                                len_ptr_data, &marshalled_inp_buff, &marshalled_inp_buff_len);

    if(ke_status != SUCCESS)
    {
        return ke_status;
    }

    //Search the map for the session information associated with the destination enclave id passed in
    std::map<sgx_enclave_id_t, dh_session_t>::iterator it = g_src_session_info_map.find(dest_enclave_id);
    if(it != g_src_session_info_map.end())
    {
        dest_session_info = &it->second;
    }
    else
    {
        SAFE_FREE(marshalled_inp_buff);
        return INVALID_SESSION;
    }

    //Core Reference Code function
    ke_status = send_request_receive_response(src_enclave_id, dest_enclave_id, dest_session_info,
                  marshalled_inp_buff, marshalled_inp_buff_len, max_out_buff_size, &out_buff, &out_buff_len);

    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    ////Un-marshal the return value and output parameters from foo1 of Enclave1
    ke_status = unmarshal_retval_and_output_parameters_e1_foo1(out_buff, p_struct_var, &retval);
    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    SAFE_FREE(marshalled_inp_buff);
    SAFE_FREE(out_buff);
    SAFE_FREE(retval);
    return SUCCESS;
}

//Makes use of the sample code function to do a generic secret message exchange (Test Vector)
uint32_t test_message_exchange(sgx_enclave_id_t src_enclave_id,
                               sgx_enclave_id_t dest_enclave_id)
{
    ATTESTATION_STATUS ke_status = SUCCESS;
    uint32_t target_fn_id, msg_type;
    char* marshalled_inp_buff;
    size_t marshalled_inp_buff_len;
    char* out_buff;
    size_t out_buff_len;
    dh_session_t *dest_session_info;
    size_t max_out_buff_size;
    char* secret_response;
    uint32_t secret_data;

    target_fn_id = 0;
    msg_type = MESSAGE_EXCHANGE;
    max_out_buff_size = 50;
    secret_data = 0x12345678; //Secret Data here is shown only for purpose of demonstration.

    //Marshals the parameters into a buffer
    ke_status = marshal_message_exchange_request(target_fn_id, msg_type, secret_data, &marshalled_inp_buff, &marshalled_inp_buff_len);
    if(ke_status != SUCCESS)
    {
        return ke_status;
    }
    //Search the map for the session information associated with the destination enclave id passed in
    std::map<sgx_enclave_id_t, dh_session_t>::iterator it = g_src_session_info_map.find(dest_enclave_id);
    if(it != g_src_session_info_map.end())
    {
        dest_session_info = &it->second;
    }
    else
    {
        SAFE_FREE(marshalled_inp_buff);
        return INVALID_SESSION;
    }

    //Core Reference Code function
    ke_status = send_request_receive_response(src_enclave_id, dest_enclave_id, dest_session_info, marshalled_inp_buff,
                                                marshalled_inp_buff_len, max_out_buff_size, &out_buff, &out_buff_len);

    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }
    //Un-marshal the secret response data
    ke_status = umarshal_message_exchange_response(out_buff, &secret_response);
    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    SAFE_FREE(marshalled_inp_buff);
    SAFE_FREE(out_buff);
    SAFE_FREE(secret_response);
    return SUCCESS;
}


//Makes use of the sample code function to close a current session
uint32_t test_close_session(sgx_enclave_id_t src_enclave_id,
                                sgx_enclave_id_t dest_enclave_id)
{
    sgx_wrapper_printf("Call test_close_session \n");
    dh_session_t dest_session_info;
    ATTESTATION_STATUS ke_status = SUCCESS;
    //Search the map for the session information associated with the destination enclave id passed in
    std::map<sgx_enclave_id_t, dh_session_t>::iterator it = g_src_session_info_map.find(dest_enclave_id);
    if(it != g_src_session_info_map.end())
    {
        dest_session_info = it->second;
    }
    else
    {
        return NULL;
    }
    //Core reference code function for closing a session
    ke_status = close_session(src_enclave_id, dest_enclave_id);

    //Erase the session information associated with the destination enclave id
    g_src_session_info_map.erase(dest_enclave_id);
    sgx_wrapper_printf("return test_close_session \n");
    return ke_status;
}

//Function that is used to verify the trust of the other enclave
//Each enclave can have its own way verifying the peer enclave identity
extern "C" uint32_t verify_peer_enclave_trust(sgx_dh_session_enclave_identity_t* peer_enclave_identity)
{
    if(!peer_enclave_identity)
    {
        return INVALID_PARAMETER_ERROR;
    }
    if(peer_enclave_identity->isv_prod_id != 0 || !(peer_enclave_identity->attributes.flags & SGX_FLAGS_INITTED))
        // || peer_enclave_identity->attributes.xfrm !=3)// || peer_enclave_identity->mr_signer != xx //TODO: To be hardcoded with values to check
    {
        return ENCLAVE_TRUST_ERROR;
    }
    else
    {
        return SUCCESS;
    }
}


//Dispatch function that calls the approriate enclave function based on the function id
//Each enclave can have its own way of dispatching the calls from other enclave
extern "C" uint32_t enclave_to_enclave_call_dispatcher(char* decrypted_data,
                                                       size_t decrypted_data_length,
                                                       char** resp_buffer,
                                                       size_t* resp_length)
{
    ms_in_msg_exchange_t *ms;
    uint32_t (*fn1)(ms_in_msg_exchange_t *ms, size_t, char**, size_t*);
    if(!decrypted_data || !resp_length)
    {
        return INVALID_PARAMETER_ERROR;
    }
    ms = (ms_in_msg_exchange_t *)decrypted_data;
    if(ms->target_fn_id >= func_table.num_funcs)
    {
        return INVALID_PARAMETER_ERROR;
    }
    fn1 = (uint32_t (*)(ms_in_msg_exchange_t*, size_t, char**, size_t*))func_table.table[ms->target_fn_id];
    return fn1(ms, decrypted_data_length, resp_buffer, resp_length);
}

//Operates on the input secret and generates the output secret
uint32_t get_message_exchange_response(uint32_t inp_secret_data)
{
    uint32_t secret_response;

    //User should use more complex encryption method to protect their secret, below is just a simple example
    secret_response = inp_secret_data & 0x11111111;

    return secret_response;

}
//Generates the response from the request message
extern "C" uint32_t message_exchange_response_generator(char* decrypted_data,
                                              char** resp_buffer,
                                              size_t* resp_length)
{
    ms_in_msg_exchange_t *ms;
    uint32_t inp_secret_data;
    uint32_t out_secret_data;
    if(!decrypted_data || !resp_length)
    {
        return INVALID_PARAMETER_ERROR;
    }
    ms = (ms_in_msg_exchange_t *)decrypted_data;

    if(umarshal_message_exchange_request(&inp_secret_data,ms) != SUCCESS)
        return ATTESTATION_ERROR;

    out_secret_data = get_message_exchange_response(inp_secret_data);

    if(marshal_message_exchange_response(resp_buffer, resp_length, out_secret_data) != SUCCESS)
        return MALLOC_ERROR;

    return SUCCESS;

}


static uint32_t e3_foo1(param_struct_t *p_struct_var)
{
    if(!p_struct_var)
    {
        return INVALID_PARAMETER_ERROR;
    }
    p_struct_var->var1++;
    p_struct_var->var2++;

    return(p_struct_var->var1 * p_struct_var->var2);
}

//Function which is executed on request from the source enclave
static uint32_t e3_foo1_wrapper(ms_in_msg_exchange_t *ms,
                    size_t param_lenth,
                    char** resp_buffer,
                    size_t* resp_length)
{
    UNUSED(param_lenth);
    
    uint32_t ret;
    param_struct_t *p_struct_var;
    if(!ms || !resp_length)
    {
        return INVALID_PARAMETER_ERROR;
    }
    p_struct_var = (param_struct_t*)malloc(sizeof(param_struct_t));
    if(!p_struct_var)
        return MALLOC_ERROR;

    if(unmarshal_input_parameters_e3_foo1(p_struct_var, ms) != SUCCESS)
    {
        SAFE_FREE(p_struct_var);
        return ATTESTATION_ERROR;
    }

    ret = e3_foo1(p_struct_var);

    if(marshal_retval_and_output_parameters_e3_foo1(resp_buffer, resp_length, ret, p_struct_var) != SUCCESS)
    {
        SAFE_FREE(p_struct_var);
        return MALLOC_ERROR;
    }
    SAFE_FREE(p_struct_var);
    return SUCCESS;
}

void ecall_set_communication_enclave_ids(sgx_enclave_id_t tds_id,
                               sgx_enclave_id_t vrfcert_id)
{
    sgx_wrapper_printf("\nCall ecall set token tds_id:%d - vrfcert_id:%d", tds_id, vrfcert_id);
    tds_enclave_id = tds_id;
    vrfcert_enclave_id = vrfcert_id;
}

void ecall_x509_main(int argc, char** argv, sgx_enclave_id_t main_enclave_id,
 sgx_enclave_id_t vrfcert_enclave_id)
{

}

