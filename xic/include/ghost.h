
/*========================================================================*
 *                                                                        *
 *  XICTOOLS Integrated Circuit Design System                             *
 *  Copyright (c) 2007 Whiteley Research Inc, all rights reserved.        *
 *                                                                        *
 *  WHITELEY RESEARCH INCORPORATED PROPRIETARY SOFTWARE                   *
 *                                                                        *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES      *
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-        *
 *   INFRINGEMENT.  IN NO EVENT SHALL WHITELEY RESEARCH INCORPORATED      *
 *   OR STEPHEN R. WHITELEY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE       *
 *   USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                        *
 *========================================================================*
 *                                                                        *
 * XIC Integrated Circuit Layout and Schematic Editor                     *
 *                                                                        *
 *========================================================================*
 $Id: ghost.h,v 5.17 2016/05/28 06:24:27 stevew Exp $
 *========================================================================*/

#ifndef GHOST_H
#define GHOST_H


// Mode selection for the ghosting functions.  There is an enum for every
// mode that might be used in the program.  Only the basic ghost functions
// are enabled by default, others must have drawing callbacks registered
// explicitly.
//
enum GFtype
{
    // ghost basic
    GFnone, GFline, GFline_ns, GFvector, GFvector_ns, GFbox, GFbox_ns,
    GFzoom, GFruler, GFscript,

    // edit
    GFpathseg, GFwireseg,
    GFdisk, GFdonut, GFarc,
    GFstretch, GFrotate, GFmove, GFplace, GFlabel, GFput, GFgrip,

    // sced
    GFdiskpth, GFarcpth,
    GFshape, GFeterms,

    // extract
    GFpterms, GFmeasbox,

    GF_END
};

// Enum to set in which windows ghosting is displayed.  Below, "similar"
// windows means the same cell, electrical/physical mode, and database
// mode.
//
enum GhostMode
{
    GhostVanilla,
        // Show in windows similar to the main window only.
    GhostZoom,
        // Show in windows similar to the window from which a zoom
        // operation was initiated only.  Applies only to GFzoom.
    GhostAltOnly,
        // Show in windows similar to the "alt" window (as per the
        // CursorDesc) only.  It there is no alt window, show in
        // windows similar to the main window only.
    GhostAltIncluded,
        // As above, but also show in the main window if the main
        // window has the same electrical/physical and database mode
        // as the alt window.  However, the ghosting is only shown in
        // windows similar to the one that has focus, i.e., either in
        // the alt window or the main window, but not both
        // simultaneously.
    GhostSnapPoint
        // Show in all drawing windows.
};

// Allow this depth for push/pop of ghosting state.
//
#define GHOST_LEVELS 3

// Typedefs.
// The GhostDrawFunc typedef is in graphics.h
//
typedef void(*GhostSetupFunc)(bool);

// The setup function, if registered, is called with argument true when
// the respective ghost mode is entered, false when terminated.  This can
// be used by the application to setup/free stuff needed for ghost drawing
// in that mode.

// Drawing function context element.
//
struct ghparm_t
{
    ghparm_t()
        {
            func = 0;
            x = y = 0;
            type = GFnone;
            mode = GhostVanilla;
        }

    void set(GFtype t, GhostDrawFunc f, int xx, int yy, GhostMode m)
        {
            type = t;
            func = f;
            x = xx;
            y = yy;
            mode = m;
        }

    bool operator==(const ghparm_t &g)
        {
            return (type == g.type && func == g.func && x == g.x && y == g.y
                && mode == g.mode);
        }

    GhostDrawFunc func;
    int x, y;
    GFtype type;
    GhostMode mode;
};


inline class cGhost *Gst();

// Main class
//
class cGhost
{
    static cGhost *ptr()
        {
            if (!instancePtr)
                on_null_ptr();
            return (instancePtr);
        }

    static void on_null_ptr();

public:
    friend inline cGhost *Gst() { return (cGhost::ptr()); }

    struct gf_t
    {
        gf_t()
            {
                draw_func = 0;
                setup_func = 0;
            }

        GhostDrawFunc draw_func;
        GhostSetupFunc setup_func;
    };

    cGhost();

    // Drawing callback registration.
    void RegisterFunc(GFtype, GhostDrawFunc, GhostSetupFunc = 0);

    // Display control.
    void SetGhost(GFtype, GhostMode = GhostVanilla);
    void SetGhostAt(GFtype, int, int, GhostMode = GhostVanilla);
    void SaveGhost();
    void RestoreGhost();
    void RepaintGhost();
    void BumpGhostPointer(int);
    bool ShowingGhostInWindow(WindowDesc*);
    void ShowGhostBox(int, int, int, int);
    void ShowGhostPath(const Point*, int);
    void ShowGhostCross(int, int, int, bool);

    // events.h
    void ShowGhostZoom(int, int, int, int);

    // measure.cc
    void ShowGhostRuler(int, int, int, int, bool);

    // main_scriptif.cc
    void ShowGhostScript(int, int, int, int);

    // No ghosting until this is called.
    void StartGhost() {
        if (!g_started) {
            g_started = true;
            SetGhost(GFnone);
        }
    }

    // GFline/GFline_ns orientation.
    bool GhostLineVert()            { return (g_ghost_line_vert); }
    void SetGhostLineVert(bool b)   { g_ghost_line_vert = b; }

private:
    void push(GFtype, int, int, GhostMode);
    void push();
    void pop();
    void setghost();

    // Built-in drawing callbacks.
    static void ghost_snap_point(int, int, int, int, bool);
    static void ghost_line(int, int, int, int, bool);
    static void ghost_line_snap(int, int, int, int, bool);
    static void ghost_vector(int, int, int, int, bool);
    static void ghost_vector_snap(int, int, int, int, bool);
    static void ghost_box(int, int, int, int, bool);
    static void ghost_box_snap(int, int, int, int, bool);
    static void ghost_zoom(int, int, int, int, bool);
    static void ghost_ruler(int, int, int, int, bool);
    static void ghost_script(int, int, int, int, bool);

    int g_level;
    bool g_started;
    bool g_ghost_line_vert;
    gf_t g_functions[GF_END];
    ghparm_t g_context[GHOST_LEVELS];
    ghparm_t g_saved_context;

    static cGhost *instancePtr;
};

#endif

