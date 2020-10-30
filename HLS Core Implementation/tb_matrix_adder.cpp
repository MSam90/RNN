#include<stdio.h>
#include "m_adder.h"

int main()
{

	hls::stream<s_data> inputA;
	hls::stream<s_data> inputB;
	hls::stream<s_data> output;
	int row = 8;
	int col = 8;
	conv out_print[row][col];


	for(float i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
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
	}

	m_add(row, col, inputA, inputB, output);

	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			s_data c;
			conv c_temp;
			output.read(c);
			c_temp.i = c.data;
			out_print[i][j].f = c_temp.f;
			printf("out_print[%d][%d] = %f\n",i,j,out_print[i][j].f);
		}
	}

	return 0;
}
