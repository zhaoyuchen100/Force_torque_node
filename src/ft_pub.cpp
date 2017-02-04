#include <include/ft_node/ft_stream_node.h>
#include <ros/ros.h>
#include <geometry_msgs/WrenchStamped.h>

int main(int argc, char** argv)
{
    ros::init(argc,argv,"ft_pub");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::WrenchStamped>("ft_message",1);
    ros::Rate loop_rate(2000);
    myFT myFT_obj;
    int gain = 1;
    while(ros::ok())
    {   myFT_obj.publish();
        geometry_msgs::WrenchStamped msg;
        msg.header.stamp = ros::Time::now();
        msg.header.frame_id = "FT_frame";
        msg.wrench.force.x = myFT_obj.resp.FTData[0]/gain;
        msg.wrench.force.y = myFT_obj.resp.FTData[1]/gain;
        msg.wrench.force.z = myFT_obj.resp.FTData[2]/gain;
        msg.wrench.torque.x = myFT_obj.resp.FTData[3]/gain;
        msg.wrench.torque.y = myFT_obj.resp.FTData[4]/gain;
        msg.wrench.torque.z = myFT_obj.resp.FTData[5]/gain;

        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
