set(TARGET GstPlayer)

include_directories (
    /usr/include/glib-2.0
    /usr/include/gstreamer-1.0
    /usr/lib/x86_64-linux-gnu/
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
    /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
    .
)

set(SOURCE
    gst_player.cc
    main.cc
)

set(LIBRARY
    gstreamer-1.0
    gobject-2.0
    glib-2.0
)

add_executable(${TARGET} ${SOURCE})

target_link_libraries(${TARGET} ${LIBRARY})
