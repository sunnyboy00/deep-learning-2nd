/*
    Copied and Pasted by Jay (JongYoon) Kim, jyoon95@gmail.com 
*/
#pragma once

#include "common.h"

namespace TDNN_Models {

	// Neural Network for Command-Line Breakout
	void cl_breakout_net(network<sequential>& nn, 
						tiny_dnn::core::backend_t backend_type,
						const int& height,
						const int& width, 
  						const int& input_channel_nums, 
  						const int& output_nums){


		assert(height > 0 && width > 0 && input_channel_nums > 0 && output_nums > 0 );

		//typedef convolutional_layer<tan_h> conv;
		//typedef max_pooling_layer<relu> pool;

		//core::backend_t backend_type = core::default_engine();

		//const int height = 20;
	    //const int width = 20;
	    //const int input_channel_nums = 4;
	    //const int output_nums = 3;

		const int kernel_size = 5;					// 5*5 kernel
		const int n_fmaps = height;		//< number of feature maps for upper layer
		const int n_fmaps2 =height*2;	//< number of feature maps for lower layer
		const int n_fc =height*2;		//< number of hidden units in fully-connected layer

		nn	<< conv(height, width, kernel_size, input_channel_nums, n_fmaps, padding::same, true, 1, 1, backend_type)
			 << pool(height, width, n_fmaps, 2)
			 << relu()
			 << conv(height/2, width/2, kernel_size, n_fmaps, n_fmaps2, padding::same, true, 1, 1, backend_type)
			 << pool(height/2, width/2, n_fmaps2, 2)
			 << relu()
			 << fully_connected_layer(height/4 * width/4 * n_fmaps2, n_fc, true, backend_type)
			 << relu()
			 << fully_connected_layer(n_fc, output_nums, true, backend_type)
			 << elu() //leaky_relu()
			 //<< softmax(output_nums)
			 ;
	}  

}  // namespace TDNN_Models


// end of file
