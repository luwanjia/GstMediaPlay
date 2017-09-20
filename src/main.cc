#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gst/gst.h>
#include "gst_player.h"

int main(int argc, char *argv[]) {
    std::string filename;
    unsigned char ch;
    
    if (argc < 2) {
        printf("Error: Please input video file name.\n");
        return 0;
    }
    
    filename = argv[1];
    GstPlayer mediaplayer(filename);
  
    mediaplayer.play();
    
    while (1) {
        ch = getchar();
        switch(ch) {
            case ' ':
                if (mediaplayer.get_state() == STATE_PLAYING) {
                    mediaplayer.pause();
                }
                else if (mediaplayer.get_state() == STATE_PAUSED) {
                    mediaplayer.play();
                }
            default:
                break;
        }
    }
    printf("-- Exit.\n");
    return 0;
}
