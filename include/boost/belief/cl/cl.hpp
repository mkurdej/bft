#ifdef _MSC_VER
#   pragma warning(disable:4365)

#   pragma warning(push)	// disable for this header only
#   pragma warning(disable:4100)
#   pragma warning(disable:4245)
#   pragma warning(disable:4290)
#   pragma warning(disable:4350)
#   pragma warning(disable:4510)
#   pragma warning(disable:4512)
#   pragma warning(disable:4610)
#   pragma warning(disable:4668)
#elif defined(__GNUC__)
#   pragma GCC diagnostic push
#endif // _MSC_VER

#if defined(__APPLE__) || defined(__MACOSX)
#   include <OpenCL/cl.hpp>
#else
#   include <CL/cl.hpp>
#endif

#ifdef _MSC_VER
#   pragma warning(pop)     // restore original warning level
#elif defined(__GNUC__)
#   pragma GCC diagnostic pop
#endif // _MSC_VER
