## Mapping
```
ros2 launch localization_launch mapping.launch.xml
ros2 bag play '/home/dzt/bags/furong_ros2/rosbag2_2022_02_28-14_14_01' --topic /rslidar_points /driver/imu /odom
ros2 service call /finish_trajectory cartographer_ros_msgs/srv/FinishTrajectory "{trajectory_id: 0}"
ros2 service call /write_state cartographer_ros_msgs/srv/WriteState "{filename: '/home/$(whoami)/mymap.pbstream'}"
```

## Pcd
```
ros2 launch dt_launch pcd.launch.xml urdf_filename:='/home/dzt/dtsimulation.ros2/src/dt/launcher/dt_launch/urdf/mn.urdf' bag_filenames:='/home/dzt/bags/furong_ros2/rosbag2_2022_02_28-14_14_01' pose_graph_filename:='/home/dzt/dtsimulation.ros2/mymap.pbstream'

```
## Tracking
ros2 launch dt_launch tracking_offline.launch.xml
ros2 bag play '/home/dzt/bags/furong_ros2/rosbag2_2022_02_28-14_37_16/rosbag2_2022_02_28-14_37_16_0.db3'  --topic /rslidar_points /driver/imu /odom --clock
