find_package(Qt6 REQUIRED COMPONENTS 
	Core PrintSupport Widgets Gui Graphs
)

qt_standard_project_setup()


add_subdirectory(exprtk)
add_subdirectory(statistics)

add_subdirectory(qcustomplot)
add_subdirectory(gui)

qt_add_executable(lab
	main.cpp
)

target_link_libraries(lab PRIVATE
	Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Graphs
	ss::statistics qcustomplot gui 
)
