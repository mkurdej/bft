#          Copyright Marek Kurdej 2011 - 2012.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

################################################################################
find_package(OpenCL)
if(OPENCL_FOUND)
    add_definitions( -DPACPUS_OPENCL )
    
    message(STATUS "OPENCL_INCLUDE_DIRS=${OPENCL_INCLUDE_DIRS}")
    message(STATUS "OPENCL_LIBRARIES=${OPENCL_LIBRARIES}")
    
    include_directories(${OPENCL_INCLUDE_DIRS})
    link_directories(${OPENCL_LIBRARIES})
endif()

################################################################################

set(DST_PATH "${SRC_PATH}/boost/dst")
set(CL_DST_PATH "${SRC_PATH}/boost/dst/cl")

#******************************************************************************
add_test_executable(TestDst
    ${DST_PATH}/belief.hpp
    ${DST_PATH}/boost_dst_define_class.hpp
    ${DST_PATH}/commonality.hpp
    ${DST_PATH}/conjunctive_decomposition.hpp
    ${DST_PATH}/contextual_discounting.hpp
    ${DST_PATH}/discounting.hpp
    ${DST_PATH}/disjunctive_decomposition.hpp
    ${DST_PATH}/dst.hpp
    ${DST_PATH}/extension.hpp
    ${DST_PATH}/fod.hpp
    ${DST_PATH}/fod_minus.hpp
    ${DST_PATH}/fod_union.hpp
    ${DST_PATH}/implicability.hpp
    ${DST_PATH}/marginalization.hpp
    ${DST_PATH}/mass.hpp
    ${DST_PATH}/min.hpp
    ${DST_PATH}/max.hpp
    ${DST_PATH}/plausibility.hpp
    ${DST_PATH}/rule_base.hpp
    ${DST_PATH}/rule_conjunctive.hpp
    ${DST_PATH}/rule_conjunctive_cautious.hpp
    ${DST_PATH}/rule_dempster.hpp
    ${DST_PATH}/rule_disjunctive.hpp
    ${DST_PATH}/rule_disjunctive_bold.hpp
    ${DST_PATH}/rule_dubois_prade.hpp
    ${DST_PATH}/rule_jeffrey_dempster.hpp
    ${DST_PATH}/rule_normalization.hpp
    ${DST_PATH}/rule_normalization_inagaki.hpp
    ${DST_PATH}/rule_pcr5.hpp
    ${DST_PATH}/rule_yager.hpp
    ${DST_PATH}/rules.hpp
    ${DST_PATH}/to_belief.hpp
    ${DST_PATH}/to_commonality.hpp
    ${DST_PATH}/to_implicability.hpp
    ${DST_PATH}/to_mass.hpp
    ${DST_PATH}/to_pignistic.hpp
    ${DST_PATH}/to_plausibility.hpp
    ${DST_PATH}/total_conflict_exception.hpp

    ${DST_PATH}/private/deref.hpp
        ${DST_PATH}/private/emptytype.hpp
    ####${DST_PATH}/private/pow.hpp
    ${DST_PATH}/private/to_void.hpp
)

if(OPENCL_FOUND)
    file(GLOB_RECURSE TestOpenCLDst_KERNELS
        ${CL_DST_PATH}/*.cl
    )
    set_property(SOURCE ${TestOpenCLDst_KERNELS} PROPERTY HEADER_FILE_ONLY)
    source_group("OpenCL kernels" FILES ${TestOpenCLDst_KERNELS})

    add_test_executable(TestOpenCLDst
        ${TestOpenCLDst_KERNELS}
        
        ${CL_DST_PATH}/cl.hpp
        ${CL_DST_PATH}/log.hpp
        ${CL_DST_PATH}/set.h
        ${CL_DST_PATH}/util.hpp
        
        ${CL_DST_PATH}/GridSize1D.h
        ${CL_DST_PATH}/OpenCL.hpp
    )
    target_link_libraries(TestOpenCLDst
        ${OPENCL_LIBRARIES}
    )
endif()

add_test_executable(test_discounting
    ${DST_PATH}/contextual_discounting.hpp
    ${DST_PATH}/discounting.hpp
)
add_test_executable(test_dst_function
    ${DST_PATH}/dst_function.hpp
)
add_test_executable(test_mass)
add_test_executable(test_rule_jeffrey_dempster)
add_test_executable(test_rules)

################################################################################
install(TARGETS TestDst test_discounting test_dst_function test_mass test_rule_jeffrey_dempster test_rules
    RUNTIME DESTINATION ${MKPHD_BIN_DIR}
    LIBRARY DESTINATION ${MKPHD_BIN_DIR}
    ARCHIVE DESTINATION ${MKPHD_LIB_DIR}
)

if(OPENCL_FOUND)
    install(TARGETS TestOpenCLDst
        RUNTIME DESTINATION ${MKPHD_BIN_DIR}
        LIBRARY DESTINATION ${MKPHD_BIN_DIR}
        ARCHIVE DESTINATION ${MKPHD_LIB_DIR}
    )
endif()
