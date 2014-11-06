/*
 *  Stream Socket Server example for testing communication with Android SmartHome application 
 *  The following example allows to test:
 *  - Switch function
 *  - Temperature reader function
 *
 *  This example server program was tested on Olinuxino A20 (Debian) and Raspberry Pi.
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 

#define MAX 50

int main(int argc, char *argv[])
{
	// Checking passed port number:  
	if(argc < 2)
	{
		printf("Warning!\nMissing required argument.\n");
		printf("Usage:  %s <Server Port>\n", argv[0]);
		exit(1);
	}
	else if( argc > 2 )
	{
		printf("Warning!\nToo many arguments supplied.\n");
		exit(1);
	}

	
	/***********************
	 *    Socket Server    *
	 ***********************/

	char buffer[MAX];  //for receiving data from client
	char *message;	   //for sending message to client
	char *led_state;   //for keeping led state
	
	int server_sockfd, client_sockfd; 
	int server_len, client_len;
	struct sockaddr_in server_address; 
	struct sockaddr_in client_address;

	// Create socket for incoming connections
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sockfd < 0)  
	{
		perror("ERROR opening socket");
		exit(1);
	}

	// Initialize server address structure
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1])); //port nr
	server_len = sizeof(server_address);
	
	// Bind to the local address
	if ( bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0)
	{
		perror("ERROR on binding");
	    exit(1);
	}
	
	// Listen for incoming connections
	listen(server_sockfd, 5);

	// The function bzero() sets all values in a buffer to zero.
	bzero((char *) &server_address, sizeof(server_address));
	
	//on the starting server led state is off
	led_state = "led is off";
	
	int listening = 1;

	while(listening)
	{
		bzero(buffer,MAX);

		printf("\nServer waiting >>>\n");

		client_len = sizeof(client_address);
		// Wait for a client to connect
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
		if (client_sockfd < 0) 
		{
			perror("ERROR on accept");
			exit(1);
		}
		printf("Client connected\n");

		//Reading data from client
		read(client_sockfd, buffer, MAX-1);
		printf("Data received from client: %s\n",buffer);

		/*
		 * Switch function example
		 */
		// if data received from client is equal to command ledon
		if (strncmp("ledon",buffer,5)==0) {
			message = "led is on";  //response from server to client	
		    led_state = message;
			// Here you can add GPIO pin controlling
		}
		else if (strncmp("ledoff",buffer,6)==0) {
			message = "led is off";	
			led_state = message;
		    // Here you can add GPIO pin controlling
		}
		else if (strncmp("state",buffer,5)==0) {
			message = led_state;	
		    // Here you can add GPIO pin controlling
		}

		/*
		 * Temperature function example
		 */
		else if (strncmp("tempin",buffer,6)==0) {
			message = "24.5°C";
		    // Here you can add temperature inside reader
		}
		else if (strncmp("tempout",buffer,7)==0) {
			message = "18.2°C";
			// Here you can add temperature outside reader
		}

		/*
		 * Closing Server command
		 */
		// Command "server off" from client closing the server
		else if (strncmp("server off",buffer,10)==0) 
		{
			listening = 0;
			message = "server is closed";
		}

		else
		    message = "unknown command";
		
		
		printf("Sending message back to client: %s\n",message);
		// Sending message back to client
		write(client_sockfd,message,strlen(message));
		// Connection closed
		close(client_sockfd);
		printf("Connection closed\n");
	}

	printf("\n## Server closed ##\n\n");
	return 0;
}
