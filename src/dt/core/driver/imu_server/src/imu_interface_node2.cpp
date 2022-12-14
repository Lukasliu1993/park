#include <imu_interface_node2.hpp>

ImuInterfaceNode2::ImuInterfaceNode2(const rclcpp::NodeOptions & node_options) 
: Node("imu_interface", node_options)
{
  // read parameter for serial
  port_ = declare_parameter("port", "/dev/ttyUSB0");
  baud_ = declare_parameter("baud", 460800);
  topic_name =  declare_parameter("topic", std::string("imu"));
  time_now = rclcpp::Node::now();

  // set parameter for serial
  this->serial_.setPort(port_);
  this->serial_.setBaudrate(baud_);
  this->serial_.setTimeout(std::numeric_limits<uint32_t>::max(), 5000, 0, 5000, 0);
  this->serial_.open() ;
  // imu data publisher 
  publisher = create_publisher<sensor_msgs::msg::Imu>(topic_name, 1);

  // Use a timer to schedule periodic message publishing.
  const double dt = 1.0 / 300.0;
  /* Timer */
  {
    auto timer_callback = std::bind(&ImuInterfaceNode2::on_timer, this);
    auto period =
      std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(dt));
    timer_ = std::make_shared<rclcpp::GenericTimer<decltype(timer_callback)>>(
      this->get_clock(), period, std::move(timer_callback),
      this->get_node_base_interface()->get_context());
    this->get_node_timers_interface()->add_timer(timer_, nullptr);
  }
}

void ImuInterfaceNode2::on_timer()
{

  sensor_msgs::msg::Imu msg;
  uint8_t payload[DL_CHECK_LENGTH];
  fetch_payload(payload);
  convert_to_msg(msg, payload);
  if(!started && (msg.header.stamp.sec - time_now.seconds()) < 5 ){
    refe = msg;
    num ++;
    started = true;
  }
  else if(started && (msg.header.stamp.sec - time_now.seconds()) < 5){
    refe.angular_velocity.x = (refe.angular_velocity.x + msg.angular_velocity.x);
    refe.angular_velocity.y = (refe.angular_velocity.y + msg.angular_velocity.y);
    refe.angular_velocity.z = (refe.angular_velocity.z + msg.angular_velocity.z);
    refe.linear_acceleration.x = (refe.linear_acceleration.x + msg.linear_acceleration.x);
    refe.linear_acceleration.y = (refe.linear_acceleration.y + msg.linear_acceleration.y);  
    refe.linear_acceleration.z = (refe.linear_acceleration.z + msg.linear_acceleration.z);
    num ++;

  }
  else if(started && (msg.header.stamp.sec - time_now.seconds()) >= 5){
  msg.angular_velocity.x = msg.angular_velocity.x - refe.angular_velocity.x / num;
  msg.angular_velocity.y = msg.angular_velocity.y - refe.angular_velocity.y / num;
  msg.angular_velocity.z = msg.angular_velocity.z - refe.angular_velocity.z / num;
  msg.linear_acceleration.x = msg.linear_acceleration.x - refe.linear_acceleration.x / num;
  msg.linear_acceleration.y = msg.linear_acceleration.y - refe.linear_acceleration.y / num;
  if(fabs(msg.linear_acceleration.x / 9.8) < 16 && fabs(msg.linear_acceleration.y / 9.8) < 16 && fabs(msg.linear_acceleration.z / 9.8) < 16 && fabs(msg.linear_acceleration.z / 9.8) > 0.001){
    publisher->publish(msg);
      //RCLCPP_INFO(this->get_logger(), " publish start " );
    }
    // publisher->publish(msg);
    

  }
  //  publisher->publish(msg);

}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(ImuInterfaceNode2)
