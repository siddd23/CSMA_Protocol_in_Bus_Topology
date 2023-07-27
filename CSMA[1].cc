#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/csma-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"


using namespace ns3;


NS_LOG_COMPONENT_DEFINE ("P2P-CSMA");

int main (int argc, char *argv[]){

	bool verbose = true;
	uint32_t nCsma = 19;

	CommandLine cmd;
	cmd.AddValue("nCsna","Number of CSMA nodes", nCsma); 
	cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);
	cmd.Parse (argc, argv);
	Time::SetResolution(Time::NS);

	if(verbose){
	LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
	}
	
	NodeContainer p2pNodes;
	p2pNodes.Create(2);
	
	NodeContainer csmaNodes;
	csmaNodes.Add(p2pNodes.Get(1));
	csmaNodes.Create(nCsma);

	
	PointToPointHelper pointToPoint;
	pointToPoint.SetDeviceAttribute("DataRate",StringValue("100Mbps"));
	pointToPoint.SetChannelAttribute("Delay",StringValue("2ms"));
	
	NetDeviceContainer p2pDevices;
	p2pDevices = pointToPoint.Install(p2pNodes);
	
	CsmaHelper csma;
	csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
	csma.SetChannelAttribute("Delay", StringValue("2ms"));

	NetDeviceContainer csmaDevices;
	csmaDevices = csma.Install(csmaNodes);

	InternetStackHelper stack;
	stack.Install(p2pNodes.Get(0));
	stack.Install(csmaNodes);

	Ipv4AddressHelper address;
	address.SetBase("192.168.1.0","255.255.255.0");
	Ipv4InterfaceContainer p2pInterfaces = address.Assign(p2pDevices);

	address.SetBase("192.168.2.0","255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces = address.Assign(csmaDevices);

	UdpEchoServerHelper echoServer(4445);

	ApplicationContainer serverApps = echoServer.Install(csmaNodes.Get(nCsma));
	serverApps.Start(Seconds(1.0));
	serverApps.Stop(Seconds(10.0));
	UdpEchoClientHelper echoClient(csmaInterfaces.GetAddress(nCsma),4445);
	echoClient.SetAttribute("MaxPackets",UintegerValue(1));
	echoClient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize",UintegerValue(1024));

	ApplicationContainer clientApps = echoClient.Install(p2pNodes.Get(0));
	clientApps.Start(Seconds(2.0));
	clientApps.Stop(Seconds(10.0));
	
	AnimationInterface anim ("CSMA.xml");
	
	for (uint32_t i = 0; i < nCsma + 1; i++) {
        	double xPos = i * 50.0;
        	double yPos = 0.0;
        	anim.SetConstantPosition(csmaNodes.Get(i), xPos, yPos);
    	}

	

	Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	
	pointToPoint.EnablePcapAll("p2p-csma");

	Simulator::Run();
	Simulator::Destroy();
}

	
	
