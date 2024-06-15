cmake_minimum_required(VERSION 3.16)

project(lab VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "~/Qt/6.6.2/macos/lib/cmake")

add_subdirectory(${PROJECT_SOURCE_DIR}/exprtk_cmake)

find_package(Qt6 REQUIRED COMPONENTS PrintSupport Widgets Gui Charts)
qt_standard_project_setup()

file(GLOB STATISTICS_FILES CONFIGURE_DEPENDS 
	${PROJECT_SOURCE_DIR}/include/statistics/*.cpp
	${PROJECT_SOURCE_DIR}/include/statistics/dataVector/src/*.cpp
)
file(GLOB GUI_FILES CONFIGURE_DEPENDS
	${PROJECT_SOURCE_DIR}/include/gui/*.cpp
)

qt_add_executable(lab
	main.cpp
	${STATISTICS_FILES}
	${GUI_FILES}
	${PROJECT_SOURCE_DIR}/include/QCustomPlot/qcustomplot.cpp
)

target_include_directories(lab PRIVATE
	./include
	./exprtk_cmake/include
	./include/statistics/dataVector
	./include/statistics
)

target_link_libraries(lab PRIVATE exprtk Qt6::Widgets Qt6::PrintSupport Qt6::Gui Qt6::Charts)

set_target_properties(lab PROPERTIES
	MACOSX_BUNDLE OFF
)
