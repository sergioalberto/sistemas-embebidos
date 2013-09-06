#include <gst/gst.h>

static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data) {
  GMainLoop *loop = data;

  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_EOS:
      g_print ("End-of-stream\n");
      g_main_loop_quit (loop);
      break;
    case GST_MESSAGE_ERROR: {
      gchar *debug = NULL;
      GError *err = NULL;

      gst_message_parse_error (msg, &err, &debug);

      g_print ("Error: %s\n", err->message);
      g_error_free (err);

      if (debug) {
        g_print ("Debug details: %s\n", debug);
        g_free (debug);
      }

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}

int main (gint   argc, gchar *argv[]) {
	
	GstStateChangeReturn ret;
	GMainLoop *loop;
	GstElement *pipeline, *filesrc, *decoder, *filter, *sink;

	/* initialization */
	gst_init (&argc, &argv);
	loop = g_main_loop_new (NULL, FALSE);

	if (argc != 2) {
		g_print ("Usage: %s <mp3 filename>\n", argv[0]);
		exit(0);
	}

	/* create elements */
	pipeline = gst_pipeline_new ("my_pipeline"); // Create a new pipeline with the given name.
	
	filesrc  = gst_element_factory_make ("filesrc", "my_filesource");
	decoder  = gst_element_factory_make ("mad", "my_decoder");
	
	sink     = gst_element_factory_make ("pulsesink", "audiosink");

	g_object_set (G_OBJECT (filesrc), "location", argv[1], NULL);

	gst_bin_add_many (GST_BIN (pipeline), filesrc, decoder, sink, NULL);
	
	/* link everything together */
	if (!gst_element_link_many (filesrc, decoder, sink, NULL)) {
		g_print ("Failed to link one or more elements!\n");
		exit(0);
	}

	/* run */
  	ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {

		g_print ("Failed to start up pipeline!\n");
		exit(0);
	}
	
	g_main_loop_run (loop);

	/* clean up */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	g_main_loop_unref (loop);

	return 0;
}
