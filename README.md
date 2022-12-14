# dtsimulation.ros2
## Diagram
![Node diagram](docs/design/software_architecture/image/ArchitectureMain.drawio.svg)

## Installation steps

> Note: If the CUDA or TensorRT frameworks have already been installed, we strongly recommend uninstalling them first.
```
sudo apt-get --purge remove "*cublas*" "cuda*" "nsight*" 

sudo apt-get --purge remove "*nvidia*"

sudo rm -rf /usr/local/cuda*

```

1. Run the setup script to install CUDA, cuDNN 8, OSQP, ROS 2 and TensorRT 7, entering 'y' when prompted (this step will take1around 45 minutes)

   ```sh: type n for Would you like to install the optional GPU modules
   ./setup_ubuntu.sh
   ```


2. Build the source code (this will take around 15 minutes)

   ```sh
   source ~/.bashrc

   #Build with GPU
   colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release --parallel-workers 1

   #Build without GPU
   colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release --parallel-workers 1 --packages-skip   lidar_apollo_instance_segmentation tensorrt_yolo
   ```

   > Several modules will report stderr output, but these are just warnings and can be safely ignored.


## Quick start

```sh
   source install/setup.bash
   ros2 launch dt_launch planning_simulator.launch.xml
   ```


## Debug mode

reference:
[https://navigation.ros.org/tutorials/docs/get_backtrace.html]
[http://wiki.ros.org/roslaunch/Tutorials/Roslaunch%20Nodes%20in%20Valgrind%20or%20GDB]

* add -g to compile options for debugging node Cmakelist `add_compile_options(-Wall -Wextra -Wpedantic -Werror -g)`

* add `launch-prefix="xterm -e gdb -ex run --args" ` to launched node   

```

  container = ComposableNodeContainer(
      name="motion_planning_container",
      namespace="",
      package="rclcpp_components",
      executable=LaunchConfiguration("container_executable"),
      composable_node_descriptions=[
          obstacle_avoidance_planner_component,
          obstacle_stop_planner_component,
      ],
      prefix="xterm -e gdb -ex run --args",
  )

  <node pkg="path_server" exec="record_path" name="record_path_node" launch-prefix="xterm -e gdb -ex run --args"  >

```

* run `backtrace` in xtrem after crashing 

## linter

### install dependencies
1. install clang-format and clang-tidy

```
sudo apt-get install -y clang-tidy
sudo apt install ros-galactic-ament-clang-format
```

2. add `clang-tidy` and `clang-format` extension in vscode

### build with flag
```
   colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON --parallel-workers 1 --packages-skip   lidar_apollo_instance_segmentation pointcloud_preprocessor
```

### configure for clang-tidy lint

add following file

```
#.vscode/settings.json
{
  "clang-tidy.buildPath": "build/",
  "files.associations": {
    "limits": "cpp"
  }
}
```

## working in same network
```
~/.bashrc

export ROS_DOMAIN_ID=2

```

## record bag
```
ros2 bag record /driver/imu /driver/steer /odom /localization/twist /vehicle/status/steering /vehicle/status/control_mode  /rslidar_points /tf /tf_static /map/vector_map_marker /diagnostics_err /sensing/lidar/no_ground/pointcloud /perception/object_recognition/tracking/objects/visualization /planning/scenario_planning/lane_driving/motion_planning/surround_obstacle_checker/debug/marker /planning/scenario_planning/lane_driving/motion_planning/obstacle_stop_planner/debug/marker /control/trajectory_follower/predicted_trajectory /control/trajectory_follower/debug/marker/marker_array /planning/scenario_planning/lane_driving/motion_planning/obstacle_avoidance_planner/trajectory  --qos-profile-overrides-path record_qos.yaml
```

## perf
maybe need  to modify kernel setting
```
sudo sh -c 'echo "kernel.perf_event_paranoid=-1" >> /etc/sysctl.conf'
sudo sysctl -p
sudo sh -c " echo 0 > /proc/sys/kernel/kptr_restrict"
```

1. build with debug -g `add_compile_options(-Wall -Wextra -Wpedantic -g)`
2. `perf record --call-graph lbr ros2 launch planning_launch planning_debug.launch.xml`
3. `perf script > out.perf`
4. `./stackcollapse-perf.pl out.perf > out.folded`
5. `./flamegraph.pl out.folded > out.svg`

## Deployment
1. just install this image as normal ubuntu on IPC(legacy)
download image from BaiduYunDisk
 
链接：https://pan.baidu.com/s/1IrKx4Ckg0e2T0IvzUielwA  
提取码：gp97  

2. git clone path
```
/home/dzt/.product/dtsimulation.ros2
/home/dzt/.product/dt-frontend
```

3. run setup and build

4. config file of record param path: backend_control.py , please fill the absolute path of ymal in this line: "--qos-profile-overrides-path { absolute_path}"
for new car absolute_path: /home/dzt/.product/dtsimulation.ros2/record_qos.yaml
for old car absolute_path: /home/dzt/dtsimulation.ros2/record_qos.yaml

## parking
ros2 topic pub --once /vehicle/park_engage autoware_vehicle_msgs/msg/Engage "stamp:
  sec: 0
  nanosec: 0
engage: true"