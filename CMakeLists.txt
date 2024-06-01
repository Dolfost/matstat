cmake_minimum_required(VERSION 3.16)

project(lab1 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "~/Qt/6.6.2/macos/lib/cmake")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(./include
	./exprtk_cmake/include
	./include/statistics/dataVector
	./include/QCustomPlot
	./include/statistics)

add_subdirectory(${PROJECT_SOURCE_DIR}/exprtk_cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/include/QCustomPlot)
add_subdirectory(${PROJECT_SOURCE_DIR}/include/gui)
add_subdirectory(${PROJECT_SOURCE_DIR}/include/statistics)

find_package(Qt6 REQUIRED COMPONENTS PrintSupport Widgets Gui)
qt_standard_project_setup()


qt_add_executable(lab1
    main.cpp
)

target_link_libraries(lab1 PRIVATE gui qcustomplot exprtk statistics Qt6::Widgets Qt6::PrintSupport Qt6::Gui)

set_target_properties(lab1 PROPERTIES
    MACOSX_BUNDLE ON
)
