### Instruction how to run Server on Linux (Raspberry Pi)

In terminal enter following commands:

1. Download source code from Github: (if you don’t have git install it) 

 `$ git clone https://github.com/mikemat/SmartHome-Server.git`

2.  Go into SmartHome-Server directory:

 `$ cd SmartHome-Server`

3. Compile file smart_home1.c 

  `$ gcc smart_home1.c -o smart_home1`

4. Run Server:

 `$ ./smart_home1 [Port Number]`
 for example:
 `$ ./smart_home1 12345`

 In terminal should be displayed information:

 `Server waiting >>>`

5. Now you can check out the Android application

 Enter appropriate commands and responses into application settings



Remember to forward 12345 port on router when you using public IP.
