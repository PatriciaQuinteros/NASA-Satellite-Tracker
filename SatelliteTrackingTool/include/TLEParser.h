#ifndef TLE_PARSER_H
#define TLE_PARSER_H

#include <string>

// Define struct to hold satellite orbit information including additional parameters
struct SatelliteOrbit {
    std::string satelliteId;
    std::string name;
    std::string date;
    std::string line1;
    std::string line2;
   
};

// Function to fetch satellite information from the NASA API using a satellite name
std::string fetchSatelliteInfo(const std::string& name);

#endif
