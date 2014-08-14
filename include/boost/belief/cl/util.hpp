#ifndef BOOST_DST_CL_UTIL_HPP
#define BOOST_DST_CL_UTIL_HPP

#include "cl.hpp"

#ifdef _MSC_VER
#   pragma warning(disable:4365)

#   pragma warning(push)	// disable for this header only
#   pragma warning(disable:4350)
#elif defined(__GNUC__)
#   pragma GCC diagnostic push
#endif // _MSC_VER

#include <boost/algorithm/string/case_conv.hpp>
#include <cmath>
#include <fstream>
#include <utility>

#ifdef _MSC_VER
#   pragma warning(pop)     // restore original warning level
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif // _MSC_VER

#include "log.hpp"

bool doesFileExist(const cl::STRING_CLASS & path);
cl::STRING_CLASS getOpenCLErrorMessage(cl_int errorCode);
cl::Program getProgramFromFile(cl::Context context, cl::STRING_CLASS filename);
cl::Platform getPlatformByName(const char * name);
::size_t getRoundedGlobalRange(::size_t N, ::size_t local);
cl::Context getContextByDeviceType(cl_device_type deviceType);

//==============================================================================

cl::STRING_CLASS getOpenCLErrorMessage(cl_int errorCode)
{
    switch (errorCode) {
    case CL_SUCCESS:
        return "Success";
    case CL_DEVICE_NOT_FOUND:
        return "Device not found";
    case CL_DEVICE_NOT_AVAILABLE:
        return "Device not available";
    case CL_COMPILER_NOT_AVAILABLE:
        return "Compiler not available";
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
        return "Memory object allocation failure";
    case CL_OUT_OF_RESOURCES:
        return "Out of resources";
    case CL_OUT_OF_HOST_MEMORY:
        return "Out of host memory";
    case CL_PROFILING_INFO_NOT_AVAILABLE:
        return "Profiling info not available";
    case CL_MEM_COPY_OVERLAP:
        return "Copy overlap";
    case CL_IMAGE_FORMAT_MISMATCH:
        return "Image format mismatch";
    case CL_IMAGE_FORMAT_NOT_SUPPORTED:
        return "Image format not supported";
    case CL_BUILD_PROGRAM_FAILURE:
        return "Build program failure";
    case CL_MAP_FAILURE:
        return "Map failure";
    case CL_MISALIGNED_SUB_BUFFER_OFFSET:
        return "Misaligned subbuffer offset";
    case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
        return "Exec status error for events in wait list";
    case CL_INVALID_VALUE:
        return "Invalid value";
    case CL_INVALID_DEVICE_TYPE:
        return "Invalid device type";
    case CL_INVALID_PLATFORM:
        return "Invalid platform";
    case CL_INVALID_DEVICE:
        return "Invalid device";
    case CL_INVALID_CONTEXT:
        return "Invalid context";
    case CL_INVALID_QUEUE_PROPERTIES:
        return "Invalid queue properties";
    case CL_INVALID_COMMAND_QUEUE:
        return "Invalid command queue";
    case CL_INVALID_HOST_PTR:
        return "Invalid host pointer";
    case CL_INVALID_MEM_OBJECT:
        return "Invalid memory object";
    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
        return "Invalid image format descriptor";
    case CL_INVALID_IMAGE_SIZE:
        return "Invalid image size";
    case CL_INVALID_SAMPLER:
        return "Invalid sampler";
    case CL_INVALID_BINARY:
        return "Invalid binary";
    case CL_INVALID_BUILD_OPTIONS:
        return "Invalid build options";
    case CL_INVALID_PROGRAM:
        return "Invalid program";
    case CL_INVALID_PROGRAM_EXECUTABLE:
        return "Invalid program executable";
    case CL_INVALID_KERNEL_NAME:
        return "Invalid kernel name";
    case CL_INVALID_KERNEL_DEFINITION:
        return "Invalid kernel definition";
    case CL_INVALID_KERNEL:
        return "Invalid kernel";
    case CL_INVALID_ARG_INDEX:
        return "Invalid argument index";
    case CL_INVALID_ARG_VALUE:
        return "Invalid argument value";
    case CL_INVALID_ARG_SIZE:
        return "Invalid argument size";
    case CL_INVALID_KERNEL_ARGS:
        return "Invalid kernel arguments";
    case CL_INVALID_WORK_DIMENSION:
        return "Invalid work dimension";
    case CL_INVALID_WORK_GROUP_SIZE:
        return "Invalid workgroup size";
    case CL_INVALID_WORK_ITEM_SIZE:
        return "Invalid workitem size";
    case CL_INVALID_GLOBAL_OFFSET:
        return "Invalid global offset";
    case CL_INVALID_EVENT_WAIT_LIST:
        return "Invalid event waitlist";
    case CL_INVALID_EVENT:
        return "Invalid event";
    case CL_INVALID_OPERATION:
        return "Invalid operation";
    case CL_INVALID_GL_OBJECT:
        return "Invalid GL object";
    case CL_INVALID_BUFFER_SIZE:
        return "Invalid buffer size";
    case CL_INVALID_MIP_LEVEL:
        return "Invalid MIP level";
    case CL_INVALID_GLOBAL_WORK_SIZE:
        return "Invalid global worksize";
    case CL_INVALID_PROPERTY:
        return "Invalid property";
    default:
        return cl::STRING_CLASS();
    }
}

cl::Program getProgramFromFile(cl::Context context, cl::STRING_CLASS filename)
{
    using namespace cl;
    using std::ifstream;
    using std::make_pair;
    typedef std::istreambuf_iterator<char> is_iter_char;

    if (!doesFileExist(filename)) {
        throw Error(CL_INVALID_PROGRAM, "kernel file does not exist");
    }

    // Read source file
    ifstream sourceFile(filename);
    cl::STRING_CLASS sourceCode(is_iter_char(sourceFile), (is_iter_char()));
    Program::Sources source(1, make_pair(sourceCode.c_str(), sourceCode.length()+1));
    
    // Make program of the source code in the context
    return Program(context, source);
}

/// Finds a platform that contains given name
cl::Platform getPlatformByName(const char * name)
{
    using boost::to_lower;
    using namespace cl;

    // Get available platforms
    VECTOR_CLASS<Platform> platforms;
    Platform::get(&platforms);

    cl::STRING_CLASS lname = name;
    to_lower(lname);

    LOG_DEBUG("Found " << platforms.size() << " platforms:");

    for (unsigned int plid = 0; plid < platforms.size(); ++plid) {
        cl::STRING_CLASS platformName;
        platforms[plid].getInfo(CL_PLATFORM_NAME, &platformName);
        LOG_DEBUG("Checking platform: " << platformName);
        
        to_lower(platformName);
        std::size_t found = platformName.find(lname);
        if (found != cl::STRING_CLASS::npos) {
            // found a platform with given string
            return platforms[plid];
        }
        // continue searching
    }
    // no platform found
    throw Error(CL_DEVICE_NOT_FOUND, "platform not found");
}

::size_t getRoundedGlobalRange(::size_t N, ::size_t local)
{
    return static_cast< ::size_t >(std::ceil(static_cast<float>(N) / local) * local);
}

/// Finds a context corresponding to a platform which has devices of a given type
cl::Context getContextByDeviceType(cl_device_type deviceType)
{
    using namespace cl;

    // Get available platforms
    VECTOR_CLASS<Platform> platforms;
    Platform::get(&platforms);

    // Select the default platform and create a context using this platform and the GPU
    Context context;

    LOG_INFO("Found " << platforms.size() << " platforms:");
    for (unsigned int plid = 0; plid < platforms.size(); ++plid) {
        STRING_CLASS platformName;
        platforms[plid].getInfo(CL_PLATFORM_NAME, &platformName);
        LOG_DEBUG("\t" << platformName);

        try {
            cl_context_properties cps[] = { 
                CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[plid])(),
                0
            };
            Context context(deviceType, cps);
            switch (deviceType) {
            case CL_DEVICE_TYPE_CPU:
                LOG_DEBUG("Found platform with a CPU device:");
                break;

            case CL_DEVICE_TYPE_GPU:
                LOG_DEBUG("Found platform with a GPU device:");
                break;
            }
            LOG_DEBUG("\t" << platformName);
            return context;
        } catch(Error & error) {
            if (plid+1 >= platforms.size()) {
                LOG_WARN("No more platforms to check");
                throw;
            } else if (CL_DEVICE_NOT_FOUND == error.err()) {
                LOG_TRACE("Trying next platform");
            } else {
                throw;
            }
        }
    }
    // no platform found
    throw Error(CL_DEVICE_NOT_FOUND, "platform not found");
}

bool doesFileExist(const cl::STRING_CLASS & path)
{
    using namespace std;

    bool fileExists = false;
    fstream f(path.c_str(), ios_base::in);
    if (f.good()) {
        fileExists = true;
    }
    f.close();
    return fileExists;
}

#endif // BOOST_DST_CL_UTIL_HPP
