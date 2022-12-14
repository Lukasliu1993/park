
include "map_builder.lua"
include "trajectory_builder.lua"

options = {
  map_builder = MAP_BUILDER,
  trajectory_builder = TRAJECTORY_BUILDER,
  map_frame = "map",
  tracking_frame = "imu_link",
  published_frame = "base_link",
  odom_frame = "odom",
  provide_odom_frame = true,
  publish_frame_projected_to_2d = false,
  use_pose_extrapolator = true,
  use_odometry = true,
  use_nav_sat = false,
  use_landmarks = false,
  num_laser_scans = 0,
  num_multi_echo_laser_scans = 0,
  num_subdivisions_per_laser_scan = 1,
  num_point_clouds = 1,
  lookup_transform_timeout_sec = 0.2,
  submap_publish_period_sec = 0.3,
  pose_publish_period_sec = 0.1,
  trajectory_publish_period_sec = 30e-3,
  rangefinder_sampling_ratio = 1.,
  odometry_sampling_ratio = 1.,
  fixed_frame_pose_sampling_ratio = 1.,
  imu_sampling_ratio = 1.,
  landmarks_sampling_ratio = 1.,
  publish_to_tf = true,
  publish_tracked_pose = true,
}

TRAJECTORY_BUILDER_2D.num_accumulated_range_data = 1

MAP_BUILDER.use_trajectory_builder_2d = true
MAP_BUILDER.num_background_threads = 6
POSE_GRAPH.optimization_problem.huber_scale = 5e2
POSE_GRAPH.optimize_every_n_nodes = 5
POSE_GRAPH.global_constraint_search_after_n_seconds = 30
POSE_GRAPH.constraint_builder.max_constraint_distance = 4
POSE_GRAPH.constraint_builder.sampling_ratio = 0.2
POSE_GRAPH.optimization_problem.ceres_solver_options.max_num_iterations = 12
POSE_GRAPH.constraint_builder.min_score = 0.47
POSE_GRAPH.constraint_builder.global_localization_min_score = 0.55
POSE_GRAPH.global_sampling_ratio = 0.0095

TRAJECTORY_BUILDER_2D.motion_filter.max_time_seconds = 1.0
TRAJECTORY_BUILDER_2D.use_imu_data = true
TRAJECTORY_BUILDER_2D.use_online_correlative_scan_matching = false
TRAJECTORY_BUILDER_2D.min_range = 0.2
TRAJECTORY_BUILDER_2D.max_range = 15.
TRAJECTORY_BUILDER_2D.min_z = 0.7

TRAJECTORY_BUILDER_2D.adaptive_voxel_filter.max_length = 1.5
TRAJECTORY_BUILDER_2D.adaptive_voxel_filter.min_num_points = 100
TRAJECTORY_BUILDER_2D.adaptive_voxel_filter.max_range = 20

POSE_GRAPH.optimization_problem.odometry_translation_weight = 100
POSE_GRAPH.optimization_problem.odometry_rotation_weight = 100

TRAJECTORY_BUILDER_2D.ceres_scan_matcher.rotation_weight = 10
TRAJECTORY_BUILDER_2D.ceres_scan_matcher.translation_weight = 1

POSE_GRAPH.constraint_builder.ceres_scan_matcher.rotation_weight = 10
POSE_GRAPH.constraint_builder.ceres_scan_matcher.translation_weight = 10

TRAJECTORY_BUILDER_2D.submaps.num_range_data = 30
TRAJECTORY_BUILDER.pure_localization_trimmer = {
  max_submaps_to_keep = 3,
}
-- POSE_GRAPH.constraint_builder.fast_correlative_scan_matcher_3d.linear_xy_search_window = 30.
-- POSE_GRAPH.constraint_builder.fast_correlative_scan_matcher_3d.angular_search_window =  math.rad(45.)
-- POSE_GRAPH.constraint_builder.fast_correlative_scan_matcher.linear_search_window = 30.
-- POSE_GRAPH.constraint_builder.fast_correlative_scan_matcher.angular_search_window = math.rad(45.)
-- POSE_GRAPH.constraint_builder.sampling_ratio = 0.1
-- POSE_GRAPH.constraint_builder.max_constraint_distance = 8
-- TRAJECTORY_BUILDER_2D.motion_filter.max_distance_meters = 0.8
-- TRAJECTORY_BUILDER_2D.motion_filter.max_angle_radians = math.rad(2.)

return options