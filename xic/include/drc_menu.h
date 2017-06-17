
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
 $Id: drc_menu.h,v 5.7 2015/01/05 17:18:57 stevew Exp $
 *========================================================================*/

#ifndef DRCMENU_H
#define DRCMENU_H

// DRC Menu
enum
{
    drcMenu,
    drcMenuLimit,
    drcMenuSflag,
    drcMenuIntr,
    drcMenuNopop,
    drcMenuCheck,
    drcMenuPoint,
    drcMenuClear,
    drcMenuQuery,
    drcMenuErdmp,
    drcMenuErupd,
    drcMenuNext,
    drcMenuErlyr,
    drcMenuDredt,
    drcMenu_END
};

#define    MenuDRC       "drc"
#define    MenuLIMIT     "limit"
#define    MenuSFLAG     "sflag"
#define    MenuINTR      "intr"
#define    MenuNOPOP     "nopop"
#define    MenuCHECK     "check"
#define    MenuPOINT     "point"
#define    MenuCLEAR     "clear"
#define    MenuQUERY     "query"
#define    MenuERDMP     "erdmp"
#define    MenuERUPD     "erupd"
#define    MenuNEXT      "next"
#define    MenuERLYR     "erlyr"
#define    MenuDREDT     "dredt"

#endif

