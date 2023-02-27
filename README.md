#


# Configuring the simulation



The simulation can be customized for basically any straight road either using the prompts given on start up:
  * throughput
  * Iteration speed
  * cars per second
  * Total lanes
  * bus lanes
  * duration of the simulation
  
 ![image](https://user-images.githubusercontent.com/47646799/221696206-e1057bc8-65c9-443e-8bfd-4135ef87b0c4.png)
 
Currently the traffic lights are hardcoded in their position, but with a little change it would easily be able to be dynamic
![image](https://user-images.githubusercontent.com/47646799/221696093-cd46e3cb-4ff5-4492-8a41-38a54908fcc7.png)

# Running the simulation

This image shows the simulation while its running
This shows information about the simulation such as average speed of all cars on the bridge and average speed per lane.
It also shows information on each car that is currently on the bridge such as position and speed.

![image](https://user-images.githubusercontent.com/47646799/221694284-03860efd-ad21-487f-9296-3a1014ce4ab8.png)

# Finished a simulation
When the simulation is done it prints the following information aswell as creating a csv which can be used to analyze the information that was found in the simulation.

![image](https://user-images.githubusercontent.com/47646799/221694982-1581d019-1bfa-4357-8d85-74a09934523e.png)

# Data
The data used in our simulation are from real world observations which can be seen here:

![image](https://user-images.githubusercontent.com/47646799/221696516-f95fcde7-4102-4907-9dd8-c2d250cbc180.png)
![image](https://user-images.githubusercontent.com/47646799/221696526-965173ae-8f71-4fd9-b569-0f44df717750.png)
![image](https://user-images.githubusercontent.com/47646799/221696537-cc6ff5d5-cc67-4876-a9eb-3aca3a61e43a.png)

From the data of the csv file the following data can be extracted

## Average speeds of all cars currently on the bridge

![image](https://user-images.githubusercontent.com/47646799/221695343-d16775b2-0ddf-4afc-982f-1b89d9979137.png)
![image](https://user-images.githubusercontent.com/47646799/221695351-413ce1f9-721d-4796-a4d4-a381dfb43f5e.png)
![image](https://user-images.githubusercontent.com/47646799/221695360-0b7c3772-8716-4e7f-baa1-9ee98ecd9dec.png)


## Time waited of all cars currently on the bridge
![image](https://user-images.githubusercontent.com/47646799/221695364-019f3935-d97b-4e8e-8a52-00ad94900a97.png)
![image](https://user-images.githubusercontent.com/47646799/221695374-b47182e4-dfac-41fd-9c6d-5c866914c49c.png)
![image](https://user-images.githubusercontent.com/47646799/221695385-5823bf5b-0ed4-41b0-90d2-5ab3cd74ed28.png)
![image](https://user-images.githubusercontent.com/47646799/221695449-5ee97146-d283-4e52-b429-7056693caa50.png)

This data clearly shows that in this case they should not choose to implement more than 1 Buslane since that would destroy the flow of traffic.
More graphs can be made from the data using the csv file, this is just a few of the relevant ones in our case

# Accuracy of data

While this is a very simple simulation it can give powerful results. We have a bunch of unit tests that makes sure both the physics of the acceleration is correct, and to make sure that the cars behaves as they should in all scenarios. We did make some assumptions in this simulation based on observations from our data.

 * Out of all the cars that drove on the bridge only 3 cars switched lane while on the bridge which made us limit the cars in our simulation to not being able to switch lane
 * We also limited traffic lights to not have a yellow light, which should not affect the overall results
 * cars have a fixed acceleration, this is something that would be easy to change but unsure if it would break anything so we had a static accelerationn

