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
    GstElement* videosink;
    
    if (state_ == STATE_PLAYING) {
        return true;
    }
    
    g_object_get(pipeline_, "video-sink", &videosink, NULL);
    if(videosink == NULL) {
        return false;
    }
    
    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    if(GST_STATE_CHANGE_FAILURE != ret) {
        printf("-- GST: playing");
        state_ = STATE_PLAYING;
        return true;
    }
  
    return false;
}

bool GstPlayer::stop() {
    if (state_ == STATE_STOPPED) {
        return true;
    }
    
    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_READY);
    
    if (GST_STATE_CHANGE_FAILURE != ret) {
        printf("-- GST: stopped");
        state_ = STATE_STOPPED;
        g_main_loop_quit(main_loop_);
        return true;
    }
    return false;
}

bool GstPlayer::pause() {
    if (state_ != STATE_PLAYING) {
        return false;
    }
    
    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PAUSED);
    if (GST_STATE_CHANGE_FAILURE != ret) {
      state_ = STATE_PAUSED;
      return true;
    }
    
    return false;
}

bool GstPlayer::Init() {
    GstElement* videosink;
    GstElement* audiosink;
        
    // Initialize gstreamer
    if(gst_init_check(NULL,NULL,NULL)==false) {
        return false;
    }
    
    // 
    main_loop_ = g_main_loop_new(NULL,FALSE);
    
    // Create pipeline
    pipeline_ = gst_element_factory_make("playbin","player");
    
    // Create video sink
    videosink = gst_element_factory_make("ximagesink","videosink");
    
    // Create audio sink
    audiosink = gst_element_factory_make("alsasink","audiosink");
    
    // Check vaild
    if(pipeline_ == NULL || videosink == NULL || audiosink == NULL) {
        printf("-- Create pipeline failed.\n");
    }
    
    // Set pipeline
    g_object_set(G_OBJECT(pipeline_), "audio-sink", audiosink, "video-sink", videosink, "volume", volume_, NULL);
    
    // Set uri
    g_object_set(G_OBJECT(pipeline_), "uri", file_path_.c_str(), NULL);
    
    // Listen messages from bus
    GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline_));
    gst_bus_add_watch(bus, bus_callback, this);
    
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
