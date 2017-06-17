
/*========================================================================*
 *                                                                        *
 *  XICTOOLS Integrated Circuit Design System                             *
 *  Copyright (c) 2013 Whiteley Research Inc, all rights reserved.        *
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
 $Id: oa_nametab.h,v 1.5 2016/03/08 04:52:19 stevew Exp $
 *========================================================================*/

#ifndef OA_NAMETAB_H
#define OA_NAMETAB_H

//
// The name table, used when reading cells from OA to determine which
// cells have already been read, and performs name aliasing to avoid
// conflicts.  This is persistent and accumulative until explicitly
// cleared.
//

// Status flags used in the cellname table.
//
#define OAL_READP   0x1
#define OAL_READE   0x2
#define OAL_READS   0x4
#define OAL_NOOA    0x8
#define OAL_REFP    0x10
#define OAL_REFE    0x20
//
// OAL_READP: Have read maskLayer data for cell.
// OAL_READE: Have read schematic data for cell.
// OAL_READS: Have read symbolic data for cell.
// OAL_NOOA:  Cell was referenced, but not resolved in OA libraries.
// OAL_REFP:  Cell was referenced in layout data.
// OAL_REFE:  Cell was referenced in schematic data.

// Name of the Virtuoso analogLib.
#define ANALOG_LIB      "analogLib"

// Cells from the ANALOG_LIB will be given this prefix.
#define ANALOG_LIB_PFX  "alib_"

// The class provides two interfaces:  The find/update functions keep
// track of the Xic cell names created, with a status flag.  The
// getMasterName group takes care of cell name aliasing.  Aliasing is
// needed to avoid name clashes with Xic library devices, and in the
// situation where a design reads the same cell name from two
// different libraries.  It also generates pcell sub-master names.

class cOAnameTab
{
public:
    cOAnameTab();
    ~cOAnameTab();

    unsigned long findCname(const oaString &cname)
        {
            if (!nt_cname_tab)
                return (0);
            return (findCname(CD()->CellNameTableAdd(cname)));
        }

    void updateCname(const oaString &cname, unsigned long f)
        {
            updateCname(CD()->CellNameTableAdd(cname), f);
        }

    SymTab *cnameTab()          { return (nt_cname_tab); }

    unsigned long findCname(CDcellName);
    void updateCname(CDcellName, unsigned long);
    void clearCnameTab();

    CDcellName getMasterName(const oaScalarName&, const oaScalarName&,
        const oaScalarName&, const oaParamArray&, bool);
    CDcellName cellNameAlias(const oaScalarName&, const oaScalarName&, bool);
    CDcellName getNewName(CDcellName);
    stringlist *listLibNames();

private:
    SymTab *nt_cname_tab;       // Xic cellname -> flags
    SymTab *nt_libtab_tab;      // libname -> cellname table -> Xic cellname
};

#endif

