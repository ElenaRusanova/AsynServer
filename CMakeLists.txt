project(KoshkinServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "C:/Users/zxc18/Desktop/Library/test/include/boost-1_87")
find_package(Boost REQUIRED)

if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(KoshkinServer ${SOURCES})

target_link_libraries(KoshkinServer Boost::boost)