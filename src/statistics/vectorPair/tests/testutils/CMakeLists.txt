add_library(testutils)
target_sources(testutils
	PRIVATE
		src/testutils.cpp
	PUBLIC FILE_SET testutils_headers
		TYPE HEADERS 
		BASE_DIRS 
			include/
		FILES include/testutils.hpp
)

target_link_libraries(testutils 
	ss::vector ss::vectorPair ss::statistics
)
