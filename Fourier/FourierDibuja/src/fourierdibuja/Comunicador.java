
package fourierdibuja;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStreamWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;

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
                
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                
                Integer xo = x;
                String xs = xo.toString();
                
                Integer yo = y;
                String ys = yo.toString();
                
                String msj = xs + "?" + ys;
                byte [] buf = msj.getBytes();
                System.out.println(buf.length);
                    
                DatagramPacket p = new DatagramPacket(buf, buf.length, InetAddress.getByName(ip), puerto);
                s.send(p);
                
                //System.out.println("Se ha enviado");
                s.close();
                
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