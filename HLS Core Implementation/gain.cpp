#include "gain.h"

void gain_mult(unsigned int row, unsigned int col, conv gain, hls::stream<s_data> &in, hls::stream<s_data> &result)
{
#pragma HLS INTERFACE s_axilite port=row bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=col bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=gain bundle=CRTL_BUS
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=result
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS


	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
#pragma HLS PIPELINE
			conv temp_input;
			s_data output;
			s_data input = in.read();
			temp_input.i = input.data;
			temp_input.f = temp_input.f * gain.f;
			output.data = temp_input.i;
			output.last = input.last;
			result.write(output);
		}
	}

}
