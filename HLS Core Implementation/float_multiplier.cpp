#include "float_multiplier.h"
#define HIDDEN 8

void m_multi(bool type, unsigned int rowA, unsigned colA, unsigned int rowB, unsigned int colB, hls::stream<s_data> &inA, hls::stream<s_data> &inB, hls::stream<s_data> &result)
{
#pragma HLS INTERFACE s_axilite port=rowA bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=colA bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=rowB bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=colB bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=type bundle=CRTL_BUS
#pragma HLS INTERFACE axis port=inA
#pragma HLS INTERFACE axis port=inB
#pragma HLS INTERFACE axis port=result
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS

	s_data in_A[HIDDEN][HIDDEN];
	s_data in_B[HIDDEN][HIDDEN];
	s_data out_C[HIDDEN][HIDDEN];
	s_data c;
	conv A,B,C;

	if(type == true)
	{

		for(int i = 0; i < rowA; i++)
		{
	#pragma HLS PIPELINE
			for(int j = 0; j < colA; j++)
				in_A[i][j] = inA.read();
		}

		for(int i = 0; i < rowB; i++)
		{
	#pragma HLS PIPELINE
			for(int j = 0; j < colB; j++)
				in_B[i][j] = inB.read();
		}

		for(int i = 0; i < rowA; i++)
		{
	#pragma HLS PIPELINE
			for(int j = 0; j < colB; j++)
			{
				C.f = 0.0;
				for(int k = 0; k < rowB; k++)
				{
					A.i = in_A[i][k].data;
					B.i = in_B[k][j].data;
					C.f += A.f * B.f;
				}
				out_C[i][j].last = 0;
				out_C[i][j].data = C.i;
			}
		}

		for(int i = 0; i < rowA; i++)
		{
			for(int j = 0; j < colB; j++)
			{
				if((i == rowA-1) && (j == colB-1))
					out_C[i][j].last = 1;
				result.write(out_C[i][j]);
			}
		}
	}
	else if(type == false)
	{
		for(int i = 0; i < rowA; i++)
		{
			conv tempA,tempB,tempC;
			s_data out;
#pragma HLS PIPELINE
			s_data A = inA.read();
			s_data B = inB.read();
			tempA.i = A.data;
			tempB.i = B.data;
			tempC.f = tempA.f * tempB.f;
			out.data  = tempC.i;
			out.last = A.last;
			result.write(out);
		}
	}



}
