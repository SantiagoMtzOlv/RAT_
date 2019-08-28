
package clientejava;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

// Código de ejemplo para proyecto final
//Por favor estudie y profundice en la comprensión del tema de comunicaciones  (TCP)
// y uso de sockets
public class ClienteJava {



    private final static int PUERTO = 2400;
    private final static String SERVIDOR = "192.168.43.192";
    public static Socket clientSocket; 
    public static BufferedReader brRequest;
    public static PrintStream toServer;
    public static InputStream stream;
    public static String request;
    public static String received;
    
    /**
     * @param args the command line arguments
     * @throws java.lang.ClassNotFoundException
     */
    public static void main(String[] args) throws ClassNotFoundException {                
        //Socket para la comunicacion cliente servidor                        
        try{
            System.out.println("Cliente Inicializado");
            while( true ){//ciclo repetitivo     
                //abre socket   
                clientSocket = new Socket(SERVIDOR,PUERTO);
                //Para leer lo que escriba el usuario                       
                 brRequest = new BufferedReader(new InputStreamReader(System.in));
                //para imprimir datos del servidor
                toServer = new PrintStream(clientSocket.getOutputStream());
                //Para leer lo que envie el servidor      
                stream = clientSocket.getInputStream();  
                //mensaje para el cliente
                System.out.println("Introdusca un simbolo:");
                //captura comando escrito por el usuario
                request = brRequest.readLine();    
                //manda al servidor
                toServer.println(request); 
                //lee respuesta del servidor
                byte[] bytes = new byte[256];
                stream.read(bytes,0,256);
                //convierte a string
                received = new String(bytes,"UTF-8");           
                //imprime en pantalla
                System.out.println("Servidor " + request + " = " + received.trim());
                return;
            }
        }catch(IOException | NumberFormatException ex){            
            System.out.println(ex.getMessage());
        }
        
    }

    
    
}

