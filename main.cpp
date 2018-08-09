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

#include "graph.h"
#include "delivery.h"

const int MAX = 100;
const int SIZE = 8; 

int main()
{


	delivery my_delivery;

	//load package from file
	list my_list;
	my_list.load_package("package.txt");


	//char origination[] = "a";    //set the delivery oritination
	//char destination[] = "t";    //set the delivery destination
	
	char origination[] = "Portland";    //set the delivery oritination
	char destination[] = "Medford";    //set the delivery destination


	//load graph from outside file		
	graph loc_graph;
	loc_graph.load_graph_vertex("my_vertex.txt");
	graph e_graph;
	e_graph.load_graph_vertex("my_vertex.txt"); 
	
	loc_graph.load_graph_edge("my_edge.txt");
	e_graph.load_graph_edge("my_edge.txt");

	//find the delivery route from the graph
	route s_route;
	route e_route;
	float route_distance = 0.0;
	float route_time = 0.0;
	route_distance = loc_graph.shortest_path(s_route, loc_graph.get_location("Portland"), loc_graph.get_location("Medford"));
	route_time = e_graph.shortest_time(e_route, e_graph.get_location("Portland"), e_graph.get_location("Medford"));
//	route_distance = loc_graph.shortest_distance_path(r_route,total_time);

	//Standard delivery
	int max_standard = 10;
	standard standard_delivery;
	standard_delivery.set_delivery(origination,destination, my_list);
	standard_delivery.set_standard(max_standard, s_route);
	cout<<"\n\n\nStandard delivery: "<<endl;
	standard_delivery.deliver_package();

	cout<<"total distance of the route is: "<<endl;
	cout<<route_distance<<endl;

	//Express delivery
	int max_express = 3;
	express express_delivery;
	express_delivery.set_delivery(origination,destination, my_list);
	express_delivery.set_express(max_express, e_route);
	cout<<"\n\n\nExpress delivery: "<<endl;
	express_delivery.deliver_package();

	cout<<"total time for the route is: "<<endl;
	cout<<route_time<<endl;

	//by drone delivery
	drone drone_delivery;
	drone_delivery.set_delivery(origination,destination, my_list);
	cout<<"\n\n\nby drone delivery: "<<endl;
	drone_delivery.deliver_package();
	
	return 0;
}






