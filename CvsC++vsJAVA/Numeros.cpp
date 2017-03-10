#include <bits/stdc++.h>

using namespace std;
int main()
{
	double i=0,seno=0,coseno=0,tangente=0,logaritmo=0,raizCuad=0;
	double max = 1000000;
	while(i<max)
	{
		seno+= sin(i);
		coseno += cos(i);
		tangente += tan(i);
		logaritmo += log10(i);
		raizCuad += sqrt(i);
		i++;
	}

	cout << seno << endl;
	cout << coseno << endl;
	cout << tangente << endl;
	return 0;
}