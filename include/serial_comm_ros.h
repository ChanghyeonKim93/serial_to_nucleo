#ifndef _SERIAL_COMM_ROS_H_
#define _SERIAL_COMM_ROS_H_

#include <iostream>
#include <ros/ros.h>

#include <std_msgs/Int8MultiArray.h>
#include <std_msgs/UInt16MultiArray.h>

#include "serial_comm_linux.h"

#define BUF_SIZE 1024

class SerialCommROS{
public:
    SerialCommROS(ros::NodeHandle& nh);
    ~SerialCommROS();

private:
    void getParameters();

    void run();

    void callbackToSend(const std_msgs::UInt16MultiArray::ConstPtr& msg);
    
    bool receiveDataReady();
    int  getMessage(char* data);

    void sendMessage(char* data, int len);
    int fill16bitsTo8bits(const std_msgs::UInt16MultiArray::ConstPtr& msg, char* buf_send);

private:
    std::shared_ptr<SerialCommunicatorLinux> serial_comm_linux_;
    std::string portname_;
    int baudrate_;

    char buf_send_[BUF_SIZE];
    char buf_recv_[BUF_SIZE];

private:
    ros::NodeHandle nh_;

    int loop_frequency_;

    std::string topicname_msg_to_send_;
    ros::Subscriber sub_msg_to_send_;
    std_msgs::UInt16MultiArray msg_to_send_;


    std::string topicname_msg_recv_;
    ros::Publisher pub_msg_recv_;
    std_msgs::Int8MultiArray msg_recv_;

};
#endif