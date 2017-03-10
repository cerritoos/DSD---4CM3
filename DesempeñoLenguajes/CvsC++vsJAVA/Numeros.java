public class Numeros
{
	public static void  main(String[] args)
	{
		double i=0,seno=0,coseno=0,tangente=0,logaritmo=0,raizCuad=0;
		double max = 1000000;
		while(i<max)
		{
			seno+= Math.sin(i);
			coseno += Math.cos(i);
			tangente += Math.tan(i);
			logaritmo += Math.log10(i);
			raizCuad += Math.sqrt(i);
			i++;
		}
	}
}