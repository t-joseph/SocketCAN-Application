/* Header file for the project "MOBILE PLATTFORM 		*/


#include <math.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
#define Cluster_QuaInfId 0x702
/* Definitions for Cluster genral information*/
#define Cluster_Gen 0x701
#define scal_dist 0.2
#define scal_vrel 0.25
#define RCS_res 0.5
#define offst_dtlong -500
#define offst_dtlat -102.3
#define offst_vrellong -128
#define offst_vrellat -64
#define offst_rcs -64

#define X_max 12			/* Maximum of X-Axis */
#define X_min 0			/* Minimum of X-Axis */
#define Y_max 8.34		/* Maximum of Y-Axis */
#define Y_min 0			/* Minimum of Y-Axis */
#define BUF_LEN 20			/* Number of Elements in the Path-Buffer */

#define offset_DistLat -204.6
#define Object_stat 0x60A
#define Object_geninformation 0x60B
#define Object_qualityinformation 0x60C
#define Object_extendedinformation 0x60D
#define scal_object_arel 0.01
#define offset_obj_arellong -10
#define offset_obj_arellat -2.5
#define scal_obj_orientationangle 0.4
#define offset_obj_orientationangle -180
#define Object_collisiondetect 0x60E



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

struct Cluster_GenInf{
	int clust_id;
	int clust_distlong;
	int clust_distlat;
	int clust_vrelLong;
	int clust_vrelLat;
	int clust_dycprop;
	int clust_RCS;
};

struct Cluster_GenInf_ar{
	int clust_id;
	int clust_distlong;
	int clust_distlat;
};



struct Cluster_QuaInf{
	int clust_id;
	int clust_distlong_rms;
	int clust_distlat_rms;
	int clust_vrelLong_rms;
	int clust_vrelLat_rms;
	int clust_Pdh0;
	int clust_AmbigState;
	int clust_InvalidState;
};

struct Path_Buf{
	int Elements;		/* Number of Elements in the Path_Buf 	*/
	float x[BUF_LEN];	/* X-Kooordinate of a Path-Point	*/
	float y[BUF_LEN];	/* Y-Koordinate of a Path-Point		*/
};



struct Object_0_Status{
	int Obj_NofObjects;
	int Obj_MeasCounter;
	int Obj_InterfaceVersion;
	};

struct Object_Gen_Information {
	int Obj_ID;
	int Obj_DistLong;
	int Obj_DistLat;
	int Obj_VrelLong;
	int Obj_VrelLat;
	int Obj_DynProp;
	int Obj_RCS;
};

struct Object_GenInf_ar{
	int Obj_ID;
	int Obj_DistLong;
	int Obj_DistLat;
};

struct Object_Quality_Information {
	int Obj_ID;
	int Obj_DistLong_rms;
	int Obj_DistLat_rms;
	int Obj_VrelLong_rms;
	int Obj_VrelLat_rms;
	int Obj_ArelLong_rms;
	int Obj_ArelLat_rms;
	int Obj_Orientation_rms;
	int Obj_ProbOfExist;
	int Obj_MeasState;

};

struct Object_Extended_Information {
	int Obj_ID;
	int Obj_ArelLong;
	int Obj_ArelLat;
	int Obj_Class;
	int Obj_OrientationAngle;
	int Obj_Length;
	int Obj_Width;

};

struct Object_CollisionDetection_Warning {

	int Obj_ID;
	int Obj_CollDetRegionBitField;
	int Reserved1;
	int Reserved2;

};


extern void Read_Object (int socket_id, struct Object_0_Status *Object_0_Status);
extern void Object_Gen_Information( int socket_id, struct Object_Gen_Information *Object_Gen_Information,
	                                  struct Object_GenInf_ar *Geninf_array);
extern void Object_Quality_Information( int socket_id, struct Object_Quality_Information *Object_Quality_Information);
extern void Object_Extended_Information( int socket_id, struct Object_Extended_Information *Object_Extended_Information);
extern void Object_CollisionDetection_Warning (int socket_id, struct Object_CollisionDetection_Warning *Object_CollisionDetection_Warning);


extern int open_socket(int *socket_id);
extern void Read_Cluster(int socket_id, struct Cluster *Cluster_ptr);
extern void Read_ClusterGen(int socket_id, struct Cluster_GenInf *Cluster_ptr, struct Cluster_GenInf_ar *Geninf_array);
extern void Read_Radar_State(int socket_id, struct Radar_State *Radar_State_ptr);
extern void displayRadarState(struct Radar_State Radar_State);
extern void Read_ClusterQual(int socket_id, struct Cluster_QuaInf *Cluster_ptr);
extern void Init_Gnuplot(FILE *Gnu_fd);
extern void gnu_point(FILE *Gnu_fd, struct Cluster_GenInf_ar *Geninf_array, int numClusters);
extern void configRadar(int socket_id, int flag);
