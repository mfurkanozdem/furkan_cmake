cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME furkan_cmake)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(STM TRUE)
#set(NXP TRUE)
#set(BSP 3)


# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

set(DRIVER_SOURCES)

if (STM)
    set(DRIVER_SOURCES
        Core/App/hal/stm32/ArchUart.cpp
    )
#list(APPEND DRIVER_SOURCES
#Core/App/utils/RingBuffer.hpp
#Core/App/interface/UartConfig.hpp
#Core/App/interface/IUart.hpp
#Core/App/interface/IComm.hpp
#Core/App/protocol/Uart.hpp
#Core/App/hal/stm32/ArchUart.hpp
#)
elseif (NXP)
    set(DRIVER_SOURCES
        Core/App/hal/nxp/ArchUart.cpp
    )
#list(APPEND DRIVER_SOURCES
#Core/App/utils/RingBuffer.hpp
#Core/App/interface/UartConfig.hpp
#Core/App/interface/IUart.hpp
#Core/App/interface/IComm.hpp
#Core/App/protocol/Uart.hpp
#Core/App/hal/nxp/ArchUart.hpp
#)
endif()

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    Core/App/main.cpp
    ${DRIVER_SOURCES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    Core/App/interface
    Core/App/protocol
    Core/App/utils
    Core/App/hal/stm32
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
    USE_CPP_MAIN
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
