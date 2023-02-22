/*
 *  
 *  Author: John Eastman
 *  CS 131 Assignment #2: Informed Search
 * 
 */
#include <vector>

#ifndef UCS_NODE_H
#define UCS_NODE_H

using namespace std;

class UCSNode {
public:
        UCSNode(vector<int> s, int g_, UCSNode *p);
        
        int f() const;

        bool operator<(const UCSNode &other) const;

        vector<int> getStack() const;

        int backCost()const;

        UCSNode* getParent() const;

        //Give credit to where I found this...
        struct VectorHasher {
                int operator()(const vector<int> &V) const {
                        int hash = V.size();
                        for(auto &i : V) {
                        hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
                        }
                        return hash;
                }
        };
private:
        vector<int> stack;
        int g;
        UCSNode *parent;
};

#endif