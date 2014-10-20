### SmartHome Server

Source in file `smart_home1.c` is Linux Server program for testing connection with Android application. For testing application you don‘t need to connect any peripherial devices (relays an temperature sensors) to singleboard. 

==
#### Instruction how to run Server on Linux (Raspberry Pi)

In terminal enter following commands:

1. Download source code from Github:

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

 Enter appropriate text commands and responses into application settings

Network settings and Temperature commands:
![](./SettingScreens/settings.png =100x20)
<img src="https://raw.githubusercontent.com/mikemat/SmartHome-Server/eda8d43080a7dfa88ecf49c76bb09dcddf951e93/SettingScreens/settings.png" alt="Drawing" style="width: 200px;"/>

Switch1 commands
![](https://github.com/mikemat/SmartHome-Server/blob/master/SettingScreens/switch1.png)

==
###### Additional commands


Check if Server process is running: 

`$ sudo netstat -anltp | grep "LISTEN"`

Kill Server process:

`$ sudo killall -9 smart_home1`

<br>
Remember to forward 12345 port on router when you using public IP.
