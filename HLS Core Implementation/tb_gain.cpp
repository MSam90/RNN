#include "gain.h"

int main()
{
	hls::stream<s_data> input;
	hls::stream<s_data> output;

	for(int i = 0; i < 8; i++)
	{
		for(float j = 0; j < 8; j++)
		{
			conv in;
			in.f = j;
			s_data in2;
			in2.data = in.i;
			input << in2;
			printf("in[%d][%d] = %f\n",i,int(j),in.f);
		}
	}

	conv temp_gain;
	temp_gain.f = -0.1;

	gain_mult(8, 8, temp_gain, input, output);

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			s_data out;
			output.read(out);
			conv out2;
			out2.i = out.data;
			printf("out2[%d][%d] = %f\n",i,j,out2.f);
		}
	}
}
