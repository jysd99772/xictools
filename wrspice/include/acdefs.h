
/*========================================================================*
 *                                                                        *
 *  XICTOOLS Integrated Circuit Design System                             *
 *  Copyright (c) 1996 Whiteley Research Inc, all rights reserved.        *
 *                                                                        *
 *                                                                        *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES      *
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-        *
 *   INFRINGEMENT.  IN NO EVENT SHALL STEPHEN R. WHITELEY BE LIABLE       *
 *   FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION      *
 *   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN           *
 *   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN         *
 *   THE SOFTWARE.                                                        *
 *                                                                        *
 *========================================================================*
 *                                                                        *
 * Whiteley Research Circuit Simulation and Analysis Tool                 *
 *                                                                        *
 *========================================================================*
 $Id: acdefs.h,v 2.49 2015/08/20 03:32:10 stevew Exp $
 *========================================================================*/

/***************************************************************************
JSPICE3 adaptation of Spice3e2 - Copyright (c) Stephen R. Whiteley 1992
Copyright 1990 Regents of the University of California.  All rights reserved.
Authors: 1985 Thomas L. Quarles
         1992 Stephen R. Whiteley
****************************************************************************/

#ifndef ACDEFS_H
#define ACDEFS_H

#include "dctdefs.h"

//
// Structures used to describe an AC analysis to be performed.
//

struct sACAN : public sDCTAN
{
    virtual ~sACAN() { }

    virtual sJOB *dup()
        {
            sACAN *ac = new sACAN;
            ac->b_name = b_name;
            ac->b_type = b_type;
            ac->JOBoutdata = new sOUTdata(*JOBoutdata);
            ac->JOBrun = JOBrun;
            ac->JOBdc = JOBdc;
            ac->JOBdc.uninit();
            ac->JOBac = JOBac;
            return (ac);
        }

    virtual bool threadable()   { return (true); }

    virtual int points(const sCKT *ckt)
        {
            return (JOBac.points(ckt));
        }

    sACprms JOBac;              // AC parameter storage
};

struct ACanalysis : public IFanalysis
{
    // acsetp.cc
    ACanalysis();
    int setParm(sJOB*, int, IFdata*);

    // acaskq.cc
    int askQuest(const sCKT*, const sJOB*, int, IFdata*) const;

    // acprse.cc
    int parse(sLine*, sCKT*, int, const char**, sTASK*);

    // acan.cc
    int anFunc(sCKT*, int);

    sJOB *newAnal() { return (new sACAN); }

private:
    static int ac_init(sCKT*);
    static int ac_dcoperation(sCKT*, int);
    static int ac_operation(sCKT*, int);
};

extern ACanalysis ACinfo;

#endif // ACDEFS_H

