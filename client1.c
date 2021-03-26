#include <stdio.h>    //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h>    //inet_addr
#include <unistd.h>

int main(int argc , char *argv[])
{
    int sock, num, f=0, cont=0;
    int llista[25];
    for (int n=0; n<25; n++){
        llista[n]=NULL;
    }
    struct sockaddr_in server;
    char message[1] , server_reply[1],guanyador[1];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
   char name[20];
   // Demanem al usuari que introdueixi la ip
    printf("Enter IP: (127.0.0.1) ");
    scanf("%s", name);
    server.sin_addr.s_addr = inet_addr(name);
    server.sin_family = AF_INET;
    int var;
    //demanem que introdueixi el socket
	printf("Enter the to bind the sockets");
        scanf("%d", &var);
	server.sin_port = htons( var );
    server.sin_port = htons( var );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    //imprimim la graella
    puts("Connected\n");
    
    //keep communicating with server
    while(strcmp(message,"00") != 0)
    {   
        if (cont==0){
        printf("\n");
            cont=3;
            }

        else {
        //imprimim la graella amb les posicions de cada jugador
	    printf("\n");
	    }
	    //-Preguntem al usuari quin numero vol introduir
    
        printf("enter the number you want to select (1,25): ");
        scanf("%s" , message);
        //el passem a int
        num = atoi(message);
        printf("%d\n", num);
                //mirem que estigui entre 1 i 25
        while (num<1 && num>25){
            printf("Wrong number, please select an other: ");
            scanf("%s" , message);
            num = atoi(message);
        }   
        //Mirem que no s'hagi afegit ya
        while (llista[num-1]!=NULL){
            printf("Number marked, please select an other");
            scanf("%s" , message);
            num = atoi(message);
        }   
        //marquem el numero
        llista[num-1]=2;                    //1=servidor i 2=client
        
        
        //Enviem el numero que volem marcar al server
        if( send(sock , message , 3 , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        //Receive a message from the server
        if( recv(sock , server_reply , 3, 0) < 0)
        {
            puts("recv failed");
            break;
        }   strcpy(guanyador, server_reply); 

        //mirem si es un numero 
        if(atoi(server_reply)==0){
        //sino es un numero sortiem del while
        //sino es un numero vol dir que el arbit ha decidit que acabi
                strcpy(message, "00"); 
            close(sock);
        }
        else{
        //marquem el numero
        num = atoi(server_reply);
        llista[num-1]=1;                    //1=servidor i 2=client
        
        puts("Server reply :");

        
        //print graella i comprovar guanyador
        }
    }
//imprimim el resultat del arbitre
    printf("******************************************\n");
	if(guanyador[0]=='s'){
		printf("YOU HAS LOSE\n");
	}
	else if(guanyador[0]=='c'){
	printf("YOU HAS WIN\n");
	}
	else{
		printf("YOU HAS DRAW\n");
	}
	
	printf("******************************************\n");
    
    return 0;
}
