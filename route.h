//Open Source Project: Delivery Services

// Copyright (c) 2018 ChunyanBao 
// This program is released under the "MIT license". 

/*
The purpose of this program is to create an object oriented program 
that will provide three different types of delivery service: Standard, 
Express, and by Drone.

Standard - For standard delivery, the driver will find the best route
           to take to deliver all of the packages, but time is not of
	   the essence.
Express - Express delivery must find the fastest route to deliver the
	  package. An express delivery service can have up to 3 packages
	  being delivered at any one trip.
By Drone - Delivery by drone means that only one package can be delivered
	   at a time. The package must be under 1- pounds and under 1 sq ft.
	   They do not need to find a route(since roads are not used).
*/

/*
This "route.h" includes two classes: edge and route. The edge class is a node class, the route class
is a circular linked list. The route class has an edge class.
*/

#ifndef ROUTH_H
#define ROUTH_H

#include <iostream>
#include <cstring>
#include <cctype>
//#include "graph.h"    //cause problem because two included each other


using namespace std;

class edge
{
	public:
		edge();                            //constructor
		edge(float speed, float dis);      //constructor
		edge(const edge & to_copy);        //copy constructor
		
		void set_edge( float speed, float dis);  //set the edge with given arguments
		float total_time();                      //the total time takes for this edge
		void get_speed(float &speed);            //get the speed limit of the edge
		void get_distance(float & dis);          //get the distance of the edge
		float get_distance();
		float get_speed();
		void get_location(char *& address);      //get the adjacency's address
		class location *& get_my_location();     //get the adjacnecy
		void set_next(edge * next);              // set the next
		void display();                          //display edge list
		edge *& go_next();                       //go next
		bool if_next();                          //if next is null?
		void connect(class location * a_location);   //connect the adjacency
		
	protected:
		float speed_limit;                  //speed limit of the edge
		float distance;                     //distance of the edge
		class location * my_location;       //adjacency will be used in the graph class
		edge * next;
};

//this is a circular linked list of edge
class route
{
	public:
		route();                                     //constructor
		route(const route & to_copy);                //copy constructor
		~route();                                    //destructor 
		void add_edge(const edge & to_add);          //add edge to the CLL
		int copy_route(const route & to_copy);       //copy CLL from a given CLL
		void display_all();                          //display all in the list
		void delete_all();                           //remove the list
		edge *& go_rear();                           //->rear
	protected:
		edge * rear;
		int copy_list(edge *& result, edge * source); 
		int copy_list(edge *& result, edge * current, edge *& temp);
		void delete_all(edge *&rear);
		void display_all(edge *rear);
		void remove_edge( edge *& rear); 
};


#endif
