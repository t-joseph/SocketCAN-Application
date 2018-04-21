/* Header file for the project "MOBILE PLATTFORM 		*/


#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <string.h>


#define Buf_Max 500			/* maximum size of the record buffer */

struct Cluster{
	int near_target;
	int far_target;
	int cycle_counter;
	int interface;
};


	

#define Cluster_stat 0x600
#define d1 0.0
#define d2 0.0
#define c1 0.0
#define c2 0.0


extern int open_socket(int *socket_id);
extern void Read_Cluster(int socket_id, struct Cluster *Cluster_ptr);
