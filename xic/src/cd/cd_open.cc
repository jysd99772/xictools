
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
 $Id: cd_open.cc,v 5.22 2015/04/18 16:44:56 stevew Exp $
 *========================================================================*/

#include "cd.h"
#include "cd_propnum.h"
#include "cd_celldb.h"
#include "fio.h"
#include "fio_library.h"


// Create a new cell if it doesn't already exist in the database, or
// clear and return an existing cell.  Make the cell consistent
// with the current cdNoElec state.
//
CDs *
cCD::ReopenCell(const char *spath, DisplayMode mode)
{
    const char *cname = lstring::strip_path(spath);
    if (!cname || !*cname) {
        Errs()->add_error(
            "ReopenCell: null or empty cell name encountered.");
        return (0);
    }

    CDs *sd = CDcdb()->findCell(CellNameTableFind(cname), mode);
    if (sd) {
        if (mode == Electrical && cdNoElec) {
            // Hmmm, we really don't want this cell, delete it.  This
            // clears it from the table.
            delete sd;
            sd = 0;
        }
        else {
            // Clear the contents.
            if (sd->isImmutable()) {
                Errs()->add_error(
                    "ReopenCell: can't overwrite immutable cell.");
                return (0);
            }
            sd->clear(true);
            sd->setUnread(false);
        }
    }
    else if (mode == Physical || (mode == Electrical && !cdNoElec))
        sd = CDcdb()->insertCell(cname, mode);
    return (sd);
}


// Open an existing cell, which if not in memory must be an inlined or
// top-level indirected native library cell.
//
OItype
cCD::OpenExisting(const char *spath, CDcbin *cbret)
{
    if (cbret)
        cbret->reset();
    const char *cname = lstring::strip_path(spath);
    if (!cname || !*cname) {
        Errs()->add_error(
            "OpenExisting: null or empty cell name encountered.");
        return (OIerror);
    }
    OItype oiret = OIok;
    CDcbin cbin;
    if (CDcdb()->findSymbol(CellNameTableFind(cname), &cbin))
        oiret = OIold;
    else {
        oiret = FIO()->OpenLibCell(
            0, cname, LIBdevice | LIBuser | LIBnativeOnly, &cbin);
        if (oiret == OIok && !cbin.phys() && !cbin.elec()) {
            Errs()->add_error("OpenExisting: unknown cell %s.", cname);
            return (OIerror);
        }
    }
    if (cbret)
        *cbret = cbin;
    return (oiret);
}


// Remove the cell from the database.
//
void
cCD::Close(CDcellName name)
{
    CDs *sd = CDcdb()->findCell(name, Physical);
    delete sd;
    sd = CDcdb()->findCell(name, Electrical);
    delete sd;
}


// Close cell 'name' and all descendents, if 'name' is top level.
// Close only descendents not referenced by a cell outside the
// hirearchy, and don't close device library cells.
//
void
cCD::Clear(CDcellName name)
{
    CDs *sdphys = CDcdb()->findCell(name, Physical);
    if (sdphys && sdphys->isSubcell())
        return;
    CDs *sdelec = CDcdb()->findCell(name, Electrical);
    if (sdelec && sdelec->isSubcell())
        return;

    SymTab *symtab = new SymTab(false, false);
    if (sdphys) {
        CDm_gen pgen(sdphys, GEN_MASTERS);
        for (CDm *mdesc = pgen.m_first(); mdesc; mdesc = pgen.m_next()) {
            CDs *msdesc = mdesc->celldesc();
            if (msdesc)
                symtab->add(mdesc->cellname()->string(), 0, true);
        }
        delete sdphys;
    }
    if (sdelec) {
        CDm_gen egen(sdelec, GEN_MASTERS);
        for (CDm *mdesc = egen.m_first(); mdesc; mdesc = egen.m_next()) {
            CDs *msdesc = mdesc->celldesc();
            if (msdesc && (!msdesc->isDevice() || !msdesc->isLibrary()))
                symtab->add(mdesc->cellname()->string(), 0, true);
        }
        delete sdelec;
    }
    SymTabGen ngen(symtab, true);
    SymTabEnt *h;
    while ((h = ngen.next()) != 0) {
        Clear((CDcellName)h->stTag);
        delete h;
    }
    delete symtab;
}

