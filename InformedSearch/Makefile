##
##  Makefile
##  Author: John Eastman
##  CS 131 Assignment #2: Informed Search
## 	
##	Executables should be in submission to Canvas, but just in case,
##		--the "AstarPancakes" rule builds my implementation of A* (informed
##			search) for the Pancake problem		
##		--the "UCSPancakes" rule builds my implementation of UCS (uninformed
##			search) for the Pancake problem

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -O2 -g -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds the A* executable
AstarPancakes: A_star.o aStarNode.o
	$(CXX) $(LDFLAGS) $^ -o AstarPancakes

# This rule builds the UCS executable
UCSPancakes: UCS.o UCSNode.o aStarNode.o
	$(CXX) $(LDFLAGS) $^ -o UCSPancakes

A_star.o: A_star.cpp aStarNode.cpp aStarNode.hpp
	$(CXX) $(CXXFLAGS) -c A_star.cpp

UCS.o: UCS.cpp UCSNode.o
	$(CXX) $(CXXFLAGS) -c UCS.cpp

aStarNode.o: aStarNode.cpp aStarNode.hpp
	$(CXX) $(CXXFLAGS) -c aStarNode.cpp

UCSNode.o: UCSNode.cpp UCSNode.hpp
	$(CXX) $(CXXFLAGS) -c UCSNode.cpp

# remove executables, object code, and temporary files from the directory
clean: 
	rm *.o