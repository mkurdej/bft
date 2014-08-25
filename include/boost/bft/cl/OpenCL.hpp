#ifndef BOOST_BFT_CL_OPENCL_HPP
#define BOOST_BFT_CL_OPENCL_HPP

#include "cl.hpp"
#include "util.hpp"
#include "GridSize1D.h"

namespace boost { namespace bft { 

namespace /* anonymous */ {

    class OpenCL
    {
    public:
        OpenCL(cl::Context context, cl::CommandQueue queue);
        OpenCL(cl::Context context, cl::CommandQueue queue, cl_uint workgroupSize);
        ~OpenCL();

        cl_uint getWorkgroupSize();
        void setWorkgroupSize(cl_uint workgroupSize);

        void rule_conjunctive_q(cl::Buffer & dQconj12, const cl::Buffer & dQ1, const cl::Buffer & dQ2, cl_uint setSize, cl_ulong count);
        
        void commonality_to_mass_aos(cl::Buffer & dM, const cl::Buffer & dQ, cl_uint setSize, cl_ulong count);
        void commonality_to_mass_soa(cl::Buffer & dM, const cl::Buffer & dQ, cl_uint setSize, cl_ulong count);

        void mass_to_commonality_aos(cl::Buffer & dQ, const cl::Buffer & dM, cl_uint setSize, cl_ulong count);
        void mass_to_commonality_soa(cl::Buffer & dQ, const cl::Buffer & dM, cl_uint setSize, cl_ulong count);

        void rule_conjunctive_m_aos(cl::Buffer & dMconj12, const cl::Buffer & dM1, const cl::Buffer & dM2, cl_uint setSize, cl_ulong count);
        void rule_conjunctive_m_soa(cl::Buffer & dMconj12, const cl::Buffer & dM1, const cl::Buffer & dM2, cl_uint setSize, cl_ulong count);

        void create_lidar_grid(cl::Buffer & dFree, cl::Buffer & dOccupied, cl::Buffer & dOmega, const cl::Buffer & dScanAngle, const cl::Buffer & dScanRadius,
            cl_uint pointCount, GridSize1D gridSizeAngle, GridSize1D gridSizeRadius, cl_float massFree, cl_float massOccupied);

    private:
        void loadKernels();
        cl::Kernel loadKernel(cl::STRING_CLASS const & sourceDirectory, cl::STRING_CLASS const & filePath, cl::STRING_CLASS const & kernelName, cl::STRING_CLASS const & flags = "");
        
        void commonality_to_mass(cl::Kernel & kernel, cl::Buffer & dM, const cl::Buffer & dQ, cl_uint setSize, cl_ulong count);
        void mass_to_commonality(cl::Kernel & kernel, cl::Buffer & dQ, const cl::Buffer & dM, cl_uint setSize, cl_ulong count);
        //void rule_conjunctive_m(cl::Kernel & kernel, cl::Buffer & dMconj12, const cl::Buffer & dM1, const cl::Buffer & dM2, cl_uint setSize, cl_ulong count);
        
    private:
        cl::Context mContext;
        cl::CommandQueue mQueue;

        VECTOR_CLASS<cl::Device> mDevices;

        cl_uint mWorkgroupSize;
        
        cl::Kernel commonality_to_mass_1d_aos;
        cl::Kernel commonality_to_mass_1d_soa;
        cl::Kernel mass_to_commonality_1d_aos;
        cl::Kernel mass_to_commonality_1d_soa;
        cl::Kernel multiply_1d;
        
        cl::Kernel create_lidar_grid_2d;
    };

    //==============================================================================

    OpenCL::OpenCL(cl::Context context, cl::CommandQueue queue)
        : mContext(context)
        , mQueue(queue)
    {
        LOG_INFO("OpenCL() ctor");
        // Get a list of devices for this context
        mDevices = mContext.getInfo<CL_CONTEXT_DEVICES>();
        LOG_INFO("mDevices: size = " << mDevices.size());

        loadKernels();
        LOG_INFO("loadKernels()");
        
        cl_int errorCode;
        cl_uint maxWorkgroupSize = static_cast<cl_uint>( mDevices[0].getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>(&errorCode) );
        // FIXME: C4267 cl_uint is defined as 32-bit, return value is 64-bit (::size_t) on 64-bit platforms
        LOG_INFO("errorCode = " << errorCode);
        LOG_INFO("mDevices[0]: maxWorkgroupSize = " << maxWorkgroupSize);
        setWorkgroupSize(maxWorkgroupSize);
    }

    OpenCL::OpenCL(cl::Context context, cl::CommandQueue queue, cl_uint workgroupSize)
        : mContext(context)
        , mQueue(queue)
    {
        // Get a list of devices for this context
        mDevices = mContext.getInfo<CL_CONTEXT_DEVICES>();
        
        loadKernels();

        setWorkgroupSize(workgroupSize);
    }

    OpenCL::~OpenCL()
    {
    }
    
    //==============================================================================

    cl_uint OpenCL::getWorkgroupSize()
    {
        return mWorkgroupSize;
    }

    void OpenCL::setWorkgroupSize(cl_uint workgroupSize)
    {
        mWorkgroupSize = workgroupSize;
    }

    void OpenCL::loadKernels()
    {
        commonality_to_mass_1d_aos = loadKernel("cl/", "cl/commonality.cl", "commonality_to_mass_1d_aos");
        commonality_to_mass_1d_soa = loadKernel("cl/", "cl/commonality.cl", "commonality_to_mass_1d_soa");
        mass_to_commonality_1d_aos = loadKernel("cl/", "cl/commonality.cl", "mass_to_commonality_1d_aos");
        mass_to_commonality_1d_soa = loadKernel("cl/", "cl/commonality.cl", "mass_to_commonality_1d_soa");
        multiply_1d = loadKernel("cl/", "cl/multiply.cl", "multiply_1d");
        create_lidar_grid_2d = loadKernel("cl/", "cl/lidar.cl", "create_lidar_grid_2d");
    }

    cl::Kernel OpenCL::loadKernel(cl::STRING_CLASS const & sourceDirectory, cl::STRING_CLASS const & filePath, cl::STRING_CLASS const & kernelName, cl::STRING_CLASS const & flags)
    {
        using namespace cl;
        
        // Read kernel source file
        Program program = getProgramFromFile(mContext, filePath);
        // Build program for these specific devices
        STRING_CLASS buildOptions = " -I " + sourceDirectory;
#ifdef OPENCL_DEBUGGING
        buildOptions += " -g -s \"d:/phd/cpp/src/boost/bft/" + filePath + "\"";
#endif
        buildOptions += flags;

        try {
            program.build(mDevices, buildOptions.c_str());
        } catch (cl::Error & error) {
            LOG_INFO("Building file: " << filePath << ", kernel: " << kernelName);
            LOG_INFO("Build options: " << buildOptions);

            LOG_ERROR(error.what() << "(" << error.err() << ")");
            LOG_ERROR(getOpenCLErrorMessage(error.err()));

            switch (error.err()) {
            case CL_BUILD_PROGRAM_FAILURE:
                LOG_DEBUG("Build log:");
                LOG_DEBUG(program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(mDevices[0]));
                break;
            }
            throw;
        }

        // Make kernel
        return Kernel(program, kernelName.c_str());
    }

    //==============================================================================

    void OpenCL::commonality_to_mass(cl::Kernel & kernel, cl::Buffer & dM, const cl::Buffer & dQ, cl_uint setSize, cl_ulong count)
    {
        using namespace cl;
        
        NDRange global(getRoundedGlobalRange((::size_t) count, mWorkgroupSize));
        NDRange local(mWorkgroupSize);

        //==============================================================================
        // Calculate mass M
        {
            kernel.setArg(0, dM);
            kernel.setArg(1, dQ);
            kernel.setArg(2, setSize);
            kernel.setArg(3, count);
            mQueue.enqueueNDRangeKernel(kernel, /* offset = */ NullRange, global, local);
        }
    }

    void OpenCL::commonality_to_mass_aos(cl::Buffer & dM, const cl::Buffer & dQ, cl_uint setSize, cl_ulong count)
    {
        commonality_to_mass(commonality_to_mass_1d_aos, dM, dQ, setSize, count);
    }
    
    void OpenCL::commonality_to_mass_soa(cl::Buffer & dM, const cl::Buffer & dQ, cl_uint setSize, cl_ulong count)
    {
        commonality_to_mass(commonality_to_mass_1d_soa, dM, dQ, setSize, count);
    }
    
    //==============================================================================

    void OpenCL::mass_to_commonality(cl::Kernel & kernel, cl::Buffer & dQ, const cl::Buffer & dM, cl_uint setSize, cl_ulong count)
    {
        using namespace cl;
        
        NDRange global(getRoundedGlobalRange((::size_t) count, mWorkgroupSize));
        NDRange local(mWorkgroupSize);

        //==============================================================================
        // Calculate commonality Q
        {
            kernel.setArg(0, dQ);
            kernel.setArg(1, dM);
            kernel.setArg(2, setSize);
            kernel.setArg(3, count);
            mQueue.enqueueNDRangeKernel(kernel, /* offset = */ NullRange, global, local);
        }
    }
    
    void OpenCL::mass_to_commonality_aos(cl::Buffer & dQ, const cl::Buffer & dM, cl_uint setSize, cl_ulong count)
    {
        mass_to_commonality(mass_to_commonality_1d_aos, dQ, dM, setSize, count);
    }

    void OpenCL::mass_to_commonality_soa(cl::Buffer & dQ, const cl::Buffer & dM, cl_uint setSize, cl_ulong count)
    {
        mass_to_commonality(mass_to_commonality_1d_soa, dQ, dM, setSize, count);
    }
    
    //==============================================================================

    void OpenCL::rule_conjunctive_m_aos(cl::Buffer & dMconj12, const cl::Buffer & dM1, const cl::Buffer & dM2, cl_uint setSize, cl_ulong count)
    {
        using namespace cl;

        ::size_t powersetSize = (1 << setSize);
        ::size_t memSize = (::size_t) (count * powersetSize * sizeof(float));
        
        //==============================================================================
        // Calculate commonality Q1
        Buffer dQ1 = Buffer(mContext, CL_MEM_WRITE_ONLY, memSize);
        mass_to_commonality_aos(dQ1, dM1, setSize, count);
        
        //==============================================================================
        // Calculate commonality Q2
        Buffer dQ2 = Buffer(mContext, CL_MEM_WRITE_ONLY, memSize);
        mass_to_commonality_aos(dQ2, dM2, setSize, count);
        
        // Wait to have commonality Q1 and Q2
        mQueue.finish();

        //==============================================================================
        // Calculate commonality Qconj12
        Buffer dQconj12 = Buffer(mContext, CL_MEM_READ_WRITE, memSize);
        rule_conjunctive_q(dQconj12, dQ1, dQ2, setSize, count);
        
        // Wait to have commonality Qconj12
        mQueue.finish();

        //==============================================================================
        // Calculate mass Mconj12
        commonality_to_mass_aos(dMconj12, dQconj12, setSize, count);
    }

    void OpenCL::rule_conjunctive_m_soa(cl::Buffer & dMconj12, const cl::Buffer & dM1, const cl::Buffer & dM2, cl_uint setSize, cl_ulong count)
    {
        using namespace cl;

        ::size_t powersetSize = (1 << setSize);
        ::size_t memSize = (::size_t) (count * powersetSize * sizeof(float));
        
        //==============================================================================
        // Calculate commonality Q1
        Buffer dQ1 = Buffer(mContext, CL_MEM_READ_WRITE, memSize);
        mass_to_commonality_soa(dQ1, dM1, setSize, count);
        
        //==============================================================================
        // Calculate commonality Q2
        Buffer dQ2 = Buffer(mContext, CL_MEM_READ_WRITE, memSize);
        mass_to_commonality_soa(dQ2, dM2, setSize, count);
        
        // Wait to have commonality Q1 and Q2
        mQueue.finish();

        //==============================================================================
        // Calculate commonality Qconj12
        Buffer dQconj12 = Buffer(mContext, CL_MEM_READ_WRITE, memSize);
        rule_conjunctive_q(dQconj12, dQ1, dQ2, setSize, count);
        
        // Wait to have commonality Qconj12
        mQueue.finish();

        //==============================================================================
        // Calculate mass Mconj12
        commonality_to_mass_soa(dMconj12, dQconj12, setSize, count);
    }
    
    //==============================================================================

    void OpenCL::rule_conjunctive_q(cl::Buffer & dQconj12, const cl::Buffer & dQ1, const cl::Buffer & dQ2, cl_uint setSize, cl_ulong count)
    {
        using namespace cl;
        
        cl_ulong powersetSize = (1 << setSize);
        cl_ulong N = count * powersetSize;
        NDRange global(getRoundedGlobalRange((::size_t) N, mWorkgroupSize));
        NDRange local(mWorkgroupSize);

        //==============================================================================
        // Calculate commonality Qconj12
        {
            multiply_1d.setArg(0, dQconj12);
            multiply_1d.setArg(1, dQ1);
            multiply_1d.setArg(2, dQ2);
            multiply_1d.setArg(3, N);
            mQueue.enqueueNDRangeKernel(multiply_1d, /* offset = */ NullRange, global, local);
        }
    }
    
    //==============================================================================

    void OpenCL::create_lidar_grid(cl::Buffer & dFree, cl::Buffer & dOccupied, cl::Buffer & dOmega, const cl::Buffer & dScanAngle, const cl::Buffer & dScanRadius,
            const cl_uint pointCount, const struct GridSize1D gridSizeAngle, const struct GridSize1D gridSizeRadius, const cl_float massFree, const cl_float massOccupied)
    {
        using namespace cl;

        NDRange global(getRoundedGlobalRange(pointCount, mWorkgroupSize), getRoundedGlobalRange(gridSizeRadius.size, mWorkgroupSize));
        NDRange local(1, mWorkgroupSize);
        LOG_INFO("global = " << global[0] << " x " << global[1]);
        LOG_INFO("local  = " << local[0] << " x " << local[1]);

        {
            create_lidar_grid_2d.setArg(0, dFree);
            create_lidar_grid_2d.setArg(1, dOccupied);
            create_lidar_grid_2d.setArg(2, dOmega);
            create_lidar_grid_2d.setArg(3, dScanAngle);
            create_lidar_grid_2d.setArg(4, dScanRadius);
            create_lidar_grid_2d.setArg(5, pointCount);
            create_lidar_grid_2d.setArg(6, gridSizeAngle);
            create_lidar_grid_2d.setArg(7, gridSizeRadius);
            create_lidar_grid_2d.setArg(8, massFree);
            create_lidar_grid_2d.setArg(9, massOccupied);

            mQueue.enqueueNDRangeKernel(create_lidar_grid_2d, /* offset = */ NullRange, global, local);
        }
    }

} // namespace
} // namespace bft
} // namespace boost

#endif // BOOST_BFT_CL_OPENCL_HPP
