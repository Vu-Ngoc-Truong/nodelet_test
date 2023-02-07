
#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <sensor_msgs/Image.h>

namespace nodelet_test {

class CameraForwardNodelet : public nodelet::Nodelet
{
public:
    CameraForwardNodelet() {}

private:
    ros::Subscriber camera_sub_;
    ros::Publisher camera_forward_pub_;

    void callback(const sensor_msgs::ImageConstPtr &msg)
    {
        camera_forward_pub_.publish(msg);
    }

    virtual void onInit()
    {
        ros::NodeHandle &nh = getNodeHandle();
        ros::NodeHandle &private_nh = getPrivateNodeHandle();

        camera_sub_ = nh.subscribe("/camera", 1, &CameraForwardNodelet::callback, this);
        camera_forward_pub_ = nh.advertise<sensor_msgs::Image>("/camera_forward", 1);
    }
};

} // namespace nodelet_test

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(nodelet_test::CameraForwardNodelet, nodelet::Nodelet)
