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
#define Cluster_stat 0x600
#define RadarState 0x201



struct Cluster{
	int near_target;
	int far_target;
	int cycle_counter;
	int interface;
};


struct Radar_State{
	int NVMReadStatus;
	int NVMwriteStatus;
	int MaxDistanceCfg;
	int Persistent_Error;
	int Interference;
	int Temperature_Error;
	int Temporary_Error;
	int Voltage_Error;
	int SensorID;
	int SortIndex;
	int RadarPowerCfg;
	int CtrlRelayCfg;
	int OutputTypeCfg;
	int SendQualityCfg;
	int SendExtInfoCfg;
	int MotionRxState;
	int RCS_Threshold;
};


	





extern int open_socket(int *socket_id);
extern void Read_Cluster(int socket_id, struct Cluster *Cluster_ptr);
extern void Read_Radar_State(int socket_id, struct Radar_State *Radar_State_ptr);
extern void displayRadarState(struct Radar_State Radar_State);
