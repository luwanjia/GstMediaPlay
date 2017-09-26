#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gst/gst.h>
#include "gst_player.h"

int main(int argc, char *argv[]) {
    std::string filename;
    std::string videosink = "ximagesink";
    std::string is_sync = "true";
    
    unsigned char ch;
    unsigned int exit_flag = 0;
    
    if (argc < 2) {
        printf("Error: Please input video file name.\n");
        return 0;
    }    
    else if (argc == 2) {
        filename    = argv[1];
    }
    else if (argc == 3) {
        filename    = argv[1];
        videosink   = argv[2];
    }
    else if (argc == 4) {
        filename    = argv[1];
        videosink   = argv[2];
        is_sync     = argv[3];
    }
    
    
    GstPlayer mediaplayer(filename, videosink, is_sync == "false" ? false : true, 0);
  
    mediaplayer.play();
    
    while (1) {
        if (exit_flag) break;
        
        ch = getchar();
        switch(ch) {
            case 'p':
            case 'P':
                mediaplayer.play();
                break;
            case ' ':
                if (mediaplayer.get_state() == STATE_PLAYING) {
                    mediaplayer.pause();
                }
                else if (mediaplayer.get_state() == STATE_PAUSED) {
                    mediaplayer.play();
                }
                break;
            case 's':
            case 'S':
                mediaplayer.stop();
                break;
            case 'q':
            case 'Q':
                exit_flag = 1;
                break;
            default:
                break;
        }
    }
    printf("-- Exit.\n");
    return 0;
}
