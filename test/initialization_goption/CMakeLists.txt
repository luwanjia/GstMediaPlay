set(TARGET_initialization_goption test_initialization_goption)

include_directories (
	/usr/include/glib-2.0
	/usr/include/gstreamer-1.0
	/usr/lib/x86_64-linux-gnu/glib-2.0/include
)

set(SOURCE_initialization_goption
	initialization_goption.c
)

set(LIBRARY_initialization_goption
	gstreamer-1.0
	glib-2.0
)

add_executable(${TARGET_initialization_goption} ${SOURCE_initialization_goption})

target_link_libraries(${TARGET_initialization_goption} ${LIBRARY_initialization_goption})
