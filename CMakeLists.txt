set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set(RELEASE_NAME "Trunk")
set(PROJECT_VERSION ${COMPLETE_VERSION})

if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW) # v3.0
endif()
project(mkphd VERSION ${PROJECT_VERSION})

# By default, do not warn when built on machines using only VS Express:
if(NOT DEFINED CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS ON)
endif()

# Note the version no is Mmmpp for Major/minor/patch, 0-padded, thus '10100' for 1.1.0
math(EXPR MKPHD_VERSION_INT "${CPACK_PACKAGE_VERSION_MAJOR}*10000+${CPACK_PACKAGE_VERSION_MINOR}*100+${CPACK_PACKAGE_VERSION_PATCH}")
message(STATUS "Marek Kurdej Ph.D. version: ${COMPLETE_VERSION} ${RELEASE_NAME} (${MKPHD_VERSION_INT})")

#############################################################
# CMake settings
# 2.6.2 required for VERSION_LESS
cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_COLOR_MAKEFILE      ON)

# use project groups
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set path to additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# in generated makefiles use relative paths so the project dir is moveable
# Note commented out since it cause problems but it would be nice to resolve these and enable
#
# issue is caused by INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}) near the end of this file generating incorrect path
#set(CMAKE_USE_RELATIVE_PATHS ON)

# Compile flag. Turns on all warnings, including pedantic.
set(MK_PEDANTIC TRUE CACHE BOOL "Determines if we should compile in pedantic mode.")
mark_as_advanced(MK_PEDANTIC)

# whether unit tests should be build
set(MK_ENABLE_TESTS TRUE CACHE BOOL "Build unit tests?")

# whether to use folders
set(MK_USE_FOLDERS TRUE CACHE BOOL "Use project folders?")
set(USE_FOLDERS ${MK_USE_FOLDERS})

# what build type?
set(CMAKE_BUILD_TYPE Debug CACHE STRING "What type of build? (None|Debug|Release|RelWithDebInfo|MinSizeRel)")

########################################
#set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(
    Boost
    1.36.0
    COMPONENTS unit_test_framework serialization
    REQUIRED
)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    #link_libraries(${Boost_${COMPONENT}_LIBRARY})
    #link_libraries(${Boost_LIBRARIES})
    #or
    #target_link_libraries(<target> ${Boost_${COMPONENT}_LIBRARY})
    #target_link_libraries(<target> ${Boost_LIBRARIES})
endif()

#message(STATUS "Boost_${COMPONENT}_LIBRARY = ${Boost_${COMPONENT}_LIBRARY}")
message(STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")

################################################################################
if(MK_ENABLE_TESTS)
    #include(CTest)
    enable_testing()
    #set(ENV{CTEST_OUTPUT_ON_FAILURE} true)
    
    add_custom_target(TEST
        COMMAND ${CMAKE_CTEST_COMMAND} --build-config ${CMAKE_BUILD_TYPE}
    )
    set_property(TARGET TEST PROPERTY FOLDER "Tests")
endif(MK_ENABLE_TESTS)

#############################################################
# enable warnings
set(MK_WARNING_LEVEL "4" CACHE STRING "Warning level (0-4)")
mark_as_advanced(MK_WARNING_LEVEL)
if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W${MK_WARNING_LEVEL}" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        add_definitions( /W${MK_WARNING_LEVEL} )
    endif()
else(MSVC)
    add_definitions( )
endif(MSVC)

if(MK_PEDANTIC)
    message(STATUS "Pedantic compiler settings enabled")
    if(MSVC)
        if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/Wall" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else()
            add_definitions( /Wall )
        endif()

        # disable warnings
        #    add_definitions( /wd4068 )  # unknown pragma
        #    add_definitions( /wd4100 )  # unused formal parameters
        #    add_definitions( /wd4127 )  # constant conditional expressions (used in Qt template classes)
        #    add_definitions( /wd4510 )  # default constructor could not be generated (sqlite3_index_info, QMap)
        #    add_definitions( /wd4512 )  # assignment operator could not be generated (sqlite3_index_info)
        #    add_definitions( /wd4610 )  # user defined constructor required (sqlite3_index_info)
        #    add_definitions( /wd4706 )  # assignment within conditional expression (pal)
        add_definitions( /wd4514 )
        add_definitions( /wd4710 )
        add_definitions( /wd4820 )
    endif(MSVC)
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        add_definitions( -pedantic -Wall -Wextra )
        add_definitions(
            -Wno-long-long
            #-Wno-non-virtual-dtor
            #-Wno-strict-aliasing
            # user-defined '...::operator,(const T&)' always evaluates both arguments
            # 'class ...' has pointer data members
            # prefix ... should return
            # should be initialized in the member initialization list
        )
        add_definitions(
            #-Waggregate-return
            -Wcast-align
            -Wcast-qual  -Wchar-subscripts  -Wcomment
            -Wconversion
            -Wdisabled-optimization
            #-Weffc++
            #-Werror
            -Wfloat-equal
            -Wformat -Wformat=2
            -Wformat-nonliteral -Wformat-security
            -Wformat-y2k
            -Wimport  -Winit-self  -Winline
            -Winvalid-pch
            -Wunsafe-loop-optimizations
            #-Wlong-long
            -Wmissing-braces
            -Wmissing-field-initializers -Wmissing-format-attribute
            -Wmissing-include-dirs
            -Wmissing-noreturn
            -Wpacked
            #-Wpadded
            -Wparentheses  -Wpointer-arith
            -Wredundant-decls
            -Wreturn-type
            -Wsequence-point
            -Wshadow
            -Wsign-compare  -Wstack-protector
            -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default
            -Wswitch-enum
            -Wtrigraphs  -Wuninitialized
            -Wunknown-pragmas
            -Wunreachable-code
            -Wunused
            -Wunused-function  -Wunused-label  -Wunused-parameter
            -Wunused-value  -Wunused-variable  -Wvariadic-macros
            -Wvolatile-register-var  -Wwrite-strings
        )
    endif()
endif(MK_PEDANTIC)

if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    message(STATUS "Debug output enabled")
    add_definitions(-DMKPHDDEBUG=1)
endif(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

    set(DEFAULT_LIB_SUBDIR     lib)
    set(DEFAULT_LIBEXEC_SUBDIR .)
    set(DEFAULT_DATA_SUBDIR    .)
    set(DEFAULT_PLUGIN_SUBDIR  plugins)
    set(DEFAULT_INCLUDE_SUBDIR include)

#############################################################
# platform specific stuff

if(MSVC)
    set(DEFAULT_BIN_SUBDIR bin)
    set(DEFAULT_CGIBIN_SUBDIR bin)
    # put all the build products into a single directory
    # under build (doesn't affect install target) to make for
    # easier debugging.

    # Turn on defines for non standard maths stuff
    #    add_definitions(-D_USE_MATH_DEFINES)

    # Turn off deprecation warnings
    #    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    #    add_definitions(-D_CRT_NONSTDC_NO_WARNINGS)

    if(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
        message(STATUS "Generating browse files")
        add_definitions( /FR )
    endif(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

    if(INSTALL_DEPS)
        install(DIRECTORY ${INSTALL_DEPS} DESTINATION .)
    endif(INSTALL_DEPS)
else()
    set(DEFAULT_BIN_SUBDIR bin)
    set(DEFAULT_CGIBIN_SUBDIR bin)
endif()

if(WIN32)
    set(DLLIMPORT "__declspec(dllimport)")
    set(DLLEXPORT "__declspec(dllexport)")
else()
    set(DLLIMPORT "")
    set(DLLEXPORT "")
endif()

add_definitions("-DCORE_EXPORT=${DLLIMPORT}")
add_definitions("-DGUI_EXPORT=${DLLIMPORT}")

#############################################################
# user-changeable settings which can be used to customize
# layout of MKPHD installation
# (default values are platform-specific)

set(MKPHD_BIN_SUBDIR     ${DEFAULT_BIN_SUBDIR}     CACHE STRING "Subdirectory where executables will be installed")
set(MKPHD_CGIBIN_SUBDIR  ${DEFAULT_CGIBIN_SUBDIR}  CACHE STRING "Subdirectory where CGI executables will be installed")
set(MKPHD_LIB_SUBDIR     ${DEFAULT_LIB_SUBDIR}     CACHE STRING "Subdirectory where libraries will be installed")
set(MKPHD_LIBEXEC_SUBDIR ${DEFAULT_LIBEXEC_SUBDIR} CACHE STRING "Subdirectory where private executables will be installed")
set(MKPHD_DATA_SUBDIR    ${DEFAULT_DATA_SUBDIR}    CACHE STRING "Subdirectory where MKPHD data will be installed")
set(MKPHD_PLUGIN_SUBDIR  ${DEFAULT_PLUGIN_SUBDIR}  CACHE STRING "Subdirectory where plugins will be installed")
set(MKPHD_INCLUDE_SUBDIR ${DEFAULT_INCLUDE_SUBDIR} CACHE STRING "Subdirectory where header files will be installed")

# mark *_SUBDIR variables as advanced as this is not something
# that an average user would use
mark_as_advanced(MKPHD_BIN_SUBDIR MKPHD_CGIBIN_SUBDIR MKPHD_LIB_SUBDIR MKPHD_LIBEXEC_SUBDIR MKPHD_DATA_SUBDIR MKPHD_PLUGIN_SUBDIR MKPHD_INCLUDE_SUBDIR)

# full paths for the installation
set(MKPHD_BIN_DIR     ${MKPHD_BIN_SUBDIR})
set(MKPHD_CGIBIN_DIR  ${MKPHD_CGIBIN_SUBDIR})
set(MKPHD_LIB_DIR     ${MKPHD_LIB_SUBDIR})
set(MKPHD_LIBEXEC_DIR ${MKPHD_LIBEXEC_SUBDIR})
set(MKPHD_DATA_DIR    ${MKPHD_DATA_SUBDIR})
set(MKPHD_PLUGIN_DIR  ${MKPHD_PLUGIN_SUBDIR})
set(MKPHD_INCLUDE_DIR ${MKPHD_INCLUDE_SUBDIR})

# set the default locations where the targets (executables, libraries) will land when compiled
# this is to allow running mkphd from the source tree without having to actually do a "make install"
set(MKPHD_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MKPHD_OUTPUT_DIRECTORY}/${MKPHD_BIN_SUBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MKPHD_OUTPUT_DIRECTORY}/${MKPHD_LIB_SUBDIR})

# write a marker with source directory path into the output's bin directory
# if run from the build directory MKPHD will detect it and alter the paths
file(WRITE ${MKPHD_OUTPUT_DIRECTORY}/${MKPHD_BIN_SUBDIR}/source_path.txt "${CMAKE_SOURCE_DIR}")

# manual page - makes sense only on unix systems
if(UNIX AND NOT APPLE)
  set(DEFAULT_MANUAL_SUBDIR  man)
  set(MKPHD_MANUAL_SUBDIR  ${DEFAULT_MANUAL_SUBDIR}  CACHE STRING "Subdirectory where manual files will be installed")
  mark_as_advanced(MKPHD_MANUAL_SUBDIR)
  set(MKPHD_MANUAL_DIR  ${CMAKE_INSTALL_PREFIX}/${MKPHD_MANUAL_SUBDIR})
endif(UNIX AND NOT APPLE)

#############################################################
# create mkversion.h

# find_file(GIT_MARKER index PATHS ${CMAKE_SOURCE_DIR}/.git)
# if(GIT_MARKER)
    # find_program(GIT git PATHS $ENV{PATH})
    # if(GIT)
        # if(MSVC)
            # ADD_CUSTOM_COMMAND(
                # OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mkversion.h
                # COMMAND for /f \"usebackq tokens=1\" %%a in "(`\"${GIT}\" log -n1 --oneline`)" do echo \#define MKVERSION \"%%a\" >${CMAKE_CURRENT_BINARY_DIR}/mkversion.h
                # MAIN_DEPENDENCY ${GIT_MARKER}
                # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            # )
        # else(MSVC)
            # execute_process(
                # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                # COMMAND ${GIT} log -n1 --pretty=%h OUTPUT_VARIABLE MK_REVISION
            # )
            # string(STRIP "${MK_REVISION}" MK_REVISION)
            # add_custom_command(
                # OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/mkversion.h
                # COMMAND echo \\\#define MKVERSION \\\"${MK_REVISION}\\\" >${CMAKE_CURRENT_BINARY_DIR}/mkversion.h
                # MAIN_DEPENDENCY ${GIT_MARKER}
                # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            # )
        # endif(MSVC)
    # else(GIT)
        # message(STATUS "git marker, but no git found - version will be unknown")
        # set(MK_REVISION "unknown")
    # endif(GIT)
# else(GIT_MARKER)
    # set(MK_REVISION "exported")
# endif(GIT_MARKER)

#############################################################
# find last author and revision number
find_file(SVN_MARKER .svn PATHS ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/.. ${CMAKE_SOURCE_DIR}/../..)
if(SVN_MARKER)
    find_program(SVN svn PATHS $ENV{PATH})
    if(SVN)
        execute_process(
            WORKING_DIRECTORY "${SVN_MARKER}/.."
            COMMAND ${SVN} log -r HEAD --xml OUTPUT_VARIABLE SVN_XML
        )
        string(REGEX REPLACE ".*<author>([^<]*)</author>.*" "\\1"
            MK_LAST_AUTHOR "${SVN_XML}"
        )
        string(REGEX REPLACE ".*<logentry[ \t\n\r]+revision=\"([0-9]*)\">.*" "\\1"
            MK_REVISION "${SVN_XML}"
        )
    else(SVN)
        message(STATUS "svn marker, but no svn found - version will be unknown")
        set(MK_REVISION "unknown")
    endif(SVN)
else(SVN_MARKER)
    set(MK_REVISION "exported")
endif(SVN_MARKER)

#create mkversion.h
#file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/mkversion.h "#define MKVERSION \"exported\"")
#
#ADD_CUSTOM_TARGET(version ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/mkversion.h)

#############################################################
# create mkconfig.h
# installed with app target

#configure_file(${CMAKE_SOURCE_DIR}/cmake_templates/mkconfig.h.in ${CMAKE_BINARY_DIR}/mkconfig.h)
#include_directories(${CMAKE_BINARY_DIR})

#############################################################
# process subdirs

#add_subdirectory(libs)
#add_subdirectory(src)
#add_subdirectory(doc)
#add_subdirectory(images)
#add_subdirectory(resources)
#add_subdirectory(i18n)

if(MK_ENABLE_TESTS)
    #create a variable to specify where our test data is
    #so that unit tests can use TEST_DATA_DIR to locate
    #the test data. See CMakeLists in test dirs for more info
    set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/testdata")
    set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/include")
    set(SRC_PATH "${CMAKE_SOURCE_DIR}/src")
    add_subdirectory(test)
endif(MK_ENABLE_TESTS)

# manual page - makes sense only on unix systems
if(UNIX AND NOT APPLE)
    #install(FILES mkphd.1 DESTINATION ${MKPHD_MANUAL_DIR}/man1)
endif(UNIX AND NOT APPLE)

install(FILES cmake/FindMKPHD.cmake DESTINATION ${MKPHD_DATA_DIR})

#############################################################
# Uninstall stuff see: http://www.vtk.org/Wiki/CMake_FAQ
#configure_file(
#    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_templates/cmake_uninstall.cmake.in"
#    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
#    IMMEDIATE @ONLY
#)

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
)

#############################################################
# Enable packaging

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Marek Kurdej Ph.D.")
set(CPACK_PACKAGE_VENDOR "Marek Kurdej - UTC Heudiasyc DGA")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Quantum GIS ${COMPLETE_VERSION}")
if(WIN32 AND NOT UNIX)
    # watch out for \\backslash -- escape character!
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/win_build\\\\sidebar.bmp")
    set(CPACK_MKPHD_INSTALLED_ICON_NAME "\\\\mkphd.exe")
    set(CPACK_MKPHD_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Marek Kurdej Ph.D.")
    set(CPACK_MKPHD_HELP_LINK "http:\\\\www.hds.utc.fr\\~kurdejma\\phd\\help.html")
    set(CPACK_MKPHD_URL_INFO_ABOUT "http:\\\\www.hds.utc.fr\\~kurdejma\\phd")
    set(CPACK_MKPHD_CONTACT "marek.kurdej@hds.utc.fr")
    #set(CPACK_MKPHD_MODIFY_PATH ON)

    #  set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "  !include \\\"${CMAKE_SOURCE_DIR}\\\\win_build\\\\extra.nsh\\\"")
else(WIN32 AND NOT UNIX)
    #set(CPACK_STRIP_FILES "Marek Kurdej PhD")
    #set(CPACK_SOURCE_STRIP_FILES "")
endif(WIN32 AND NOT UNIX)

set(CPACK_PACKAGE_EXECUTABLES "mkphd" "MKPHD")
#include(CPack)
