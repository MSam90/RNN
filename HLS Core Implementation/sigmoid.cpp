#include "sigmoid.h"

void sigmoid(unsigned int size, bool deriv, hls::stream<s_data> &in, hls::stream<s_data> &result)
{
#pragma HLS INTERFACE s_axilite port=size bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=deriv bundle=CRTL_BUS
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=result
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS

	for(int i = 0; i < size; i++)
	{
#pragma HLS PIPELINE
		conv tempA,tempC;
		s_data A = in.read();
		tempA.i = A.data;
		if(deriv == true)
		{
			tempC.f = tempA.f * (1.0 - tempA.f);
		}
		else if (deriv == false)
		{
			tempC.f = 1.0/(1.0 + exp(-tempA.f));
		}
		s_data out;
		out.data  = tempC.i;
		out.last = A.last;
		result.write(out);
	}
}
