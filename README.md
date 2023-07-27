# CSMA_Protocol_in_Bus_Topology
NS3 Project on Implementing CSMA Protocol in Bus Topology

This project implements a simulation of a CSMA network in a bus topology. The simulation includes one point-to-point link and multiple CSMA nodes connected to it. The code sets up the network topology, assigns IP addresses to the nodes, installs the Internet stack, and configures the CSMA channel and devices. The simulation also includes an echo server application running on the last CSMA node and an echo client application running on the first point-to-point node.

The code uses the NS-3 network simulator and includes several NS-3 module headers, such as core, network, internet, point-to-point, applications, csma, ipv4-global-routing-helper, and netanim. The code uses the CommandLine class to parse command-line arguments and sets the simulation time resolution to nanoseconds.

The simulation is visualized using the NetAnim module, which creates an animation file of the network topology. The code uses the AnimationInterface class to set the positions of the CSMA nodes in the animation.

Finally, the code runs the simulation using the NS-3 Simulator class, which executes the network simulation and outputs the simulation results to a pcap file. The simulation runs for 10 seconds, during which the echo client sends one packet to the echo server every second. The simulation also logs the output of the echo server and client applications if the verbose flag is set to true. The code populates the routing tables using the Ipv4GlobalRoutingHelper class before running the simulation.
