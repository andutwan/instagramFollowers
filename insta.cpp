#include <iostream>
#include <fstream>
#include "json.hpp"

// void printNotFollowing(std::vector<std::string> notFollowing) {
//     for (auto person : notFollowing) {
//         std::cout << person << std::endl;
//     }
// }

int main (int argc, char** argv) {
    nlohmann::json followers;
    nlohmann::json followings;
    std::vector<std::string> notFollowing;
    bool follows = false;
    int numNotFollowed = 0;
    std::ifstream file(argv[1]); // Holds the list of followers
    followers = nlohmann::json::parse(file);
    std::ifstream file2(argv[2]);              // Holds the list of followings
    followings = nlohmann::json::parse(file2);

    for (auto itr = followings["relationships_following"].begin(); itr != followings["relationships_following"].end(); ++itr) {
       for (auto itr2 = followers.begin(); itr2 != followers.end(); ++itr2) {
            if (itr[0]["string_list_data"][0]["value"] != itr2[0]["string_list_data"][0]["value"]) {
                continue;
            } else {
                // They follow you back
                follows = true;
                break;
            }
       }
       if (follows == false) {
            std::cout << itr[0]["string_list_data"][0]["value"] << std::endl;
            numNotFollowed++;
       } 
       follows = false;
    }
    std::cout << "This many people do not follow you back " << numNotFollowed << std::endl;
    // printNotFollowing(notFollowing);

    return 0;
}
