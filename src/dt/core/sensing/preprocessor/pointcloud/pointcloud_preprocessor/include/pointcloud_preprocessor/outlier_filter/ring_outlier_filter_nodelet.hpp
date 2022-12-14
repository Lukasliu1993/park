// Copyright 2020 Tier IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef POINTCLOUD_PREPROCESSOR__OUTLIER_FILTER__RING_OUTLIER_FILTER_NODELET_HPP_
#define POINTCLOUD_PREPROCESSOR__OUTLIER_FILTER__RING_OUTLIER_FILTER_NODELET_HPP_

#include "pointcloud_preprocessor/filter.hpp"

#include <pcl/filters/voxel_grid.h>
#include <pcl/search/pcl_search.h>

#include <vector>

namespace pointcloud_preprocessor
{
class RingOutlierFilterComponent : public pointcloud_preprocessor::Filter
{
protected:
  virtual void filter(
    const PointCloud2ConstPtr & input, const IndicesPtr & indices, PointCloud2 & output);

private:
  double distance_ratio_;
  double object_length_threshold_;
  int num_points_threshold_;

  /** \brief Parameter service callback result : needed to be hold */
  OnSetParametersCallbackHandle::SharedPtr set_param_res_;

  /** \brief Parameter service callback */
  rcl_interfaces::msg::SetParametersResult paramCallback(const std::vector<rclcpp::Parameter> & p);

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  explicit RingOutlierFilterComponent(const rclcpp::NodeOptions & options);
};

}  // namespace pointcloud_preprocessor

namespace custom_pcl
{
struct PointXYZIRADT
{
  PCL_ADD_POINT4D;
  float intensity;
  std::uint16_t ring;
  float azimuth;
  float distance;
  double time_stamp;
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

struct PointXYZI
{
  PCL_ADD_POINT4D;
  float intensity;
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;

}  // namespace custom_pcl

POINT_CLOUD_REGISTER_POINT_STRUCT(
  custom_pcl::PointXYZIRADT,
  (float, x, x)(float, y, y)(float, z, z)(float, intensity, intensity)(std::uint16_t, ring, ring)(
    float, azimuth, azimuth)(float, distance, distance)(double, time_stamp, time_stamp))

POINT_CLOUD_REGISTER_POINT_STRUCT(
  custom_pcl::PointXYZI, (float, x, x)(float, y, y)(float, z, z)(float, intensity, intensity))

#endif  // POINTCLOUD_PREPROCESSOR__OUTLIER_FILTER__RING_OUTLIER_FILTER_NODELET_HPP_
