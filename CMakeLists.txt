cmake_minimum_required(VERSION 2.8.3)
project(ydlidar_ros)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#add_definitions(-std=c++11) # Use C++11

find_package(catkin REQUIRED COMPONENTS
  message_generation
  rosconsole
  roscpp
  sensor_msgs
)

#add_subdirectory(sdk)

set(SDK_PATH "./sdk/")

FILE(GLOB SDK_SRC 
  "${SDK_PATH}/src/impl/unix/*.cpp"
  "${SDK_PATH}/src/*.cpp"
  "${SDK_PATH}/src/*.c"
)
set(LASER_FUSE_PATH "./laser_fuse")

FILE(GLOB LASER_FUSE_SRC 
  "${LASER_FUSE_PATH}/*.cpp"
)



add_message_files(DIRECTORY msg
  FILES
  LaserFan.msg
)

generate_messages(DEPENDENCIES
  std_msgs
)
catkin_package(
CATKIN_DEPENDS message_generation)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/laser_fuse
  ${PROJECT_SOURCE_DIR}/sdk/include
  ${PROJECT_SOURCE_DIR}/sdk/src
)

add_executable(ydlidar_node src/ydlidar_node.cpp  ${SDK_SRC} ${LASER_FUSE_SRC})
add_executable(ydlidar_client src/ydlidar_client.cpp)

target_link_libraries(ydlidar_node
   ${catkin_LIBRARIES} 
 )
target_link_libraries(ydlidar_client
   ${catkin_LIBRARIES} 
 )

install(TARGETS ydlidar_node ydlidar_client
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


install(DIRECTORY launch startup sdk
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  USE_SOURCE_PERMISSIONS
)


