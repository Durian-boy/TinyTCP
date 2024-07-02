#include <stdio.h>
#include "sys_plat.h"
#include "echo/tcp_echo_client.h"
#include "echo/tcp_echo_server.h"

static sys_semt sem;
static sys_mutex_t mutex;
static int count

static char buffer[100];
static int write_index, read_index, total;
static sys_sem_t read_sem, write_sem;

void thread1_entry(void* arg) {
	for (int i = 0; i < 2 * sizeof(buffer); ++i) {
		sys_sem_wait(read_sem, 0);

		char data = buffer[read_index++];
	}
}