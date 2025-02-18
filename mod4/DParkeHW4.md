# Homework Four : Queues and Lists

## Question One 

> Develop an ADT specification for a priority queue. A priority queue is like a FIFO
> queue except that items are ordered by some priority setting instead of time. In
> fact, you may think of a FIFO queue as a priority queue in which the time stamp
> is used to define priority.

### ADT - Priority Queue 

A list of data items which are ordered by their corresponding priority flag, which is represented by a natural number, with 0 being the highest priority message, and further priority descending as the number ascends. The values are stored as a priority, value pair, with priority inside of priority tiers being based on entrty time. 

### Methods: 

#### PQInsert(k, v):
input: k, the priority of the key-value pair. v, the value associated with the key
preconditions: none
process: store an item at the rear of the key tier of the list 
postconditions: The priority queue will contain an additional key-value pair 
outputs: nothing

#### PQPeek():
input: nothing
preconditions: none
process:  returns (but does not destroy) priority queue item with the highest priority item; 
postconditions: The priority queue is unchanged
outputs: returns null if the priority queue is empty, else returns the highest priotity item

#### PQPop():
input: nothing 
preconditions: there is at least one entry in the priority queue 
process: returns and then destroys the highest priority item in the queue 
postconditions: the queue has one less entry than the last time
output: returns highest priority item

#### PQSize():
input: nothing
preconditions: nothing
process: counts the number of items in the priority queue
postconditions: nothing
outputs: the number of items in the priority queue


#### PQisEmpty():
input: nothing 
preconditions: nothing
process: counts the number of items in the priority queue. Return true if zero, return false else. 
postconditions: nothing 
outputs: true if the priority queue is empty, else it returns false