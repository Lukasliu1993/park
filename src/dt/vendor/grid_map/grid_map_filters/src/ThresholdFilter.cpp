/*
 * ThresholdFilter.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: Martin Wermelinger, Peter Fankhauser
 *   Institute: ETH Zurich, ANYbotics
 */

#include "grid_map_filters/ThresholdFilter.hpp"

#include <grid_map_core/grid_map_core.hpp>
#include <pluginlib/class_list_macros.hpp>

#include <string>

#include "grid_map_cv/utilities.hpp"

namespace grid_map
{

template<typename T>
ThresholdFilter<T>::ThresholdFilter()
: lowerThreshold_(0.0),
  upperThreshold_(1.0),
  setTo_(0.5),
  useLowerThreshold_(false),
  useUpperThreshold_(false)
{
}

template<typename T>
ThresholdFilter<T>::~ThresholdFilter()
{
}

template<typename T>
bool ThresholdFilter<T>::configure()
{
  ParameterReader param_reader(this->param_prefix_, this->params_interface_);

  if (param_reader.get(std::string("lower_threshold"), lowerThreshold_)) {
    useLowerThreshold_ = true;
    RCLCPP_DEBUG(this->logging_interface_->get_logger(), "lower threshold = %f", lowerThreshold_);
  }

  if (param_reader.get(std::string("upper_threshold"), upperThreshold_)) {
    useUpperThreshold_ = true;
    RCLCPP_DEBUG(this->logging_interface_->get_logger(), "upper threshold = %f", upperThreshold_);
  }

  if (!useLowerThreshold_ && !useUpperThreshold_) {
    RCLCPP_ERROR(
      this->logging_interface_->get_logger(),
      "ThresholdFilter did not find parameter 'lower_threshold' or 'upper_threshold',");
    return false;
  }

  if (useLowerThreshold_ && useUpperThreshold_) {
    RCLCPP_ERROR(
      this->logging_interface_->get_logger(),
      "Set either 'lower_threshold' or 'upper_threshold'! Only one threshold can be used!");
    return false;
  }

  if (!param_reader.get(std::string("set_to"), setTo_)) {
    RCLCPP_ERROR(
      this->logging_interface_->get_logger(), "ThresholdFilter did not find parameter 'set_to'.");
    return false;
  }

  if (!param_reader.get(std::string("layer"), layer_)) {
    RCLCPP_ERROR(
      this->logging_interface_->get_logger(), "ThresholdFilter did not find parameter 'layer'.");
    return false;
  }

  return true;
}

template<typename T>
bool ThresholdFilter<T>::update(const T & mapIn, T & mapOut)
{
  mapOut = mapIn;

  // Check if layer exists.
  if (!mapOut.exists(layer_)) {
    RCLCPP_ERROR(
      this->logging_interface_->get_logger(), "Check your threshold types! Type %s does not exist",
      layer_.c_str());
    return false;
  }

  // For each cell in map.
  auto & data = mapOut[layer_];
  for (grid_map::GridMapIterator iterator(mapOut); !iterator.isPastEnd(); ++iterator) {
    if (!mapOut.isValid(*iterator, layer_)) {continue;}
    const size_t i = iterator.getLinearIndex();
    float & value = data(i);
    if (useLowerThreshold_) {if (value < lowerThreshold_) {value = setTo_;}}
    if (useUpperThreshold_) {if (value > upperThreshold_) {value = setTo_;}}
  }

  return true;
}

}  // namespace grid_map

PLUGINLIB_EXPORT_CLASS(
  grid_map::ThresholdFilter<grid_map::GridMap>,
  filters::FilterBase<grid_map::GridMap>)
