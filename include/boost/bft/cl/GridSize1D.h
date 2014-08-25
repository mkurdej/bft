#ifndef BOOST_BFT_CL_GRIDSIZE1D
#define BOOST_BFT_CL_GRIDSIZE1D

#ifndef __OPENCL_VERSION__
#   define float cl_float
#   define uint cl_uint
#endif

struct GridSize1D
{
    float minRange;
    float maxRange;
    float step;
    /// size = (maxRange - minRange) / step;
    uint size;
};

#ifndef __OPENCL_VERSION__
namespace /* anonymous */ {
#endif

uint getGridIndex(const float measure, const struct GridSize1D gridSize)
{
    return (uint)((measure - gridSize.minRange) / gridSize.step); // floor
}

#ifndef __OPENCL_VERSION__
} // namespace
#endif

#endif // BOOST_BFT_CL_GRIDSIZE1D
