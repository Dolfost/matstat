find_package(Qt6 REQUIRED COMPONENTS 
	Core
)

file(GLOB SOURCES CONFIGURE_DEPENDS 
	*.cpp
	vector/src/*.cpp
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	include/*.hpp
	vector/include/*.hpp
)

qt_add_library(statistics STATIC)
target_sources(statistics
	PRIVATE
		${SOURCES}
	PUBLIC FILE_SET statistics_headers
		TYPE HEADERS 
		BASE_DIRS 
			include
			vector/include
		FILES ${HEADERS}
)

target_include_directories(statistics 
	PUBLIC 
		include/
		dataVector/
)

target_link_libraries(statistics PRIVATE
	exprtk Qt6::Core 
)
