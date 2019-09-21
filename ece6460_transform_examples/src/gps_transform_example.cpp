// Include the main header for the TF library
#include <tf/tf.h>

// Terminal IOs
#include <stdio.h>

// ROS message containing raw position info
#include <gps_common/GPSFix.h>

// Header to convert to and from UTM
#include <gps_common/conversions.h>

int main(int argc, char** argv)
{
  // Reference coordinates
  gps_common::GPSFix reference_coordinates;
  reference_coordinates.latitude = 42.6707444;
  reference_coordinates.longitude = -83.2172277;

  // Current position
  gps_common::GPSFix current_position;
  current_position.latitude = 42.6721583;
  current_position.longitude = -83.2150027;

  // Convert reference to UTM
  double ref_utm_x;
  double ref_utm_y;
  std::string ref_utm_zone;
  gps_common::LLtoUTM(reference_coordinates.latitude, reference_coordinates.longitude, 
                      ref_utm_y, ref_utm_x, ref_utm_zone);
  std::cout << "Reference UTM coordinates: (" << ref_utm_x << ", " << ref_utm_y << ") Zone: " << ref_utm_zone << "\n";

  // Convert current position to UTM
  double current_utm_x;
  double current_utm_y;
  std::string current_utm_zone;
  gps_common::LLtoUTM(current_position.latitude, current_position.longitude, 
                      current_utm_y, current_utm_x, current_utm_zone);
  std::cout << "Current UTM position:      (" << current_utm_x << ", " << current_utm_y << ") Zone: " << current_utm_zone << "\n";

  // Compute relative position vector in UTM
  double relative_pos_east = current_utm_x - ref_utm_x;
  double relative_pos_north = current_utm_y - ref_utm_y;
  std::cout << "Our current position is " << relative_pos_east << " meters East and "
            << relative_pos_north << " meters North of the reference point\n";

}