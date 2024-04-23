#include <string>
#include "TLEParser.h"
#include <curl/curl.h> //libvurl library used to transfer data with URL syntax

/*Callback function to handle response data from libcurl
    void *contents: This parameter represents a pointer to the received data.
    size_t size: This parameter specifies the size of each data element.
    size_t nmemb: This parameter specifies the number of data elements.
    std::string *data: This parameter is a pointer to a std::string object where the received data will be appended.
*/
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *data) {
    // Calculate total size of data received
    size_t totalSize = size * nmemb;
    // Append received data to the string pointed to by 'data'
    data->append((char*)contents, totalSize);
    // Return total size of data received
    return totalSize;
}

// Function to fetch satellite information
std::string fetchSatelliteInfo(const std::string& query) {
    // Initialize libcurl handle
    CURL *curl = curl_easy_init();
    // Check if initialization was successful
    if (!curl) {
        return "Failed to initialize libcurl";
    }

    // String to store API response
    std::string apiResponse;
    // String to store URL
    std::string url;

    // Check if query consists only of digits (presumably a satellite ID)
    bool isNumber = true;
    for (char c : query) {
        if (!std::isdigit(c)) {
            isNumber = false;
            break;
        }
    }

    // Construct URL based on whether query is a number or not
    if (isNumber) {
        // If query is a number, construct URL to get satellite info directly
        url = "https://tle.ivanstanojevic.me/api/tle/" + query;
    } else {
        // If query is not a number, construct URL to search for satellite by name
        url = "https://tle.ivanstanojevic.me/api/tle?search=" + query;
    }

    // Set libcurl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Set URL
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Set callback function for writing response data
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse); // Set where to store response data

    // Perform HTTP request
    CURLcode res = curl_easy_perform(curl);
    // Check if request was successful
    if (res != CURLE_OK) {
        // If request failed, return error message along with libcurl error string
        return "Failed to fetch satellite information: " + std::string(curl_easy_strerror(res));
    }

    // Clean up libcurl handle
    curl_easy_cleanup(curl);
    // Return API response
    return apiResponse;
}
