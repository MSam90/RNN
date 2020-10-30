#include<stdio.h>
#include "sigmoid.h"

int main()
{

	hls::stream<s_data> inputA;
	hls::stream<s_data> output;
	unsigned int size = 10;
	bool deriv = true;
	conv out_print[size];


	for(float i = 0; i < size; i++)
	{
			conv a;
			a.f = i/10;
			printf("a.f = %f\n",a.f);
			s_data A,B;
			A.data = a.i;
			inputA << A;

	}

	sigmoid(size, deriv,inputA, output);

		for(int i = 0; i < size; i++)
		{
			s_data c;
			conv c_temp;
			output.read(c);
			c_temp.i = c.data;
			out_print[i].f = c_temp.f;
			printf("out_print[%d] = %f\n",i,out_print[i].f);
		}

	return 0;
}
