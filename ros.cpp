#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include <iostream>
#include <cstdlib> 
#include <mavros_msgs/ActuatorControl.h>
#include <string.h>


int w=0;
int y=0;
double ww=0.0;
double yy=0.0;
int count=0;
double division=500.0;
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{

  const char * c = msg->data.c_str();
  ROS_INFO("%s",c);
  char  t[30];
  strncpy(t,c,30);
  printf("%s\n" , t);

  char * temp =strtok(t,",");
 
  while(temp != NULL)
  {
    if(count == 0)
    {
	y=atoi(temp);
	count++;
    }
    else if(count ==1)
    {
	w=atoi(temp);
        count++;
	if( count ==2)
		count =0;
    }
    
    temp= strtok(NULL , " ");
  }

   printf("%d.%d \n" , w,y);
 } 

}
int main(int argc, char **argv)
{
   ros::init(argc, argv, "pub_setpoints");
   ros::NodeHandle n;
 
   ros::Publisher pub = n.advertise<mavros_msgs::ActuatorControl>("/mavros/actuator_controls",100);
   ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
   ros::Rate loop_rate(100);
   ros::spinOnce();

   mavros_msgs::ActuatorControl msg;

   int count = 1;
	
		//PositionReciever qp;:
		//Body some_object;
		//qp.connect_to_server();
   
	
   while(ros::ok()){
v      ww= ((double)(w-1500))/division;
       yy=((double)(y-1500))/division;

	   //some_object = qp.getStatus();
		// some_object.print();
		//printf("%f\n",some_object.position_x);
       msg.header.stamp = ros::Time::now();
       msg.header.seq=count;
       msg.header.frame_id = 1;
       msg.group_mix = 0;
       msg.controls[0] = yy;
       msg.controls[1] = ww;
       msg.controls[2] = 0.0;
       msg.controls[3] = 0.0;
       msg.controls[4] = 0.0;
       msg.controls[5] = 0.0;
       msg.controls[6] = 0.0;
       msg.controls[7] = 0.0;

       pub.publish(msg);
       ros::spinOnce();
       count++;
       loop_rate.sleep();
   }
   
      
   return 0;
}