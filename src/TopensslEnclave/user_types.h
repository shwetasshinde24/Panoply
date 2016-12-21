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

/* User defined types */

#include "sgx_eid.h"

#ifdef _MSC_VER
#define memccpy _memccpy
#endif

#define LOOPS_PER_THREAD 100000
#define REMOVE_REPLACEMENT 1

typedef void *buffer_t;
typedef int array_t[10];

#include "struct/sgx_stdio_struct.h"


#ifndef STRING_DUP_H
#define STRING_DUP_H
#include <stdlib.h>
#include <string.h>
// extern 
static inline char *strdup (const char *s) {
  if (s == NULL) return NULL;  
	int len = strlen (s) + 1;
    char *d = (char*)malloc (len);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strncpy (d,s,len);                        // Copy the characters
    return d;                            // Return the new string
}
#endif

extern char *tds_getpassarg(char *arg);
// extern char *tds_readpassphrase(const char *prompt, char *buf, size_t bufsiz, int flags);

extern sgx_enclave_id_t tds_enclave_id;
extern sgx_enclave_id_t vrfcert_enclave_id;
extern uint32_t test_create_session(sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id);
extern uint32_t test_encalve_to_enclave_verify_cert(sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id, uint8_t* data, long len_data);
extern uint32_t test_close_session(sgx_enclave_id_t src_enclave_id, sgx_enclave_id_t dest_enclave_id);

# ifndef _STRUCT_TIMEVAL
# define _STRUCT_TIMEVAL 1

#include <time.h>
struct timeval   {
 time_t tv_sec;
 long int tv_usec;
};
# endif  /* struct timeval */

#ifndef TDS_NET_H
#define TDS_NET_H

#endif

