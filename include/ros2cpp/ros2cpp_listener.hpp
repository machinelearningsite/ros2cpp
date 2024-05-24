#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float32.hpp"

#include <message_filters/subscriber.h>
#include "message_filters/synchronizer.h"
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <utility>
#include <string>

class OsccListener: public rclcpp::Node
{
    public:
        OsccListener();
        
    private:
        using OsccListenerTimePolicy = message_filters::sync_policies::ApproximateTime<std_msgs::msg::String, std_msgs::msg::Float32>;        
        
        // Defining subsribers
        std::unique_ptr<message_filters::Subscriber<std_msgs::msg::String>> chatter_sub;
        std::unique_ptr<message_filters::Subscriber<std_msgs::msg::Float32>> speed_sub;
        std::unique_ptr<message_filters::Synchronizer<OsccListenerTimePolicy>> oscc_listener_feedbacks_sync;

        // Sample Publisher
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr oscc_listener_pub;

        // Defining OsccListener callback
        void callbackPrompt(const std_msgs::msg::String::ConstSharedPtr& chatter_rpt, const std_msgs::msg::Float32::ConstSharedPtr& speed_rpt);
};