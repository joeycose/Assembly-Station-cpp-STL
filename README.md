# Intro - Assembly Station
 Developing a simulation of an assembly line with any number of stations using C++ and STL methods. 
 
 
 # Visual 
 ![image](https://user-images.githubusercontent.com/85801475/222190210-0cd9222f-b85b-44e7-9299-976778c3c68b.png)

 
 # Summary
 
The solution involves an assembly line consisting of several workstations, each holding a set of specific stock items. A line manager moves customer orders along the line, filling orders at each station as requested. Each station processes a queue of orders by filling the next order in the queue if that order requests the station's item and that item is in stock. Once all orders have been processed, the line manager lists the completed and incomplete orders due to a lack of inventory at one or more stations.

In the implementation of this solution, the Standard Template Library (STL) in C++ was used. The STL provides a set of powerful and efficient data structures and algorithms that can be used to build complex programs. In this solution, STL's queue data structure was used to implement the order queue at each workstation. 

The queue allows for a first-in-first-out (FIFO) order processing, which is suitable for processing customer orders. Additionally, the STL's vector container was used to store the stock items at each station. 

The vector provides a dynamic array that can be resized at runtime and is well suited for holding a varying number of stock items at each workstation. Overall, the use of STL in this solution helped simplify the implementation and improve the efficiency of the program.





