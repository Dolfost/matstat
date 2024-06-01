find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(qcustomplot SHARED ${CMAKE_CURRENT_SOURCE_DIR}/qcustomplot.cpp)

target_link_libraries(qcustomplot Qt6::Core)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
