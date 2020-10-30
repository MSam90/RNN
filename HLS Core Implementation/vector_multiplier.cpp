#include "vector_multiplier.h"

void v_mul(unsigned int rows, hls::stream<s_data> &inA, hls::stream<s_data> &inB, hls::stream<s_data> &result)
{
#pragma HLS INTERFACE s_axilite port=rows bundle=CRTL_BUS
#pragma HLS INTERFACE axis port=inA
#pragma HLS INTERFACE axis port=inB
#pragma HLS INTERFACE axis port=result
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS


	for(int i = 0; i < rows; i++)
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

