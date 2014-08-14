//          Copyright Marek Kurdej 2011 - 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE TestOpenCLDst

#define __CL_ENABLE_EXCEPTIONS
//#define OPENCL_DEBUGGING 1
//#define OPENCL_PROFILING 1

#ifdef _MSC_VER
#   pragma warning(push)	// disable for this header only
#   pragma warning(disable:4265)
#   pragma warning(disable:4571)
#   pragma warning(disable:4625)
#   pragma warning(disable:4626)
#   pragma warning(disable:4640)
#   pragma warning(disable:4668)
#elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wunused-function"

#   pragma GCC diagnostic push
#endif // _MSC_VER

#include <boost/dst/cl/OpenCL.hpp>
#include <boost/dst/cl/util.hpp>

#include <boost/scoped_array.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/timer/timer.hpp>
#ifdef _MSC_VER
#   pragma warning(pop)  	// restore original warning level
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif // _MSC_VER

using namespace boost;
using namespace boost::dst;
using boost::timer::cpu_timer;
using boost::timer::cpu_times;
using boost::timer::nanosecond_type;
using namespace cl;
using std::cout;

const int kRepetitions = 10;
const cl_ulong N = 1025; //4 * 1 * 1024 - (1 << 10) + 1;
const cl_device_type kDeviceType = CL_DEVICE_TYPE_GPU;

// Kernel source directory
STRING_CLASS sourceDirectory = "cl/";

//cl_uint preferredWorkgroupSize;
//mKernel.getWorkGroupInfo<cl_uint>(mDevice, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, &preferredWorkgroupSize);
//LOG_INFO("Preferred workgroup size = " << preferredWorkgroupSize);

//==============================================================================
//struct kernel_fixture {
//    kernel_fixture(STRING_CLASS const & fileName, STRING_CLASS const & kernelName);
//    ~kernel_fixture();
//
//    Context mContext;
//    CommandQueue mQueue;
//    Device mDevice;
//    Kernel mKernel;
//};
//
//kernel_fixture::kernel_fixture(STRING_CLASS const & filePath, STRING_CLASS const & kernelName)
//{
//    BOOST_TEST_MESSAGE( "setup fixture" );
//    Program program;
//    VECTOR_CLASS<Device> devices;
//
//    try {
//        // Get a context for specific device type
//        mContext = getContextByDeviceType(kDeviceType);
//
//        // Get a list of devices for this context
//        devices = mContext.getInfo<CL_CONTEXT_DEVICES>();
//        mDevice = devices[0];
//
//        // Create a command queue and use the first device
//#ifdef OPENCL_PROFILING
//        cl_uint queueProperties = CL_QUEUE_PROFILING_ENABLE;
//#else
//        cl_uint queueProperties = 0u;
//#endif
//        mQueue = CommandQueue(mContext, mDevice, queueProperties);
//
//        // Read kernel source file
//        program = getProgramFromFile(mContext, filePath);
//
//        // Build program for these specific devices
//        STRING_CLASS buildIncludes = "-I " + sourceDirectory;
//        program.build(devices, buildIncludes.c_str());
//
//        // Make kernel
//        mKernel = Kernel(program, kernelName.c_str());
//    } catch(Error & error) {
//        LOG_ERROR(error.what() << "(" << error.err() << ")");
//        LOG_ERROR(getOpenCLErrorMessage(error.err()));
//
//        switch (error.err()) {
//        case CL_BUILD_PROGRAM_FAILURE:
//            LOG_DEBUG("Build log:");
//            LOG_DEBUG(program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]));
//            break;
//        }
//    }
//}
//
//kernel_fixture::~kernel_fixture()
//{
//    BOOST_TEST_MESSAGE( "teardown fixture" );
//}
//
////==============================================================================
//
//struct mass_to_communality_1d_soa
//    : kernel_fixture
//{
//    mass_to_communality_1d_soa()
//        : kernel_fixture(sourceDirectory + "communality.cl", "mass_to_communality_1d_soa")
//    {}
//};
//
////==============================================================================
//BOOST_FIXTURE_TEST_SUITE( s_mass_to_communality_1d_soa, mass_to_communality_1d_soa )
//
//BOOST_AUTO_TEST_CASE(test_cl_mass_to_communality_1d_soa_Mx1)
//{
//#ifdef OPENCL_PROFILING
//    Event startTime, endTime;
//#endif
//    
//    OpenCL ocl(mContext, mQueue);
//
//    //==============================================================================
//    const cl_uint setSize = 2u;
//    const cl_uint powersetSize = (1 << setSize);
//    
//    ::size_t mSize = N * powersetSize * sizeof(float);
//
//    //==============================================================================
//    // INPUT
//    scoped_array<float> aM(new float[N*powersetSize]);
//    float * hM = aM.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hM[0*N + i] = 0.0f;
//        hM[1*N + i] = 0.3f;
//        hM[2*N + i] = 0.6f;
//        hM[3*N + i] = 0.1f;
//    }
//    
//    // OUTPUT
//    scoped_array<float> aQ(new float[N*powersetSize]);
//    float * hQ = aQ.get();
//    
//    // EXPECTED OUTPUT
//    scoped_array<float> aQ_expected(new float[N*powersetSize]);
//    float * hQ_expected = aQ_expected.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hQ_expected[0*N + i] = 1.0f;
//        hQ_expected[1*N + i] = 0.4f;
//        hQ_expected[2*N + i] = 0.7f;
//        hQ_expected[3*N + i] = 0.1f;
//    }
//    
//    //==============================================================================
//    try {
//        // Create memory buffers
//        Buffer dQ = Buffer(mContext, CL_MEM_WRITE_ONLY, mSize);
//        Buffer dM = Buffer(mContext, CL_MEM_READ_ONLY, mSize);
//        // Copy lists to the memory buffers
//        mQueue.enqueueWriteBuffer(dM, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hM);
//
//        cl_uint maxWorkgroupSize = 1;
//        mDevice.getInfo<cl_uint>(CL_DEVICE_MAX_WORK_GROUP_SIZE, &maxWorkgroupSize);
//        //cl_uint wgSize = maxWorkgroupSize;
//        cl_uint preferredWorkgroupSize = 1;
//        mKernel.getWorkGroupInfo<cl_uint>(mDevice, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, &preferredWorkgroupSize);
//        cl_uint wgSize = preferredWorkgroupSize;
//#ifdef OPENCL_PROFILING
//        cpu_timer timer;
//        LOG_INFO("Workgroup size    Duration [ms]");
//        for (wgSize = 1; wgSize <= maxWorkgroupSize; wgSize <<= 1) {
//            mQueue.finish();
//            cpu_times const previousTimes(timer.elapsed());
//            mQueue.enqueueMarker(&startTime);
//            {
//                //boost::timer::auto_cpu_timer t;
//                for (int i = 0; i < kRepetitions; ++i) {
//#endif
//                    ocl.setWorkgroupSize(wgSize);
//                    ocl.mass_to_communality_soa(dQ, dM, setSize, N);
//#ifdef OPENCL_PROFILING
//                }
//                mQueue.enqueueMarker(&endTime);
//                mQueue.finish();
//            }
//
//            cpu_times const elapsedTimes(timer.elapsed());
//            nanosecond_type const elapsedNs((elapsedTimes.system + elapsedTimes.user) - (previousTimes.system + previousTimes.user));
//
//            cl_ulong startTimeVal = 0, endTimeVal = 0;
//            startTime.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_END, &startTimeVal);
//            endTime.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_END, &endTimeVal);
//
//            //cl_ulong durationNs = endTimeVal - startTimeVal;
//            //LOG_INFO(wgSize << "\t" << 1.0e-6 * durationNs);
//            LOG_INFO(wgSize << "\t" << 1.0e-6 * elapsedNs);
//        }
//#endif
//        // Read buffer dQ into a local list hQ
//        mQueue.enqueueReadBuffer(dQ, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hQ);
//    } catch (Error & error) {
//        LOG_ERROR(error.what() << "(" << error.err() << ")");
//        LOG_ERROR(getOpenCLErrorMessage(error.err()));
//
//        throw;
//    } catch (std::exception & e) {
//        LOG_ERROR(e.what());
//        
//        throw;
//    }
//
//    //==============================================================================
//    for (cl_uint i = 0; i < powersetSize * N; i+=N) {
//        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
//        //BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
//        BOOST_CHECK_CLOSE(hQ[i], hQ_expected[i], 1e-5f);
//    }
//}
//
//BOOST_AUTO_TEST_SUITE_END()
//
////==============================================================================
//
//struct mass_to_communality_1d_aos
//    : kernel_fixture
//{
//    mass_to_communality_1d_aos()
//        : kernel_fixture(sourceDirectory + "communality.cl", "mass_to_communality_1d_aos")
//    {
//    }
//};
//
//BOOST_FIXTURE_TEST_SUITE( s_mass_to_communality_1d_aos, mass_to_communality_1d_aos )
//
//BOOST_AUTO_TEST_CASE(test_cl_mass_to_communality_1d_aos_Mx1)
//{
//#ifdef OPENCL_PROFILING
//    Event startTime, endTime;
//#endif
//    
//    OpenCL ocl(mContext, mQueue);
//
//    //==============================================================================
//    const cl_uint setSize = 2u;
//    const cl_uint powersetSize = (1 << setSize);
//    
//    ::size_t mSize = N * powersetSize * sizeof(float);
//
//    //==============================================================================
//    // INPUT
//    scoped_array<float> aM(new float[N*powersetSize]);
//    float * hM = aM.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hM[i*powersetSize + 0] = 0.0f;
//        hM[i*powersetSize + 1] = 0.3f;
//        hM[i*powersetSize + 2] = 0.6f;
//        hM[i*powersetSize + 3] = 0.1f;
//    }
//    
//    // OUTPUT
//    scoped_array<float> aQ(new float[N*powersetSize]);
//    float * hQ = aQ.get();
//    
//    // EXPECTED OUTPUT
//    scoped_array<float> aQ_expected(new float[N*powersetSize]);
//    float * hQ_expected = aQ_expected.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hQ_expected[i*powersetSize + 0] = 1.0f;
//        hQ_expected[i*powersetSize + 1] = 0.4f;
//        hQ_expected[i*powersetSize + 2] = 0.7f;
//        hQ_expected[i*powersetSize + 3] = 0.1f;
//    }
//
//    //==============================================================================
//    try {
//        // Create memory buffers
//        Buffer dQ = Buffer(mContext, CL_MEM_WRITE_ONLY, mSize);
//        Buffer dM = Buffer(mContext, CL_MEM_READ_ONLY, mSize);
//        // Copy lists to the memory buffers
//        mQueue.enqueueWriteBuffer(dM, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hM);
//        
//        cl_uint maxWorkgroupSize = 1;
//        mDevice.getInfo<cl_uint>(CL_DEVICE_MAX_WORK_GROUP_SIZE, &maxWorkgroupSize);
//        cl_uint wgSize = maxWorkgroupSize;
//        //cl_uint preferredWorkgroupSize = 1;
//        //mKernel.getWorkGroupInfo<cl_uint>(mDevice, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, &preferredWorkgroupSize);
//        //cl_uint wgSize = preferredWorkgroupSize;
//#ifdef OPENCL_PROFILING
//        cpu_timer timer;
//
//        LOG_INFO("Workgroup size    Duration [ms]");
//        for (wgSize = 1; wgSize <= maxWorkgroupSize; wgSize <<= 1) {
//            mQueue.finish();
//            cpu_times const previousTimes(timer.elapsed());
//            mQueue.enqueueMarker(&startTime);
//            {
//                //boost::timer::auto_cpu_timer t;
//                for (int i = 0; i < kRepetitions; ++i) {
//#endif
//                    ocl.setWorkgroupSize(wgSize);
//                    ocl.mass_to_communality_aos(dQ, dM, setSize, N);
//#ifdef OPENCL_PROFILING
//                }
//                mQueue.enqueueMarker(&endTime);
//                mQueue.finish();
//            }
//            
//            cpu_times const elapsedTimes(timer.elapsed());
//            nanosecond_type const elapsedNs((elapsedTimes.system + elapsedTimes.user) - (previousTimes.system + previousTimes.user));
//
//            cl_ulong startTimeVal = 0, endTimeVal = 0;
//            startTime.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_END, &startTimeVal);
//            endTime.getProfilingInfo<cl_ulong>(CL_PROFILING_COMMAND_END, &endTimeVal);
//
//            //cl_ulong durationNs = endTimeVal - startTimeVal;
//            //LOG_INFO(wgSize << "\t" << 1.0e-6 * durationNs);
//            LOG_INFO(wgSize << "\t" << 1.0e-6 * elapsedNs);
//        }
//#endif
//
//        // Read buffer dQ into a local list hQ
//        mQueue.enqueueReadBuffer(dQ, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hQ);
//    } catch (Error & error) {
//        LOG_ERROR(error.what() << "(" << error.err() << ")");
//        LOG_ERROR(getOpenCLErrorMessage(error.err()));
//
//        throw;
//    }
//
//    //==============================================================================
//    for (cl_uint i = 0; i < powersetSize * N; ++i) {
//        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
//        //BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
//        BOOST_CHECK_CLOSE(hQ[i], hQ_expected[i], 1e-5f);
//    }
//}
//
//BOOST_AUTO_TEST_SUITE_END()
//
//BOOST_AUTO_TEST_CASE(test_cl_rule_conjunctive_q_Mx1)
//{
//    Context context = getContextByDeviceType(kDeviceType);
//    CommandQueue queue = CommandQueue(context, context.getInfo<CL_CONTEXT_DEVICES>()[0]/*, queueProperties*/);
//    
//    OpenCL ocl(context, queue);
//
//    //==============================================================================
//    const cl_uint setSize = 2u;
//    const cl_uint powersetSize = (1 << setSize);
//    
//    ::size_t mSize = N * powersetSize * sizeof(float);
//
//    //==============================================================================
//    // INPUT
//    scoped_array<float> aQ1(new float[N*powersetSize]);
//    float * hQ1 = aQ1.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hQ1[0*N + i] = 1.0f;
//        hQ1[1*N + i] = 0.4f;
//        hQ1[2*N + i] = 0.7f;
//        hQ1[3*N + i] = 0.1f;
//    }
//    Buffer dQ1 = Buffer(context, CL_MEM_READ_ONLY, mSize);
//    queue.enqueueWriteBuffer(dQ1, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hQ1);
//
//    scoped_array<float> aQ2(new float[N*powersetSize]);
//    float * hQ2 = aQ2.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hQ2[0*N + i] = 1.0f;
//        hQ2[1*N + i] = 1.0f;
//        hQ2[2*N + i] = 1.0f;
//        hQ2[3*N + i] = 1.0f;
//    }
//    Buffer dQ2 = Buffer(context, CL_MEM_READ_ONLY, mSize);
//    queue.enqueueWriteBuffer(dQ2, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hQ2);
//    
//    // OUTPUT
//    scoped_array<float> aQconj12(new float[N*powersetSize]);
//    float * hQconj12 = aQconj12.get();
//    Buffer dQconj12 = Buffer(context, CL_MEM_WRITE_ONLY, mSize);
//    
//    // EXPECTED OUTPUT
//    float * hQconj12_expected = hQ1;
//    
//    //==============================================================================
//    ocl.rule_conjunctive_q(dQconj12, dQ1, dQ2, setSize, N);
//    queue.enqueueReadBuffer(dQconj12, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hQconj12);
//    queue.finish();
//
//    //==============================================================================
//    for (cl_uint i = 0; i < powersetSize * N; ++i) {
//        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
//        //BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
//        BOOST_CHECK_CLOSE(hQconj12[i], hQconj12_expected[i], 1e-5f);
//    }
//}
//
//BOOST_AUTO_TEST_CASE(test_cl_communality_to_mass_soa_Mx1)
//{
//    Context context = getContextByDeviceType(kDeviceType);
//    CommandQueue queue = CommandQueue(context, context.getInfo<CL_CONTEXT_DEVICES>()[0]/*, queueProperties*/);
//    
//    OpenCL ocl(context, queue);
//
//    //==============================================================================
//    const cl_uint setSize = 2u;
//    const cl_uint powersetSize = (1 << setSize);
//    
//    ::size_t mSize = N * powersetSize * sizeof(float);
//
//    //==============================================================================
//    // INPUT
//    scoped_array<float> aQ(new float[N*powersetSize]);
//    float * hQ = aQ.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hQ[0*N + i] = 1.0f;
//        hQ[1*N + i] = 0.4f;
//        hQ[2*N + i] = 0.7f;
//        hQ[3*N + i] = 0.1f;
//    }
//    Buffer dQ = Buffer(context, CL_MEM_READ_ONLY, mSize);
//    queue.enqueueWriteBuffer(dQ, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hQ);
//    
//    // OUTPUT
//    scoped_array<float> aM(new float[N*powersetSize]);
//    float * hM = aM.get();
//    Buffer dM = Buffer(context, CL_MEM_WRITE_ONLY, mSize);
//    
//    // EXPECTED OUTPUT
//    scoped_array<float> aM_expected(new float[N*powersetSize]);
//    float * hM_expected = aM_expected.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hM_expected[0*N + i] = 0.0f;
//        hM_expected[1*N + i] = 0.3f;
//        hM_expected[2*N + i] = 0.6f;
//        hM_expected[3*N + i] = 0.1f;
//    }
//    
//    //==============================================================================
//    ocl.communality_to_mass_soa(dM, dQ, setSize, N);
//    queue.enqueueReadBuffer(dM, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hM);
//
//    //==============================================================================
//    for (cl_uint i = 0; i < powersetSize * N; i+=N) {
//        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
//        //BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
//        BOOST_CHECK_CLOSE(1 + hM[i], 1 + hM_expected[i], 1e-5f);
//    }
//}
//
//BOOST_AUTO_TEST_CASE(test_cl_rule_conjunctive_1d_soa_Mx1)
//{
//    Context context = getContextByDeviceType(kDeviceType);
//    CommandQueue queue = CommandQueue(context, context.getInfo<CL_CONTEXT_DEVICES>()[0]/*, queueProperties*/);
//
//    OpenCL ocl(context, queue);
//    
//    //==============================================================================
//    const cl_uint setSize = 2u;
//    const cl_uint powersetSize = (1 << setSize);
//    
//    ::size_t mSize = N * powersetSize * sizeof(float);
//    
//    //==============================================================================
//    // INPUT
//    scoped_array<float> aM1(new float[N*powersetSize]);
//    float * hM1 = aM1.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hM1[0*N + i] = 0.0f;
//        hM1[1*N + i] = 0.3f;
//        hM1[2*N + i] = 0.6f;
//        hM1[3*N + i] = 0.1f;
//    }
//    Buffer dM1 = Buffer(context, CL_MEM_READ_ONLY, mSize);
//    queue.enqueueWriteBuffer(dM1, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hM1);
//
//    scoped_array<float> aM2(new float[N*powersetSize]);
//    float * hM2 = aM2.get();
//    for (cl_uint i = 0; i < N; ++i) {
//        hM2[0*N + i] = 0.0f;
//        hM2[1*N + i] = 0.0f;
//        hM2[2*N + i] = 0.0f;
//        hM2[3*N + i] = 1.0f;
//    }
//    Buffer dM2 = Buffer(context, CL_MEM_READ_ONLY, mSize);
//    queue.enqueueWriteBuffer(dM2, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hM2);
//
//    // OUTPUT
//    scoped_array<float> aMconj12(new float[N*powersetSize]);
//    float * hMconj12 = aMconj12.get();
//    Buffer dMconj12 = Buffer(context, CL_MEM_WRITE_ONLY, mSize);
//    
//    // EXPECTED OUTPUT
//    float * hMconj12_expected = hM1;
//    
//    //==============================================================================
//    ocl.rule_conjunctive_m_soa(dMconj12, dM1, dM2, setSize, N);
//    queue.enqueueReadBuffer(dMconj12, /* blocking = */ CL_TRUE, /* offset = */ 0, mSize, hMconj12);
//
//    //==============================================================================
//    for (cl_uint i = 0; i < powersetSize * N; i+=N) {
//        //BOOST_TEST_MESSAGE("Calling [i] with i=" << i); // temporary fix
//        //BOOST_TEST_CHECKPOINT("Calling [i] with i=" << i); // FIXME: wanted but doesn't work
//        BOOST_CHECK_CLOSE(hMconj12[i], hMconj12_expected[i], 1e-5f);
//    }
//}

BOOST_AUTO_TEST_CASE(test_cl_create_lidar_grid)
{
    Context context = getContextByDeviceType(kDeviceType);
    CommandQueue queue = CommandQueue(context, context.getInfo<CL_CONTEXT_DEVICES>()[0]/*, queueProperties*/);

    OpenCL ocl(context, queue);
    
    //==============================================================================
    float massFree = 0.7f;
    float massOccupied = 0.8f;
    
    //==============================================================================
    // INPUT
    const ::size_t pointCount = 5;
    const ::size_t scanMemSize = pointCount * sizeof(float);
    
    scoped_array<float> aScanAngle(new float[pointCount]);
    scoped_array<float> aScanRadius(new float[pointCount]);

    {
        int i = 0;
        aScanAngle[i] = -30;
        aScanRadius[i] = 1;
        ++i;

        aScanAngle[i] = 10;
        aScanRadius[i] = 5;
        ++i;
        
        aScanAngle[i] = -10;
        aScanRadius[i] = 3;
        ++i;
        
        aScanAngle[i] = 30;
        aScanRadius[i] = 9;
        ++i;
        
        aScanAngle[i] = 29;
        aScanRadius[i] = 8;
        ++i;
    }

    Buffer dScanAngle = Buffer(context, CL_MEM_WRITE_ONLY, scanMemSize);
    Buffer dScanRadius = Buffer(context, CL_MEM_WRITE_ONLY, scanMemSize);

    queue.enqueueWriteBuffer(dScanAngle, /* blocking = */ CL_TRUE, /* offset = */ 0, scanMemSize, aScanAngle.get());
    queue.enqueueWriteBuffer(dScanRadius, /* blocking = */ CL_TRUE, /* offset = */ 0, scanMemSize, aScanRadius.get());

    //==============================================================================
    // OUTPUT
    GridSize1D gridSizeAngle;
    gridSizeAngle.minRange = -40;
    gridSizeAngle.maxRange = 40;
    gridSizeAngle.step = 20;
    gridSizeAngle.size = getGridIndex(gridSizeAngle.maxRange, gridSizeAngle);
    
    GridSize1D gridSizeRadius;
    gridSizeRadius.minRange = 0;
    gridSizeRadius.maxRange = 10;
    gridSizeRadius.step = 2;
    gridSizeRadius.size = getGridIndex(gridSizeRadius.maxRange, gridSizeRadius);

    const ::size_t gridMemSize = gridSizeAngle.size * gridSizeRadius.size * sizeof(float);

    Buffer dFree = Buffer(context, CL_MEM_WRITE_ONLY, gridMemSize);
    Buffer dOccupied = Buffer(context, CL_MEM_WRITE_ONLY, gridMemSize);
    Buffer dOmega = Buffer(context, CL_MEM_WRITE_ONLY, gridMemSize);
    
    scoped_array<float> aFree(new float[gridSizeAngle.size * gridSizeRadius.size]);
    scoped_array<float> aOccupied(new float[gridSizeAngle.size * gridSizeRadius.size]);
    scoped_array<float> aOmega(new float[gridSizeAngle.size * gridSizeRadius.size]);

    //==============================================================================
    ocl.create_lidar_grid(dFree, dOccupied, dOmega, dScanAngle, dScanRadius,
        pointCount, gridSizeAngle, gridSizeRadius, massFree, massOccupied);
    
    queue.enqueueReadBuffer(dFree, /* blocking = */ CL_TRUE, /* offset = */ 0, gridMemSize, aFree.get());
    queue.enqueueReadBuffer(dOccupied, /* blocking = */ CL_TRUE, /* offset = */ 0, gridMemSize, aOccupied.get());
    queue.enqueueReadBuffer(dOmega, /* blocking = */ CL_TRUE, /* offset = */ 0, gridMemSize, aOmega.get());
    queue.finish();
    
    //==============================================================================
    cout << "Free:\n";
    for (cl_uint m = 0; m < gridSizeAngle.size; ++m) {
        for (cl_uint n = 0; n < gridSizeRadius.size; ++n) {
            cout << aFree[n * gridSizeAngle.size + m]  << "\t";
        }
        cout << "\n";
    }
    cout << "Occupied:\n";
    for (cl_uint m = 0; m < gridSizeAngle.size; ++m) {
        for (cl_uint n = 0; n < gridSizeRadius.size; ++n) {
            cout << aOccupied[n * gridSizeAngle.size + m]  << "\t";
        }
        cout << "\n";
    }
    cout << "Omega:\n";
    for (cl_uint m = 0; m < gridSizeAngle.size; ++m) {
        for (cl_uint n = 0; n < gridSizeRadius.size; ++n) {
            cout << aOmega[n * gridSizeAngle.size + m]  << "\t";
        }
        cout << "\n";
    }
}
