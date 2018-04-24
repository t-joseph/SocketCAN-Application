

#include "../inc/radar.h"

int open_socket(int *socket_id){

/* Open an existing CAN-Device File and generate a Socket-ID.		*/
/* Function give a -1 back if the device is not existing		*/
/* If the Socket-ID was succsessfully opened the function give a 0 back	*/
 

	
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame_read;
	char *ifname = "can0";

	*socket_id = socket(PF_CAN, SOCK_RAW, CAN_RAW);
//	printf("After Socket Socket = %d \n", *socket_id);
	strcpy(ifr.ifr_name, ifname);
	ioctl(*socket_id, SIOCGIFINDEX, &ifr);
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	bind(*socket_id, (struct sockaddr *)&addr, sizeof(addr));

	return 0;

}

void Read_Cluster(int socket_id, struct Cluster *Cluster_ptr){
/* Read in a Cluster from the CAN id 600. Read in the load of 5 bytes 	*/
/* decode these loads to the input definition of Cluster.		*/
/* Parameter socket_id: Number of the socket file descriptor 		*/
/* Parameter *Cluster_ptr: Reference pointing to the cluster structure  */

	struct can_frame frame_read;
	int nbytes;
	int tempFrame = 0;

	nbytes = read(socket_id, &frame_read, sizeof(struct can_frame));  

	if	(frame_read.can_id == Cluster_stat){
		Cluster_ptr->near_target = (int)frame_read.data[0];
		Cluster_ptr->far_target = (int)frame_read.data[1];

		tempFrame = frame_read.data[2];
		tempFrame *= 256;
		Cluster_ptr->cycle_counter = (int)tempFrame + (int)frame_read.data[3];

		Cluster_ptr->interface = ((int)frame_read.data[4] >> 4) & 0x0f;
	}
		  
}


  void Read_ClusterGen(int socket_id, struct Cluster_GenInf *Cluster_ptr){
/* Read in Cluster Genral Information form the CAN id 701 */
  struct can_frame frame_read;
  int tempFrame1 = 0;
  int tempFrame2 = 0;
  int nbytes;	
  memset(Cluster_ptr, 0, sizeof(struct Cluster_GenInf));
  nbytes = read(socket_id, &frame_read, sizeof(struct can_frame));

  if (frame_read.can_id == Cluster_Gen){
    Cluster_ptr->clust_id = (int)frame_read.data[0];
	
    tempFrame1 = frame_read.data[1];
    tempFrame1 = tempFrame1 << 5;
    tempFrame2 = frame_read.data[2];
    tempFrame2 = tempFrame2 >> 3;
    Cluster_ptr->clust_distlong = (scal_dist*(tempFrame1 + tempFrame2)) + offst_dtlong;     	
    tempFrame1 = 0;
    tempFrame2 = 0;		

     	
    tempFrame1 = frame_read.data[2] & 0x03;
    tempFrame1 = tempFrame1 << 8;     		
    Cluster_ptr->clust_distlat = (scal_dist*(tempFrame1 + (int)frame_read.data[3]))+offst_dtlat;
    tempFrame1 = 0;		

    tempFrame1 = frame_read.data[4];
    tempFrame1 = tempFrame1 << 2;
    tempFrame2 = frame_read.data[5];
    tempFrame2 = tempFrame1 >> 6;     		
    Cluster_ptr->clust_vrelLong = (scal_vrel *(tempFrame1 + (tempFrame2 & 0x03)))+offst_vrellong;
    tempFrame1 = 0;
    tempFrame2 = 0;    

    tempFrame1 = frame_read.data[5] & 0x3f;
    tempFrame1 = tempFrame1 << 3;
    tempFrame2 = frame_read.data[6];
    tempFrame2 = tempFrame1 >> 5;     		     		
    Cluster_ptr->clust_vrelLat = (scal_vrel*((tempFrame1) + tempFrame2))+offst_vrellat;
  
    Cluster_ptr->clust_dycprop = ((int)frame_read.data[6] & 0x07);
    Cluster_ptr->clust_RCS =(RCS_res * (int) (frame_read.data[7]))+ offst_rcs;

  }

}


void Read_ClusterQual(int socket_id, struct Cluster_QuaInf *Cluster_ptr){
/* Read in Cluster Quality Information from the CAN ID 702*/
	struct can_frame frame_read;
	int nbytes;
	int tempFrame1 = 0;
  	int tempFrame2 = 0;
	memset(Cluster_ptr, 0, sizeof(struct Cluster_QuaInf));
	
	nbytes = read(socket_id, &frame_read, sizeof(struct can_frame));

	if(frame_read.can_id == Cluster_QuaInfId){
	 	Cluster_ptr -> clust_id = (int)frame_read.data[0];
		

		tempFrame1 = frame_read.data[1];
		tempFrame1 = tempFrame1 >> 3;
		Cluster_ptr -> clust_distlong_rms = tempFrame1;
		tempFrame1 = 0;		

		tempFrame1 = frame_read.data[2];
		tempFrame1 = tempFrame1 >>  6;	
		Cluster_ptr -> clust_distlat_rms = (((int)frame_read.data[1] << 2) & 0x1c) + (tempFrame1 & 0x03);
		tempFrame1 = 0;


		tempFrame1 = frame_read.data[2];
		tempFrame1 = tempFrame1 >>  1;	
		Cluster_ptr -> clust_vrelLong_rms  = tempFrame1 & 0x1f;
		tempFrame1 = 0;

		tempFrame1 = frame_read.data[3];
		tempFrame1 = tempFrame1 >>  4;	
		Cluster_ptr ->clust_vrelLat_rms= (((int)frame_read.data[2] << 4) & 0x10) + tempFrame1;
		tempFrame1 = 0;


		Cluster_ptr -> clust_Pdh0 = (int)frame_read.data[3] & 0x07;


		tempFrame1 = frame_read.data[4];
		tempFrame1 = tempFrame1 >>  3;
		Cluster_ptr ->clust_InvalidState= tempFrame1;
		tempFrame1 = 0;

		Cluster_ptr ->clust_AmbigState  = (int)frame_read.data[4] & 0x1f;

	}
}


void Read_Radar_State(int socket_id, struct Radar_State *Radar_State_ptr){
/* Read in a Radar State from the CAN id 201. Read in the load of 8 bytes 	*/
/* decode these loads to the input definition of Radar State.			*/
/* Parameter socket_id: Number of the socket file descriptor 			*/
/* Parameter *Radar_State_ptr: Reference pointing to the Radar_State structure  	*/

	struct can_frame frame_read;
	int nbytes;
	int tempFrame1 = 0;
  	int tempFrame2 = 0;

	nbytes = read(socket_id, &frame_read, sizeof(struct can_frame));  

	if	(frame_read.can_id == RadarState){
		tempFrame1 = frame_read.data[0];
		tempFrame1 = tempFrame1 >> 6;
		Radar_State_ptr->NVMReadStatus = tempFrame1 & 0x01;
		tempFrame1 = 0;		

		tempFrame1 = frame_read.data[0];
		tempFrame1 = tempFrame1 >> 7;
		Radar_State_ptr->NVMwriteStatus = tempFrame1 & 0x01;
		tempFrame1 = 0;
		
		tempFrame1 = frame_read.data[1];
		tempFrame1 = tempFrame1 << 2;
		tempFrame2 = frame_read.data[2];
		tempFrame2 = tempFrame2 >> 6;
		Radar_State_ptr->MaxDistanceCfg = 2*(tempFrame1  + tempFrame2);
		tempFrame1 = 0;
		tempFrame2 = 0;

		tempFrame1 = frame_read.data[2];
		tempFrame1 = tempFrame1 >> 5;
		Radar_State_ptr->Persistent_Error = tempFrame1 & 0x01;
		tempFrame1 = 0;	

		tempFrame1 = frame_read.data[2];
		tempFrame1 = tempFrame1 >> 4;
		Radar_State_ptr->Interference = tempFrame1 & 0x01;
		tempFrame1 = 0;	

		
		tempFrame1 = frame_read.data[2];
		tempFrame1 = tempFrame1 >> 3;
		Radar_State_ptr->Temperature_Error = tempFrame1 & 0x01;
		tempFrame1 = 0;	

		
		tempFrame1 = frame_read.data[2];
		tempFrame1 = tempFrame1 >> 2;
		Radar_State_ptr->Temporary_Error  = tempFrame1 & 0x01;
		tempFrame1 = 0;	

		tempFrame1 = frame_read.data[2];
		tempFrame1 = tempFrame1 >> 1;
		Radar_State_ptr->Voltage_Error  = tempFrame1 & 0x01;
		tempFrame1 = 0;	
		
		tempFrame1 = frame_read.data[4];
		tempFrame1 = tempFrame1 >> 7;
		Radar_State_ptr->RadarPowerCfg = ((int)frame_read.data[3] << 1)  + tempFrame1;
		tempFrame1 = 0;

		tempFrame1 = frame_read.data[4];
		tempFrame1 = tempFrame1 >> 4;
		Radar_State_ptr->SortIndex =  tempFrame1 & 0x07;
		tempFrame1 = 0;

		Radar_State_ptr->SensorID = ((int)frame_read.data[4])  & 0x07;

		tempFrame1 = frame_read.data[5];
		tempFrame1 = tempFrame1 >> 1;
		Radar_State_ptr->CtrlRelayCfg = tempFrame1 & 0x01;
		tempFrame1 = 0;

		tempFrame1 = frame_read.data[5];
		tempFrame1 = tempFrame1 >> 2;
		Radar_State_ptr->OutputTypeCfg = tempFrame1 & 0x03;
		tempFrame1 = 0;

		tempFrame1 = frame_read.data[5];
		tempFrame1 = tempFrame1 >> 4;
		Radar_State_ptr->SendQualityCfg = tempFrame1 & 0x01;
		tempFrame1 = 0;

		tempFrame1 = frame_read.data[5];
		tempFrame1 = tempFrame1 >> 5;
		Radar_State_ptr->SendExtInfoCfg = tempFrame1 & 0x01;
		tempFrame1 = 0;

		tempFrame1 = frame_read.data[5];
		tempFrame1 = tempFrame1 >> 6;
		Radar_State_ptr->MotionRxState  = tempFrame1 & 0x03;
		tempFrame1 = 0;

		Radar_State_ptr->RCS_Threshold = ((int)frame_read.data[7] >> 2) & 0x07;
	}
		  
}


void displayRadarState(struct Radar_State Radar_State)
{

/* To Radar State from the CAN id 201. 						*/
/* Parameter Radar_State: Radar_State structure instance		 	*/

			printf("Non Volatile Read Status is %s\n",(Radar_State.NVMReadStatus == 1) ? "successful":"failed");

			printf("Non Volatile Write Status is %s\n",(Radar_State.NVMwriteStatus == 1) ? "successful":"failed");

			printf("Maximum distance configured is %d m\n", Radar_State.MaxDistanceCfg);

			printf("%s\n", (Radar_State.Persistent_Error == 1) ? "Persistent error is active":"No persistent error");

			printf("%s\n", (Radar_State.Interference == 1) ? "Interference detected":"No interference");

			printf("%s\n", (Radar_State.Temperature_Error == 1) ? "Temperature error is active":"No temperature error");

			printf("%s\n", (Radar_State.Temporary_Error == 1) ? "Temporary error is active":"No temporary error");

			printf("%s\n", (Radar_State.Voltage_Error == 1) ? "Voltage error is active":"No voltage error");

			printf("Sensor ID = %d\n", Radar_State.SensorID);
			
			/*Current configuration of sorting index for object list*/
			if(0 == Radar_State.SortIndex)
			{
				printf("No sorting\n");
			}
			else if(1 == Radar_State.SortIndex)
			{
				printf("Sorted by range\n");
			}
			else if(2 == Radar_State.SortIndex)
			{
				printf("Sorted by RCS\n");
			}

			/*Current configuration of transmitted radar power parameter*/
			if(0 == Radar_State.RadarPowerCfg)
			{
				printf("Standard power\n");
			}
			else if(1 == Radar_State.RadarPowerCfg)
			{
				printf("-3dB Tx gain\n");
			}
			else if(2 == Radar_State.RadarPowerCfg)
			{
				printf("-6dB Tx gain\n");
			}
			else if(3 == Radar_State.RadarPowerCfg)
			{
				printf("-9dB Tx gain\n");
			}
			
			/*Active if relay control message is sent*/
			printf("Control relay configuration is %s\n", (Radar_State.CtrlRelayCfg == 1) ? "active":"inactive");	

			/*Currently selected output type as either clusters or objects*/
			if(0 == Radar_State.OutputTypeCfg)
			{
				printf("Send None\n");
			}
			else if(1 == Radar_State.OutputTypeCfg)
			{
				printf("Send Objects\n");
			}
			else if(2 == Radar_State.OutputTypeCfg)
			{
				printf("Send Clusters\n");
			}
			
			/*Active if quality information is sent for clusters or objects*/
			printf("Sending quality information is %s\n", (Radar_State.SendQualityCfg == 1) ? "active":"inactive");

			/*Active if extended information is sent for objects*/
			printf("Sending extended information is %s\n", (Radar_State.SendExtInfoCfg == 1) ? "active":"inactive");	
			
			/*Shows the state of the speed and yaw rate input signals*/
			if(0 == Radar_State.MotionRxState)
			{
				printf("input ok\n");
			}
			else if(1 == Radar_State.MotionRxState)
			{
				printf("Speed missing\n");
			}
			else if(2 == Radar_State.MotionRxState)
			{
				printf("Yaw rate missing\n");
			}
			else if(3 == Radar_State.MotionRxState)
			{
				printf("Speed and yaw rate missing\n");
			}

			/*If active the high sensitivity mode of sensor is active*/
			printf("RCS threshold has %s\n", (Radar_State.RCS_Threshold == 1) ? "high sensitivity":"standard sensitivity");	
	
}

