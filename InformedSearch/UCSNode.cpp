/*
 *  
 *  Author: John Eastman
 *  CS 131 Assignment #2: Informed Search
 * 
 */
#include "UCSNode.hpp"

using namespace std;

UCSNode::UCSNode(vector<int> s, int g_, UCSNode *p) {
        this->stack = s;
        this->g = g_;
        this->parent = p;
}

int UCSNode::f() const {
        return this->g;
}

bool UCSNode::operator<(const UCSNode &other) const {    
        return this->f() > other.f();
}

vector<int> UCSNode::getStack() const {
        return this->stack;
}

int UCSNode::backCost() const {
        return this->g;
}

UCSNode* UCSNode::getParent() const {
        return this->parent;
}