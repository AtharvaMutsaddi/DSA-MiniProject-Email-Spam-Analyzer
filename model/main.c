#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "bloomfilter.h"
#include <gtk/gtk.h>
#include "model_to_score_an_email_file.h"
#define ll long long
#define MAX_DOMAIN_SIZE 100

void on_button_clicked(GtkWidget *button, gpointer user_data)
{
    GtkEntry *entry = GTK_ENTRY(user_data);
    const char *text = gtk_entry_get_text(entry);
    int len=20+strlen(text);
    char commandlinearg[len];
    strcat(commandlinearg,"./a.out ");
    strcat(commandlinearg,text);
    strcat(commandlinearg,">> cache.txt");
    system("gcc finalmodel.c");
    system(commandlinearg);
    char txt[5000];
    char finaltxt[5000];
    FILE * cacheFile=fopen("cache.txt","r");
    if (!cacheFile)
    {
        perror("Cannot find file!\n");
        return;
    }
    
    char buffer[100];
    while (fgets(buffer,100,cacheFile))
    {
        strcat(txt,buffer);
    }
    int flag=0;
    int i=0;
    while (txt[i]!='\n')
    {
        i++;
    }
    int j=0;
    while (i<strlen(txt))
    {
        finaltxt[j++]=txt[i++];
    }  
    GtkWidget *label = g_object_get_data(G_OBJECT(button), "label");
    gtk_label_set_text(GTK_LABEL(label), finaltxt);
    system("rm -r cache.txt");
}
int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window), "Spam Email Indicator");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add(GTK_CONTAINER(window), box);
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("submit");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    GtkWidget *label = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    g_object_set_data(G_OBJECT(button), "label", label);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
