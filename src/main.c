/* Program to record the CAN-Messages and give the responce to 		*/
/* the data structure Cluster						*/
/*									*/


#include "../inc/radar.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLUSTER 1
#define OBJECT 0

static int socket_id;
static char dataType[16];
static int clusterOrObject = 1;

static void updateLabel(GtkLabel *sum, int num)
{
    gchar *display;
    display = g_strdup_printf("%d", num);         //convert num to str
    gtk_label_set_text (GTK_LABEL(sum), display); //set label to "display
    g_free(display);                             //free display
}
static void updateLabelText(GtkLabel *sum, char* txt)
{
		gchar *display;
		display = g_strdup_printf("%s", txt);         //convert num to str
		gtk_label_set_text (GTK_LABEL(sum), display); //set label to "display
    g_free(display);                              //free display
}



static void send_can_obj (GtkWidget *widget,
             gpointer   data)
{
  clusterOrObject = OBJECT;
	configRadar(socket_id, OBJECT);
	strcpy(dataType, "Object");
}

static void send_can_cluster(GtkWidget *widget,
             gpointer   data)
{
  clusterOrObject = CLUSTER;
	configRadar(socket_id, CLUSTER);
	strcpy(dataType, "Cluster");
}


int main(int argc,char **argv){

	int error;
	struct Cluster Cluster_Status;
	struct Cluster_GenInf Cluster_gen;
	struct Radar_State Radar_State;
	struct Cluster_QuaInf Cluster_qual;
  struct Cluster_GenInf_ar Geninf_array[25];
  struct Object_0_Status Object_Status;
  struct Object_Gen_Information Object_gen;
  struct Object_GenInf_ar GeninfObj_array[25];
	int numClusters, j;

	GtkWidget *window1;
	GtkWidget *LabelTop;
  GtkWidget *Labelc1,*Labelc2,*Labelc3,*Labelc4,*Labelc5,*Labelc6,*Labelc7,*Labelc8,*Labelc9,*Labelc10;
  GtkWidget *Labely1,*Labely2,*Labely3,*Labely4,*Labely5,*Labely6,*Labely7,*Labely8,*Labely9,*Labely10;
  GtkWidget *Labelx1,*Labelx2,*Labelx3,*Labelx4,*Labelx5,*Labelx6,*Labelx7,*Labelx8,*Labelx9,*Labelx10;

	GtkWidget *LabelDT,*Labeldata;
	GtkWidget *Labelnum, *Labeltxt;
	GtkWidget *button1,*button2;
	GtkWidget *LabelTop1;
	GtkWidget *grid;

  GtkWidget *LabelObj1Txt,*LabelObj2Txt,*LabelObj3Txt,*LabelObj4Txt,*LabelObj5Txt,*LabelObj6Txt,*LabelObj7Txt,*LabelObj8Txt,*LabelObj9Txt,*LabelObj10Txt;
  GtkWidget *LabelObjx1,*LabelObjx2,*LabelObjx3,*LabelObjx4,*LabelObjx5,*LabelObjx6,*LabelObjx7,*LabelObjx8,*LabelObjx9,*LabelObjx10;
  GtkWidget *LabelObjy1,*LabelObjy2,*LabelObjy3,*LabelObjy4,*LabelObjy5,*LabelObjy6,*LabelObjy7,*LabelObjy8,*LabelObjy9,*LabelObjy10;



	{
		gtk_init (&argc,&argv);

		button1 = gtk_button_new_with_label ("Send_Obj");
    button2 = gtk_button_new_with_label ("Send_Clus");
    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title (GTK_WINDOW (window1), "CAN RECEIVE Frame ");

    LabelTop =gtk_label_new(" Radar Gen Information ");
    LabelDT = gtk_label_new(" Showing Data type : ");
    Labelnum = gtk_label_new(" Total no of cluster detected: ");
    Labeldata = gtk_label_new("Clusters");
    Labeltxt  = gtk_label_new("0");
    Labelc1  = gtk_label_new("Cluster 1");
    Labelc2  = gtk_label_new("Cluster 2");
    Labelc3  = gtk_label_new("Cluster 3");
    Labelc4  = gtk_label_new("Cluster 4");
    Labelc5 = gtk_label_new("Cluster 5");
    Labelc6  = gtk_label_new("Cluster 6");
    Labelc7  = gtk_label_new("Cluster 7");
    Labelc8  = gtk_label_new("Cluster 8");
    Labelc9  = gtk_label_new("Cluster 9");
    Labelc10  = gtk_label_new("Cluster 10");

    Labelx1 = gtk_label_new("0");
    Labelx2 = gtk_label_new("0");
    Labelx3 = gtk_label_new("0");
    Labelx4 = gtk_label_new("0");
    Labelx5 = gtk_label_new("0");
    Labelx6 = gtk_label_new("0");
    Labelx7 = gtk_label_new("0");
    Labelx8 = gtk_label_new("0");
    Labelx9 = gtk_label_new("0");
    Labelx10 = gtk_label_new("0");

    Labely1 = gtk_label_new("0");
    Labely2 = gtk_label_new("0");
    Labely3 = gtk_label_new("0");
    Labely4 = gtk_label_new("0");
    Labely5 = gtk_label_new("0");
    Labely6 = gtk_label_new("0");
    Labely7 = gtk_label_new("0");
    Labely8 = gtk_label_new("0");
    Labely9 = gtk_label_new("0");
    Labely10 = gtk_label_new("0");

    LabelObj1Txt = gtk_label_new("Object 1");
    LabelObj2Txt = gtk_label_new("Object 2");
    LabelObj3Txt = gtk_label_new("Object 3");
    LabelObj4Txt = gtk_label_new("Object 4");
    LabelObj5Txt = gtk_label_new("Object 5");
    LabelObj6Txt = gtk_label_new("Object 6");
    LabelObj7Txt = gtk_label_new("Object 7");
    LabelObj8Txt = gtk_label_new("Object 8");
    LabelObj9Txt = gtk_label_new("Object 9");
    LabelObj10Txt = gtk_label_new("Object 10");

    LabelObjx1 = gtk_label_new("0");
    LabelObjx2 = gtk_label_new("0");
    LabelObjx3 = gtk_label_new("0");
    LabelObjx4 = gtk_label_new("0");
    LabelObjx5 = gtk_label_new("0");
    LabelObjx6 = gtk_label_new("0");
    LabelObjx7 = gtk_label_new("0");
    LabelObjx8 = gtk_label_new("0");
    LabelObjx9 = gtk_label_new("0");
    LabelObjx10 = gtk_label_new("0");
    LabelObjy1 = gtk_label_new("0");
    LabelObjy2 = gtk_label_new("0");
    LabelObjy3 = gtk_label_new("0");
    LabelObjy4 = gtk_label_new("0");
    LabelObjy5 = gtk_label_new("0");
    LabelObjy6 = gtk_label_new("0");
    LabelObjy7 = gtk_label_new("0");
    LabelObjy8 = gtk_label_new("0");
    LabelObjy9 = gtk_label_new("0");
    LabelObjy10 = gtk_label_new("0");


    grid = gtk_grid_new();

    LabelTop1 = gtk_label_new("CAN SEND FRAME");


    //sizing
    gtk_window_set_default_size (GTK_WINDOW (window1), 800, 800);
    gtk_container_set_border_width (GTK_CONTAINER(window1), 120);
    gtk_widget_set_size_request    (GTK_WIDGET(window1), 250, 200);
    gtk_grid_set_row_spacing       (GTK_GRID(grid), 4);
    gtk_grid_set_column_spacing    (GTK_GRID(grid), 5);
    gtk_container_add              (GTK_CONTAINER(window1), grid);

    //                                      x y h v
    gtk_grid_attach(GTK_GRID(grid),LabelTop,0,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelDT,0,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labeldata,1,1,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelnum,0,2,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labeltxt,1,2,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc1,0,3,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx1,1,3,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely1,2,3,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc2,0,4,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx2,1,4,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely2,2,4,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc3,0,5,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx3,1,5,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely3,2,5,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc4,0,6,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx4,1,6,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely4,2,6,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc5,0,7,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx5,1,7,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely5,2,7,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc6,0,8,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx6,1,8,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely6,2,8,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc7,0,9,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx7,1,9,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely7,2,9,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc8,0,10,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx8,1,10,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely8,2,10,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc9,0,11,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx9,1,11,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely9,2,11,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelc10,0,12,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labelx10,1,12,1,1);
    gtk_grid_attach(GTK_GRID(grid),Labely10,2,12,1,1);

    gtk_grid_attach(GTK_GRID(grid),LabelObj1Txt,3,3,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx1,4,3,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy1,5,3,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj2Txt,3,4,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx2,4,4,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy2,5,4,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj3Txt,3,5,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx3,4,5,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy3,5,5,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj1Txt,3,6,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx4,4,6,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy4,5,6,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj5Txt,3,7,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx5,4,7,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy5,5,7,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj6Txt,3,8,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx6,4,8,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy6,5,8,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj7Txt,3,9,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx7,4,9,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy7,5,9,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj8Txt,3,10,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx8,4,10,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy8,5,10,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj9Txt,3,11,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx9,4,11,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy9,5,11,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObj10Txt,3,12,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjx10,4,12,1,1);
    gtk_grid_attach(GTK_GRID(grid),LabelObjy10,5,12,1,1);


    gtk_grid_attach(GTK_GRID(grid),button1,0,13,1,1);
    gtk_grid_attach(GTK_GRID(grid),button2,1,13,1,1);


    gtk_widget_show_all (window1);

    g_signal_connect(button1,"clicked",G_CALLBACK(send_can_obj),NULL);
    g_signal_connect(button2,"clicked",G_CALLBACK(send_can_cluster),NULL);

    g_signal_connect(G_OBJECT(window1),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	}

	error = open_socket(&socket_id);
  /* Program for the GNU PLot*/
	FILE *Gnu_fd;
	struct 	 lab;
	FILE *fp;

	Gnu_fd = popen ("gnuplot -persistent", "w");
	if(Gnu_fd == 0)
	{
		printf("Error during Open Pipe for gnuplot! \n");
		return -1;
	}

	Init_Gnuplot(Gnu_fd);

	if(error == -1)
	{
		printf("Failed Connection \n");
		return -1;
	}

	if(error == 0)
	{
		fp = fopen("file.txt", "w");
		fprintf(fp, "ClustId \tLongVal \tLatVal\n");
		do {
			 while (gtk_events_pending())
         gtk_main_iteration();


  			printf("***********************************************************************************\n");

  			/*Radar State Information*/
  			printf("\tRadar State Output\n");
  			Read_Radar_State(socket_id, &Radar_State);
  			displayRadarState(Radar_State);


  			Read_Cluster(socket_id, &Cluster_Status);
        Display_Object_0(socket_id, &Object_Status);
        if(clusterOrObject == CLUSTER)
        {
  			  numClusters = Cluster_Status.near_target + Cluster_Status.far_target;
        }
        else if(clusterOrObject == OBJECT)
        {
          numClusters = Object_Status.Obj_NofObjects;
        }

  			if(numClusters > 10)
   			numClusters = 10;

        if(clusterOrObject == CLUSTER)
        {
          //memset(Cluster_gen, 0, sizeof(struct Cluster_GenInf ));
    			for(j= 0; j< numClusters; j++)
    			{
    			  Read_ClusterGen(socket_id, &Cluster_gen, &Geninf_array[j]);
    			}

    			updateLabelText(GTK_LABEL(Labeldata), dataType);
    			updateLabel(GTK_LABEL(Labeltxt),Cluster_Status.near_target + Cluster_Status.far_target);
    			updateLabel(GTK_LABEL(Labelx1),Geninf_array[0].clust_distlong);
    			updateLabel(GTK_LABEL(Labely1),Geninf_array[0].clust_distlat);
    			updateLabel(GTK_LABEL(Labelx2),Geninf_array[1].clust_distlong);
    			updateLabel(GTK_LABEL(Labely2),Geninf_array[1].clust_distlat);
    			updateLabel(GTK_LABEL(Labelx3),Geninf_array[2].clust_distlong);
    			updateLabel(GTK_LABEL(Labely3),Geninf_array[2].clust_distlat);
    			updateLabel(GTK_LABEL(Labelx4),Geninf_array[3].clust_distlong);
    			updateLabel(GTK_LABEL(Labely4),Geninf_array[3].clust_distlat);
    	    updateLabel(GTK_LABEL(Labelx5),Geninf_array[4].clust_distlong);
    			updateLabel(GTK_LABEL(Labely5),Geninf_array[4].clust_distlat);
    			updateLabel(GTK_LABEL(Labelx6),Geninf_array[5].clust_distlong);
    			updateLabel(GTK_LABEL(Labely6),Geninf_array[5].clust_distlat);
    			updateLabel(GTK_LABEL(Labelx7),Geninf_array[6].clust_distlong);
    			updateLabel(GTK_LABEL(Labely7),Geninf_array[6].clust_distlat);
    			updateLabel(GTK_LABEL(Labelx8),Geninf_array[7].clust_distlong);
    			updateLabel(GTK_LABEL(Labely8),Geninf_array[7].clust_distlat);
          updateLabel(GTK_LABEL(Labelx9),Geninf_array[8].clust_distlong);
    			updateLabel(GTK_LABEL(Labely9),Geninf_array[8].clust_distlat);
    			updateLabel(GTK_LABEL(Labelx10),Geninf_array[9].clust_distlong);
    			updateLabel(GTK_LABEL(Labely10),Geninf_array[9].clust_distlat);
        }
        else if(clusterOrObject == OBJECT)
        {
          //memset(Object_gen, 0, sizeof(Object_Gen_Information));
          for(j= 0; j< numClusters; j++)
          {
            Object_Gen_Information(socket_id, &Object_gen, &GeninfObj_array[j]);
          }

          updateLabelText(GTK_LABEL(Labeldata), dataType);
          updateLabel(GTK_LABEL(Labeltxt),Object_Status.Obj_NofObjects);
          updateLabel(GTK_LABEL(Labelx1),GeninfObj_array[0].Obj_DistLong);
          updateLabel(GTK_LABEL(Labely1),GeninfObj_array[0].Obj_DistLat);
          updateLabel(GTK_LABEL(Labelx2),GeninfObj_array[1].Obj_DistLong);
          updateLabel(GTK_LABEL(Labely2),GeninfObj_array[1].Obj_DistLat);
          updateLabel(GTK_LABEL(Labelx3),GeninfObj_array[2].Obj_DistLong);
          updateLabel(GTK_LABEL(Labely3),GeninfObj_array[2].Obj_DistLat);
          updateLabel(GTK_LABEL(Labelx4),GeninfObj_array[3].Obj_DistLong);
          updateLabel(GTK_LABEL(Labely4),GeninfObj_array[3].Obj_DistLat);
          updateLabel(GTK_LABEL(LabelObjx5),GeninfObj_array[4].Obj_DistLong);
          updateLabel(GTK_LABEL(LabelObjy5),GeninfObj_array[4].Obj_DistLat);
          updateLabel(GTK_LABEL(LabelObjx6),GeninfObj_array[5].Obj_DistLong);
          updateLabel(GTK_LABEL(LabelObjy6),GeninfObj_array[5].Obj_DistLat);
          updateLabel(GTK_LABEL(LabelObjx7),GeninfObj_array[6].Obj_DistLong);
          updateLabel(GTK_LABEL(LabelObjy7),GeninfObj_array[6].Obj_DistLat);
          updateLabel(GTK_LABEL(LabelObjx8),GeninfObj_array[7].Obj_DistLong);
          updateLabel(GTK_LABEL(LabelObjy8),GeninfObj_array[7].Obj_DistLat);
          updateLabel(GTK_LABEL(LabelObjx9),GeninfObj_array[8].Obj_DistLong);
          updateLabel(GTK_LABEL(LabelObjy9),GeninfObj_array[8].Obj_DistLat);
          updateLabel(GTK_LABEL(LabelObjx10),GeninfObj_array[9].Obj_DistLong);
          updateLabel(GTK_LABEL(LabelObjy10),GeninfObj_array[9].Obj_DistLat);
        }
    			gnu_point(Gnu_fd, Geninf_array, numClusters);
    			printf("***********************************************************************************\n");

  		} while(1);
  		fclose(fp);
	}

	close(socket_id);
	return(0);
}
