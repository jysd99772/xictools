
/*========================================================================*
 *                                                                        *
 *  Whiteley Research Inc, Sunnyvale, CA USA, http://wrcad.com            *
 *  Copyright (C) 2017 Whiteley Research Inc, all rights reserved.        *
 *                                                                        *
 *  Licensed under the Apache License, Version 2.0 (the "License");       *
 *  you may not use this file except in compliance with the License.      *
 *  You may obtain a copy of the License at                               *
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

/***********************************************************************
 HiSIM (Hiroshima University STARC IGFET Model)
 Copyright (C) 2003 STARC

 VERSION : HiSIM 1.2.0
 FILE : hsm1acld.c of HiSIM 1.2.0

 April 9, 2003 : released by STARC Physical Design Group
***********************************************************************/

#include "hsm1defs.h"
#include "gencurrent.h"

#define HSM1nextModel      next()
#define HSM1nextInstance   next()
#define HSM1instances      inst()


int
HSM1dev::acLoad(sGENmodel *genmod, sCKT *ckt)
{
    sHSM1model *model = static_cast<sHSM1model*>(genmod);
    sHSM1instance *here;

  double xcggb, xcgdb, xcgsb, xcbgb, xcbdb, xcbsb, xcddb, xcssb, xcdgb;
  double gdpr, gspr, gds, gbd, gbs, capbd, capbs, xcsgb, xcdsb, xcsdb;
  double cggb, cgdb, cgsb, cbgb, cbdb, cbsb, cddb, cdgb, cdsb, omega;
  double cgso, cgdo, cgbo, FwdSum, RevSum, gm, gmbs;
  double gbspsp, gbbdp, gbbsp, gbspg, gbspb;
  double gbspdp, gbdpdp, gbdpg, gbdpb, gbdpsp;
  double gIbtotg, gIbtotd, gIbtots, gIbtotb;
  double gIgtotg, gIgtotd, gIgtots, gIgtotb;
  double gIdtotg, gIdtotd, gIdtots, gIdtotb;
  double gIstotg, gIstotd, gIstots, gIstotb;

  omega = ckt->CKTomega;
  for ( ; model != NULL; model = model->HSM1nextModel ) {
    for ( here = model->HSM1instances; here!= NULL;
          here = here->HSM1nextInstance ) {
      if ( here->HSM1_mode >= 0 ) {
        gm = here->HSM1_gm;
        gmbs = here->HSM1_gmbs;
        FwdSum = gm + gmbs;
        RevSum = 0.0;
        
        gbbdp = -here->HSM1_gbds;
        gbbsp = here->HSM1_gbds + here->HSM1_gbgs + here->HSM1_gbbs;
        
        gbdpg = here->HSM1_gbgs;
        gbdpb = here->HSM1_gbbs;
        gbdpdp = here->HSM1_gbds;
        gbdpsp = -(gbdpg + gbdpb + gbdpdp);
        
        gbspdp = 0.0;
        gbspg = 0.0;
        gbspb = 0.0;
        gbspsp = 0.0;

        if (model->HSM1_coiigs) {
          gIbtotg = here->HSM1_gigbg;
          gIbtotd = here->HSM1_gigbd;
          gIbtots = here->HSM1_gigbs;
          gIbtotb = here->HSM1_gigbb;

          gIstotg = here->HSM1_gigsg;
          gIstotd = here->HSM1_gigsd;
          gIstots = here->HSM1_gigss;
          gIstotb = here->HSM1_gigsb;

          gIdtotg = here->HSM1_gigdg;
          gIdtotd = here->HSM1_gigdd;
          gIdtots = here->HSM1_gigds;
          gIdtotb = here->HSM1_gigdb;
        }
        else {
          gIbtotg = gIbtotd = gIbtots = gIbtotb = 0.0;
          gIstotg = gIstotd = gIstots = gIstotb = 0.0;
          gIdtotg = gIdtotd = gIdtots = gIdtotb = 0.0;
        }

        if (model->HSM1_coiigs) {
          gIgtotg = gIbtotg + gIstotg + gIdtotg;
          gIgtotd = gIbtotd + gIstotd + gIdtotd;
          gIgtots = gIbtots + gIstots + gIdtots;
          gIgtotb = gIbtotb + gIstotb + gIdtotb;
        }
        else
          gIgtotg = gIgtotd = gIgtots = gIgtotb = 0.0;
        
        cggb = here->HSM1_cggb;
        cgsb = here->HSM1_cgsb;
        cgdb = here->HSM1_cgdb;

        cbgb = here->HSM1_cbgb;
        cbsb = here->HSM1_cbsb;
        cbdb = here->HSM1_cbdb;
          
        cdgb = here->HSM1_cdgb;
        cdsb = here->HSM1_cdsb;
        cddb = here->HSM1_cddb;
      }                  
      else {
        gm = -here->HSM1_gm;
        gmbs = -here->HSM1_gmbs;
        FwdSum = 0.0;
        RevSum = -(gm + gmbs);
        
        gbbsp = -here->HSM1_gbds;
        gbbdp = here->HSM1_gbds + here->HSM1_gbgs + here->HSM1_gbbs;
        
        gbdpg = 0.0;
        gbdpsp = 0.0;
        gbdpb = 0.0;
        gbdpdp = 0.0;

        gbspg = here->HSM1_gbgs;
        gbspsp = here->HSM1_gbds;
        gbspb = here->HSM1_gbbs;
        gbspdp = -(gbspg + gbspsp + gbspb);

        if (model->HSM1_coiigs) {
          gIbtotg = here->HSM1_gigbg;
          gIbtotd = here->HSM1_gigbs;
          gIbtots = here->HSM1_gigbd;
          gIbtotb = here->HSM1_gigbb;

          gIstotg = here->HSM1_gigsg;
          gIstotd = here->HSM1_gigss;
          gIstots = here->HSM1_gigsd;
          gIstotb = here->HSM1_gigsb;

          gIdtotg = here->HSM1_gigdg;
          gIdtotd = here->HSM1_gigds;
          gIdtots = here->HSM1_gigdd;
          gIdtotb = here->HSM1_gigdb;
        }
        else {
          gIbtotg = gIbtotd = gIbtots = gIbtotb = 0.0;
          gIstotg = gIstotd = gIstots = gIstotb = 0.0;
          gIdtotg = gIdtotd = gIdtots = gIdtotb = 0.0;
        }
        
        if (model->HSM1_coiigs) {
          gIgtotg = gIbtotg + gIstotg + gIdtotg;
          gIgtotd = gIbtotd + gIstotd + gIdtotd;
          gIgtots = gIbtots + gIstots + gIdtots;
          gIgtotb = gIbtotb + gIstotb + gIdtotb;
        }
        else
          gIgtotg = gIgtotd = gIgtots = gIgtotb = 0.0;
        
        cggb = here->HSM1_cggb;
        cgsb = here->HSM1_cgdb;
        cgdb = here->HSM1_cgsb;
        
        cbgb = here->HSM1_cbgb;
        cbsb = here->HSM1_cbdb;
        cbdb = here->HSM1_cbsb;
        
        cdgb = -(here->HSM1_cdgb + cggb + cbgb);
        cdsb = -(here->HSM1_cddb + cgsb + cbsb);
        cddb = -(here->HSM1_cdsb + cgdb + cbdb);
      }
      
      gdpr = here->HSM1drainConductance;
      gspr = here->HSM1sourceConductance;
      gds = here->HSM1_gds;
      gbd = here->HSM1_gbd;
      gbs = here->HSM1_gbs;
      capbd = here->HSM1_capbd;
      capbs = here->HSM1_capbs;
      
      cgso = here->HSM1_cgso;
      cgdo = here->HSM1_cgdo;
      cgbo = here->HSM1_cgbo;
      
      xcdgb = (cdgb - cgdo) * omega;
      xcddb = (cddb + capbd + cgdo) * omega;
      xcdsb = cdsb * omega;
      xcsgb = -(cggb + cbgb + cdgb + cgso) * omega;
      xcsdb = -(cgdb + cbdb + cddb) * omega;
      xcssb = (capbs + cgso - (cgsb + cbsb + cdsb)) * omega;
      xcggb = (cggb + cgdo + cgso + cgbo) * omega;
      xcgdb = (cgdb - cgdo) * omega;
      xcgsb = (cgsb - cgso) * omega;
      xcbgb = (cbgb - cgbo) * omega;
      xcbdb = (cbdb - capbd) * omega;
      xcbsb = (cbsb - capbs) * omega;

      *(here->HSM1GgPtr +1) += xcggb;
      *(here->HSM1GgPtr) += gIgtotg;
      *(here->HSM1BbPtr +1) -= xcbgb + xcbdb + xcbsb;
      *(here->HSM1DPdpPtr +1) += xcddb;
      *(here->HSM1SPspPtr +1) += xcssb;
      *(here->HSM1GbPtr +1) -= xcggb + xcgdb + xcgsb;
      *(here->HSM1GbPtr) += gIgtotb;
      *(here->HSM1GdpPtr +1) += xcgdb;
      *(here->HSM1GdpPtr) += gIgtotd;
      *(here->HSM1GspPtr +1) += xcgsb;
      *(here->HSM1GspPtr) += gIgtots;
      *(here->HSM1BgPtr +1) += xcbgb;
      *(here->HSM1BdpPtr +1) += xcbdb;
      *(here->HSM1BspPtr +1) += xcbsb;
      *(here->HSM1DPgPtr +1) += xcdgb;
      *(here->HSM1DPbPtr +1) -= xcdgb + xcddb + xcdsb;
      *(here->HSM1DPspPtr +1) += xcdsb;
      *(here->HSM1SPgPtr +1) += xcsgb;
      *(here->HSM1SPbPtr +1) -= xcsgb + xcsdb + xcssb;
      *(here->HSM1SPdpPtr +1) += xcsdb;

      *(here->HSM1DdPtr) += gdpr;
      *(here->HSM1SsPtr) += gspr;
      *(here->HSM1BbPtr) += gbd + gbs - here->HSM1_gbbs - gIbtotb;
      *(here->HSM1DPdpPtr) += gdpr + gds + gbd + RevSum + gbdpdp;
      *(here->HSM1SPspPtr) += gspr + gds + gbs + FwdSum + gbspsp;
      
      *(here->HSM1DdpPtr) -= gdpr;
      *(here->HSM1SspPtr) -= gspr;

      *(here->HSM1BgPtr) -= here->HSM1_gbgs + gIbtotg;
      *(here->HSM1BdpPtr) -= gbd - gbbdp + gIbtotd;
      *(here->HSM1BspPtr) -= gbs - gbbsp + gIbtots;

      *(here->HSM1DPdPtr) += gdpr - gIdtotd;
      *(here->HSM1DPgPtr) += gm + gbdpg - gIdtotg;
      *(here->HSM1DPbPtr) -= gbd - gmbs - gbdpb + gIdtotb;
      *(here->HSM1DPspPtr) -= gds + FwdSum - gbdpsp + gIdtots;
      
      *(here->HSM1SPgPtr) -= gm - gbspg + gIstotg;
      *(here->HSM1SPsPtr) -= gspr - gIstots;
      *(here->HSM1SPbPtr) -= gbs + gmbs - gbspb + gIstotb;
      *(here->HSM1SPdpPtr) -= gds + RevSum - gbspdp + gIstotd;

      /* stamp gidl */
      *(here->HSM1DPdpPtr) += here->HSM1_gigidlds;
      *(here->HSM1DPgPtr) += here->HSM1_gigidlgs;
      *(here->HSM1DPspPtr) -= (here->HSM1_gigidlgs + 
                               here->HSM1_gigidlds + here->HSM1_gigidlbs);
      *(here->HSM1DPbPtr) += here->HSM1_gigidlbs;
      *(here->HSM1BdpPtr) -= here->HSM1_gigidlds;
      *(here->HSM1BgPtr) -= here->HSM1_gigidlgs;
      *(here->HSM1BspPtr) += (here->HSM1_gigidlgs + 
                              here->HSM1_gigidlds + here->HSM1_gigidlbs);
      *(here->HSM1BbPtr) -= here->HSM1_gigidlbs;
      /* stamp gisl */
      *(here->HSM1SPdpPtr) -= (here->HSM1_gigislsd + 
                               here->HSM1_gigislgd + here->HSM1_gigislbd);
      *(here->HSM1SPgPtr) += here->HSM1_gigislgd;
      *(here->HSM1SPspPtr) += here->HSM1_gigislsd;
      *(here->HSM1SPbPtr) += here->HSM1_gigislbd;
      *(here->HSM1BdpPtr) += (here->HSM1_gigislgd + 
                              here->HSM1_gigislsd + here->HSM1_gigislbd);
      *(here->HSM1BgPtr) -= here->HSM1_gigislgd;
      *(here->HSM1BspPtr) -= here->HSM1_gigislsd;
      *(here->HSM1BbPtr) -= here->HSM1_gigislbd;
      
      /*
      *(here->HSM1GgPtr) -= xgtg;
      *(here->HSM1GbPtr) -= xgtb;
      *(here->HSM1GdpPtr) -= xgtd;
      *(here->HSM1GspPtr) -= xgts;
      */
      
    }
  }
  return(OK);
}
