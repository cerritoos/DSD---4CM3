#ifndef HORA_H
#define HORA_H

class Hora{
	private:
		short hr;
		short min;
		short seg;
		short dec;

	public:
		Hora();
		Hora(short, short, short, short);
		short getHr();
		short getMin();
		short getSeg();
		short getDec();
		void setHr(short);
		void setMin(short);
		void setSeg(short);
		void setDec(short);
		char * toString();
};

#endif