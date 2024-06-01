find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(gui ${files})

target_link_libraries(gui qcustomplot Qt6::Core Qt6::Widgets Qt6::Gui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
