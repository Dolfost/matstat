cmake_minimum_required(VERSION 3.16)

project(lab1 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "~/Qt/6.6.0/macos/lib/cmake")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Charts)
qt_standard_project_setup()

file(GLOB STATISTICS_FILES ${PROJECT_SOURCE_DIR}/statistics/*.cpp)

qt_add_executable(lab1
    main.cpp
	${STATISTICS_FILES}
)

target_link_libraries(lab1 PRIVATE Qt6::Widgets Qt6::Gui Qt6::Charts)

set_target_properties(lab1 PROPERTIES
    MACOSX_BUNDLE ON
)

