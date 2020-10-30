#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include <hls_math.h>

typedef union {
	unsigned int i;
	float f;
} conv;

struct s_data{
	unsigned int	data;
    ap_uint<1>		last;
};

void sigmoid(unsigned int size, bool deriv, hls::stream<s_data> &in, hls::stream<s_data> &result);
