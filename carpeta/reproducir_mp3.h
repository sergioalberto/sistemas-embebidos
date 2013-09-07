#include <gst/gst.h>

#ifndef _REPRODUCIR_MP3_H_
#define _REPRODUCIR_MP3_H_

GstStateChangeReturn ret;
GMainLoop *loop;
GstElement *pipeline, *filesrc, *decoder, *filter, *sink;

void play(char *name);

#endif /* _REPRODUCIR_MP3_H_ */
