#include <iostream>
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include "priorityqueue.h"

int main(int argc, char** argv) {
    std::ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }//read in the file

    nlohmann::json finalObject;
    std::size_t maxnum = jsonObject["metadata"]["maxHeapSize"];
    //the max number of elements possible during operations in heap 
    //which represented as an array
    PriorityQueue targetQueue(maxnum); //one instance of the heap

    //build the heap
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {
        // std::cout<<itr.key()<<"\n";
        if(itr.key()=="metadata"){
            break;
        }//since "metadata" is at the last position, so we can break
        if(jsonObject[itr.key()]["operation"]=="insert"){
            Key eachKey = jsonObject[itr.key()]["key"];
            targetQueue.insert(eachKey);
        }else{
            targetQueue.removeMin();
        }
    }
    finalObject = targetQueue.JSON();
    finalObject["metadata"]= jsonObject["metadata"];
    finalObject["metadata"]["size"]= targetQueue.size();//return size_
    finalObject["metadata"]["max_size"]= maxnum;


    std::cout << finalObject.dump(2) << "\n";
    return 0;
}
