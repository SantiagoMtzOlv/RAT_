#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>//
#include <unistd.h>//Libreria que contiene funciones para el manejo de directorios y archivos.
#include <time.h>//

	int open_socket();
	void bind_to_port(int ,int);//
	

	

int main()
{

	/*Datos de fecha y hora*/
	time_t tiempo=time(0);
	struct tm *tlocal=localtime(&tiempo);
	

	const int port=2400;
	char*Array_hola[]={"Hola\n"};
					
	int listener=open_socket();//creando primer socket que estara escuchando

	if(listener==-1)
	{
		printf("Error en el listener\n");
		

	}

	bind_to_port(listener,port);

	if(listen (listener,10)==-1)
	{
		printf("No es posible escuchar en ese puerto\n");
		
	}



	struct sockaddr_storage client;
		unsigned int addres_size=sizeof(client);
		printf("Servidor conectado\n");
		printf("Esperando conexion del cliente\n");
		int connect=accept(listener, (struct sockaddr*) &client, &addres_size);
		if(connect==-1)
		{
			printf("No se puede conectar el socket \n");
		}	

	                  

	while(1)
	{
                char ch[100];
		char s[]={"Adios ;)"};
		char f[]={"Fecha: "};
		char ser[]={"Servidor: "};
		char cli[]={"Cliente: "};
      
                
  		printf("Conexion Exitosa\n");
		printf("Cliente....\n");
                *ch=' ';
		read(connect, &ch,sizeof(ch));
		printf("El cliente Envio:  %s\n",ch);
		send(connect,cli,strlen(cli),0);
		send(connect,ch,strlen(ch),0);
                
 if (*ch=='S')//salir
               {
		send(connect,&s,strlen(s),0);
     		close(connect);
		return 0;
  		}

if(*ch=='M'){//mensaje al cliente
			char*msg=Array_hola[rand() %5];
			send(connect,ser,strlen(ser),0);
			send(connect,msg,strlen(msg),0);
			msg=NULL;
		    	    }
if(*ch=='C'){//mensaje al cliente
			char*msg=Array_hola[rand() %5];
			send(connect,ser,strlen(ser),0);
			send(connect,msg,strlen(msg),0);
			printf(":D :) :o xD");
		    	    }
if(*ch=='F')//fecha
		{
		*ch=' ';
		char fecha[128];
		strftime(fecha, 128, "%d/%m/%y",tlocal);
		send(connect,ser,strlen(ser),0);
		send(connect,f,strlen(f),0);
		send(connect,fecha,strlen(fecha),0);
		printf("Fecha: %s\n",fecha);
		return 0;
		}
}//terminando la conexion del cliente
	return 0;
}



		

/*socket*/

int open_socket()
{
	int s=socket(PF_INET,SOCK_STREAM,0);
	if(s == -1)
		printf("Error al abrir socket\n");
	return s;

}

void bind_to_port(int socket,int port)
{
	struct sockaddr_in name;//Nos referimos a la máquina que aloja el servidor para la conexión. 
	name.sin_family=PF_INET;
	name.sin_port=(in_port_t)htons(port);
	name.sin_addr.s_addr=htonl(INADDR_ANY); 
	int reuse=1;
	if(setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char*) &reuse,sizeof(int))==-1)//
	{
		perror("NO es posible usar el sockets\n");
	}

	int c=bind(socket,(struct sockaddr*) &name, sizeof(name));

	if(c==-1)
	{
		perror("NO se puede enlazar el puerto\n");
	}
}
	
