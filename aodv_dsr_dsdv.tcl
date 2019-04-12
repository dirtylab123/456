puts "Enter the routing protocol in mobile networking {1 : AODV, 2 : DSR, 3 : DSDV}"
set val(nrp) [gets stdin]
if {$val(nrp) == 1} {
  set val(rp)         AODV;
} elseif {$val(nrp) == 2} {
  set val(rp)         DSR;
} elseif {$val(nrp) == 3} {
  set val(rp)         DSDV;
}
puts "Enter the no of nodes in network"
set no_nodes [gets stdin]

puts "Enter the node number to send data"
set src_node [gets stdin]

puts "Enter the node number to receive data"
set dest_node [gets stdin]

set val(chan)           Channel/WirelessChannel    ;# channel type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail    	   ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(nn)             $no_nodes                  ;# number of mobilenodes
set val(ifqlen)         50                         ;# max packet in ifq
set val(stop)		150			   ;# time of simulation end
set val(u)              500   			   ;# X dimension of topography
set val(v)              400   			   ;# Y dimension of topography

set ns		  [new Simulator]
set tracefd       [open simple-dsdv.tr w]
set windowVsTime2 [open win.tr w]
set namtrace      [open simwrls1.nam w]

$ns trace-all $tracefd
$ns use-newtrace
$ns namtrace-all-wireless $namtrace $val(u) $val(v)
	
set topo       [new Topography]
$topo load_flatgrid $val(u) $val(v)

create-god $val(nn)

        $ns node-config \
			 -adhocRouting $val(rp) \
			 -channelType $val(chan) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -llType $val(ll) \
			 -antType $val(ant) \
			 -ifqLen $val(ifqlen) \
			 -topoInstance $topo \
			 -agentTrace ON \
			 -routerTrace ON \
			 -macTrace OFF \
			 -movementTrace ON

for {set i 0} {$i < $val(nn) } { incr i } {
	set node_($i) [$ns node]
}

for {set i 0} {$i < $val(nn)} {incr i} {
  $node_($i) set X_ [expr rand()*500]
  $node_($i) set Y_ [expr rand()*400]
  $node_($i) set Z_ 0
}

for {set i 0} {$i < $val(nn)} { incr i } {
	$ns initial_node_pos $node_($i) 30
}


# Generation of movements
$ns at 10.0 "$node_(0) setdest 250.0 250.0 3.0"
$ns at 15.0 "$node_(1) setdest 45.0 285.0 5.0"
$ns at 110.0 "$node_(0) setdest 480.0 300.0 5.0"

# Set a TCP connection between node_(0) and node_(1)
set tcp [new Agent/TCP/Newreno]
$tcp set class_ 2
$ns attach-agent $node_($src_node) $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $node_($dest_node) $sink

$ns connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp






# Telling nodes when the simulation ends
for {set i 0} {$i < $val(nn) } { incr i } {
    $ns at $val(stop) "$node_($i) reset";
}

# ending nam and the simulation
$ns at 10.0 "$ftp start"
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 150.01 "puts \"end simulation\" ; $ns halt"
proc stop {} {
    global ns tracefd namtrace
    $ns flush-trace
    close $tracefd
    close $namtrace
    exec nam simwrls1.nam &
    exec awk -f aodv.awk simple-dsdv.tr > output.tr &
    exit 0
}

$ns run
