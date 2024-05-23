#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/sync_policies/approximate_time.h>

class OsccListener: public rclcpp::Node
{
    public:
    OsccListener():Node("oscc_listener"){
        
    }
    private:
    message_filters::Subscription<std_msgs::msg::String>::SharedPtr data_sub;

}