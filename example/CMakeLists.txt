#          Copyright Marek Kurdej 2011 - 2012.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

################################################################################
add_executable(simple_fusion
    simple_fusion.cpp
)
set_property(TARGET simple_fusion PROPERTY FOLDER "Examples")

################################################################################
install(TARGETS simple_fusion
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
