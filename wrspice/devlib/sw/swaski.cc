
/*========================================================================*
 *                                                                        *
 *  Distributed by Whiteley Research Inc., Sunnyvale, California, USA     *
 *                       http://wrcad.com                                 *
 *  Copyright (C) 2017 Whiteley Research Inc., all rights reserved.       *
 *  Author: Stephen R. Whiteley, except as indicated.                     *
 *                                                                        *
 *  As fully as possible recognizing licensing terms and conditions       *
 *  imposed by earlier work from which this work was derived, if any,     *
 *  this work is released under the Apache License, Version 2.0 (the      *
 *  "License").  You may not use this file except in compliance with      *
 *  the License, and compliance with inherited licenses which are         *
 *  specified in a sub-header below this one if applicable.  A copy       *
 *  of the License is provided with this distribution, or you may         *
 *  obtain a copy of the License at                                       *
 *                                                                        *
 *        http://www.apache.org/licenses/LICENSE-2.0                      *
 *                                                                        *
 *  See the License for the specific language governing permissions       *
 *  and limitations under the License.                                    *
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
 *               XicTools Integrated Circuit Design System                *
 *                                                                        *
 * WRspice Circuit Simulation and Analysis Tool:  Device Library          *
 *                                                                        *
 *========================================================================*
 $Id:$
 *========================================================================*/

/***************************************************************************
JSPICE3 adaptation of Spice3f2 - Copyright (c) Stephen R. Whiteley 1992
Copyright 1990 Regents of the University of California.  All rights reserved.
Authors: 1987 Thomas L. Quarles
         1992 Stephen R. Whiteley
****************************************************************************/

#include "swdefs.h"


int
SWdev::askInst(const sCKT *ckt, const sGENinstance *geninst, int which,
    IFdata *data)
{
#ifdef WITH_CMP_GOTO
    // Order MUST match parameter definition enum!
    static void *array[] = {
        0, // notused
        0, // &&L_SW_IC_ON,
        0, // &&L_SW_IC_OFF,
        &&L_SW_IC,
        &&L_SW_CONTROL,
        &&L_SW_VOLTAGE,
        &&L_SW_CURRENT,
        &&L_SW_POWER,
        &&L_SW_POS_NODE,
        &&L_SW_NEG_NODE,
        &&L_SW_POS_CONT_NODE,
        &&L_SW_NEG_CONT_NODE};

    if ((unsigned int)which > SW_NEG_CONT_NODE)
        return (E_BADPARM);
#endif

    const sSWinstance *inst = static_cast<const sSWinstance*>(geninst);

    // Need to override this for non-real returns.
    data->type = IF_REAL;

#ifdef WITH_CMP_GOTO
    void *jmp = array[which];
    if (!jmp)
        return (E_BADPARM);
    goto *jmp;
    L_SW_IC:
        data->type = IF_FLAG;
        data->v.iValue = inst->SWzero_stateGiven;
        return (OK);
    L_SW_CONTROL:
        data->type = IF_INSTANCE;
        data->v.uValue = inst->SWcontName;
        return (OK);
    L_SW_VOLTAGE:
        if (ckt->CKTcurrentAnalysis & DOING_AC) {
            data->type = IF_COMPLEX;
            data->v.cValue.real = ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode);
            data->v.cValue.imag = ckt->irhsOld(inst->SWposNode) -
                ckt->irhsOld(inst->SWnegNode);
        }
        else {
            data->v.rValue = (ckt->rhsOld(inst->SWposNode)
                - ckt->rhsOld(inst->SWnegNode));
        }
        return (OK);
    L_SW_CURRENT:
        if (ckt->CKTcurrentAnalysis & DOING_AC) {
            data->type = IF_COMPLEX;
            data->v.cValue.real = (ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode))*inst->SWcond;
            data->v.cValue.imag = (ckt->irhsOld(inst->SWposNode) -
                ckt->irhsOld(inst->SWnegNode))*inst->SWcond;
        }
        else {
            data->v.rValue = (ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode))*inst->SWcond;
        }
        return (OK);
    L_SW_POWER:
        if (ckt->CKTcurrentAnalysis & DOING_AC)
            data->v.rValue = 0.0;
        else {
            data->v.rValue = ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode);
            data->v.rValue *= data->v.rValue * inst->SWcond;
        }
        return (OK);
    L_SW_POS_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWposNode;
        return (OK);
    L_SW_NEG_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWnegNode;
        return (OK);
    L_SW_POS_CONT_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWposCntrlNode;
        return (OK);
    L_SW_NEG_CONT_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWnegCntrlNode;
        return (OK);
#else
    switch (which) {
    case SW_IC:
        data->type = IF_FLAG;
        data->v.iValue = inst->SWzero_stateGiven;
        break;
    case SW_CONTROL:
        data->type = IF_INSTANCE;
        data->v.uValue = inst->SWcontName;
        break;
    case SW_VOLTAGE:
        if (ckt->CKTcurrentAnalysis & DOING_AC) {
            data->type = IF_COMPLEX;
            data->v.cValue.real = ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode);
            data->v.cValue.imag = ckt->irhsOld(inst->SWposNode) -
                ckt->irhsOld(inst->SWnegNode);
        }
        else {
            data->v.rValue = (ckt->rhsOld(inst->SWposNode)
                - ckt->rhsOld(inst->SWnegNode));
        }
        break;
    case SW_CURRENT:
        if (ckt->CKTcurrentAnalysis & DOING_AC) {
            data->type = IF_COMPLEX;
            data->v.cValue.real = (ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode))*inst->SWcond;
            data->v.cValue.imag = (ckt->irhsOld(inst->SWposNode) -
                ckt->irhsOld(inst->SWnegNode))*inst->SWcond;
        }
        else {
            data->v.rValue = (ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode))*inst->SWcond;
        }
        break;
    case SW_POWER:
        if (ckt->CKTcurrentAnalysis & DOING_AC)
            data->v.rValue = 0.0;
        else {
            data->v.rValue = ckt->rhsOld(inst->SWposNode) -
                ckt->rhsOld(inst->SWnegNode);
            data->v.rValue *= data->v.rValue * inst->SWcond;
        }
        break;
    case SW_POS_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWposNode;
        break;
    case SW_NEG_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWnegNode;
        break;
    case SW_POS_CONT_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWposCntrlNode;
        break;
    case SW_NEG_CONT_NODE:
        data->type = IF_INTEGER;
        data->v.iValue = inst->SWnegCntrlNode;
        break;
    default:
        return (E_BADPARM);
    }
#endif
    return (OK);
}

