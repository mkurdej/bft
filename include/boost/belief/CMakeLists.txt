project(belief)

################################################################################
# Get all headers (using search instead of explicit filenames for the example)
file(GLOB_RECURSE HDRS
    *.hpp
)

# Get all headers (using search instead of explicit filenames for the example)
file(GLOB_RECURSE KERNELS
    *.cl
)

set_property(SOURCE ${HDRS} PROPERTY HEADER_FILE_ONLY)
set_property(SOURCE ${KERNELS} PROPERTY HEADER_FILE_ONLY)
source_group("OpenCL kernels" FILES ${KERNELS})

set(DOCS
    README
    TODO.txt
)
set_property(SOURCE ${DOCS} PROPERTY HEADER_FILE_ONLY)

################################################################################
#link_libraries(${PROJECT_NAME})
#link_libraries(${Boost_LIBRARIES})

################################################################################
#add_executable(EXE ${SOURCES})

#add_custom_target(${PROJECT_NAME}
#    SOURCES ${HDRS}
#)

add_library(${PROJECT_NAME}_HEADER_ONLY_TARGET STATIC
    ${DOCS}
    ${HDRS}
    ${KERNELS}
)
set_target_properties(${PROJECT_NAME}_HEADER_ONLY_TARGET PROPERTIES LINKER_LANGUAGE CXX)
