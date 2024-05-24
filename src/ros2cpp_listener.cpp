#include "ros2cpp/ros2cpp_listener.hpp"


OsccListener::OsccListener():Node("oscc_listener")
{
    chatter_sub =  std::make_unique<message_filters::Subscriber<std_msgs::msg::String>>(this, "/chatter");
    speed_sub =  std::make_unique<message_filters::Subscriber<std_msgs::msg::Float32>>(this, "/Vehicle/Speed");

    oscc_listener_feedbacks_sync = std::make_unique<message_filters::Synchronizer<OsccListenerTimePolicy>>(OsccListenerTimePolicy(10), *chatter_sub, *speed_sub);
    oscc_listener_feedbacks_sync->registerCallback(std::bind(&OsccListener::callbackPrompt, this, std::placeholders::_1, std::placeholders::_2));

    oscc_listener_pub = create_publisher<std_msgs::msg::String>("/oscc_chatter", rclcpp::QoS{1});
}

void OsccListener::callbackPrompt(const std_msgs::msg::String::ConstSharedPtr& chatter_rpt, const std_msgs::msg::Float32::ConstSharedPtr& speed_rpt){
  /* publish speed data */
  {
    std_msgs::msg::String data_rpt;
    data_rpt.data = speed_rpt->data;  // [m/s]
    oscc_listener_pub->publish(data_rpt);
  }   
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OsccListener>());
  rclcpp::shutdown();
  return 0;
}