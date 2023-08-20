cmake_minimum_required(VERSION 3.20)



find_package(Eigen3 3.4 REQUIRED)
find_package(OpenCV REQUIRED)
add_executable(main main.cpp)

#includes
target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS})

#link libraries
target_link_libraries(main Eigen3::Eigen)
target_link_libraries(main ${OpenCV_LIBS})