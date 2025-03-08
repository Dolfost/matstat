find_package(Qt6 REQUIRED COMPONENTS 
	Core Widgets Gui 
	DataVisualization
)

file(GLOB SOURCES CONFIGURE_DEPENDS 
	${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)
file(GLOB HEADERS CONFIGURE_DEPENDS 
	${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/include/*.h
)

qt_add_library(gui)
target_sources(gui
	PUBLIC
		${SOURCES}
	PUBLIC FILE_SET gui_headers
		TYPE HEADERS 
			BASE_DIRS include/
			FILES ${HEADERS}
)

qt_add_resources(gui "fonts"
    PREFIX "/"
    FILES
				"res/JuliaMono-Regular.ttf"
)

target_link_libraries(gui
	Qt6::Core Qt6::Widgets Qt6::Gui Qt6::DataVisualization
	exprtk ss::statistics qcustomplot
)
