
package fourierdibuja;

import javax.swing.JOptionPane;

/**
 *
 * @author Angeles Cerritos
 */
public class FourierDibuja {
    public static final int YSIZE = 600;
    public static final int XSIZE = 800;
    
    public static void main(String[] args) {
        
        int op = JOptionPane.showConfirmDialog(null, "Dibujar -> Si \nBorrar -> No", "Elija una opcion", JOptionPane.YES_NO_OPTION);
        
        
        Comunicador c = new Comunicador();
        c.opt = (char)(op + '0');
        System.out.println("Opcion: " + c.opt);
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
                        c.enviarMensaje("10.100.70.185", 7000);
                        enviados++;
		}
	}
        System.out.println("Se han enviado " + enviados + " paquetes");
    }
    
    
    
}
