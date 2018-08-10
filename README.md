# delivery-services

Copyright (c) 2018 ChunyanBao

This program is released under the "MIT license".

# Program Description

The purpose of this program is to create an object oriented program that will provide 
three different types of delivery service: Standard, Express, and by Drone.

Standard - For Standard delivery, the driver will find the best/shortest route to take to deliver
           all of the packages, but time is not of the essence.
           
Express - For Express delivery, the driver will find the fastest route to delivery the package. An express
          delivery service can have up to 3 packages being delivered at any one trip.
          
By Drone - For By Drone delivery, only one package can be delivered at a time. The 
           package must be under 10 pounds and under 1 sq ft. They do not need to find a
           route (since roads are not used).
          
# User Guide

* This program needs three external text files for input:

1. a list of packages for delivery
The package has a destination, size, and weight. So the format for the package file should be: destination#size#weight#. This program only accepts packages with the same destination. Please see the file example: package.txt
2. a list of vertices/locations
The vertex file includes all the locations. Please see the file example: my_vertex.txt
3. edges between locations
This edge file includes the edges between the locations. The format for the file should be: location1#location2#speedLimit#distance#. Please see the file example: my_edge.txt

