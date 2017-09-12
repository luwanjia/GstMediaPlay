set(TARGET_initialization test_initialization)

include_directories (
	/usr/include/glib-2.0
	/usr/include/gstreamer-1.0
	/usr/lib/x86_64-linux-gnu/glib-2.0/include
)

set(SOURCE_initialization
	initialization.c
)

set(LIBRARY_initialization
	gstreamer-1.0
)

add_executable(${TARGET_initialization} ${SOURCE_initialization})

target_link_libraries(${TARGET_initialization} ${LIBRARY_initialization})
