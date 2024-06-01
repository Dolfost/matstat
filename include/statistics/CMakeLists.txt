find_package(Qt6 REQUIRED COMPONENTS Core)

file(GLOB files 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/dataVector/src/*.cpp")

add_library(statistics ${files})
target_link_libraries(statistics exprtk Qt6::Core)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/dataVector")
