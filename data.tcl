#-------Event scheduler object creation--------#

set ns [new Simulator]

#----------creating nam objects----------------#

set nf [open prog1.nam w]
$ns namtrace-all $nf

#----------creating trace objects----------------#

set nd [open prog1.tr w]
$ns trace-all $nd

#---------finish procedure--------#
proc finish { } {
global ns nf nd
$ns flush-trace
close $nf
close $nd
exec nam prog1.nam &
exec awk -f data.awk prog1.tr > output.tr &
exit 0
}

#----------Setting color ID----------------#

$ns color 1 darkmagenta
$ns color 2 yellow
$ns color 3 blue
$ns color 4 green
$ns color 5 black

#---------- Creating Network----------------#

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

set server 0
set router 1
set client1 2
set client2 3

#---------- Creating Duplex Link----------------#

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 512Kb 10ms DropTail
$ns duplex-link $n1 $n3 512Kb 10ms DropTail

$ns queue-limit $n1 $n2 5
$ns queue-limit $n1 $n3 5

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n1 $n2 orient right-down
$ns duplex-link-op $n1 $n3 orient right-up

#------------Labelling----------------#

$ns at 0.0 "$n0 label Server"
$ns at 0.0 "$n1 label Router"
$ns at 0.0 "$n2 label Client_1"
$ns at 0.0 "$n3 label Client_2"

$ns at 0.0 "$n0 color green"
$ns at 0.0 "$n2 color blue"
$ns at 0.0 "$n3 color blue"

$n0 shape hexagon
$n2 shape hexagon
$n3 shape hexagon

#------------Data Transfer between Nodes----------------#

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0


set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0


set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1


set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005
$cbr1 attach-agent $udp1


set sink [new Agent/Null]
$ns attach-agent $n2 $sink
$ns connect $udp0 $sink

set sink1 [new Agent/Null]
$ns attach-agent $n3 $sink1
$ns connect $udp1 $sink1

# Setting flow color

$udp0 set fid_ 4
$udp1 set fid_ 1

# data packet generation starting time
$ns at 0.2 "$cbr0 start"
$ns at 0.5 "$cbr1 start"

# data packet generation ending time
$ns at 4.5 "$cbr0 stop"
$ns at 4.7 "$cbr1 stop"

#Calling finish procedure
$ns at 5.0 "finish"
$ns run
