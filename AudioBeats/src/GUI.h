#pragma once
#include <gtk/gtk.h>
#include <functional>

class GUI {
public:
    GUI(int argc, char *argv[]);
    ~GUI();
    
    void setRecordCallback(std::function<void()> callback);
    int run();

private:
    GtkWidget *window;
    GtkWidget *recordButton;
    std::function<void()> recordCallback;
    
    static void onRecordClicked(GtkWidget *widget, gpointer data);
};