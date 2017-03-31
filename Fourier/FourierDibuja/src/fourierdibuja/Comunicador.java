
package fourierdibuja;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 *
 * @author Angeles Cerritos
 */
public class Comunicador {
    DatagramSocket s;
    int x, y;
    


    public void enviarMensaje(String ip, int puerto)
    {
        try
            {
                s = new DatagramSocket();
                
                Integer xo = x;
                byte [] buf = (xo.toString()).getBytes();
                DatagramPacket p = new DatagramPacket(buf, buf.length, InetAddress.getByName(ip), puerto);
                s.send(p);
                Integer yo = y;
                
                buf = (yo.toString()).getBytes();
                p = new DatagramPacket(buf, buf.length, InetAddress.getByName(ip), puerto);
                s.send(p);
                
                //System.out.println("Se ha enviado");
                s.close();
                
                Thread.sleep(5);
            }
            catch(Exception e)
            {e.printStackTrace();}

    }
    
    public void setCoord(int xx, int yy)
    {
        x = xx;
        y = yy;
    }
    
    public void recibirMensaje()
    {
     /*   
        try
        {
            s = new DatagramSocket(puertoU);
            //cl.setReuseAddress(true);
            DatagramPacket rec = new DatagramPacket(new byte[1024], 1024);
            s.receive(rec);
            ObjectInputStream ois = new ObjectInputStream(new ByteArrayInputStream(rec.getData()));
            recibido = (Mensaje)ois.readObject();
            s.close();
        }
        catch(Exception e)
        { e.printStackTrace();}*/
    }

}