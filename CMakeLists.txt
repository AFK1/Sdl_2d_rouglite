cmake_minimum_required(VERSION 3.10)

project(Sdl_2d_rouglite)

if (WIN32)
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
endif(WIN32)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  )
  
target_include_directories(${PROJECT_NAME} PRIVATE
  include
  ${SDL2_INCLUDE_DIR}
  )

target_link_libraries(${PROJECT_NAME} PRIVATE
	${SDL2_LIBRARIES}
)