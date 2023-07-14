//reference from text book

#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
	// TODO: complete this function
    nodes_[++size_]=kv;//size+1, and get updated size
    heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
	// TODO: complete this function
    return nodes_[1];
}

KeyValuePair PriorityQueue::removeMin() {
	// TODO: complete this function
    KeyValuePair store=nodes_[1];
    removeNode(1);
    return store;
    //careful about which one should call which due to the parameter
}

bool PriorityQueue::isEmpty() const {
	// TODO: complete this function
    return (size_==0);
}

size_t PriorityQueue::size() const {
	// TODO: complete this function
    return size_;
    //size controls the boundary in the vector nodes_
    //since we can't do pop or push_back so we need to track the size
    //if we do vector.size(), it will always be the max size
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
    return result;
}

void PriorityQueue::heapifyUp(size_t i) {
	// TODO: complete this function
    nodes_[0]=std::move(nodes_[i]);
    for( ; getKey(0) < getKey(i/2);i=i/2){//hole moves up
        //if the upper one is larger do the assignment, update the hole
        //if it gets to the top, i/2 will become decimal 
        //which become 0
        //which causes the relationship becomes equal, which exits the loop 
        nodes_[i]= std::move(nodes_[i/2]);//value moves down
    }
    nodes_[i] = std::move(nodes_[0]);
    //assign target value to the hole
}

void PriorityQueue::heapifyDown(size_t i) {
	// TODO: complete this function
    int child;
    KeyValuePair temp = std::move(nodes_[i]);
    for( ; i*2 <= size_; i = child){//hole moves down
        //check if it is at the rightmost bottom, also update hole
        child = i*2;
        if(child != size_ && getKey(child+1)<getKey(child)){
            ++child;
            //check if the left child exist
        }//compare left child and right child and choose the smaller one
        if(getKey(child) < temp.first){//if the lower one is smaller
            nodes_[i]= std::move(nodes_[child]);//value moves up
        }
        else {break;}
    }
    nodes_[i] = std::move(temp);
}

void PriorityQueue::removeNode(size_t i) {
	// TODO: complete this function
    nodes_[i] = nodes_[size_--];//get the original size then -1
    heapifyDown(i);
}

Key PriorityQueue::getKey(size_t i) {
	// TODO: complete this function
    return nodes_[i].first;
}
