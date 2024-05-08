cmake_minimum_required(VERSION 3.15)

project(vcpkg_test)

set(CMAKE_CXX_STANDARD 14)


#add_subdirectory(src/pcl)

find_package(absl CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(gflags CONFIG REQUIRED)
#find_package(OpenBLAS CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
        Eigen3::Eigen
        absl::any absl::base absl::bits absl::city
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        glog::glog
        gflags::gflags
#        OpenBLAS::OpenBLAS
       protobuf::libprotoc protobuf::libprotobuf
        )

install(
        TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        )     