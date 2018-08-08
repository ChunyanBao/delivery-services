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
This "package.h" includes three classes: package, node, and list.
Package has the package information; the node class is a package, while has an next pointer.
The list class is a linear linked list of node.
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

class package
{
	public:
		package();    //defult constructor
		package( float w, float s, char * loc); //constructor--function overloading
		package(const package & to_copy);  //copy constructor
		~package();    //destructor
		void get_location( char *& loc);    //get the location of the package
		void get_weight( float & w);        //get the weight of the package
		float get_weight();
		float get_size();
		void get_size(float & s);           //get the size of the package
		void display() const;               //display information of the package
	protected:
		float weight;                       //weight of package
		float size;                         //size of package
		char * destination;                 //destination of package
};

class node:public package
{
	public:
		node(const package &);         //constructor
		node *& go_next();             //go to next
		void set_next(node * next);    //set the next
		bool if_next()const;           //check if the next is NULL
	protected:
		node * next;
};

class list
{
	public:
		list();                        //default constructor
		list( const list & to_copy);   //copy constructor
		~list();                       //default constructor
		void add_package(const package & to_add); //add a package to the list
		void display_all()const;                  //display the list
		void delete_all();                        //remove the list
		int remove_package(int num);  //deliver num number of package, remove them from the list
		int remove_package(float weight, float size); //delivery package by drone, if the package under 10 pounds and 1 sq ft
		void copy_list(const list & to_copy);     //copy a list
		int load_package(char file_name[]);       //loat a list of package from a file

	protected:
		int remove_package(int num_to_remove, node *&head, int &num_removed);    //remove number of packages after delivery
		int remove_package(float weight, float size,node *& head, int & index);
		void copy_list(node *& result, node * source); //copy list
		void add_package(node *&head, const package & to_add);  //add package to list
		void delete_all(node *& head);        //remove the list
		void display_all(node * head)const;   //display the lsit
		node * head;
};







