![YDLIDAR](sdk/image/TG30.png  "TG30")

# YDLIDAR ROS PACKAGE(V1.4.5)

## Dataset 
|LIDAR      | Model  |  Baudrate |  SampleRate(K) | Range(m)  		   |  Frequency(HZ) | Intenstiy(bit) | SingleChannel | voltage(V)|
| :-------- |:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| TX8    　 | 100	   |  115200   |   4            |  0.1~8      	   | 4~8(PWM)       | false          | true      	  | 4.8~5.2   |
| TX20    　| 100	   |  115200   |   4            |  0.1~20      	   | 4~8(PWM)       | false          | true     	  | 4.8~5.2   |
| TG15    　| 100	   |  512000   |   20/18/10     |  0.05~15      	| 3~16      	  | false          | false    	  | 4.8~5.2   |
| TG30    　| 101	   |  512000   |   20/18/10     |  0.05~30      	| 3~16      	  | false          | false    	  | 4.8~5.2   |
| TG50    　| 102	   |  512000   |   20/18/10     |  0.05~50      	| 3~16      	  | false          | false    	  | 4.8~5.2   |

Note: PWM option speed control requires external PWM wave.


## How to [install ROS](http://wiki.ros.org/ROS/Installation)

[ubuntu](http://wiki.ros.org/Installation/Ubuntu)

[windows](http://wiki.ros.org/Installation/Windows)

## How to Create a ROS workspace
[Create a workspace](http://wiki.ros.org/catkin/Tutorials/create_a_workspace)

## How to build YDLiDAR ROS Package

    1) Clone this project to your catkin's workspace src folder
    	(1). git clone https://github.com/YDLIDAR/ydlidar_ros
    	(2). git chectout TOF
    2) Running catkin_make to build ydlidar_node and ydlidar_client
    3) Create the name "/dev/ydlidar" for YDLIDAR
    --$ roscd ydlidar_ros/startup
    --$ sudo chmod 777 ./*
    --$ sudo sh initenv.sh
Note: Download and Build details [here](docs/ydlidar.md)

## How to Run YDLIDAR ROS Package
#### 1. Run YDLIDAR node and view in the rviz
------------------------------------------------------------
	roslaunch ydlidar_ros lidar_view.launch

#### 2. Run YDLIDAR node and view using test application
------------------------------------------------------------
	roslaunch ydlidar_ros lidar.launch

	rosrun ydlidar_ros ydlidar_client

## ros-interfaces

<center>

| Topic                | Type                    | Description                                      |
|----------------------|-------------------------|--------------------------------------------------|
| `scan`               | sensor_msgs/LaserScan   | 2D laser scan of the 0-angle ring                |

| Parameter         | Type                    | Description                                         |
|-----------------------|------------------------|-----------------------------------------------------|
| `port`        		| String                 	| port of lidar (ex. /dev/ttyUSB0)                         		|
| `baudrate`     	| int                      	| baudrate of lidar (ex. 512000)           				|
| `frame_id`      	| String                	| TF frame of sensor, default: `laser_frame`    		|
| `isSingleChannel` | bool                     	| Whether LiDAR is a single-channel, default: false	|
| `resolution_fixed` | bool                     	| Fixed angluar resolution, default: true                    	|
| `auto_reconnect` | bool                  	| Automatically reconnect the LiDAR, default: true    	|
| `reversion`     	| bool                  	| Reversion LiDAR, default: true  					|
| `isTOFLidar`       	| bool                  	| Whether LiDAR is TOF Type, default: true  		|
| `angle_min`       	| float                 	| Minimum Valid Angle, defalut: -180.0     			|
| `angle_max`       	| float                  	| Maximum Valid Angle, defalut: 180.0      			|
| `range_min`       	| float                  	| Minimum Valid range, defalut: 0.01m      			|
| `range_max`       	| float                  	| Maximum Valid range, defalut: 64.0m      			|
| `ignore_array`      | String                  	| LiDAR filtering angle area, default: ""      			|
| `samp_rate`       	| int                  	| sampling rate of lidar, default: 20      				|
| `frequency`       	| float                  	| scan frequency of lidar,default: 10.0      			|
| `NoiseFilter`       	| bool                  	| LiDAR Data Noise Filter,default: false      			|


</center>

## Parameters

port (string, default: /dev/ydlidar)

    serial port name used in your system. 

baudrate (int, default: 512000)

    serial port baud rate. 
    
| LiDAR                					| baudrate               | 
|-----------------------------------------------|-----------------------|
|TX8/TX20 		            | 115200			|
|TG15/TG30/TG50			 	| 512000			|

frame_id (string, default: laser_frame)

    frame ID for the device. 

isSingleChannel (bool, default: false)

    indicated whether the LIDAR is single communication(TX8) lidar.
    
| LiDAR                							| isSingleChannel    | 
|-----------------------------------------------------------|-----------------------|
|TG15/TG30/TG50                         				| false			|
|TX8/TX20         							| true			|

resolution_fixed (bool, default: true)

    indicated whether the LIDAR has a fixed angular resolution. 

auto_reconnect (bool, default: true)

    indicated whether the LIDAR auto reconnection. 

reversion (bool, default: true)

    indicated whether the LIDAR data rotation 180°. 
    
| LiDAR                								| reversion              | 
|-----------------------------------------------------------------|-----------------------|
|TG15/TG30/TG50 	                    | true			|
|TX8/TX20                   			| false			|


isTOFLidar (bool, default:true)

    indicated whether the LIDAR is TOF(TX8) lidar. 
    
| LiDAR                									| isToFLidar             | 
|-----------------------------------------------------------------------|-----------------------|
|TG15/TG30/TG50/TX8/TX20                   				| true			|


angle_min (double, default: -180)

    Min valid angle (°) for LIDAR data. 

angle_max (double, default: 180)

    Max valid angle (°) for LIDAR data. 

range_min (double, default: 0.01)

    Min valid range (m) for LIDAR data. 

range_max (double, default: 64.0)

    Max valid range (m) for LIDAR data. 

ignore_array (string, default: "")

    Set the current angle range value to zero.
    
    Note: ignore 10 to 20 and 50 to 80, ex: "10, 20, 50, 80" 

samp_rate (int, default: 9)

    the LIDAR sampling frequency.
    
| LiDAR                		| samp_rate             | 
|-----------------------------|------------------------|
|TX8/TX20 	                |4			 	 |
|TG15/TG30/TG50             | 10,18,20		 |


frequency (double, default: 10)

    the LIDAR scanning frequency.

NoiseFilter (bool, default: false)

    the LIDAR Data Noise Filter.


## Change Log

2020-01-04 version:1.4.5

  1.Support Old protocol TOF LiDAR

  1.Serial number and version can be obtained for single channel LiDAR.

2019-12-03 version:1.4.4

  1.support all standards lidar

2019-12-03 version:1.4.3

  1.Support G4, G6,G1, TG LiDAR

2019-07-16 version:1.4.2

  1.Scan Frequency Offset

2019-03-25 version:1.4.1

   1.memory leak.

2019-03-25 version:1.4.0

   1.Fixed timestamp error
   
   2.LIDAR Startup abnormal
   
   3.Only support G2A LiDAR
   
   4.optimal turnOn and  turnOff 

## Contact EAI
![Development Path](sdk/image/EAI.png)

If you have any extra questions, please feel free to [contact us](http://www.ydlidar.cn/cn/contact)