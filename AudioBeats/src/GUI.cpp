#include "GUI.h"

GUI::GUI(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "AudioBeats");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    
    recordButton = gtk_button_new_with_label("Record");
    g_signal_connect(recordButton, "clicked", G_CALLBACK(onRecordClicked), this);
    
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(box), recordButton, TRUE, TRUE, 0);
    
    gtk_container_add(GTK_CONTAINER(window), box);
}

GUI::~GUI() {
    // Cleanup if needed
}

void GUI::setRecordCallback(std::function<void()> callback) {
    recordCallback = callback;
}

int GUI::run() {
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

void GUI::onRecordClicked(GtkWidget *widget, gpointer data) {
    GUI *gui = static_cast<GUI*>(data);
    if (gui->recordCallback) {
        gui->recordCallback();
    }
}