#include <stdio.h>
#include "gst_player.h"

GstPlayer::GstPlayer(const std::string& file_path)
    : file_path_(file_path) {
    Init();
}
GstPlayer::~GstPlayer() {
    if(state_ != STATE_STOPPED) {
        stop();
    }
    gst_object_unref(GST_OBJECT(pipeline_));
    gst_deinit();
}

bool GstPlayer::play() {
    if (state_ == STATE_PLAYING) {
        return true;
    }
    
    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    if(GST_STATE_CHANGE_FAILURE != ret) {
        printf("-- GST: playing.\n");
        state_ = STATE_PLAYING;
        return true;
    }
    else {
        printf("-- GST: Failed to play.\n");
    }
  
    return false;
}

bool GstPlayer::stop() {
    if (state_ == STATE_STOPPED) {
        return true;
    }
    
    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_READY);
    
    if (GST_STATE_CHANGE_FAILURE != ret) {
        printf("-- GST: stopped.\n");
        state_ = STATE_STOPPED;
        g_main_loop_quit(main_loop_);
        return true;
    }
    else {
        printf("-- GST: Failed to stop.\n");
    }
    
    return false;
}

bool GstPlayer::pause() {
    if (state_ != STATE_PLAYING) {
        return false;
    }
    
    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PAUSED);
    if (GST_STATE_CHANGE_FAILURE != ret) {
        printf("-- GST: paused.\n");
        state_ = STATE_PAUSED;
        return true;
    }
    else {
        printf("-- GST: Failed to pause.\n");
    }
    
    return false;
}

MediaState GstPlayer::get_state() {
    return state_;
}

bool GstPlayer::Init() {
    std::string description;
    
    // Initialize gstreamer
    gst_init(NULL, NULL);
    
    // Create pipeline
    description = std::string("filesrc location=") + file_path_ + std::string(" ! decodebin ! videoconvert ! ximagesink");
    pipeline_ = gst_parse_launch(description.c_str(), NULL);
    
    // Get bus
    GstBus* bus = gst_element_get_bus(pipeline_);
    
    // Create main loop
    main_loop_ = g_main_loop_new(NULL, FALSE);
    
    // Add watch
    gst_bus_add_signal_watch (bus);
    
    // Connect signal
    g_signal_connect(bus, "message", G_CALLBACK (bus_callback), this);
    
    // Set pipeline ready to play.
    gst_element_set_state(pipeline_, GST_STATE_READY);

    state_ = STATE_STOPPED;
    
    return true;
}

gboolean GstPlayer::bus_callback(GstBus* bus, GstMessage* msg, gpointer data) {
    GstPlayer* media = (GstPlayer*)data;
    
    printf("!!! bus_callback: msg = %d\n", GST_MESSAGE_TYPE (msg));
    switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_ERROR: {
        printf("-- MSG: ERROR\n");
        media->stop();
        break;
    }
    case GST_MESSAGE_EOS:
        printf("-- MSG: EOS\n");
        media->stop();
        break;
    default:
        /* Unhandled message */
        break;
    }
}
