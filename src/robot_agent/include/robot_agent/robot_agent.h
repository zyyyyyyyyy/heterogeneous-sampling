#pragma once

#include <ros/ros.h>
#include <sampling_msgs/RequestTemperatureMeasurement.h>
#include <sensor_msgs/NavSatFix.h>
#include <string>

namespace sampling {
namespace agent {

/// robot state machine
/// Default : IDLE
/// Workflow
/// Request : Request next interest point from master computer
/// Navigate : navigate to target location
/// Report : measure temperature and report to master computer
enum STATE { IDLE, REQUEST, NAVIGATE, REPORT };

class AgentNode {
public:
  AgentNode(){};

  AgentNode(const ros::NodeHandle &nh, const ros::NodeHandle &rh);

  virtual bool update_goal_from_gps() = 0;

  virtual bool navigate() = 0;

  virtual void update_GPS_location_callback(const sensor_msgs::NavSatFix &msg);

  bool request_target_from_master();

  bool collect_temperature_sample();

  void report_temperature_sample();

  /// State machine
  void collect_sample();

protected:
  STATE agent_state_;
  std::string agent_id_;

  ros::NodeHandle nh_, rh_;
  int ros_queue_size_;
  ros::ServiceClient request_target_client_;
  ros::ServiceClient temperature_measurement_client_;
  ros::Publisher temperature_sample_pub_;
  ros::Subscriber gps_location_sub_;

  std::string request_target_channel_;
  std::string temperature_measurement_channel_;
  std::string temperature_update_channel_;
  std::string gps_location_channel_;

  double temperature_measurement_;
  double current_latitude_;
  double current_longitude_;
  double goal_rtk_latitude_;
  double goal_rtk_longitude_;
};
} // namespace agent
} // namespace sampling