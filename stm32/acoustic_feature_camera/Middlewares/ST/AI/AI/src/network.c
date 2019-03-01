/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Fri Mar  1 15:19:58 2019
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */



#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 3
#define AI_TOOLS_VERSION_MINOR 3
#define AI_TOOLS_VERSION_MICRO 0

#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 1
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "67508ec4aaa91b04ead55738bff93a31"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Fri Mar  1 15:19:58 2019"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network arrays declarations  *************************************/
AI_STATIC ai_array input_0_output_array;   /* Array #0 */
AI_STATIC ai_array conv2d_26_output_array;   /* Array #1 */
AI_STATIC ai_array conv2d_27_output_array;   /* Array #2 */
AI_STATIC ai_array conv2d_28_output_in_array;   /* Array #3 */
AI_STATIC ai_array conv2d_28_output_out_array;   /* Array #4 */
AI_STATIC ai_array dense_9_output_array;   /* Array #5 */
AI_STATIC ai_array dense_9_nl_output_array;   /* Array #6 */


/**  Forward network tensors declarations  ************************************/
AI_STATIC ai_tensor input_0_output;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_26_output;   /* Tensor #1 */
AI_STATIC ai_tensor conv2d_27_output;   /* Tensor #2 */
AI_STATIC ai_tensor conv2d_28_output_in;   /* Tensor #3 */
AI_STATIC ai_tensor conv2d_28_output_out;   /* Tensor #4 */
AI_STATIC ai_tensor dense_9_output;   /* Tensor #5 */
AI_STATIC ai_tensor dense_9_nl_output;   /* Tensor #6 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_26_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_27_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_28_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_9_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_9_nl_chain;   /* Chain #4 */


/**  Subgraph network operators tensor chain declarations  *********************************/


/**  Subgraph network operators declarations  *********************************/


/**  Forward network layers declarations  *************************************/
AI_STATIC ai_layer_conv2d_nl_pool conv2d_26_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_27_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_28_layer; /* Layer #2 */
AI_STATIC ai_layer_dense dense_9_layer; /* Layer #3 */
AI_STATIC ai_layer_sm dense_9_nl_layer; /* Layer #4 */


/**  Arrays declarations section  *********************************************/
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 3840,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_26_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 3572,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_27_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 1408,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_28_output_in_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 480,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  conv2d_28_output_out_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 480,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_9_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 7,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_9_nl_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 7,
  AI_STATIC)


/**  Activations tensors declaration section  *********************************/
AI_TENSOR_OBJ_DECLARE(
  input_0_output,
  AI_SHAPE_INIT(96, 40, 1, 1),
  AI_STRIDE_INIT(160, 4, 4, 4),
  &input_0_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_26_output,
  AI_SHAPE_INIT(47, 19, 4, 1),
  AI_STRIDE_INIT(304, 16, 4, 4),
  &conv2d_26_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_27_output,
  AI_SHAPE_INIT(22, 8, 8, 1),
  AI_STRIDE_INIT(256, 32, 4, 4),
  &conv2d_27_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_28_output_in,
  AI_SHAPE_INIT(10, 3, 16, 1),
  AI_STRIDE_INIT(192, 64, 4, 4),
  &conv2d_28_output_in_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  conv2d_28_output_out,
  AI_SHAPE_INIT(1, 1, 480, 1),
  AI_STRIDE_INIT(1920, 1920, 4, 4),
  &conv2d_28_output_out_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_9_output,
  AI_SHAPE_INIT(1, 1, 7, 1),
  AI_STRIDE_INIT(28, 28, 4, 4),
  &dense_9_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_9_nl_output,
  AI_SHAPE_INIT(1, 1, 7, 1),
  AI_STRIDE_INIT(28, 28, 4, 4),
  &dense_9_nl_output_array,
  AI_STATIC)





/* Layer #0: "conv2d_26" (Conv2D) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_26_weights_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 36,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  conv2d_26_weights,
  AI_SHAPE_INIT(4, 3, 3, 1),
  AI_STRIDE_INIT(36, 12, 4, 4),
  &conv2d_26_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_26_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 4,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  conv2d_26_bias,
  AI_SHAPE_INIT(1, 1, 4, 1),
  AI_STRIDE_INIT(16, 16, 4, 4),
  &conv2d_26_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_26_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&input_0_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_26_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_26_weights, &conv2d_26_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_26_layer, 0,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_27_layer, AI_STATIC,
  .tensors = &conv2d_26_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_2D_INIT(0, 0), 
  .filter_pad_r = AI_SHAPE_2D_INIT(0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_2D_INIT(0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

/* Layer #1: "conv2d_27" (Conv2D) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_27_weights_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 288,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  conv2d_27_weights,
  AI_SHAPE_INIT(8, 3, 3, 4),
  AI_STRIDE_INIT(144, 48, 16, 4),
  &conv2d_27_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_27_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 8,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  conv2d_27_bias,
  AI_SHAPE_INIT(1, 1, 8, 1),
  AI_STRIDE_INIT(32, 32, 4, 4),
  &conv2d_27_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_27_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&conv2d_26_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_27_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_27_weights, &conv2d_27_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_27_layer, 2,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_28_layer, AI_STATIC,
  .tensors = &conv2d_27_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_2D_INIT(0, 0), 
  .filter_pad_r = AI_SHAPE_2D_INIT(0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_2D_INIT(0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

/* Layer #2: "conv2d_28" (Conv2D) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_28_weights_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 1152,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  conv2d_28_weights,
  AI_SHAPE_INIT(16, 3, 3, 8),
  AI_STRIDE_INIT(288, 96, 32, 4),
  &conv2d_28_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_28_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 16,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  conv2d_28_bias,
  AI_SHAPE_INIT(1, 1, 16, 1),
  AI_STRIDE_INIT(64, 64, 4, 4),
  &conv2d_28_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_28_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&conv2d_27_output),
  AI_TENSOR_LIST_ENTRY(&conv2d_28_output_in),
  AI_TENSOR_LIST_ENTRY(&conv2d_28_weights, &conv2d_28_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conv2d_28_layer, 4,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &dense_9_layer, AI_STATIC,
  .tensors = &conv2d_28_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_2D_INIT(0, 0), 
  .filter_pad_r = AI_SHAPE_2D_INIT(0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_2D_INIT(0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

/* Layer #3: "dense_9" (Dense) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_weights_array, AI_DATA_FORMAT_LUT8_FLOAT, 
  NULL, NULL, 3360,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_9_weights,
  AI_SHAPE_INIT(1, 1, 7, 480),
  AI_STRIDE_INIT(3360, 3360, 480, 1),
  &dense_9_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  dense_9_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 7,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_9_bias,
  AI_SHAPE_INIT(1, 1, 7, 1),
  AI_STRIDE_INIT(28, 28, 4, 4),
  &dense_9_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_9_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&conv2d_28_output_out),
  AI_TENSOR_LIST_ENTRY(&dense_9_output),
  AI_TENSOR_LIST_ENTRY(&dense_9_weights, &dense_9_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_9_layer, 8,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_9_nl_layer, AI_STATIC,
  .tensors = &dense_9_chain, 
)

/* Layer #4: "dense_9_nl" (Nonlinearity) */
  


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_9_nl_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_9_output),
  AI_TENSOR_LIST_ENTRY(&dense_9_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_9_nl_layer, 8,
  SM_TYPE,
  sm, forward_sm,
  &AI_NET_OBJ_INSTANCE, &dense_9_nl_layer, AI_STATIC,
  .tensors = &dense_9_nl_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 10428, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 19972, 1,
                     NULL),
  &input_0_output, &dense_9_nl_output,
  &conv2d_26_layer, 0)


AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT( activations )
  AI_FLAG_SET(net_ctx->flags, AI_NETWORK_FLAG_OUT_COPY);

  {
    /* Updating activations (byte) offsets */
    input_0_output_array.data = NULL;
  input_0_output_array.data_start = NULL;
  conv2d_26_output_array.data = activations + 0;
  conv2d_26_output_array.data_start = activations + 0;
  conv2d_27_output_array.data = activations + 14304;
  conv2d_27_output_array.data_start = activations + 14304;
  conv2d_28_output_in_array.data = activations + 0;
  conv2d_28_output_in_array.data_start = activations + 0;
  conv2d_28_output_out_array.data = activations + 0;
  conv2d_28_output_out_array.data_start = activations + 0;
  dense_9_output_array.data = activations + 3840;
  dense_9_output_array.data_start = activations + 3840;
  dense_9_nl_output_array.data = activations + 3840;
  dense_9_nl_output_array.data_start = activations + 3840;
  
  }
  return true;
}

AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT( weights )

  {
    /* Updating weights (byte) offsets */
    conv2d_26_weights_array.format |= AI_FMT_FLAG_CONST;
  conv2d_26_weights_array.data = weights + 0;
  conv2d_26_weights_array.data_start = weights + 0;
  conv2d_26_bias_array.format |= AI_FMT_FLAG_CONST;
  conv2d_26_bias_array.data = weights + 144;
  conv2d_26_bias_array.data_start = weights + 144;
  conv2d_27_weights_array.format |= AI_FMT_FLAG_CONST;
  conv2d_27_weights_array.data = weights + 160;
  conv2d_27_weights_array.data_start = weights + 160;
  conv2d_27_bias_array.format |= AI_FMT_FLAG_CONST;
  conv2d_27_bias_array.data = weights + 1312;
  conv2d_27_bias_array.data_start = weights + 1312;
  conv2d_28_weights_array.format |= AI_FMT_FLAG_CONST;
  conv2d_28_weights_array.data = weights + 1344;
  conv2d_28_weights_array.data_start = weights + 1344;
  conv2d_28_bias_array.format |= AI_FMT_FLAG_CONST;
  conv2d_28_bias_array.data = weights + 5952;
  conv2d_28_bias_array.data_start = weights + 5952;
  dense_9_weights_array.format |= AI_FMT_FLAG_CONST;
  dense_9_weights_array.data = weights + 6016;
  dense_9_weights_array.data_start = weights + 9376;
  dense_9_bias_array.format |= AI_FMT_FLAG_CONST;
  dense_9_bias_array.data = weights + 10400;
  dense_9_bias_array.data_start = weights + 10400;
  
  }

  return true;
}

/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 534813,
      .n_inputs          = AI_NETWORK_IN_NUM,
      .inputs            = AI_BUFFER_OBJ_INIT(
                              AI_BUFFER_FORMAT_FLOAT,
                              96,
                              40,
                              1,
                              1, NULL),
      .n_outputs         = AI_NETWORK_OUT_NUM,
      .outputs           = AI_BUFFER_OBJ_INIT(
                              AI_BUFFER_FORMAT_FLOAT,
                              1,
                              1,
                              7,
                              1, NULL),
      .activations       = net_ctx->activations,
      .weights           = net_ctx->params,
      .n_nodes           = 0,
      .signature         = net_ctx->signature,
    };

    AI_FOR_EACH_NODE_DO(node, net_ctx->input_node)
    {
      r.n_nodes++;
    }

    *report = r;

    return ( r.n_nodes>0 ) ? true : false;
  }
  
  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);
  
  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

