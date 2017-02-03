// /*
//  * Copyright (c) 2002-2007 Niels Provos <provos@citi.umich.edu>
//  * Copyright (c) 2007-2012 Niels Provos and Nick Mathewson
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. The name of the author may not be used to endorse or promote products
//  *    derived from this software without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// #include "event2/event-config.h"

// #include <sys/types.h>
// #include <sgx/sys/stat.h>
// #include <sgx_fcntl_util.h>
// #include <stdlib.h>
// #include <sgx_stdio_util.h>
// #include <string.h>
// #ifndef WIN32
// #include <unistd.h>
// #include <sgx_unistd_util.h>
// #include <sgx_time_struct.h>
// #endif
// #include <errno.h>
// #include <sgx_trts.h>

// #include "event2/event.h"
// #include "event2/event_compat.h"
// #include "event2/event_struct.h"

// #include "TdsEnclave_t.h"

// int called = 0;

// #define NEVENT	20000

// struct event *ev[NEVENT];

// static int
// rand_int(int n)
// {
// #ifdef WIN32
// 	return (int)(rand() % n);
// #else
// 	int ran = 0;
// 	sgx_read_rand((unsigned char*)&ran, sizeof(int));
// 	return (ran % n);
// #endif
// }

// static void
// time_cb(evutil_socket_t fd, short event, void *arg)
// {
// 	struct timeval tv;
// 	int i, j;

// 	called++;

// 	if (called < 10*NEVENT) {
// 		for (i = 0; i < 10; i++) {
// 			j = rand_int(NEVENT);
// 			tv.tv_sec = 0;
// 			tv.tv_usec = rand_int(50000);
// 			if (tv.tv_usec % 2)
// 				evtimer_add(ev[j], &tv);
// 			else
// 				evtimer_del(ev[j]);
// 		}
// 	}
// }

// int
// ecall_unittest_testtime_main(int argc, char **argv)
// {
// 	struct timeval tv;
// 	int i;
// #ifdef WIN32
// 	WORD wVersionRequested;
// 	WSADATA wsaData;

// 	wVersionRequested = MAKEWORD(2, 2);

// 	(void) WSAStartup(wVersionRequested, &wsaData);
// #endif

// 	/* Initalize the event library */
// 	printf("Event init \n");
// 	event_init();
// 	printf("After Event init \n");

// 	for (i = 0; i < NEVENT; i++) {
// 		ev[i] = (event*)malloc(sizeof(struct event));

// 		/* Initalize one event */
// 		evtimer_set(ev[i], time_cb, ev[i]);
// 		tv.tv_sec = 0;
// 		tv.tv_usec = rand_int(50000);
// 		// printf("evtimer_add \n");
// 		evtimer_add(ev[i], &tv);
// 		// printf("after evtimer_add \n");
// 	}

// 	printf(" event_dispatch \n");
// 	event_dispatch();
// 	printf("after event_dispatch \n");

// 	return (called < NEVENT);
// }