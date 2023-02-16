#include <iostream>
#include <fstream>
#include "json.hpp"

int main (int argc, char** argv) {
    // json objects holds followers and followings list
    nlohmann::json followers;
    nlohmann::json followings;
    // Boolean variable to know if someone follows you or not
    bool follows = false;
    // Keeps track of how many people are not following you
    int numNotFollowed = 0;
    std::ifstream file(argv[1]); // Holds the list of followers
    followers = nlohmann::json::parse(file);
    std::ifstream file2(argv[2]);              // Holds the list of followings
    followings = nlohmann::json::parse(file2);

    // Iterates through the followings list
    for (auto itr = followings["relationships_following"].begin(); itr != followings["relationships_following"].end(); ++itr) {
       // Iterates through the followers list
       for (auto itr2 = followers.begin(); itr2 != followers.end(); ++itr2) {
            // Compares a user from the followings list to the followers list
            if (itr[0]["string_list_data"][0]["value"] != itr2[0]["string_list_data"][0]["value"]) {
                // Checks if the user is found in the followers list
                continue;
            } else {
                // They follow you back
                follows = true;
                break;
            }
       }
       // Print out the user who does not follow you back
       if (follows == false) {
            std::cout << itr[0]["string_list_data"][0]["value"] << std::endl;
            // Increase the counter for the number of people who do not follow you back
            numNotFollowed++;
       } 
       // Rest follows so we know that we have not yet found the user in the followers list
       follows = false;
    }

    // Prints out the number of people who do not follow you back
    std::cout << "This many people do not follow you back " << numNotFollowed << std::endl;

    return 0;
}
