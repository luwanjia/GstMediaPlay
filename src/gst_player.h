#ifndef SRC_GST_PLAYER_H
#define SRC_GST_PLAYER_H

#include <gst/gst.h>
#include <string>

enum MediaState
{
    STATE_STOPPED,
    STATE_PLAYING,
    STATE_PAUSED,
};

class GstPlayer {
public:
    GstPlayer(const std::string& file_path);
    ~GstPlayer();
    
    bool play();
    bool stop();
    bool pause();
    MediaState get_state();
private:
    GMainLoop*  main_loop_;
    GstElement* pipeline_;
  
    double volume_;
    MediaState state_;
    std::string file_path_;
    
    bool Init();
    static gboolean bus_callback(GstBus* bus, GstMessage* msg, gpointer data);
};

#endif // SRC_GST_PLAYER_H
