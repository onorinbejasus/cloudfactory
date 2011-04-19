#ifndef CUDA_HELPERS_HH
#define CUDA_HELPERS_HH

#include <cutil_math.h>

typedef unsigned int uint;
typedef unsigned short ushort;

#include <math.h>

/// Converts a uchar4 to a float3
inline __device__
float3 make_float3(uchar4 xx)
{
	return make_float3((float) xx.x, (float) xx.y, (float) xx.z);
}

/// Converst a float3 to a uchar4, clamping as necessary
inline __device__
uchar4 make_uchar4(float3 xx)
{
	int3 temp = clamp(make_int3(xx), 0, 255);
	return make_uchar4(temp.x, temp.y, temp.z, 255);
}

/// Returns the 3d coordinate from the blockIdx and threadIdx
inline __host__ __device__
uint3 get_coord()
{
	return make_uint3(
		blockIdx.x * blockDim.x + threadIdx.x,
		blockIdx.y * blockDim.y + threadIdx.y,
		blockIdx.z * blockDim.z + threadIdx.z);
}

/// Returns true if the coordinate is in bounds.
inline __host__ __device__
bool in_bounds(uint2 coord, uint2 size) 
{
	return (coord.x < size.x) && (coord.y < size.y);
}

/// Exits the kernel if we are out of bounds.
#define CHECK_OUT_OF_BOUNDS(coord, size) \
	if (!in_bounds(coord, size)) return;

/// Converts a 2d coordinate to a 1d index
inline __host__ __device__
int to_indx(
	uint3 coord, ///< the coordinate to convert
	uint3 dim    ///< 3D dimensions
	)
{
	return coord.x + coord.y *  dim.x + coord.z * dim.x * dim.y;
}

/// Equality operator for uint2's
inline __host__ __device__
bool operator==(const uint2 & a, const uint2 & b)
{
	return (a.x == b.x) && (a.y == b.y);
}

inline __device__ __host__ bool operator ==(float3 a, float3 b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}


#define CHECK_FOR_CUDA_ERROR(X)                \
	{                                          \
		cudaThreadSynchronize();               \
	    cudaError_t err = cudaGetLastError();  \
	    if(cudaSuccess != err) {               \
	        printf("Cuda error (%s:%i) %s\n",  \
				__FILE__, __LINE__,            \
				cudaGetErrorString(err));      \
	        assert(false);                     \
		}                                      \
    }                         

#endif /* CUTIL_MATH_H */