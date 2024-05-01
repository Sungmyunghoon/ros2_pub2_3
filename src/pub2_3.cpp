#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/string.hpp"
#include <memory>
#include <chrono>
#include <functional>
//#include <string>
using namespace std::chrono_literals;
void callback(rclcpp::Node::SharedPtr node, 
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub)
{
    geometry_msgs::msg::Twist remote;
    remote.linear.x = 4.0;
    remote.angular.z = -1.8;
    RCLCPP_INFO(node->get_logger(), "X: %lf  Z: %lf", remote.linear.x, remote.angular.z);
    pub->publish(remote);
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("mynode");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile
    );
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(100ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}