/*
 *  
 *  Author: John Eastman
 *  CS 131 Assignment #2: Informed Search
 * 
 */
#include <cstdlib>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <iostream>
#include <unordered_set>
#include "aStarNode.hpp"

using namespace std;

const int NUM_PANCAKES = 10;

int heuristic(const vector<int> &stack);
vector<int> makePancakeStack(int numPancakes); 
void printInitialStack(vector<int> stack);
vector<Node *> performFlips(Node *parent);
void printSolution(Node *node, int *count);
bool adjacent(int i, int j);

int main () 
{
    cout << "Performing A* Search..." << endl;
    //Randomize a stack of pancakes (plate will always be on the bottom)
    vector<int> initialStack = makePancakeStack(NUM_PANCAKES);

    //Initial stack will be printed here, and then also when the initialState
    //node is printed out in the printSolution function
    printInitialStack(initialStack);
    cout << "heuristic of the initial stack is:" << heuristic(initialStack) << endl;

    Node *initialState = new Node(initialStack, 0, heuristic(initialStack), nullptr);

    priority_queue<Node *> nodeQueue;
    nodeQueue.push(initialState);

    //The closed list will hold the nodes that we've already visited...
    //  This is very important because it stops program from revisiting nodes.
    unordered_set<vector<int>, Node::VectorHasher> closed_list;

    //In theory, we should never reach the end of the priority queue. That's why
    //  we break if we find the goal state.
    while (!nodeQueue.empty()) {
        Node *current_node = nodeQueue.top();
        nodeQueue.pop();
        vector <int> temp = current_node->getStack();
        closed_list.insert(temp);

        if (heuristic(temp) == 0) {
            int flipCounter = 0;
            printSolution(current_node, &flipCounter);
            cout << "Goal state reached in " << flipCounter << " flips!\n";
            break;
        }

        vector<Node *> successors = performFlips(current_node);
       
        for (Node *successor : successors) {
            if (closed_list.find(successor->getStack()) == closed_list.end()) {
                nodeQueue.push(successor);
            } else {
                delete successor;
                successor = nullptr;
            }
        }
    }

    while (!nodeQueue.empty()) {  // loop until the queue is empty
        Node* node = nodeQueue.top();  // get a pointer to the top element
        nodeQueue.pop();  // remove the top element
        delete node;  // free the memory of the node
    }
    initialStack.clear();

}

/* Name: heuristic
 *  Returns an integer equal to heuristic value. Uses the gap heuristic function
 *      from the assignment page in Canvas.
 */
int heuristic(const vector<int> &stack) {
    int h = 0;
    for (int n = 0; n < NUM_PANCAKES; n++) {
        //If pancakes are not adjacent, add 1 to the heuristic value.
        if (not adjacent(stack[n], stack[n + 1])) {
            h += 1;
        }
    }
    return h;
}

/* Name: performFlips
 *  Returns a vector of nodes. Nodes all have a backCost 1 unit greater than
 *      the parents backCost, i.e. one flip was performed for each successor
 *      node created and stored in the vector.
 */
vector<Node *> performFlips(Node *parent) 
{
    vector<Node *> successors;
    //Get the size of the stack.
    int size = (NUM_PANCAKES + 1);
    
    for (int i = 1; i < (size - 1); i++) {
        //Check if the 2 pancakes above are not adjacent, if so, we flip.
        if (not adjacent(parent->getStack()[i], parent->getStack()[i + 1])) {
            vector<int> new_stack = parent->getStack();
            //If we're at the plate, we don't want to flip the plate, we just
            //  flip the whole stack, that's why we do "+ i" for this case 
            //  instead of "i + 1"
            if (i == (size - 1)) {
                reverse(new_stack.begin(), (new_stack.begin() + i));
            } else {
                reverse(new_stack.begin(), (new_stack.begin() + (i + 1)));
            }
            //Allocate space for and push a node (with flip performed)
            //  into the vector of successors.
            successors.push_back(new Node(new_stack, (parent->backCost() + 1), 
                             heuristic(new_stack), parent));
        }
    }
    return successors;
}

/*  Name: adjacent
 *      (Helper function for performFlips)
 *  Returns true if integers are adjacent to each other in the number line
 *      returns false otherwise.
 */
bool adjacent(int i, int j) {
    if (abs(i - j) <= 1) {
        return true;
    } else {
        return false;
    }
}

/* Name: printSolution
 *  
 *  Recursively prints out the solution of the pancake problem by tracing back
 *  from the goal state node to the intial node. Function uses a pointer to 
 *  an integer to keep track of the number of flips it took to reach the goal
 *  state.
 */
void printSolution(Node *node, int *count) {
    if (node->getParent() != nullptr) {
        *count += 1;
        printSolution(node->getParent(), count);
    }
    int restriction = (NUM_PANCAKES + 1);
    vector<int> tempStack = node->getStack();
    for (int i = 0; i < restriction; i++) {
        cout << tempStack[i] << " ";
    }
    //Delete the nodes as we print out the solution. All other nodes allocated
    //  will be in the priority queue.
    delete node;
    node = nullptr;
    cout << endl;
}

/*  Name: makePancakeStack
 *
 *  Returns a vector that is randomized with integers [1...NUM_PANCAKES].
 *      the last int in the vector will be NUM_PANCAKES + 1 because this 
 *      represents the plate (which cannot be flipped, but is important in
 *      organizing pancakes in acsending order, i.e. largest on bottom)
 * 
 */
vector<int> makePancakeStack(int numPancakes) {
    vector<int> pancakeStack;
    for (int i = 1; i < (numPancakes + 1); i++) {
        pancakeStack.push_back(i);
    }

    unsigned num = chrono::system_clock::now().time_since_epoch().count();
    shuffle(pancakeStack.begin(), pancakeStack.end(), default_random_engine(num));

    //Add the plate to the bottom of the stack.
    pancakeStack.push_back(numPancakes + 1);

    return pancakeStack;
}

/*  Name: printInitialStack
 *
 *  Just prints out the contents of the pancake stack made my makePancakeStack
 *  so that it's clear to the use what the initial stack is.
 * 
 */
void printInitialStack(vector<int> stack) {
    cout << "Initial state of the stack: ";
    for (unsigned i = 0; i < stack.size(); i++) {
        cout << stack[i] << " ";
    }
    cout << endl;
}


