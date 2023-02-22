/*
 *  
 *  Author: John Eastman
 *  CS 131 Assignment #2: Informed Search
 * 
 */
#include "aStarNode.hpp"

using namespace std;


Node::Node(vector<int> s, int g_, int h_, Node *p) {
        this->stack = s;
        this->g = g_;
        this->h = h_;
        this->parent = p;
}

int Node::f() const {
        return this->g + this->h;
}

bool Node::operator<(const Node &other) const {    
        return this->f() > other.f();
}

vector<int> Node::getStack() const {
        return this->stack;
}

int Node::backCost() const {
        return this->g;
}

Node* Node::getParent() const {
        return this->parent;
}