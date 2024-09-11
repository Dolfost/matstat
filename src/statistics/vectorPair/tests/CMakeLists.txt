enable_testing()

file(GLOB TESTS CONFIGURE_DEPENDS
	*.cpp 
)

add_subdirectory(testutils)

foreach(T ${TESTS})
	cmake_path(GET T STEM TNAME)
	add_executable(${TNAME} 
		${T}
	)
	target_link_libraries(${TNAME} testutils)
	add_test(NAME ${TNAME}
		COMMAND ${TNAME}
	)
endforeach()
