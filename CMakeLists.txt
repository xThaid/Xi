cmake_minimum_required(VERSION 3.10)
project(Xi)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
#set(SOURCES "${SRC_DIR}/main.cpp")

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.h" "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw-3.2.1")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_INCLUDE_DIRS}")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# freetype
set(FREETYPE_DIR "${LIB_DIR}/freetype-2.9.1")
add_subdirectory("${FREETYPE_DIR}")
target_link_libraries(${PROJECT_NAME} "freetype" "${CMAKE_DL_LIBS}")
target_include_directories(${PROJECT_NAME} PRIVATE "${FREETYPE_DIR}/include")

# stb_image
set(STB_IMAGE_DIR "${LIB_DIR}/stb_image")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_IMAGE_DIR}/")

# FastNoise
set(FAST_NOISE_DIR "${LIB_DIR}/FastNoise")
add_library("FastNoise" "${FAST_NOISE_DIR}/FastNoise.cpp")
target_include_directories("FastNoise" PRIVATE "${FAST_NOISE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${FAST_NOISE_DIR}")
target_link_libraries(${PROJECT_NAME} "FastNoise" "${CMAKE_DL_LIBS}")