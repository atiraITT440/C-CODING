import java.lang.*;
import java.io.*;
import java.net.*;

class Tcpserver{
	public static void main(String a[]){
		String data = "Hello Mrs Client!";

		try{
			ServerSocket server = new ServerSocket(1234);
			Socket socket = server.accept();

			System.out.print("Server has connected!\n");
		
			PrintWriter out = new PrintWriter(socket.getOutputStream(),true);
			System.out.print("Sending string : "+data+" \n");
			out.print(data);
			out.close();
			socket.close();
			server.close();
		}
		catch(Exception e){
			System.out.print("Oh Oh! it didn't work... \n");
		}
	}
}
