Good evening everyone, I am Raviraj Dulange from team Technology Managers

Let's see the team and problem statement details that we have chosen for this hackathon

Our category is: 

So, our problem statement title says to ...

As discussed, our team name is, Technology Manager

# Start
So this is the fundamental flow diagram of our idea

So, the idea is to priorily detect the formation of blockages and show the location inside the pipes using GPS with easy to read color-coding

Now, if we detect some abnormal behaviour within the sewer pipe, we will notify the local authority, and this notification will be assessed by local authority for further action
And the best part is that this notification will be provided 20 mins before there arise any severe conditions within the system

Throughout the process we generate the data, and this data is stored on cloud, simply for further analysis, and for optimal sewerage system design.

# Tech Stack
So, our technology stack consists of following equipment:
So, in our model we precisely sense for 4 parameters(values). Temperature of the surrounding, velocity of water, level of water, and the amount of methane gas present in it.
Why specifically methane gas?
Because methane is highly flammable gas, so we need to avoid accumulation of such gas in our pipes.

Then these all sensors are connected to a micrcontroller. This device acts as a gateway between physical sensors and the backend. It transfers the readings picked to the backend

For transfering data, we use internet protocols such as HTTP and HTTPS. Also, we use GPS module

Now, since we are going for data analysis for the data collected in our database, we have tried to avoid multiple language dependencies by selecting python as our main language and thus we are using Django asd our backend framework.

Since, frontend is stand alone, we're using an JavaScript based framework called ReactJS

For, data base, our model can store data in any format. Therefore, using NOSQL over SQL is just a personal choice


So, there would be a circuit placed inside the sewer pipe with proper shielding such that all sensors are functional
This ckt will be attached to every manhole. The distance would be 15m to 20m long

# Use Cases:
So, the model will be helpful in taking correct decisions prior to the occurence of unwanted disturbances in the sewage system

It will also be helpful in avoiding nuisance near the occurence of mishap

Now, as the model stores data, we can use that data to better design the sewerage system, without disturbing the present system and with lesser capital cost.

Now, let's say there's some pipe which is functioning at 40%, then, the local authority can distribute some payload from other pipe to this pipe by installing valves at specified locations

# Dependencies
Now, the model depends on some of the parameters, these parameters are:

Continuous internet connection is required to the microcontroller. Now, this isn't a dependency in urban areas, where Government has already installed public internet network, and internet is available. But in absence of such public network, this problem can be solved by provision of dongle to the circuit.

The rate at which hardware connects to the cloud based software is about 1-2 mins. 

Now, the sensors need to be replaced after said amount of time. These lifespan are claims from the product owners

