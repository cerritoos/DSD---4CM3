public class Cadenas{
	
	private static String cadena = new String();
	public static final int TOKENS = 70304;

	public static void main(String args[])
	{
		generar_cadena();
		System.out.println("Veces encontrado : " + buscar_cadena());

	}

	public static  void generar_cadena()
	{
		char a, b, c;
		for(int i = 0; i < TOKENS; i++)
		{
			a = (char)(Math.random()*26 + 65);
			b = (char)(Math.random()*26 + 65);
			c = (char)(Math.random()*26 + 65);

			cadena += a;
			cadena += b;
			cadena += c;
			cadena += " ";
		}

	}

	public static int buscar_cadena()
	{
		int pos = 0;
		int found = -2;
		int found_times = 0;
		while(found != -1)
		{
			found = cadena.indexOf("IPN", pos);
			if( found > -1)
			{
				pos = found + 4;
				found_times = found_times + 1;
			}
		}

		return found_times;

	}

}