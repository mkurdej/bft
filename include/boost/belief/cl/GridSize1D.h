#ifndef BOOST_DST_CL_GRIDSIZE1D
#define BOOST_DST_CL_GRIDSIZE1D

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

uint getGridIndex(const float measure, const struct GridSize1D gridSize)
{
    return (uint)((measure - gridSize.minRange) / gridSize.step); // floor
}

#endif // BOOST_DST_CL_GRIDSIZE1D
