cmake_minimum_required(VERSION 3.10)
project(Algorithms_MazeRunner)

set(CMAKE_CXX_STANDARD 11)

# --- SDL2 Configuration ---
if(WIN32)
    # Windows Setup
    set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2")
    include_directories(${SDL2_PATH}/include)
    link_directories(${SDL2_PATH}/lib)
    set(SDL2_LIBRARIES mingw32 SDL2main SDL2)
elseif(APPLE)
    # macOS Setup (Assuming Homebrew)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    set(SDL2_LIBRARIES ${SDL2_LIBRARIES})
endif()

add_executable(Algorithms_MazeRunner main.cpp)

# Link libraries
target_link_libraries(Algorithms_MazeRunner ${SDL2_LIBRARIES})

# --- Windows DLL Handling ---
if(WIN32)
    add_custom_command(TARGET Algorithms_MazeRunner POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_PATH}/bin/SDL2.dll"
            $<TARGET_FILE_DIR:Algorithms_MazeRunner>)
endif()