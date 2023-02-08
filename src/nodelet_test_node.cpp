
#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>


namespace nodelet_test {

class CameraForwardNodelet : public nodelet::Nodelet
{
public:
    CameraForwardNodelet() {}

private:
    ros::Subscriber camera_sub_, compressed_sub_;
    ros::Publisher camera_forward_pub_, compressed_forward_pub_;

    void callback(const sensor_msgs::ImageConstPtr &msg)
    {
        camera_forward_pub_.publish(msg);
    }

    void callback1(const sensor_msgs::CompressedImageConstPtr &msg)
    {
        compressed_forward_pub_.publish(msg);
    }

    virtual void onInit()
    {
        ros::NodeHandle &nh = getNodeHandle();
        ros::NodeHandle &private_nh = getPrivateNodeHandle();

        camera_sub_ = nh.subscribe("/image_raw", 1, &CameraForwardNodelet::callback, this);
        camera_forward_pub_ = nh.advertise<sensor_msgs::Image>("/image_raw_forward", 1);
        compressed_sub_ = nh.subscribe("/image_raw/compressed", 1, &CameraForwardNodelet::callback1, this);
        compressed_forward_pub_ = nh.advertise<sensor_msgs::CompressedImage>("/image_raw/compressed_forward", 1);
    }
};

} // namespace nodelet_test

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(nodelet_test::CameraForwardNodelet, nodelet::Nodelet)
