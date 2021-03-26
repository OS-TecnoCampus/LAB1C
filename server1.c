#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size, f=0, num;
	int llista[25];
	char guanyador[1];
    char array[100];
    for (int n=0; n<25; n++){
        llista[n]=NULL;
    }
	struct sockaddr_in server , client;
	char client_message[1];
	char message[1];
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	int var;
	printf("Enter the to bind the sockets");
        scanf("%d", &var);
	server.sin_port = htons( var );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
    puts("Waiting for clients message...");
    
        recv(client_sock , client_message , 3 , 0);
    puts("Clients reply :");
	puts(client_message);
    num = atoi(client_message);
        llista[num-1]=2;
          
	
	
	
	while( strcmp(client_message,"00") != 0) 
	{
	//preguntem al arbitre si el partit ha acabat
	    printf( "Referee: Type S if the game ended is not end type another char\n");
        scanf("%s", array);
        //Si ha acabt entrem en el if
            if (strcmp(array,"S")== 0){
            //demanem al arbitre que ens indiqui el guanyador
            printf( "Type s if the sever has win, type c if the client has win or type 3 if they draw\n");
            scanf("%s" , guanyador);
            //li enviem el guanyador al client fem confiança que hagi introduit correctament qui vol que guanyi
            send(client_sock ,  guanyador, 3,0);
            strcpy(client_message, "00");    
            }
            else {
            //si el arbitre decideix que no s'ha acabat el joc
            //introduiem el numero que volem marcar
            printf("enter the number you want to select(1,25): ");
		    scanf("%s" , message);
            num = atoi(message);
            //mirem que estigui en el rang
            while (num<1 && num>25){
                printf("Wrong number, please select an other(1,25):\n ");
                scanf("%s" , message);
                num = atoi(message);
            }   
            //mirem que el numero no estigui marcat
        while (llista[num-1]!=NULL){
            printf("Number marked, please select an other ");
            scanf("%s" , message);
            num = atoi(message);
        }   
        llista[num-1]=1;                    //1=servidor i 2=client
		
		
		//enviem el numero
		send(client_sock ,  message, 3,0);
		//recivim el numero del client
		 recv(client_sock , client_message , 3 , 0);
		 //marquem el numero
        num = atoi(client_message);
        llista[num-1]=2;                    //1=servidor i 2=client
        
        
	    
	
	    }
	
	}
		 close(socket_desc);
		    //imprimir resultat arbitre
		printf("******************************************\n");
	if (strcmp(guanyador,"s")== 0){
	printf("YOU HAS WIN\n");
	}
	else if (strcmp(guanyador,"c")== 0){
	printf("YOU HAS LOSE\n");
	}
	else{
		printf("YOU HAS DRAW\n");
	}
	
	printf("******************************************\n");
	return 0;
}
