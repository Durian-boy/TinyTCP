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

		if (read_index >= sizeof(buffer)) {
			read_index = 0;
		}

		sys_mutex_lock(mutex);
		total--;
		sys_mutex_unlock(mutex);

		sys_sem_notify(write_sem);

		plat_printf("thread 1 : read data = %d\n", data);

		sys_sleep(100);
	}

	while (1) {
		plat_printf("this is thread1: %s\n", (char* )arg);
		sys_sleep(1000);
		sys_sem_notify(sem);
		sys_sleep(1000);
	}
}

void thread2_entry (void* arg) {
	sys_sleep(100);

	for (int i = 0; i < 2 * sizeof(buffer); ++i) {
		sys_sem_wait(write_sem, 0);

		buffer[write_index++] = i;

		if (write_index >= sizeof(buffer)) {
			write_index = 0;
		}

		sys_mutex_lock(mutex);
		total++;
		sys_mutex_unlock(mutex);

		plat_printf("thread 2 : write data = %d\n", data);

		sys_sem_notify(read_sem);
	}

	while (1) {
		sys_sem_wait(sem, 0);
		plat_printf("this is thread2: %s\n", (char* )arg);
	}
}

int main(void) {
	net_init();

	net_start();

	sem = sys_sem_create(0);
	mutex = sys_mutex_create();

	read_sem = sys_sem_create(0);
	write_sem = sys_sem_create(sizeof(buffer));

	// sys_thread_create(thread1_entry, "AAAA");
	// sys_thread_create(thread2_entry, "BBBB");

	// tcp_echo_client_start(friend0_ip, 5000);
	tcp_echo_server_start(5000);

	pcap_t* pcap = pcap_device_open(netdev0_phy_ip, netdev0_hwaddr);
	while(pcap) {
		static uint8_t buffer[1024];
		static int counter = 0;
		static pcap_pkthdr* pkthdr;
		const uint8_t* pkt_data;
	}
}