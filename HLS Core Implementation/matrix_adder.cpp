#include "m_adder.h"

void m_add(unsigned int row, unsigned int col, hls::stream<s_data> &inA, hls::stream<s_data> &inB, hls::stream<s_data> &result)
{
#pragma HLS INTERFACE s_axilite port=row bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=col bundle=CRTL_BUS
#pragma HLS INTERFACE axis port=inA
#pragma HLS INTERFACE axis port=inB
#pragma HLS INTERFACE axis port=result
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS


	for(int i = 0; i < row; i++)
	{
		conv tempA,tempB,tempC;
		s_data out;
		for(int j = 0; j < col; j++)
		{
#pragma HLS PIPELINE
			s_data A = inA.read();
			s_data B = inB.read();
			tempA.i = A.data;
			tempB.i = B.data;
			tempC.f = tempA.f + tempB.f;
			out.data  = tempC.i;
			out.last = A.last;
			result.write(out);
		}
	}
}

