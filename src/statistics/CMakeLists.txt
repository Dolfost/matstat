file(GLOB SOURCES CONFIGURE_DEPENDS 
	*.cpp
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	include/*.hpp
)

add_subdirectory(vector)
add_subdirectory(vectorPair)

add_library(ss_statistics)
add_library(ss::statistics ALIAS ss_statistics)
target_sources(ss_statistics
	PRIVATE
		${SOURCES}
	PUBLIC FILE_SET ss_statistics_headers
		TYPE HEADERS 
		BASE_DIRS 
			include
		FILES ${HEADERS}
)

target_include_directories(ss_statistics 
	PUBLIC 
		include/
)

target_link_libraries(ss_statistics 
	PRIVATE exprtk 
	PUBLIC ss::vector ss::vectorPair ss::vector
)
