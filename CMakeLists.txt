cmake_minimum_required(VERSION 2.8.3)
project(utils_general)

add_definitions(-W -Wall -Wno-unused-parameter -fno-strict-aliasing -Wno-unused-function -Wno-deprecated-register)

find_package(catkin REQUIRED COMPONENTS cmake_modules)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES LibUtil
)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)

include_directories(
    include
  ${EIGEN3_INCLUDE_DIR}
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

install(TARGETS LibUtil
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
