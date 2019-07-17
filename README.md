# Abstract
This document describes one way of implementing an adhoc network with ESP8266 microchips. It uses a 
self-healing method which overcomes some of the hardware limitations of ESP8266 and ensures that the network 
does not require a consistent infrastructure like traditional wireless networks. 
 
# Introduction
Why is this an interesting problem? The idea of connecting devices without the need for a central router is an 
interesting problem because it eliminates the need for a specialized device for routing and thereby making the 
network much more mobile. This has applications in disaster recovery scenarios where centralized communication is 
not possible and many other areas including experimental fields with multiple distributed sensors. 
 
High level overview of our contribution? Our aim was to connect ESP8266 devices in an adhoc-like network 
topology where each device can act as an access point as well as a client which connects to other access points 
within the network. ESP8266 devices are cheap Wi-Fi enabled microchips which allow low-level access and are 
extremely versatile in its capabilities.  
We use a proactive protocol similar to distance vector routing for the network. Distance vector routing refers to a 
form of adhoc routing where each node maintains a routing table containing distances to neighboring nodes and 
broadcasts routing tables every few seconds so as to ensure each node has up-to-date neighbor distance information 
for creating routes. 

 
# Background
Formalizing the problem space? The network that we aimed to create is one where each device can communicate to 
each other directly and do not require a static access point to be present at all times. The network topology needs to 
be able to be tampered without adversely affecting the ability for devices to communicate with each other, i.e. should not require conforming with infrastructure (ad-hoc). Challenges in solving the problem? There are countless protocols for ad-hoc networking and one challenge was to 
figure out which protocol suited the ESP8266 best. All protocols required the capability for peer-to-peer broadcast to 
figure out a route to a destination via neighboring devices. Due to hardware limitations we had to resort to making 
each device communicate with each other as both clients and access points, where a client connects to an access 
point and thereby achieves peer-to-peer communication. We achieve ad-hoc networking by ensuring that the 
network rearranges/heals itself dynamically every time any node disappears (we explain the implementation details later). 

 
Fig1 : A high-level representation of of the network 
![](/ESP8266_adhoc.png)

# Approach
Detailed description of what we did and why we made particular choices? Our approach requires that each device in 
the network hold distance information about all devices that connect to it via its access point as well as information 
about the access point to which it acts as a client. This information is updated every few seconds. In this way it is 
similar to the proactive protocol of distance vector routing except that every device can only act as a client to only 
one access point due to the limitation of the client/server model. We had to use the client/server model, as mentioned 
in the above section, due to the limitations of the hardware for ESP8266. The choice for a proactive protocol was 
made due to the requirement that the network heals itself every time changes are made to network and updating 
distance information every few seconds ensure the timely healing of the network. Self-healing of the network 
ensures that the network does not have disconnected sets of  nodes when an intermediate node is removed or no 
longer part of the network.  
During proactive scans, each node which is not already a client to another node’s access point scans for access 
points which are not already present in its distance table, i.e. it looks for nodes that are not connected to its access point.  This prevents network loops and also ensures any new node is automatically part of the network. 
 
# Motivation
Presenting our approach in the light of other people's work? Adhoc protocols have traditionally been either proactive 
or reactive. Proactive protocols which periodically update routes regardless of changes in network topology 
generally fare worse in terms of application to real life scenarios when compared to reactive protocol which only 
update on demand. Since our method uses a proactive method for finding routes, it may not be the most efficient 
protocol possible. 
 
Why is our solution better, more robust? Our solution is better for the ESP8266 as it does not require for us to make hardware changes that would allow a normal adhoc protocol. 
 
# Evaluation
How do we evaluate our solution and what metrics did we choose for the evaluation? The code used was written in 
Arduino script and uploaded to several ESP8266 devices. We tested obtaining new connections and self-healing 
capability using the Arduino IDE console as well as WS-2811 LED strips. New connections were printed out in the 
Arduino IDE console while on LED strip we used color coding to indicate when new connections were being added 
or self-healing was occurring. Our solution worked well when compared to adhoc protocols on other devices without 
the client/server model caveat. It was however slow when changes to network topology was made and this is likely 
due to the self-healing aspect of the network which requires significant rearrangement and updates. 
 
# Conclusion
What we learned? Devices like the ESP8266, even with its severe hardware limitations, may be made to 
communicate with each other without a pre-defined infrastructure. We can use this idea of using devices as both 
clients and access points to implement ad-hoc routing in other devices that follow the client/server model. This may 
also be useful if the ESP8266 is to be used in low cost adhoc embedded systems. 
Point to future research directions to extend this research/project? Future projects may look into connecting and 
publishing data to the internet through the adhoc network. Other devices that are also limited to the client/server 
model may be tested with this method of adhoc and compared with ESP8266. 
