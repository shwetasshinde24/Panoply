/**
 * @author ${kekkaishivn} - dattl@ifi.uio.no
 *
 * ${tags}
 */
#include <pthread.h>
#include <stdio.h>
#include "MyEnclave_u.h"

long ocall_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void printf_ocall_count()	{
	printf("Num of ocall: %d \n", ocall_count);
}

void increase_ocall_count()		{
	pthread_mutex_lock(&lock);
	ocall_count ++;
	pthread_mutex_unlock(&lock);
	printf_ocall_count();
}
