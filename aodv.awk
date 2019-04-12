BEGIN {

dcount = 0;

rcount = 0;

}

{

event = $1;

if(event == "d")

{

dcount++;

}

if(event == "r")

{

rcount++;

}

}

END {

printf(" packets dropped  : %d\n ",dcount);

printf("packets recieved : %d\n ",rcount);

}
