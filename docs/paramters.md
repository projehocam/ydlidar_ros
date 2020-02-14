# ROS Paramters Table

## Paramters Description
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
| `range_min`       	| float                  	| Minimum Valid range, defalut: 0.05m      			|
| `range_max`       	| float                  	| Maximum Valid range, defalut: 64.0m      			|
| `ignore_array`      | String                  	| LiDAR filtering angle area, default: ""      			|
| `samp_rate`       	| int                  	| sampling rate of lidar, default: 20      				|
| `frequency`       	| float                  	| scan frequency of lidar,default: 10.0      			|

##Baudrate Table

| LiDAR                					| baudrate               | 
|-----------------------------------------------|-----------------------|
|TX8/TX20                        		| 115200			|
|TG15/TG30/TG50	    		 	        | 512000			|

## SingleChannel Table

| LiDAR                							| isSingleChannel       | 
|-----------------------------------------------------------|-----------------------|
|TG15/TG30/TG50                         				| false			|
|TX8/TX20         							| true			|

##isToFLidar Table

| LiDAR                									| isTOFLidar             | 
|-----------------------------------------------------------------------|-----------------------|
|TG15/TG30/TG50/TX8/TX20                   				| true			|

## Sampling Rate Table

| LiDAR                		| samp_rate             | 
|-----------------------------|------------------------|
|TX8/TX20 	                  | 4			 	 |
|TG15/TG30/TG50               | 10,18,20		 |

##Frequency Table


| LiDAR                					| frequency             | 
|-----------------------------------------------|------------------------|
|TX8/TX20			                | Not Support		 |
|TG15/TG30/TG50           			| 3-16Hz			 |

Note: For unsupported LiDARs, adjusting the scanning frequency requires external access to PWM speed control.
