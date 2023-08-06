cmake_minimum_required(VERSION 3.13)

project(m2c-udp-process VERSION 0.1.0 LANGUAGES CXX)

# Default as Release
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

find_package(ryml REQUIRED)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_NO_WARN_NEW_VERSIONS ON)
if (UNIX AND NOT APPLE) # Linux
    find_package(
        Boost 1.70 REQUIRED
        COMPONENTS iostreams program_options
    )
else()
    find_package(
        Boost 1.70 REQUIRED
        COMPONENTS iostreams program_options filesystem
    )
endif()

if (UNIX)
    set(USE_THREADS TRUE BOOL "Use Threads in Unix")
else()
    set(USE_THREADS FALSE BOOL "Do not use Threads in Windows")
endif()

if (USE_THREADS)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIR}
)
link_directories(${Boost_LIBRARY_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # work around for issue with Boost library
    # which is shown https://github.com/bitcoin/bitcoin/pull/24415
    set(CMAKE_CXX_FLAGS -Wno-error=narrowing)
endif()

if (MMCESIM_BUILD_ASTYLE)
    add_subdirectory(ext/astyle)
endif()

set(SOURCES
    "src/pkt_receive.cpp"
    "src/pkt_parse.cpp"
    "src/cli_cmd.cpp"
    "src/cfg_read.cpp"
    "src/main.cpp"
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} ryml::ryml)
if (USE_THREADS)
    target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif()
