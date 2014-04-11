cmake_minimum_required(VERSION 2.8.3)
project(utils_general)

find_package(catkin REQUIRED)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES LibUtil
)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Eigen)
if(NOT ${Eigen_FOUND})
  find_package(Eigen3 REQUIRED)
endif()

include_directories(
    include
  ${EIGEN_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
)

find_package(OpenCV REQUIRED)

add_library (LibUtil SHARED
    src/CircleEstimator.cpp
    src/ConfigFileReader.cpp
    src/EggTimer.cpp
    src/EigenTools.cpp
    src/Graphics.cpp
    src/LogCollector.cpp
    src/LowPassFilter.cpp
    src/MathHelper.cpp
    src/Misc.cpp
    src/Stopwatch.cpp
    src/Strings.cpp
    src/RamaxxException.cpp
    src/CvMathHelper.cpp
    src/CvContourManipulator.cpp
    src/LaserTo3DTransformation.cpp
    src/Path.cpp
    src/runningstat.cpp
    src/Line2d.cpp
    src/Line2dSegment.cpp
)

target_link_libraries(LibUtil
    ${OpenCV_LIBS}
    ${Boost_LIBRARIES}
)

install (TARGETS LibUtil LIBRARY DESTINATION lib)
