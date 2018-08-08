//Open Source Project
//Delivery Services
//Chunyan Bao  7/31/2018

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
The purpose of this program is to create an object oriented program that will provide three
different types of delivery service: Standard, Express, and by Drone.
This "graph.h" includes two classes: location and graph
Location class hold the information of the class and a edge node pointer to head
*/

#ifndef GRAPH_H
#define GRAPH_H
#include "route.h"
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;

const float INT_MAX = 1000000;

class location
{
	public:
		location();                               //constructor
		location(char * address);                 //constructor
		~location();
		void set_address( const char * address);  //set the address
		void get_address(char *& address);        //get the address
		char * get_address(); //get the address
		void display();                           //display 
		bool is_null();//return true if address ull, else return false
		void add_edge(edge & to_add, location * a_location); //add edge
		bool head_null();// return true if head is null
		void display_edge_list();   //display edge list 
		edge *& go_head();   //used to act: edge->head
		void remove();
		
	protected:
		edge * head;	
		char * address;
		void delete_all(edge *& head);
		void display_edge_list( edge * head);
};

struct Pair
{
	location * vertex;
	float cost;
	edge * my_edge;
	Pair * previous;
	
	Pair(location * my_vertex, float my_cost, edge * an_edge, Pair * parent)
	{
		vertex = my_vertex;
		cost = my_cost;
		previous = parent;
		my_edge = an_edge;
	}

	bool operator <(const Pair p2)const
	{
		if(this->cost < p2.cost)
			return true;
		else
			return false;
	}

	bool operator >(const Pair p2)const
	{
		if(this->cost > p2.cost)
			return true;
		else
			return false;
	}
};
struct compare
{
	bool operator()(const Pair *p1, const Pair *p2)
	{
		return (*p1)>(*p2);
	}	
};

class graph
{
	public:
		graph(int size = 20); //constructor, the size of the graph is initialized to 20
		~graph(void);         //destructor
		int insert_vertex(const char * to_add);   //insert location to the graph
		int find_location(char * key_value);      //find the index of the location
		location * get_location(char * key_value);
		int insert_edge(char * current_vertex, char * to_attach, edge & to_add); //insert edge between locations
		int display_adjacent( char *key_value);  //display adjacenct of the location

		float shortest_distance_path(route & my_route, float & time); //finding the path from the origination to the desitination
		float shortest_distance_path(location * my_loc, bool * visit, edge *& head, float &time);
		
		//finding shortest distance route for standard delivery
		float shortest_path(route & my_route,location * start, location * end);
		//finding shortest time route for express delivery
		float shortest_time(route & my_route, location * start, location * end);
		
		int display_vertex();  //display vertex on the graph

		int load_graph_vertex(char file_name[]);  //load locations from a file
		int load_graph_edge(char file_name[]);    //load edges from a file
		
	protected:
		location * adjacency_list;
		int list_size;
		
};

#endif
