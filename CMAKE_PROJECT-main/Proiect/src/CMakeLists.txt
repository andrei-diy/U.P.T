# CMake version
cmake_minimum_required(VERSION 3.0)

set(myproject "BookingApp")
# Project name
project(${myproject})
# Define the search path for header files
#include_directories(src)
# Specify the required C++ standard
if(CMAKE_VERSION GREATER "3.1.2") 
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
else()
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    endif()    
endif()

add_subdirectory(cpp)
add_subdirectory(main)

#target_link_libraries(${myproject} lib1, lib2)
#add_executable(${PROJECT_NAME}
  #            cpp/Device.cpp 
    #          cpp/User.cpp 
      #        main/main.cpp 
        #       )
          

#set(myfiles src/Device.hpp, src/User.hpp ,src/Device.cpp ,src/User.cpp ,src/Main.cpp )

#add_library(lib STATIC ${myfiles})

#add_executable(${myproject} src/main.cpp)

#target_link_libraries(${myproject} PUBLIC lib)

#target_include_directories(${myproject} 
 #PRIVATE src INTERFACE
	#$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	#$<INSTALL_INTERFACE:src>)

