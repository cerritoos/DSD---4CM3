import java.util.Random;

public class java {
    public static void main(String arg[ ]) {
    	String cadenota="", cadena="";
    	Random rnd=new Random();
    	for (int j=0; j<878800; j++) {
    		for(int i=0;i<4;i++)
    			cadena+=(rnd.nextDouble()*25+65);
    		cadenota+=cadena;
		}
		while (cadenota.indexOf("IPN") > -1) {
			cadenota = cadenota.substring(cadenota.indexOf("IPN")+4,cadenota.length());
    	}
    }
}