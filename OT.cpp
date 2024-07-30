#include <iostream>
using namespace std;
#include</usr/local/include/emp-tool/emp-tool.h> // for NetIO, etc
#include</usr/local/include/emp-ot/emp-ot.h>   // for OTs


int main(int argc, char **argv) {
  	int length, port, party; // make sure all functions work for non-power-of-two lengths
    if (argc <= 3)
		length = (1<<20) + 101;
	else
		length = (1<<atoi(argv[3])) + 101;
    block b0[length], b1[length];
    bool c[length];
    NetIO io(party==ALICE ? nullptr:"127.0.0.1", port); // Create a network with Bob connecting to 127.0.0.1
    OTNP<NetIO> np(&io); // create a Naor Pinkas OT using the network above
     if (party == ALICE)
// ALICE is sender, with b0[i] and b1[i] as messages to send
         np.send(b0, b1, length); 
    else
// Bob is receiver, with c[i] as the choice bit 
// and obtains b0[i] if c[i]==0 and b1[i] if c[i]==1
         np.recv(b0, c, length);

  return 0;
}

