find_package(Qt6 REQUIRED COMPONENTS 
	Core PrintSupport Widgets
)

qt_add_library(qcustomplot STATIC)
target_sources(qcustomplot
	PRIVATE
		qcustomplot.cpp
	PUBLIC FILE_SET qcustomplot_headers
		TYPE HEADERS 
			BASE_DIRS 
				"${CMAKE_CURRENT_SOURCE_DIR}"
			FILES qcustomplot.h
)

target_include_directories(qcustomplot 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(qcustomplot PRIVATE
	Qt6::Core Qt6::PrintSupport Qt6::Widgets
)
