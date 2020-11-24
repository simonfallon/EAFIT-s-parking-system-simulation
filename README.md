# EAFIT-s-parking-system-simulation
Agent-Based simulation of the multi-parking-lot system of EAFIT's University (C++)
Users arrive according to a parametrizable non-homogeneous Poisson Proccess. 
Distrubution of the time in system is defined by a parametrizable flow-graph of time windows. 
Exits are defined by a parametrizable non-homogeneous Poisson Proccess.
Each user in the simulation is uniquely identified by a pair of indices (user_id), which point to a position in a data base. 
The simulation runs with user_id objects (indices), so that no redundant information is copied.
Two data-structures, for the queue and the parking lot, are designed to support some basic operations for the user_id objects.
An entire day of simulation (61.200 seconds, over 2000 users, 6 queues and 4 parking lots) takes under 1 second of runtime.
