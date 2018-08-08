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
This "graph.cpp" includes member function implementation for two 
classes: location and graph. Location class hold the information 
of the class and a edge node pointer to head
*/

#include "graph.h"

//location class constructor
location::location():head(NULL),address(NULL){}

//location class destructor
location::~location()
{
	if(address)
		delete [] address;
	delete_all(head);	
}

//remove the location and all its edge list
void location::remove()
{
	if(address)
	{
		delete [] address;
		address = NULL;
	}
	delete_all(head);
}

//check the address of the location is NULL
bool location::is_null()
{
	if(!address)
		return true;
	else
		return false;
}

//display location information
void location::display()
{
	cout<<"the location is: "<<address<<endl;
}

//remove the edge list
void location::delete_all(edge *& head)
{
	if(!head) return;
	delete_all(head->go_next());
	delete head;
	head = NULL;
}

//add edge between two locations
void location::add_edge(edge & to_add, location * a_location)
{
	if(!head)
	{
		head = new edge(to_add);
		head->connect(a_location);
		head->go_next() = NULL;
	}
	else
	{
		edge * temp = new edge(to_add);
		temp->connect(a_location);
		temp->set_next(head);
		head = temp;
			
	}	
		
}

//get the address of the location
char * location:: get_address()
{
	return address;
}


edge *& location::go_head()
{
	return head;
}

//graph constructor
graph::graph(int size)
{
	list_size = size;
	adjacency_list = new location[list_size];
}

//graph destructor
graph::~graph()
{

	if(adjacency_list)
	{

		for(int i=0; i<list_size; ++i)
		{
			if(!adjacency_list[i].is_null()||!adjacency_list[i].head_null()) 
			{
				//delete adjacency_list[i];
				adjacency_list[i].remove();
			}
		}

		delete [] adjacency_list;
		adjacency_list = NULL;
	}
}

//check the head is null?
bool location::head_null()
{
	if(!head)
		return true;
	else
		return false;
}

//set address of the location
void location::set_address(const char * add)
{
	if(address)
	{
		delete [] address;
		address = NULL;
	}
	address = new char[strlen(add)+1];
	strcpy(address, add);
}

//get address of location
void location::get_address(char *& addr)
{
	if(address)
	{
	addr = new char[strlen(address)+1];
	strcpy(addr,address);
	}
	else
		cout<<"no address"<<endl;
}

//display edge list
void location::display_edge_list()
{
	edge * current = head;
	char * an_address;
	while(current)
	{
		current->get_location(an_address);
		if(an_address)
			cout<<an_address<<endl;
		current = current->go_next();
		if(an_address)
		{
			delete [] an_address;
			an_address = NULL;
		}
	}
}

//insert location/vertex to the graph
int graph::insert_vertex(const char * to_add)
{
	if(!to_add)
		return 0;
	if(adjacency_list[0].is_null() == true)
	{
		adjacency_list[0].set_address(to_add);
		return 1;
	}
	else
	{
		int index = 0;
		int i = 1;
		while(i<list_size && index == 0)
		{
			if(adjacency_list[i].is_null() == true)
				index = i;
			else
				++i;
		}
		if(index == 0)
			return 0;
		else
		{
			adjacency_list[i].set_address(to_add);
			return 1;
		}
	}
}

//display all the locations/vertecies in the graph
int graph::display_vertex()
{
	for(int i=0; i<list_size; ++i)
	{
		if(adjacency_list[i].is_null()==false)
			adjacency_list[i].display();
	}
	return 1;
}

//find the location index from the table
int graph::find_location( char * key_value)
{
	char * add = NULL;
	for(int i=0; i<list_size; i++)
	{
		adjacency_list[i].get_address(add);
		if(!adjacency_list[i].is_null() && strcmp(add,key_value)==0)
		{
			if(add)
			{
				delete [] add;
				add = NULL;
			}
			return i;
		}
		if(add)
		{
			delete [] add;
			add = NULL;
		}
	}
	if(add)
	{
		delete [] add;
		add = NULL;
	}
	return -1;
}

//get the location
location * graph::get_location(char * key_value)
{
	int index = find_location(key_value);
	return &adjacency_list[index];
}

//insert an edge between two locations
int graph::insert_edge( char * current_vertex, char * to_attach, edge &to_add)
{
	int i = find_location(current_vertex);
	int j = find_location(to_attach);
	if(i<0||j<0)
		return 0;
	adjacency_list[i].add_edge(to_add, & adjacency_list[j]);

	return 1;	
}

//display adjacent locations of one location
int graph::display_adjacent(char * key_value)
{
	int index = find_location(key_value);
	if(index < 0)
		return 0;
	if(adjacency_list[index].head_null())
		return 0;
	adjacency_list[index].display_edge_list();
	return 1;
}

//find the path which returns the distance of the route - depth first search
float graph::shortest_distance_path(route & my_route, float & time)
{
	int count = 0;
	for(int i = 0; i < list_size; ++i)
	{
		if(!adjacency_list[i].is_null())
			++count;
		else
			i = list_size;
	}
	bool *visit = new bool[count];
	for(int i = 0; i < count; ++i)
		visit[i] = false;
	float total = 0;
	
	//shortest_distance_path(&adjacency_list[0],visit,my_route.go_rear(),total);
	total = shortest_distance_path(&adjacency_list[0],visit,my_route.go_rear(),time);

	edge * temp = my_route.go_rear();	
	while(temp->go_next())
	{
		temp = temp->go_next();
	}

	temp->go_next() = my_route.go_rear();
	my_route.go_rear() = temp;
	
	delete [] visit;
	return total;	
}

float graph::shortest_distance_path(location * my_location, bool * visit, edge *& head, float &time)
{
	if(!my_location) return 0;
	if(visit[my_location- adjacency_list])
		return 0;
	visit[my_location-adjacency_list] = true;	
	if(!my_location->go_head())
		return 0;
	float total = 0; 	
	edge * current = my_location->go_head();
	head = new edge(* current);
	head->go_next() = NULL;
	head->get_distance(total);
	time += head->total_time();
	total += shortest_distance_path(current->get_my_location(),visit, head->go_next(),time);	
	return total;
}

//finding the shortest path for standard delivery - Dijkstra's Algrithm
float graph::shortest_path(route & my_route, location * start, location * end)
{
	vector<Pair *> pairs;
	priority_queue <Pair *, vector<Pair*>, compare> my_pq;
	unordered_map<location *, float> seen; //store the shortest we have seen
	Pair *start_point = new Pair(start, 0.0, NULL,NULL);
	Pair *final_pair = NULL;	

	my_pq.push(start_point);	

	float final_cost = 0.;	
	seen[start] = 0.;
	while(!my_pq.empty())
	{
		location * current = my_pq.top()->vertex;
		float cost_so_far = my_pq.top()->cost;
		Pair * old_pair = my_pq.top();
		my_pq.pop();
		if(current == end){
			final_cost = cost_so_far;
			final_pair = old_pair;
			break;
		}
		edge * temp = current->go_head();
		//for(edge * temp = current->go_head(); temp; temp = temp->go_next())
		while(temp)
		{
			float new_cost = cost_so_far + temp->get_distance(); 

			if(seen.find(temp->get_my_location())==seen.end() || new_cost<seen[temp->get_my_location()])
			{
				seen[temp->get_my_location()] = new_cost;

				Pair * current_pair = new Pair(temp->get_my_location(),new_cost,temp, old_pair);
				pairs.push_back(current_pair);						
				my_pq.push(current_pair);
			}
			
			temp = temp->go_next();
		}		
	}
	//copy edges to my route
	Pair * temp_pair = final_pair;
	edge *temp_edge;

	my_route.go_rear() = new edge(* temp_pair->my_edge);
	my_route.go_rear()->go_next() = my_route.go_rear();
	while(temp_pair->previous->my_edge)
	{
		temp_edge = temp_pair->previous->my_edge;
		temp_edge->go_next() = my_route.go_rear()->go_next();
		my_route.go_rear()->go_next() = temp_edge; 		
		temp_pair = temp_pair->previous;
	}
	//release vector memory
	/*
	for(int i= 0; i<pairs.size();++i)
	{
		if(pairs[i])
			delete pairs[i];
	}
	*/
	pairs.shrink_to_fit();
	
	return final_cost;
}

//find the route that take shortest time, returns the total time - Dijkstra's Algrithm

float graph::shortest_time(route & my_route, location * start, location * end)
{
	vector<Pair *> pairs;
	priority_queue <Pair *, vector<Pair*>, compare> my_pq;
	unordered_map<location *, float> seen; //store the shortest we have seen
	Pair *start_point = new Pair(start, 0.0, NULL,NULL);
	Pair *final_pair = NULL;	
	my_pq.push(start_point);	
	float final_cost = 0.;	
	seen[start] = 0.;
	while(!my_pq.empty())
	{
		location * current = my_pq.top()->vertex;
		float cost_so_far = my_pq.top()->cost;
		Pair * old_pair = my_pq.top();
		my_pq.pop();
		if(current == end){
			final_cost = cost_so_far;
			final_pair = old_pair;
			break;
		}
		edge * temp = current->go_head();
		//for(edge * temp = current->go_head(); temp; temp = temp->go_next())
		while(temp)
		{
			float new_cost = cost_so_far + temp->total_time(); 

			if(seen.find(temp->get_my_location())==seen.end() || new_cost<seen[temp->get_my_location()])
			{
				seen[temp->get_my_location()] = new_cost;

				Pair * current_pair = new Pair(temp->get_my_location(),new_cost,temp, old_pair);
				pairs.push_back(current_pair);						
				my_pq.push(current_pair);
			}
			temp = temp->go_next();
		}		
	}
	//copy edges to my route
	Pair * temp_pair = final_pair;
	edge *temp_edge;

	my_route.go_rear() = new edge(* temp_pair->my_edge);
	my_route.go_rear()->go_next() = my_route.go_rear();
	while(temp_pair->previous->my_edge)
	{
		temp_edge = temp_pair->previous->my_edge;
		temp_edge->go_next() = my_route.go_rear()->go_next();
		my_route.go_rear()->go_next() = temp_edge; 		
		temp_pair = temp_pair->previous;
	}
	return final_cost;

}

//load the locations to the graph
int graph::load_graph_vertex(char file_name[])
{
	fstream file_in;
	file_in.open(file_name);

	if(!file_in)
		return 0;

	if(file_in)
	{
		char address[100];
				
	   	file_in.get(address, 100, '\n');
	   	file_in.ignore(100,'\n');
	    	while(!file_in.eof())
	    	{
			insert_vertex(address);

			file_in.get(address, 100, '\n');
			file_in.ignore(100,'\n');
	    	}
	}
	file_in.close();
	return 1;	
}

//load the edges to the graph
int graph::load_graph_edge(char file_name[])
{
	fstream file_in;
	file_in.open(file_name);

	if(!file_in)
		return 0;

	if(file_in)
	{
		edge my_edge;
		char address[100];
		char connected[100];
		float speed;
		float distance;
				
	    file_in.get(address, 100, '#');
	    file_in.ignore(100,'#');
	    while(!file_in.eof())
	    {

		file_in.get(connected, 100, '#');
		file_in.ignore(100, '#');
	
		file_in>>speed;
		file_in.ignore(100,'#');

		file_in>>distance;
		file_in.ignore(100,'#');
		file_in.ignore(100,'\n');
	
		my_edge.set_edge(speed,distance);
		insert_edge(address,connected,my_edge);		
		
		file_in.get(address, 100, '#');
		file_in.ignore(100,'#');
	    }
		
	}
	file_in.close();
	return 1;	
}






