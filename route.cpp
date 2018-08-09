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
This "route.cpp" includes function implementation for two classes: edge and route. 
The edge class is a node class, the route class is a circular linked list. 
The route class has an edge class.
*/

#include "route.h"
#include "graph.h"

//constructor
edge::edge():speed_limit(0.0),distance(0.0),my_location(NULL),next(NULL) {}

//constructor with given argument
edge::edge(float speed, float dis):speed_limit(speed),distance(dis),my_location(NULL),next(NULL){}

//copy constructor
edge::edge(const edge & to_copy):my_location(NULL),next(NULL)
{
	speed_limit = to_copy.speed_limit;
	distance = to_copy.distance;
}

//get the total time needed for this edge
float edge::total_time()
{
	return distance/speed_limit;
}

//set the speed limit and distance of the edge with the given arguments
void edge::set_edge(float speed, float dis)
{
	speed_limit = speed;
	distance = dis;
}

//get the speed limit of the edge
void edge::get_speed(float & speed)
{
	speed = speed_limit;
}

//get the distance of the edge
void edge::get_distance(float & dis)
{
	dis = distance;
}

//get the distance of the edge
float edge::get_distance()
{
	return distance;
}

//get the speed limit of the edge
float edge::get_speed()
{
	return speed_limit;
}

//edge->next
edge *& edge::go_next()
{
	return next;
}

//edge->next = connection
void edge::set_next( edge * connection)
{

	next = connection;
}

//check if the next pointer is null
bool edge::if_next()
{
	if(next)
		return 1;
	else
		return -1;
}

//get the address of the location
void edge::get_location(char *& an_address)
{
	my_location->get_address(an_address);	
}

//get the adjacency location
location *& edge::get_my_location()
{
	return my_location;
}

//connect the location with a pass in location
void edge::connect(location * a_location)
{
	my_location = a_location;
}

//display the edge
void edge::display()
{
	cout<<"edge speed limit is: "<<speed_limit<<endl;
	cout<<"edge distance is: "<<distance<<endl;
}


//route constructor
route::route():rear(NULL){}

//add edge to the CLL
void route::add_edge(const edge & to_add)
{
	if(!rear)
	{
		rear = new edge( to_add);
		rear->go_next() = rear;
	}
	else
	{
	edge *temp = new edge(to_add);
	temp->go_next() = rear->go_next();
	rear->go_next() = temp;
	rear = temp;
	}
}

//copy constructor
route::route(const route & to_copy)
{
	copy_list(rear, to_copy.rear);
}

//copy route from a given route list
int route::copy_route(const route & to_copy)
{
	return copy_list(rear, to_copy.rear);
}

//copy list
int route::copy_list(edge *& result, edge *source)
{
	if(!source)
	{
		result = NULL;
		return 0;
	}
	else
	{
		//break CLL
		edge * current = source->go_next();
		source->go_next() = NULL;
		
		edge *temp = NULL;
		copy_list(result, current, temp);

		//connect CLL
		source->go_next() = current;
		temp->go_next() = result;
		result = temp;
		return 1;
			
	}
}

//copy list
int route::copy_list(edge *& result, edge * current, edge *& temp)
{
	if(!current) return 0;
	result = new edge(*current);
	result->go_next() = NULL;
	temp = result;		
	return 1 + copy_list(result->go_next(), current->go_next(), temp);
}

//go to rear 
edge *& route::go_rear()
{
	return rear;
}

//display the route
void route::display_all()
{
	if(!rear)
		return;
	
	edge *current = rear->go_next();
	rear->go_next() = NULL;
	display_all(current);
	rear->go_next() = current;

}

void route::display_all(edge * current)
{
	if(!current) return;
	current->display();
	display_all(current->go_next());
}

//destructor
route::~route()
{
	delete_all();
}

//remove all on the route(CLL)
void route::delete_all()
{
	if(!rear) return;
	else
	{
		edge * current = rear->go_next();
		rear->go_next() = NULL;
		delete_all(current);
		rear = current;
	}
	
}
void route::delete_all(edge *& current)
{
	if(!current) return;
	delete_all(current->go_next());
	delete current;
	current = NULL;	
}


















