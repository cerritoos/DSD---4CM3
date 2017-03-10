#include <iostream>
2  using namespace std;
3
4  class Fecha
5  {
6  private:
7     int dia;
8     int mes;
9     int anio;
10 public:
11    Fecha(int = 3, int = 4, int = 2014);
12    void inicializaFecha(int, int, int);
13    void muestraFecha();
14 };
15
16 Fecha::Fecha(int dd, int mm, int aaaa)
17 {
18    mes = mm;
19    dia = dd;
20    anio = aaaa;
21 }
22
23 void Fecha::inicializaFecha(int dd, int mm, int aaaa)
24 {
25    anio = aaaa;
26    mes = mm;
27    dia = dd
;   
28    return;
29 }
30 
31 void Fecha::muestraFecha()
32 {
33    cout << "La fecha es(dia
-
mes
-
año): " << dia << "
-
" << mes << "
-
" << anio << endl;
34    return;   
35 }
36
37 int main()
38 {
39    Fecha a, b, c(21, 9, 1973);
40   
41    b.inicializaFec
ha(17, 6 , 2000);
42    a.muestraFecha();
43    b.muestraFecha();
44    c.muestraFecha();      