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

	error = open_socket(&socket_id);

	if (error == -1)
	{
		printf("Failed Connection \n");
		return -1;
	}
	if (error == 0){

		do {
			Read_Cluster(socket_id, &Cluster_Status);
		printf("Number of near Target = %d, Number of far Targets %d\n", Cluster_Status.near_target, Cluster_Status.far_target);
 
		printf("Number Measurement Cycles = %d\n", Cluster_Status.cycle_counter);
		 


		} while(1);
	}

	close(socket_id);
	return(0);
}


