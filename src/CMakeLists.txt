set(TARGET GstPlayer)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
include_directories (
    /usr/include/glib-2.0
    /usr/include/gstreamer-1.0
    /usr/lib/x86_64-linux-gnu/
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
    /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux_armhf")
include_directories(
    /usr/arm-linux-gnueabihf/include
    /usr/arm-linux-gnueabihf/include/gstreamer-1.0
    /usr/arm-linux-gnueabihf/include/glib-2.0
    /usr/arm-linux-gnueabihf/lib/glib-2.0/include
)
link_directories(
    /usr/arm-linux-gnueabihf/lib
)
endif()

set(SOURCE
    gst_player.cc
    main.cc
)

set(LIBRARY
    gstreamer-1.0
    gobject-2.0
    glib-2.0
    gstvideo-1.0
)

add_executable(${TARGET} ${SOURCE})

target_link_libraries(${TARGET} ${LIBRARY})
