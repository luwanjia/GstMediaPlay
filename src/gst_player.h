#ifndef SRC_GST_PLAYER_H
#define SRC_GST_PLAYER_H

#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <string>

enum MediaState
{
    STATE_NULL,
    STATE_READY,
    STATE_PLAYING,
    STATE_PAUSED,
};

class GstPlayer {
public:
    GstPlayer(const std::string& file_path, const std::string& sink, bool sync = "true");
    ~GstPlayer();
    
    bool play();
    bool pause();
    bool stop();
    MediaState get_state();
    bool set_windows_id(guintptr id);
private:
    GMainLoop*  main_loop_;
    GstElement* pipeline_;
    GstBus* bus_;
  
    double volume_;
    MediaState state_;
    bool sync_;
    std::string file_path_;
    std::string sink_;
    guintptr xwinid_;
    
    bool Init();
    bool Release();
    static gboolean bus_callback(GstBus* bus, GstMessage* msg, gpointer data);
};

#endif // SRC_GST_PLAYER_H
