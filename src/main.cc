#include <gst/gst.h>
#include <string.h>
#include "gst_player.h"

int main(int argc, char *argv[]) {
  GstPlayer mediaplayer("./test_video.mp4");
  
  mediaplayer.play();
  return 0;
}
