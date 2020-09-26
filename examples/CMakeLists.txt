# Main CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0)
project(loggertest CXX)

# grab mcommon and tell it not to install anything
set(MCOMMON_DO_NOT_INSTALL ON)
add_subdirectory(../ mcommon)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(MSVC)
	# MSVC tends to fake C++98 even with /std:c++17 on the command line.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /D_CRT_SECURE_NO_WARNINGS")
endif()

# clang-cl optimizations
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND MSVC)
	if("${CMAKE_BUILD_TYPE}" MATCHES "Release")
		set(CMAKE_CXX_FLAGS_RELEASE "/MD /Oi /DNDEBUG /clang:-O3 /clang:-ffast-math")
		set(CMAKE_C_FLAGS_RELEASE "/MD /Oi /DNDEBUG /clang:-O3 /clang:-ffast-math")
	endif()
elseif(MSVC)
	# not clang-cl, but instead, it is *really* MSVC
endif()


add_executable(loggertest loggertest.cpp)

set_property(TARGET loggertest PROPERTY CXX_STANDARD 17)
set_property(TARGET loggertest PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(loggertest mcommon)


add_executable(threadpooltest threadpooltest.cpp)
set_property(TARGET threadpooltest PROPERTY CXX_STANDARD 17)
set_property(TARGET threadpooltest PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(threadpooltest mcommon)