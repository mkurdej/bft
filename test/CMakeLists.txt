#          Copyright Marek Kurdej 2011 - 2012.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

# enable code coverage generation (only with GCC for now)
if(BOOST_BFT_ENABLE_COVERAGE AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-fprofile-arcs -ftest-coverage)
endif()

################################################################################
#find_package(OpenCL)
if(OPENCL_FOUND)
    add_definitions( -DBOOST_BFT_HAS_OPENCL )
    
    message(STATUS "OPENCL_INCLUDE_DIRS=${OPENCL_INCLUDE_DIRS}")
    message(STATUS "OPENCL_LIBRARIES=${OPENCL_LIBRARIES}")
    
    include_directories(${OPENCL_INCLUDE_DIRS})
    link_directories(${OPENCL_LIBRARIES})
endif()

################################################################################
# add_test_executable(TEST_NAME [ADDITIONAL_SOURCES])
function(add_test_executable TEST_NAME)
    set(ADDITIONAL_SOURCES ${ARGN})
    if(DEBUG)
        message(STATUS "ADDITIONAL_SOURCES = ${ADDITIONAL_SOURCES}")
    endif()
    set(EXE_NAME ${TEST_NAME})
    add_definitions( -DBOOST_TEST_DYN_LINK )
    add_executable(${EXE_NAME} ${TEST_NAME}.cpp ${ADDITIONAL_SOURCES})
    add_test(NAME ${TEST_NAME} COMMAND ${EXE_NAME})
    set_target_properties(${TEST_NAME} PROPERTIES FOLDER "Tests")
    
    target_link_libraries(${TEST_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
    # link with coverage libraries
    if(BOOST_BFT_ENABLE_COVERAGE AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_link_libraries(${TEST_NAME} -fprofile-arcs -ftest-coverage)
    endif()
endfunction()

################################################################################

# set(BFT_PATH "${SRC_PATH}/boost/bft")
set(BFT_PATH "${INCLUDE_PATH}/boost/bft")
set(CL_BFT_PATH "${SRC_PATH}/boost/bft/cl")

#******************************************************************************
add_test_executable(bft_test1
    ${BFT_PATH}/belief.hpp
    ${BFT_PATH}/boost_bft_define_class.hpp
    ${BFT_PATH}/bft.hpp
    ${BFT_PATH}/commonality.hpp
    ${BFT_PATH}/conjunctive_decomposition.hpp
    ${BFT_PATH}/contextual_discounting.hpp
    ${BFT_PATH}/discounting.hpp
    ${BFT_PATH}/disjunctive_decomposition.hpp
    ${BFT_PATH}/extension.hpp
    ${BFT_PATH}/fod.hpp
    ${BFT_PATH}/fod_minus.hpp
    ${BFT_PATH}/fod_union.hpp
    ${BFT_PATH}/implicability.hpp
    ${BFT_PATH}/marginalization.hpp
    ${BFT_PATH}/mass.hpp
    ${BFT_PATH}/min.hpp
    ${BFT_PATH}/max.hpp
    ${BFT_PATH}/plausibility.hpp
    ${BFT_PATH}/rule_base.hpp
    ${BFT_PATH}/rule_conjunctive.hpp
    ${BFT_PATH}/rule_conjunctive_cautious.hpp
    ${BFT_PATH}/rule_dempster.hpp
    ${BFT_PATH}/rule_disjunctive.hpp
    ${BFT_PATH}/rule_disjunctive_bold.hpp
    ${BFT_PATH}/rule_dubois_prade.hpp
    ${BFT_PATH}/rule_jeffrey_dempster.hpp
    ${BFT_PATH}/rule_normalization.hpp
    ${BFT_PATH}/rule_normalization_inagaki.hpp
    ${BFT_PATH}/rule_pcr5.hpp
    ${BFT_PATH}/rule_yager.hpp
    ${BFT_PATH}/rules.hpp
    ${BFT_PATH}/to_belief.hpp
    ${BFT_PATH}/to_commonality.hpp
    ${BFT_PATH}/to_implicability.hpp
    ${BFT_PATH}/to_mass.hpp
    ${BFT_PATH}/to_pignistic.hpp
    ${BFT_PATH}/to_plausibility.hpp
    ${BFT_PATH}/total_conflict_exception.hpp

    ${BFT_PATH}/detail/deref.hpp
    ${BFT_PATH}/detail/emptytype.hpp
    ${BFT_PATH}/detail/is_small.hpp
    ${BFT_PATH}/detail/pow.hpp
    ${BFT_PATH}/detail/to_void.hpp
)

if(OPENCL_FOUND)
    file(GLOB_RECURSE TestOpenCLBFT_KERNELS
        ${CL_BFT_PATH}/*.cl
    )
    set_property(SOURCE ${TestOpenCLBFT_KERNELS} PROPERTY HEADER_FILE_ONLY)
    source_group("OpenCL kernels" FILES ${TestOpenCLBFT_KERNELS})

    add_test_executable(TestOpenCLBFT
        ${TestOpenCLBFT_KERNELS}
        
        ${CL_BFT_PATH}/cl.hpp
        ${CL_BFT_PATH}/log.hpp
        ${CL_BFT_PATH}/set.h
        ${CL_BFT_PATH}/util.hpp
        
        ${CL_BFT_PATH}/GridSize1D.h
        ${CL_BFT_PATH}/OpenCL.hpp
    )
    target_link_libraries(TestOpenCLBFT
        ${OPENCL_LIBRARIES}
    )
endif()

add_test_executable(discounting_test1
    ${BFT_PATH}/contextual_discounting.hpp
    ${BFT_PATH}/discounting.hpp
)
add_test_executable(bft_function_test1
    ${BFT_PATH}/bft_function.hpp
)
add_test_executable(mass_test1)
add_test_executable(rule_jeffrey_dempster_test1)
add_test_executable(rules_test1)

################################################################################
install(TARGETS bft_test1 discounting_test1 bft_function_test1 mass_test1 rule_jeffrey_dempster_test1 rules_test1
    RUNTIME DESTINATION ${MKPHD_BIN_DIR}
    LIBRARY DESTINATION ${MKPHD_BIN_DIR}
    ARCHIVE DESTINATION ${MKPHD_LIB_DIR}
)

if(OPENCL_FOUND)
    install(TARGETS TestOpenCLBFT
        RUNTIME DESTINATION ${MKPHD_BIN_DIR}
        LIBRARY DESTINATION ${MKPHD_BIN_DIR}
        ARCHIVE DESTINATION ${MKPHD_LIB_DIR}
    )
endif()
