#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

float lin_x = 0.0;
float ang_z = 0.0;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  lin_x = msg->axes[1];
  ang_z = msg->axes[4];
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "joyRe_node");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("joy", 1000, joyCallback);
  ros::Publisher turtle_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    geometry_msgs::Twist msg;
    msg.linear.x = lin_x;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;
    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = ang_z * 1.5;

    turtle_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
