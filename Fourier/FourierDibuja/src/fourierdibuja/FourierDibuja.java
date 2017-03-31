
package fourierdibuja;
import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 *
 * @author Angeles Cerritos
 */
public class FourierDibuja {
    public static final int YSIZE = 600;
    public static final int XSIZE = 800;
    
    public static void main(String[] args) {
        Comunicador c = new Comunicador();
        
        int enviados = 0;
        for (int j= 1; j < 6; j+=2)
	{
		for (double i = -Math.PI; i < Math.PI; i+=.0001)
		{
			int x , y = 0;
			x = (int)(i*100 + XSIZE/2);

			for (int n = 1; n <= j; n+=2)
			{
				double bn = 4/(Math.PI*n);
				double y_aux=-1*(bn*Math.sin(n*i)*200);
				y += y_aux;
			}
                        
			c.setCoord(x, y+YSIZE/2);
                        System.out.println("X: " + c.x + " Y: " + c.y);
                        c.enviarMensaje("192.168.43.172", 7000);
                        enviados++;
		}
	}
        System.out.println("Se han enviado " + enviados + " paquetes");
    }
    
    
    
}
