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
This "delivery.h" includes four classes: delivery, standard, express, and drone.
Delivery class is the base class of the other three classes
*/

#ifndef DELIVERY_H
#define DELIVERY_H

#include "route.h"
#include "package.h"
#include <iostream>
#include <cstring>
#include <cctype>

class delivery
{
	public:
		delivery();                               //constructor
		delivery(const delivery & source);        //copy constructor
		~delivery();                              //destructor
		void set_delivery( char *start, char * end, list & a_list);   //set the delivery
		void display()const;                      //display the delivery information
		

	protected:
		char * origination;                    //origination of the delivery
		char * destination;                    //destination of the delivery
		list package_list;                     //package list of the delivery
};

class standard: public delivery
{
	public:
		standard();     //default constructor
		standard(const standard & );//copy constructor
		void set_standard(int max, route & a_route); //set the standard with given args
		void deliver_package();   //deliver the package
		int display();            //display the information
		
	protected:
		route my_route;              //delivery route
		int max_num_package;         //max number of package can deliver one time 
};

class express: public delivery
{
	public:
		express();                   //constructor
		express(const express &);    //copy constructor
		void set_express(int max, route & a_route); //set the express with given arguments
		void deliver_package();     //deliver the package
		int display();              //display information
	protected:
		route my_route;             //delivery route for the express delivery
		int max_num_package;        //max number of package can deliver one time
};

class drone: public delivery
{
	public:
		drone(int size =1);   //constructor
		void deliver_package();   //deliver package
	protected:
		int max_num_package;    //max number of package which is 1 for this case
};

#endif
