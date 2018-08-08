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
This "delivery.cpp" includes member functions for four classes: 
delivery, standard, express, and drone.
*/

#include "delivery.h"

//delivery constructor
delivery::delivery():origination(NULL), destination(NULL)
{
}

//copy constructor
delivery::delivery(const delivery & source)
{
	origination = new char[strlen(source.origination)+1];
	strcpy(origination, source.origination);

	destination = new char[strlen(source.destination)+1];
	strcpy(destination, source.destination);

	package_list.copy_list(source.package_list);
}

//destructor
delivery::~delivery()
{
	if(origination)
	{
		delete [] origination;
		origination = NULL;
	}
	if(destination)
	{
		delete [] destination;
		destination = NULL;
	}
}

//set the information of the delivery using argument
void delivery::set_delivery(char * start, char * end, list & a_list)
{
	origination = new char[strlen(start)+1];
	strcpy(origination, start);

	destination = new char[strlen(end)+1];
	strcpy(destination, end);
	
	package_list.copy_list(a_list);

}

//display delivery information
void delivery::display()const
{
	cout<<"delivery origination is: "<<endl;
	cout<<origination<<endl;
	cout<<"delivery destination is: "<<endl;
	cout<<destination<<endl;
	cout<<"the package list is: "<<endl;
	package_list.display_all();
}

//standard constructor
standard::standard()
{
	max_num_package = 0;
}

//copy constructor
standard::standard(const standard & to_copy)
{
	max_num_package = to_copy.max_num_package;
	my_route.copy_route(to_copy.my_route);
}

//set standard information
void standard::set_standard( int max, route & a_route)
{
	max_num_package = max;
	my_route.copy_route(a_route);
}

//display standard delivery information
int standard::display()
{
	delivery::display();
	cout<<"Standard: max number of package can deliver is:"<<endl;
	cout<<max_num_package<<endl;
	cout<<"the delivery route is:"<<endl;
	my_route.display_all();
	return 1;
}

//delivery package 
void standard::deliver_package()
{
	display();
	int num = package_list.remove_package(max_num_package);
	cout<<num<<" packages are delivered."<<endl;
	cout<<"\n\nThis is the remaining package list after delivery: "<<endl;
	package_list.display_all();	
	
}

//constructor
express::express(): max_num_package(0)
{
}

//copy constructor
express::express(const express & to_copy)
{
	max_num_package = to_copy.max_num_package;
	my_route.copy_route(to_copy.my_route);

}

//set express using arguments
void express::set_express(int max, route & a_route)
{
	max_num_package = max;
	my_route.copy_route(a_route);
}

//display express information
int express::display()
{
	delivery::display();
	cout<<"Express: max number of package can deliver is:"<<endl;
	cout<<max_num_package<<endl;
	cout<<"the delivery route is:"<<endl;
	my_route.display_all();
	return 1;
}

void express::deliver_package()
{
	display();
	int num = package_list.remove_package(max_num_package);
	cout<<num<<" packages are delivered."<<endl;
	cout<<"\n\nThis is the remaining package list after delivery: "<<endl;
	package_list.display_all();	

}

//constructor
drone::drone(int size)
{
	max_num_package = size;
}

//send delivery information
void drone::deliver_package()
{
	cout<<"Drone: the max number of package I can deliver is 1."<<endl;
	cout<<"the package must be under 10 pound and under 1 sq ft."<<endl;
	delivery::display();
	package_list.remove_package(10.0,1.0);
	cout<<"\n\nThis is the remaining package list after delivery: "<<endl;
	package_list.display_all();
}


