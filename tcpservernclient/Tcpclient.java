import java.lang.*;
import java.io.*;
import java.net.*;

class Tcpclient{
	public static void main(String a[]){

		try{
			Socket socket = new Socket("localhost",1234);

			BufferedReader in = new BufferedReader (new InputStreamReader(socket.getInputStream()));

			System.out.print("Received string! ");

			while(!in.ready()){}
			System.out.print(in.readLine());

			System.out.print("'\n'");
			in.close();
		}
		catch(Exception e){
			System.out.print("Oh Oh! it didn't work... \n");
		}
	}
}
