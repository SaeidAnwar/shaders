cmake_minimum_required(VERSION 3.10)
project(out)

# Add this line to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all .cpp and .h files
file(GLOB SOURCES "src/*.cpp" "main.cpp")

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    OpenGL::GL
    GLEW::GLEW
    SDL2::SDL2main SDL2::SDL2
)

# For macOS, we need to add these specific flags
if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
    # Add macOS frameworks
    target_link_libraries(${PROJECT_NAME} 
        "-framework OpenGL"
    )
endif()
