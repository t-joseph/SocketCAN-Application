/* Program to record the CAN-Messages and give the responce to 		*/
/* the data structure Cluster						*/
/*									*/
/* The program use the CAN-ID 601 an process the load of 5 Bytes	*/
/*									*/
/*									*/ 
/* The CAN Driver can0 have to be initialised.				*/

#include "../inc/radar.h"

int main(){

	int socket_id, error;
	struct Cluster Cluster_Status;
	struct Cluster_GenInf Cluster_gen;
	struct Radar_State Radar_State;
	struct Cluster_QuaInf Cluster_qual;

	error = open_socket(&socket_id);

	if (error == -1)
	{
		printf("Failed Connection \n");
		return -1;
	}
	if (error == 0){

		do {

			printf("***********************************************************************************\n");
			
			/*Radar State Information*/

			printf("\tRadar State Output\n");
			Read_Radar_State(socket_id, &Radar_State);
			displayRadarState(Radar_State);

			printf("\n\tStatus of Cluster List\n");
			Read_Cluster(socket_id, &Cluster_Status);
			printf("Number of near Target = %d, Number of far Targets %d\n", Cluster_Status.near_target, Cluster_Status.far_target);	 
			printf("Number Measurement Cycles = %d Interface Id %d\n", Cluster_Status.cycle_counter, Cluster_Status.interface);
			
			/* Cluster Genral Information*/
			printf("\n\tCluster General Information\n");
			Read_ClusterGen(socket_id, &Cluster_gen);
			printf("Cluster Id =  %d, dist_Longitude = %d , dist_latitude = %d \n",Cluster_gen.clust_id,Cluster_gen.clust_distlong, Cluster_gen.clust_distlat);
			printf("Cluster relative long=  %d , Cluster relative lattitude = %d\n", Cluster_gen.clust_vrelLong, Cluster_gen.clust_vrelLat);
			printf("Cluster dynamic = %d , CLuster RCS = %d\n", Cluster_gen.clust_dycprop, Cluster_gen.clust_RCS);
		
			/* CLUSTER QUALITY INFORMATION*/
			printf("\n\tCluster Quality Information\n");
			Read_ClusterQual(socket_id, &Cluster_qual);
			printf("SDiv of Long_Distance = %d, SDiv of Lat_Distance %d\n", Cluster_qual.clust_distlong_rms, Cluster_qual.clust_distlat_rms);
			printf("SDiv of Long_RVelocity = %d,SDiv of Lat_Distance %d\n", Cluster_qual.clust_vrelLong_rms, Cluster_qual.clust_vrelLat_rms);
			printf("Prob of False alarm = %d,State of Doppler amiguity %d\n", Cluster_qual.clust_Pdh0, Cluster_qual.clust_AmbigState);
			printf("Cluster Vladity = %d \n", Cluster_qual.clust_InvalidState);	
			
			printf("***********************************************************************************\n");
			
		} while(1);
	}

	close(socket_id);
	return(0);
}


