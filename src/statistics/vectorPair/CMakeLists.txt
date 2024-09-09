file(GLOB SOURCES CONFIGURE_DEPENDS
	src/*.cpp 
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	include/*.hpp
)

add_library(ss_vectorPair STATIC)
add_library(ss::vectorPair ALIAS ss_vectorPair)
target_sources(ss_vectorPair
	PRIVATE
		${SOURCES}
	PUBLIC FILE_SET ss_vectorPair_headers
		TYPE HEADERS 
		BASE_DIRS
			include 
		FILES ${HEADERS}
)

target_include_directories(ss_vectorPair
	PUBLIC
		include
)

target_link_libraries(ss_vectorPair PRIVATE 
	exprtk
)
