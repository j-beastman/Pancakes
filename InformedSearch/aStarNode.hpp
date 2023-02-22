/*
 *  
 *  Author: John Eastman
 *  CS 131 Assignment #2: Informed Search
 * 
 */
#include <vector>

#ifndef Node_H
#define Node_H

using namespace std;

class Node 
{
public:
        Node(vector<int> s, int g_, int h_, Node *p);

        int f() const;

        bool operator<(const Node &other) const;

        vector<int> getStack() const;

        int backCost()const;

        Node* getParent() const;

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

protected:
        vector<int> stack;
        int g;
        Node *parent;
private:
        int h;
};

#endif