#include <iostream>
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include "priorityqueue.h"
#include <math.h>

int main(int argc, char** argv) {
    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }

    std::map<int, int> checkPlayerExistence;
    nlohmann::json targetObject;

    //iterate over values to get the data, pointer needed
    //make sure to use double instead of int
    PriorityQueue teamQueue(jsonObject["teamStats"].size());
    for (auto itr = jsonObject["teamStats"].begin(); itr != jsonObject["teamStats"].end(); ++itr) {
        double rawPercent = (*itr)["winPercentage"];
        double midpercent = abs(rawPercent- 50);
        Key percent = midpercent;
        int playerOne = (*itr)["playerOne"];
        int playerTwo = (*itr)["playerTwo"];
        teamQueue.insert(std::make_pair(percent, std::make_pair(playerOne, playerTwo)));
    }

    std::vector<std::pair<int,int>> teamsVector;

    while(!(teamQueue.isEmpty())){
        KeyValuePair teamNode = teamQueue.removeMin();
        if(checkPlayerExistence.count(teamNode.second.first)==0 && checkPlayerExistence.count(teamNode.second.second)==0){
            checkPlayerExistence.insert({teamNode.second.first,0});
            checkPlayerExistence.insert({teamNode.second.second,0});
            teamsVector.push_back({teamNode.second.first,teamNode.second.second});
            targetObject["teams"] = teamsVector;
        }
    }//build a map, if both of the two players doesn't exist in map
    //which means they haven't chosen before
    //then they are available to be chosen
    //they are added to a vector to avoid to be replaced for each iteration
    //teamsVector becomes value in jsonObject

    std::cout << targetObject.dump(2) << "\n";
    return 0;
}

