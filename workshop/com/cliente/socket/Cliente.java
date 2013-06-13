package com.cliente.socket;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 *
 * @Jose Luis
 */
public class Cliente{

    public void establishConnection() {
        try {
            Socket s = new Socket("127.0.0.1", 3550);
            InputStreamReader stream = new InputStreamReader(s.getInputStream());
            BufferedReader reader = new BufferedReader(stream);
            String str = reader.readLine();
            System.out.println("text received from client: " + str);
            
            
            
            DataOutputStream out = new DataOutputStream(s.getOutputStream());
            BufferedReader dat = new BufferedReader(stream);
            PrintWriter pw = new PrintWriter(out);
            String read = reader.readLine();
            pw.print("HOLA");
            pw.flush();
            //System.out.println("output" + read);
            
            
            Thread.sleep(200);
            DataInputStream in = new DataInputStream(s.getInputStream());
            BufferedReader red = new BufferedReader(stream);
            char[] buffer = new char[300];
            int count = red.read(buffer,0,300);
            String reply = new String(buffer,0,count);
            String lin = reader.readLine();
            System.out.println("input" + reply);
            
            s.close();
            reader.close();
            stream.close();
            out.close();
            dat.close();
            in.close();
            red.close();
            
            
        } catch (IOException e) {
            e.printStackTrace();
        } catch (java.lang.InterruptedException e){
        	e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new Cliente().establishConnection();
    }
}
