#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gst/gst.h>
#include "gst_player.h"

int main(int argc, char *argv[]) {
    std::string filename;
    std::string is_sync;
    unsigned char ch;
    unsigned int stop_flag = 0;
    
    if (argc < 2) {
        printf("Error: Please input video file name.\n");
        return 0;
    }
    
    filename = argv[1];
    
    if (argc >=3) {
        is_sync = argv[2];
    }
    else {
        is_sync = "true";
    }
    
    GstPlayer mediaplayer(filename, is_sync == "false" ? false : true);
  
    mediaplayer.play();
    
    while (1) {
        if (stop_flag) break;
        
        ch = getchar();
        switch(ch) {
            case ' ':
                if (mediaplayer.get_state() == STATE_PLAYING) {
                    mediaplayer.pause();
                }
                else if (mediaplayer.get_state() == STATE_PAUSED) {
                    mediaplayer.play();
                }
                break;
            case 27:
                stop_flag = 1;
                break;
            default:
                break;
        }
    }
    printf("-- Exit.\n");
    return 0;
}
