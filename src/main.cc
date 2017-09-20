#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gst/gst.h>
#include "gst_player.h"

int main(int argc, char *argv[]) {
    std::string filename;
    
    if (argc < 2) {
        printf("Error: Please input video file name.\n");
        return 0;
    }
    
    filename = argv[1];
    printf("-- Playing: %s\n", filename.c_str());
    GstPlayer mediaplayer(filename);
  
    mediaplayer.play();
    
    printf("-- Exit.\n");
    return 0;
}
