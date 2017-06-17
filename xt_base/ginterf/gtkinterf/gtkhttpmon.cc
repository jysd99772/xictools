
/************************************************************************
 *
 * gtkhttpmon.cc: basic C++ class library for http/ftp communications
 *
 * S. R. Whiteley <stevew@srware.com> 2/13/00
 * Copyright (C) 2000 Whiteley Research Inc., All Rights Reserved.
 * Borrowed extensively from the XmHTML widget library
 * Copyright (C) 1994-1997 by Ripley Software Development
 * Copyright (C) 1997-1998 Richard Offer <offer@sgi.com>
 * Borrowed extensively from the Chimera WWW browser
 * Copyright (C) 1993, 1994, 1995, John D. Kilburg (john@cs.unlv.edu)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * ----------------------------------------------------------------------
 * $Id: gtkhttpmon.cc,v 2.17 2015/07/31 22:37:01 stevew Exp $
 ************************************************************************/

#include "httpget/transact.h"
#include <gtk/gtk.h>
#ifdef WITH_X11
#include <gdk/gdkx.h>
#endif
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//
// The monitor widget and functions for the httpget library and
// program.
//

namespace {
    // Drain the event queue, return false if max_events (> 0) given
    // and reached.
    //
    inline bool
    gtk_DoEvents(int max_events)
    {
        int i = 0;
        while (gtk_events_pending()) {
            gtk_main_iteration();
            if (++i == max_events)
                return (false);
        }
        return (true);
    }


    // Timer callback, exits main loop.
    //
    int
    terminate(void*)
    {
        gtk_main_quit();
        return (0);
    }


    // Handle X events when the connection is active.
    //
    bool
    event_cb(int)
    {
        gtk_DoEvents(100);
        return (false);
    }
}


struct grbits : public http_monitor
{
    grbits()
        {
            g_popup = 0;
            g_text_area = 0;
            g_textbuf = 0;
            g_jbuf_set = false;
        }

    ~grbits()
        {
            if (g_popup)
                gtk_widget_destroy(g_popup);
        }

    bool widget_print(const char*);     // print to monitor

    void abort()
        {
            if (g_jbuf_set) {
                g_jbuf_set = false;
                longjmp(g_jbuf, -2);
            }
        }

    void run(Transaction *t)            // start transfer
        {
            g_jbuf_set = true;
            http_monitor::run(t);
            g_jbuf_set = false;

            // Die after the interval.
            gtk_timeout_add(2000, (GtkFunction)terminate, 0);
        }

    bool graphics_enabled()
        {
            return (true);
        }

    void initialize(int&, char**)
        {
            // This will prevent use of themes.  The theme engine may
            // reference library functions that won't be satisfied if
            // this application is statically linked, causing an error
            // message or worse.
            //
            putenv(lstring::copy("GTK_RC_FILES="));
        }

    void setup_comm(cComm *comm)
        {
#ifdef WITH_X11
            comm->comm_set_gfd(ConnectionNumber(gdk_display), event_cb);
#else
            comm->comm_set_gfd(-1, event_cb);
#endif
        }

    void start(Transaction*);

private:
    static void g_dl_cancel_proc(GtkWidget*, void*);
    static void g_cancel_btn_proc(GtkWidget*, void*);
    static int g_da_expose(GtkWidget*, GdkEvent*, void*);
    static int g_idle_proc(void*);

public:
    GtkWidget *g_popup;
    GtkWidget *g_text_area;
    char *g_textbuf;
    bool g_jbuf_set;
    jmp_buf g_jbuf;
};


void
grbits::start(Transaction *t)
{
    grbits *gb = new grbits;
    t->set_gr(gb);
    if (setjmp(gb->g_jbuf) == -2) {
        t->set_err_return(HTTPAborted);
        return;
    }
    gtk_init(0, 0);

    gb->g_popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(gb->g_popup), "Download");
    gtk_signal_connect(GTK_OBJECT(gb->g_popup), "destroy",
        GTK_SIGNAL_FUNC(grbits::g_dl_cancel_proc), gb);
    GtkWidget *form = gtk_table_new(1, 2, false);
    gtk_widget_show(form);
    gtk_container_add(GTK_CONTAINER(gb->g_popup), form);
    GtkWidget *frame = gtk_frame_new(t->url());
    gtk_widget_show(frame);
    gb->g_text_area = gtk_drawing_area_new();
    gtk_signal_connect(GTK_OBJECT(gb->g_text_area), "expose-event",
        GTK_SIGNAL_FUNC(grbits::g_da_expose), gb);
    gtk_widget_show(gb->g_text_area);
    gtk_drawing_area_size(GTK_DRAWING_AREA(gb->g_text_area), 320, 30);
    gtk_container_add(GTK_CONTAINER(frame), gb->g_text_area);
    gtk_table_attach(GTK_TABLE(form), frame, 0, 1, 0, 1,
        (GtkAttachOptions)(GTK_EXPAND | GTK_FILL | GTK_SHRINK),
        (GtkAttachOptions)(GTK_EXPAND | GTK_FILL | GTK_SHRINK), 2, 2);
    GtkWidget *button = gtk_button_new_with_label("Cancel");
    gtk_widget_show(button);
    gtk_table_attach(GTK_TABLE(form), button, 0, 1, 1, 2,
        (GtkAttachOptions)(GTK_EXPAND | GTK_FILL | GTK_SHRINK),
        (GtkAttachOptions)0, 2, 2);
    gtk_signal_connect(GTK_OBJECT(button), "clicked",
        GTK_SIGNAL_FUNC(grbits::g_cancel_btn_proc), gb);
    if (t->xpos() >= 0 && t->ypos() >= 0) {
        GdkScreen *scrn = gdk_screen_get_default();
        int x, y;
        gdk_window_get_pointer(0, &x, &y, 0);
        int pmon = gdk_screen_get_monitor_at_point(scrn, x, y);
        GdkRectangle r;
        gdk_screen_get_monitor_geometry(scrn, pmon, &r);
        gtk_widget_set_uposition(gb->g_popup, t->xpos() + r.x, t->ypos() + r.y);
    }
    gtk_widget_show(gb->g_popup);

    gtk_idle_add((GtkFunction)grbits::g_idle_proc, t);
    gtk_main();
}


// This will override the http_monitor stubs on httpget, when linked
// with this, enabling graphics.
//
namespace {
    grbits _monitor_;

    struct http_init_t
    {
        http_init_t()
            {
                httpget::Monitor = &_monitor_;
            }
    };

    http_init_t _http_init_;
}


//-----------------------------------------------------------------------------
// The download monitor widget

// Function to print a message in the text area.  If buf is 0, reprint
// from the t_textbuf.  This also services events, if the widget is
// realized, and returns true.  False is returned if the widget is not
// realized.
//
bool
grbits::widget_print(const char *buf)
{
    if (g_text_area && g_text_area->window) {
        char *str = lstring::copy(buf ? buf : g_textbuf);
        if (str) {
            char *e = str + strlen(str) - 1;
            while (e >= str && isspace(*e))
                *e-- = 0;
            char *s = str;
            while (*s == '\r' || *s == '\n')
                s++;
            if (*s) {
                if (buf) {
                    delete [] g_textbuf;
                    g_textbuf = lstring::copy(s);  // for expose
                }
                gdk_window_clear(g_text_area->window);
                GdkFont *fnt = gtk_style_get_font(g_text_area->style);
                gdk_draw_string(g_text_area->window, fnt,
                    g_text_area->style->black_gc, 2, fnt->ascent + 2, s);
            }
            delete [] str;
        }
        gtk_DoEvents(100);
        return (true);
    }
    return (false);
}


// Static private function.
// Window destroy callback, does not abort transfer.
//
void
grbits::g_dl_cancel_proc(GtkWidget*, void *data)
{
    grbits *gb = (grbits*)data;
    gtk_signal_disconnect_by_func(GTK_OBJECT(gb->g_popup),
        GTK_SIGNAL_FUNC(g_dl_cancel_proc), data);
    gtk_widget_destroy(GTK_WIDGET(gb->g_popup));
    delete [] gb->g_textbuf;
    gb->g_textbuf = 0;
    gb->g_text_area = 0;
    gb->g_popup = 0;
}


// Static private function.
// Cancel button callback, aborts transfer.
//
void
grbits::g_cancel_btn_proc(GtkWidget*, void *data)
{
    grbits *gb = (grbits*)data;
    gtk_signal_disconnect_by_func(GTK_OBJECT(gb->g_popup),
        GTK_SIGNAL_FUNC(g_dl_cancel_proc), gb);
    gtk_widget_destroy(GTK_WIDGET(gb->g_popup));
    delete [] gb->g_textbuf;
    gb->g_textbuf = 0;
    gb->g_text_area = 0;
    gb->g_popup = 0;
    gb->abort();
}


// Static private function.
// Expose handler for text area.
//
int
grbits::g_da_expose(GtkWidget*, GdkEvent*, void *data)
{
    http_monitor *gb = (grbits*)data;
    gb->widget_print(0);
    return (1);
}


// Static private function.
// Idle procedure to actually perform transfer.
//
int
grbits::g_idle_proc(void *arg)
{
    Transaction *t = (Transaction*)arg;
    http_monitor *gb = t->gr();
    gb->run(t);
    gtk_main_quit();
    return (false);
}

