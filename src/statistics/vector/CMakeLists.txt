file(GLOB SOURCES CONFIGURE_DEPENDS
	src/*.cpp 
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	include/*.hpp
)

add_library(ss_vector STATIC)
add_library(ss::vector ALIAS ss_vector)
target_sources(ss_vector
	PRIVATE
		${SOURCES}
	PUBLIC FILE_SET ss_vector_headers
		TYPE HEADERS 
		BASE_DIRS
			include 
		FILES ${HEADERS}
)

target_include_directories(ss_vector 
	PUBLIC
		include
)

target_link_libraries(ss_vector PRIVATE 
	exprtk
)
