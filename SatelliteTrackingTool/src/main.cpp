#include <iostream>
#include <iostream>
#include "json.hpp"
#include "TLEParser.h"

using json = nlohmann::json;

void displaySatelliteInfo(const std::string& jsonResponse) {
    json data = json::parse(jsonResponse);

    std::cout << "Satellite ID: " << data["satelliteId"] << std::endl;
    std::cout << "Name: " << data["name"] << std::endl;
    std::cout << "Date: " << data["date"] << std::endl;
    std::cout << "Line 1: " << data["line1"] << std::endl;
    std::cout << "Line 2: " << data["line2"] << std::endl;
}



int main() {
  

     std::string query;
    std::cout << "Enter satellite name or ID: \n";
    std::getline(std::cin, query);

    std::string jsonResponse = fetchSatelliteInfo(query);
    displaySatelliteInfo(jsonResponse);
 

    return 0;
}
