# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (LearnOpenGL)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

# Include directory
include_directories(
	./include
)

# Compile external dependencies 
add_subdirectory(libs)

# Executatbles
set(SOURCES 
	./src/display.cpp
	./src/stb_image.cpp
	./src/shader.cpp
	./src/texture.cpp
	./src/camera.cpp
	./src/callback_handler.cpp
	./src/transform.cpp
	./src/obj_loader.cpp
	./src/mesh.cpp
	./src/indexed_model.cpp
)

# Add executable
add_executable(main main.cpp ${SOURCES} )

# Link executable to external libaries
target_link_libraries(main PUBLIC ext_libs)
