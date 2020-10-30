#include "float_multiplier.h"
#include <stdio.h>

int main()
{
	hls::stream<s_data> inputA,inputB,outputC;
	s_data inA,inB,outC;
	conv a,b,c;
	conv prev_layer_1[8];
	conv layer_1_delta[8];

	prev_layer_1[0].f = 0.812890;
	prev_layer_1[1].f = 0.853727;
	prev_layer_1[2].f = 0.712038;
	prev_layer_1[3].f = 0.134889;
	prev_layer_1[4].f = 0.415155;
	prev_layer_1[5].f = 0.629588;
	prev_layer_1[6].f = 0.793653;
	prev_layer_1[7].f = 0.576319;

	layer_1_delta[0].f = 0.000126;
	layer_1_delta[1].f = 0.000104;
	layer_1_delta[2].f = 0.000170;
	layer_1_delta[3].f = 0.000097;
	layer_1_delta[4].f = 0.000202;
	layer_1_delta[5].f = 0.000194;
	layer_1_delta[6].f = 0.000136;
	layer_1_delta[7].f = 0.000203;




	for(float i = 0; i < 8; i++)
	{
		for(float j = 0; j < 1; j++)
		{
			a.f = i;
			inA.data = a.i;
			inputA << inA;
			printf("A[%d][%d] = %f\n",int(i),int(j),a.f);
		}
	}


	for(float i = 0; i < 1; i++)
	{
		for(float j = 0; j < 8; j++)
		{
			b.f = j;
			inB.data = b.i;
			inputB << inB;
			printf("B[%d][%d] = %f\n",int(i),int(j),b.f);
		}
	}


	m_multi(true,8,1,1,8,inputA,inputB,outputC);

	for(int i = 0; i < 8*8; i++)
	{
		outputC.read(outC);
		c.i = outC.data;
		printf("c.f[%d] = %f\n",i,c.f);
	}
	return 0;
}
