###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother Kirby, CS235
# Author:
#     Ken Smith
#     Tim O'Barr
#     Jessica Smith
# Summary:
#     An impementation of a Binary Search Tree
# Time:
#     Team: 8hours
#     Solo:
#        Ken: 10
#        Tim: 10
#        Jessica: 10.5
#     harder parts:
#        Ken: All the fixes(insert, find, erase, assignment operator), strange errors, and seg faults.
#        Jessica: assignment operator without recursion. and seg faults
#        Tim: the insert function
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -g -std=c++11
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bst.h assignment09.cpp
	g++ -c assignment09.cpp -g -std=c++11

