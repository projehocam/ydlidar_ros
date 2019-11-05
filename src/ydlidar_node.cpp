/*
 *  YDLIDAR SYSTEM
 *  YDLIDAR ROS Node Client 
 *
 *  Copyright 2015 - 2018 EAI TEAM
 *  http://www.ydlidar.com
 * 
 */

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "CYdLidar.h"
#include <vector>
#include <iostream>
#include <string>
#include <signal.h>

using namespace ydlidar;

#define ROSVerision "1.4.2"

void LidarCtrlFreqCallback(bool isLowerFreq) {
  if (isLowerFreq) { //低频模式
    //设置雷达频率小于6.8Hz

  } else {//高频模式
    //设置雷达频率大于11.7Hz

  }
}

std::vector<float> split(const std::string &s, char delim) {
    std::vector<float> elems;
    std::stringstream ss(s);
    std::string number;
    while(std::getline(ss, number, delim)) {
        elems.push_back(atof(number.c_str()));
    }
    return elems;
}


int main(int argc, char * argv[]) {
    ros::init(argc, argv, "ydlidar_node"); 
    printf("__   ______  _     ___ ____    _    ____     _____ _____ __  __ ___  \n");
    printf("\\ \\ / /  _ \\| |   |_ _|  _ \\  / \\  |  _ \\   |_   _| ____|  \\/  |_ _| \n");
    printf(" \\ V /| | | | |    | || | | |/ _ \\ | |_) |____| | |  _| | |\\/| || |  \n");
    printf("  | | | |_| | |___ | || |_| / ___ \\|  _ <_____| | | |___| |  | || |  \n");
    printf("  |_| |____/|_____|___|____/_/   \\_\\_| \\_\\    |_| |_____|_|  |_|___| \n");
    printf("\n");
    fflush(stdout);
  
    std::string port;
    int baudrate=214285;
    bool intensities = true;
    std::string frame_id;
    bool reversion, resolution_fixed;
    bool auto_reconnect;
    double angle_max,angle_min;
    std::string list;
    std::vector<float> ignore_array;  
    double max_range, min_range;
    bool sun_noise, glass_noise;

    ros::NodeHandle nh;
    ros::Publisher scan_pub = nh.advertise<sensor_msgs::LaserScan>("scan", 1000);
    ros::NodeHandle nh_private("~");
    nh_private.param<std::string>("port", port, "/dev/ydlidar"); 
    nh_private.param<int>("baudrate", baudrate, 214285);
    nh_private.param<std::string>("frame_id", frame_id, "laser_frame");
    nh_private.param<bool>("resolution_fixed", resolution_fixed, "true");
    nh_private.param<bool>("auto_reconnect", auto_reconnect, "true");
    nh_private.param<bool>("sun_noise", sun_noise, "true");
    nh_private.param<bool>("glass_noise", glass_noise, "true");
    nh_private.param<bool>("reversion", reversion, "false");
    nh_private.param<double>("angle_max", angle_max , 180);
    nh_private.param<double>("angle_min", angle_min , -180);
    nh_private.param<double>("range_max", max_range , 16.0);
    nh_private.param<double>("range_min", min_range , 0.08);
    nh_private.param<std::string>("ignore_array",list,"");

    ignore_array = split(list ,',');
    if(ignore_array.size()%2){
        ROS_ERROR_STREAM("ignore array is odd need be even");
    }

    for(uint16_t i =0 ; i < ignore_array.size();i++){
        if(ignore_array[i] < -180 && ignore_array[i] > 180){
            ROS_ERROR_STREAM("ignore array should be between -180 and 180");
        }
    }

    CYdLidar laser;
    if(angle_max < angle_min){
        double temp = angle_max;
        angle_max = angle_min;
        angle_min = temp;
    }

    ROS_INFO("[YDLIDAR INFO] Now YDLIDAR ROS SDK VERSION:%s .......", ROSVerision);
    laser.setSerialPort(port);
    laser.setSerialBaudrate(baudrate);
    laser.setIntensities(intensities);
    laser.setMaxRange(max_range);
    laser.setMinRange(min_range);
    laser.setMaxAngle(angle_max);
    laser.setMinAngle(angle_min);
    laser.setFixedResolution(resolution_fixed);
    laser.setAutoReconnect(auto_reconnect);
    laser.setSunNoise(sun_noise);
    laser.setGlassNoise(glass_noise);
    laser.setIgnoreArray(ignore_array);
    bool ret = laser.initialize();
    if (!ret) {
        ROS_ERROR("Error initializing YDLIDAR Comms and Status!!!");
    }
    ros::Rate rate(20);
    //开启修正需注册高低频回调函数, 外部调用设定雷达高低频率
    laser.RegisterCtrlFreqCallback(std::bind(LidarCtrlFreqCallback,
                                 std::placeholders::_1));

    //如果要开启进入修正模式并修正, 调用startCorrectionMod函数
    //laser.startCorrectionMod();
    //修正中可以通过getCheckStateError函数获取状态信息
    //开启修正模式后, 判断是否修正完成, 调用IsCheckingFinished函数, 返回值是true, 修正完成, 否则,正在修正
    //laser.IsCheckingFinished();
    //修正完成后, 判断修正成功还是失败调用getResult函数, 返回值是true, 修正成功, 否则修正失败
   //laser.getResult();

    while (ret&&ros::ok()) {
        bool hardError;
        LaserScan scan;//原始激光数据
        if(laser.doProcessSimple(scan, hardError )){
            sensor_msgs::LaserScan scan_msg;
            ros::Time start_scan_time;
            start_scan_time.sec = scan.system_time_stamp/1000000000ul;
            start_scan_time.nsec = scan.system_time_stamp%1000000000ul;
            scan_msg.header.stamp = start_scan_time;
            scan_msg.header.frame_id = frame_id;
            scan_msg.angle_min = scan.config.min_angle;
            scan_msg.angle_max = scan.config.max_angle;
            scan_msg.angle_increment = scan.config.ang_increment;
            scan_msg.scan_time = scan.config.scan_time;
            scan_msg.time_increment = scan.config.time_increment;
            scan_msg.range_min = scan.config.min_range;
            scan_msg.range_max = scan.config.max_range;
            
            scan_msg.ranges = scan.ranges;
            scan_msg.intensities =  scan.intensities;
            scan_pub.publish(scan_msg);
        }  
        if (laser.IsCheckingFinished()) {//修正完成
          if (laser.getResult()) { //修正成功

          } else {//修正失败

          }
        } else {//查看修正状态
          switch (laser.getCheckStateError()) {
           case CYdLidar::NOERROR:

          break;

          case CYdLidar::FREQUENCYOUT:

          break;

          case CYdLidar::JUMPFREQUENCY:

          break;

          default:
          break;
         }
        }
        rate.sleep();
        ros::spinOnce();
    }

    laser.turnOff();
    printf("[YDLIDAR INFO] Now YDLIDAR is stopping .......\n");
    laser.disconnecting();
    return 0;
}
