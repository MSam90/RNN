#include "dot_product.h"

void dot_product(hls::stream<s_data> &inA, hls::stream<s_data> &inB, hls::stream<s_data> &result)
{
#pragma HLS INTERFACE axis port=inA
#pragma HLS INTERFACE axis port=inB
#pragma HLS INTERFACE axis port=result
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS

	s_data inA_container[HIDDEN];
	s_data inB_container[HIDDEN][HIDDEN];
	s_data result_container[HIDDEN];

	for(int i = 0; i < HIDDEN; i ++)
	{
#pragma HLS PIPELINE
		inA_container[i] = inA.read();
	}


	for(int i = 0; i < HIDDEN; i ++)
	{
		for(int j = 0; j < HIDDEN; j ++)
		{
#pragma HLS PIPELINE
			inB_container[i][j] = inB.read();
		}
	}

	for(int i = 0; i < HIDDEN; i++)
	{
		conv tempA, tempB, tempR;
		tempA.i = 0;
		tempB.i = 0;
		tempR.i = 0;
		for(int j = 0; j < HIDDEN; j++)
		{
			tempA.i = inA_container[j].data;
			tempB.i = inB_container[j][i].data;
#pragma HLS PIPELINE
			tempR.f += tempA.f * tempB.f;
		}
		result_container[i].data = tempR.i;
		result_container[i].last = inA_container[i].last;
	}

	for(int i = 0; i < HIDDEN; i++)
		result.write(result_container[i]);
}
