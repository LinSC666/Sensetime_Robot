#include "ros/ros.h"
#include "std_msgs/String.h"
#include "apf/atificial_potential_field.h"
#include <sstream>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "apf_node");
  ros::NodeHandle n("~");
  
  ArtificialPotentialField apf(n);
  apf.loop();

  return 0;
}

