file(GLOB SOURCES CONFIGURE_DEPENDS
	src/*.cpp 
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	include/*.hpp
	include/vectorChain/*.hpp
)

add_library(ss_vectorChain)
add_library(ss::vectorChain ALIAS ss_vectorChain)
target_sources(ss_vectorChain
	PRIVATE
		${SOURCES}
	PUBLIC FILE_SET ss_vectorChain_headers
		TYPE HEADERS 
		BASE_DIRS
			include 
		FILES ${HEADERS}
)

target_include_directories(ss_vectorChain
	PUBLIC
		include
)

target_link_libraries(ss_vectorChain PRIVATE 
	exprtk ss::vector ss::vectorPair
)

add_subdirectory(tests)
