#include<stdio.h>
#include "vector_multiplier.h"

int main()
{

	hls::stream<s_data> inputA;
	hls::stream<s_data> inputB;
	hls::stream<s_data> output;
	int row = 8;
	conv out_print[row];


	for(float i = 0; i < row; i++)
	{
			conv a,b;
			a.f = i/10;
			b.f = i/10;
			printf("a.f,b.f = %f\n",a.f);
			s_data A,B;
			A.data = a.i;
			B.data = b.i;
			inputA << A;
			inputB << B;
	}

	v_mul(row, inputA, inputB, output);

	for(int i = 0; i < row; i++)
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
