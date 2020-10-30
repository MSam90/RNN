#include <stdio.h>
#include "dot_product.h"

int main()
{
	hls::stream<s_data> A;
	hls::stream<s_data> B;
	hls::stream<s_data> out;
	s_data input_A;
	s_data input_B;
	s_data output[8];

	for(float i = 0; i < HIDDEN; i++)
	{
		conv tempA;
		tempA.f = i/10;
		input_A.data = tempA.i;
		printf("input_A = %f\n",tempA.f);
		A << input_A;
	}

	for(float i = 0; i < HIDDEN; i++)
	{
		for(int j = 0; j < HIDDEN; j++)
		{
			conv tempB;
			tempB.f = i/10;
			input_B.data = tempB.i;
			printf("input_B[%d][%d] = %f\n",(int)i,j,tempB.f);
			B << input_B;
		}
	}

	dot_product(A, B, out);

	for(int i = 0; i < HIDDEN; i++)
	{
		conv temp0;
		out.read(output[i]);
		temp0.i = output[i].data;
		printf("temp0[%d] = %f\n",i,temp0.f);
	}

	return 0;
}
