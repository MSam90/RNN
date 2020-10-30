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

#define HIDDEN 8

void dot_product(hls::stream<s_data> &inA, hls::stream<s_data> &inB, hls::stream<s_data> &result);
