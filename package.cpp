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
This "package.cpp" includes function implementations of three classes: package, node, and list.
Package has the package information; the node class is a package, while has an next pointer.
The list class is a linear linked list of node.
*/

#include "package.h"

//constructor
package::package():weight(0),size(0),destination(NULL){}

//constructor with argument
package::package(float w, float s, char * loc)
{
	weight = w;
	size = s;
	destination = new char[strlen(loc)+1];
	strcpy(destination,loc);
}

//copy constructor
package::package(const package & to_copy)
{
	weight = to_copy.weight;
	size = to_copy.size;
	destination = new char[strlen(to_copy.destination)+1];
	strcpy(destination,to_copy.destination);
}

//destructor to release memory
package::~package()
{
	if(destination)
	{
		delete [] destination;
		destination = NULL;
	}
}

//get location of the package
void package::get_location(char *&loc)
{
	loc = new char[strlen(destination)+1];
	strcpy(loc,destination);
}

//get the weight of the package
void package::get_weight(float & w)
{
	w = weight;
}

//get the size of the package
void package::get_size(float & s)
{
	s = size;
}

//get the weight of the package
float package::get_weight()
{
	return weight;
}

//get the sise of the package
float package::get_size()
{
	return size;
}
//display package information
void package::display()const
{
	cout<<"package weight is: "<<weight<<endl;
	cout<<"package size is: "<<size<<endl;
	cout<<"package location is: "<<destination<<endl;
}

//node constructor
node::node(const package & a_package):package(a_package),next(NULL){}

//go to next
node *& node::go_next()
{
	return next;
}

//set the next
void node::set_next(node * connection)
{
	next = connection;
}

//check if the next is NULL
bool node::if_next()const
{
	if(next) 
		return 1;
	else
		return -1;
}

//list constructor
list::list():head(NULL){}

//add package to the list
void list::add_package(const package & to_add)
{
	add_package(head,to_add);
}

//add package to the list
void list::add_package(node *& head, const package &to_add)
{
	if(!head)
	{
		head = new node(to_add);
		head->go_next() = NULL;
	}
	else
		add_package(head->go_next(), to_add);
}

//display all the packages in the list
void list::display_all()const
{
	display_all(head);
}

//display all the packages in the list
void list::display_all(node * head)const
{
	if(!head)   return;
	head->display();
	display_all(head->go_next());
}

//copy constructor
list::list(const list &to_copy):head(NULL)
{
	copy_list(head, to_copy.head);
}

//destructor
list::~list()
{
	delete_all(head);
}

//copy a list
void list::copy_list(const list & to_copy)
{
	copy_list(head, to_copy.head);
}

//copy a list
void list::copy_list(node *& result, node * source)
{
	if(!source)
		result = NULL;
	else
	{
		result = new node(*source);
		copy_list(result->go_next(),source->go_next());
	}
}

//remove all the list
void list::delete_all()
{
	delete_all(head);
	head = NULL;
}

//remove the whole list
void list::delete_all(node *& head)
{
	if(!head) return;
	delete_all(head->go_next());	
	delete head;
	head = NULL;
}

//remove certern number of packages from the list 
int list::remove_package( int num_to_remove)
{
	if(!head) return 0;
	int num_removed = 0;
	remove_package(num_to_remove, head,num_removed);
	return num_removed;
}

//remove the packages from the list after they were delivered
int list::remove_package(int num_to_remove, node *& head, int & num_removed)
{
	if(!head || num_removed == num_to_remove)
		return 0;
	delete head;
	head = head->go_next();
	++num_removed;
	return remove_package(num_to_remove, head,num_removed);	
} 

int list::remove_package(float weight, float size)
{
	if(!head) return 0;
	int index  = 0;
	return remove_package(weight,size,head,index);	
}

int list::remove_package(float weight, float size, node *& head, int & index)
{
	if(!head ||index>0)
		return 1;
	if(head->get_weight()<weight && head->get_size()<size)
	{
		delete head;
		head = head->go_next();
		index = 1;
	}
	return remove_package(weight, size, head->go_next(),index);
	 
}
//load the package list from outside file
int list::load_package(char file_name[])
{
	ifstream file_in;
	file_in.open(file_name);

	if(!file_in)
		return 0;

	if(file_in)
	{
		char address[100];
		float weight;
		float size;
		
	    file_in.get(address, 100, '#');
	    file_in.ignore(100,'#');
	    while(!file_in.eof())
	    {
		file_in>>weight;
		file_in.ignore(100, '#');

		file_in>>size;
		file_in.ignore(100,'#');
		file_in.ignore(100,'\n');

		package a_package(weight, size, address);
		add_package(a_package);

		file_in.get(address, 100, '#');
		file_in.ignore(100,'#');
	    }
	}
	file_in.close();
	return 1;
}






