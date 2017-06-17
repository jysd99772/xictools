
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
 * Device Library                                                         *
 *                                                                        *
 *========================================================================*
 $Id: capacld.cc,v 1.2 2011/07/13 18:26:58 stevew Exp $
 *========================================================================*/

/***************************************************************************
JSPICE3 adaptation of Spice3f2 - Copyright (c) Stephen R. Whiteley 1992
Copyright 1990 Regents of the University of California.  All rights reserved.
Authors: 1985 Thomas L. Quarles
         1992 Stephen R. Whiteley
****************************************************************************/

#include "capdefs.h"


int
CAPdev::acLoad(sGENmodel *genmod, sCKT *ckt)
{
    sCAPmodel *model = static_cast<sCAPmodel*>(genmod);
    for ( ; model; model = model->next()) {
        sCAPinstance *inst;
        for (inst = model->inst(); inst; inst = inst->next()) {

            double val = ckt->CKTomega * inst->CAPcapac;
            *(inst->CAPposPosptr +1) += val;
            *(inst->CAPnegNegptr +1) += val;
            *(inst->CAPposNegptr +1) -= val;
            *(inst->CAPnegPosptr +1) -= val;
        }
    }
    return (OK);
}

