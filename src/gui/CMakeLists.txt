find_package(Qt6 REQUIRED COMPONENTS 
	Core Widgets Gui 
	Graphs
)

file(GLOB SOURCES CONFIGURE_DEPENDS 
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
)

qt_add_library(gui STATIC)
target_sources(gui
	PUBLIC
		${SOURCES}
	PUBLIC FILE_SET gui_headers
		TYPE HEADERS 
			BASE_DIRS include/
			FILES ${HEADERS}
)

target_include_directories(gui 
	PUBLIC include
)

target_link_libraries(gui
	Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Graphs
	exprtk ss::statistics qcustomplot
)
