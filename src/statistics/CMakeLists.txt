file(GLOB SOURCES CONFIGURE_DEPENDS 
	*.cpp
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	include/*.hpp
)

add_subdirectory(vector)
add_subdirectory(vectorPair)

qt_add_library(statistics STATIC)
target_sources(statistics
	PRIVATE
		${SOURCES}
	PUBLIC FILE_SET statistics_headers
		TYPE HEADERS 
		BASE_DIRS 
			include
		FILES ${HEADERS}
)

target_include_directories(statistics 
	PUBLIC 
		include/
)

target_link_libraries(statistics 
	PRIVATE exprtk 
	PUBLIC ss::vector ss::vectorPair
)
