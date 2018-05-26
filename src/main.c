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
        struct Cluster_GenInf_ar Geninf_array[25];
	int numClusters, j;

	error = open_socket(&socket_id);
/* Program for the GNU PLot*/
	FILE *Gnu_fd;
	struct 	 lab;
	FILE *fp;

	Gnu_fd = popen ("gnuplot -persistent", "w");
	if(Gnu_fd == 0){
		printf("Error during Open Pipe for gnuplot! \n");
		return -1;
	}

	Init_Gnuplot(Gnu_fd);

	if(error == -1)
	{
		printf("Failed Connection \n");
		return -1;
	}
	if(error == 0){
		fp = fopen("file.txt", "w");
		fprintf(fp, "ClustId \tLongVal \tLatVal\n");
		do {

			printf("***********************************************************************************\n");

			/*Radar State Information*/

			printf("\tRadar State Output\n");
			Read_Radar_State(socket_id, &Radar_State);
			displayRadarState(Radar_State);

			printf("\n\tStatus of Cluster List\n");
			Read_Cluster(socket_id, &Cluster_Status);
			numClusters = Cluster_Status.near_target + Cluster_Status.far_target;

			if(numClusters > 10)
 			numClusters = 10;

			printf("Number of near Target = %d, Number of far Targets %d\n", Cluster_Status.near_target, Cluster_Status.far_target);
			printf("Number Measurement Cycles = %d Interface Id %d\n", Cluster_Status.cycle_counter, Cluster_Status.interface);

			/* Cluster Genral Information*/
			printf("\n\tCluster General Information\n");

			for(j= 0; j< numClusters; j++)
			{

			  Read_ClusterGen(socket_id, &Cluster_gen, &Geninf_array[j]);
				if(Geninf_array[j].clust_id < 10)
				{
			    fprintf(fp, "%d \t\t %d \t\t %d\n",Geninf_array[j].clust_id,  Geninf_array[j].clust_distlong, Geninf_array[j].clust_distlat);
			    printf("ClusterId =  %d, dist_Longitude = %d , dist_latitude = %d \n",Cluster_gen.clust_id,Cluster_gen.clust_distlong, Cluster_gen.clust_distlat);
			    printf("Cluster relative long=  %d , Cluster relative lattitude = %d\n", Cluster_gen.clust_vrelLong, Cluster_gen.clust_vrelLat);
			    printf("Cluster dynamic = %d , CLuster RCS = %d\n", Cluster_gen.clust_dycprop, Cluster_gen.clust_RCS);
        }
			}

			/* CLUSTER QUALITY INFORMATION*/
			printf("\n\tCluster Quality Information\n");
			Read_ClusterQual(socket_id, &Cluster_qual);
			printf("SDiv of Long_Distance = %d, SDiv of Lat_Distance %d\n", Cluster_qual.clust_distlong_rms, Cluster_qual.clust_distlat_rms);
			printf("SDiv of Long_RVelocity = %d,SDiv of Lat_Distance %d\n", Cluster_qual.clust_vrelLong_rms, Cluster_qual.clust_vrelLat_rms);
			printf("Prob of False alarm = %d,State of Doppler amiguity %d\n", Cluster_qual.clust_Pdh0, Cluster_qual.clust_AmbigState);
			printf("Cluster Vladity = %d \n", Cluster_qual.clust_InvalidState);

			gnu_point(Gnu_fd, Geninf_array, numClusters);
			printf("***********************************************************************************\n");

		} while(1);
		fclose(fp);
	}

	close(socket_id);
	return(0);
}
