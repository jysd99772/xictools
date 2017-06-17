
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
 $Id: soi3defs.h,v 2.20 2016/09/26 01:48:27 stevew Exp $
 *========================================================================*/

/**********
STAG version 2.6
Copyright 2000 owned by the United Kingdom Secretary of State for Defence
acting through the Defence Evaluation and Research Agency.
Developed by :     Jim Benson,
                   Department of Electronics and Computer Science,
                   University of Southampton,
                   United Kingdom.
With help from :   Nele D'Halleweyn, Bill Redman-White, and Craig Easson.

Based on STAG version 2.1
Developed by :     Mike Lee,
With help from :   Bernard Tenbroek, Bill Redman-White, Mike Uren, Chris Edwards
                   and John Bunyan.
Acknowledgements : Rupert Howes and Pete Mole.
**********/

#ifndef SOI3DEFS_H
#define SOI3DEFS_H

#include "device.h"

#define NEWCONV

#define FABS            fabs
#define REFTEMP         wrsREFTEMP       
#define CHARGE          wrsCHARGE        
#define CONSTCtoK       wrsCONSTCtoK     
#define CONSTboltz      wrsCONSTboltz    
#define CONSTvt0        wrsCONSTvt0      
#define CONSTKoverQ     wrsCONSTKoverQ   
#define CONSTroot2      wrsCONSTroot2    
#define CONSTe          wrsCONSTe        

namespace SOI3 {

struct sSOI3model;
struct sSOI3instance;

struct SOI3dev : public IFdevice
{
    SOI3dev();
    sGENmodel *newModl();
    sGENinstance *newInst();
    int destroy(sGENmodel**);
    int delInst(sGENmodel*, IFuid, sGENinstance*);
    int delModl(sGENmodel**, IFuid, sGENmodel*);

    void parse(int, sCKT*, sLine*);
//    int loadTest(sGENinstance*, sCKT*);   
    int load(sGENinstance*, sCKT*);   
    int setup(sGENmodel*, sCKT*, int*);  
    int unsetup(sGENmodel*, sCKT*);
    int resetup(sGENmodel*, sCKT*);
    int temperature(sGENmodel*, sCKT*);    
    int getic(sGENmodel*, sCKT*);  
//    int accept(sCKT*, sGENmodel*); 
    int trunc(sGENmodel*, sCKT*, double*);  
    int convTest(sGENmodel*, sCKT*);  

    int setInst(int, IFdata*, sGENinstance*);  
    int setModl(int, IFdata*, sGENmodel*);   
    int askInst(const sCKT*, const sGENinstance*, int, IFdata*);    
    int askModl(const sGENmodel*, int, IFdata*); 
//    int findBranch(sCKT*, sGENmodel*, IFuid); 

    int acLoad(sGENmodel*, sCKT*); 
//    int pzLoad(sGENmodel*, sCKT*, IFcomplex*); 
//    int disto(int, sGENmodel*, sCKT*);  
    int noise(int, int, sGENmodel*, sCKT*, sNdata*, double*);
};

struct sSOI3instance : public sGENinstance
{
    sSOI3instance()
        {
            memset(this, 0, sizeof(sSOI3instance));
            GENnumNodes = 7;
        }
    sSOI3instance *next()
        { return (static_cast<sSOI3instance*>(GENnextInstance)); }

    int SOI3dNode;  /* number of the drain node of the mosfet */
    int SOI3gfNode;  /* number of the front gate node of the mosfet */
    int SOI3sNode;  /* number of the source node of the mosfet */
    int SOI3gbNode;   /* number of the back gate node of the mosfet */
    int SOI3bNode;  /* number of the bulk node of the mosfet */
    int SOI3toutNode;  /* number of thermal output node (tout) */

    int SOI3branch; /* branch number for zero voltage source if no thermal */

    int SOI3dNodePrime; /* number of the internal drain node of the mosfet */
    int SOI3sNodePrime; /* number of the internal source node of the mosfet */

    int SOI3tout1Node; /* first internal thermal node */
    int SOI3tout2Node; /* second internal thermal node */
    int SOI3tout3Node; /* third internal thermal node */
    int SOI3tout4Node; /* fourth internal thermal node */

    double SOI3l;   /* the length of the channel region */
    double SOI3w;   /* the width of the channel region */
    
    double SOI3drainSquares;    /* the length of the drain in squares */
    double SOI3sourceSquares;   /* the length of the source in squares */
    
    double SOI3sourceConductance;   /*conductance of source(or 0):set in setup*/
    double SOI3drainConductance;    /*conductance of drain(or 0):set in setup*/
    double SOI3temp;    /* operating temperature of this instance */
    double SOI3rt;          /* Thermal resistance */
    double SOI3ct;          /* Thermal capacitance */
    double SOI3rt1;          /* 1st internal Thermal resistance */
    double SOI3ct1;          /* 1st internal Thermal capacitance */
    double SOI3rt2;          /* 2nd internal Thermal resistance */
    double SOI3ct2;          /* 2nd internal Thermal capacitance */
    double SOI3rt3;          /* 3rd internal Thermal resistance */
    double SOI3ct3;          /* 3rd internal Thermal capacitance */
    double SOI3rt4;          /* 4th internal Thermal resistance */
    double SOI3ct4;          /* 4th internal Thermal capacitance */


    double SOI3tTransconductance;   /* temperature corrected transconductance (KP param) */
    double SOI3ueff;                /* passed on to noise model */
    double SOI3tSurfMob;            /* temperature corrected surface mobility */
    double SOI3tPhi;                /* temperature corrected Phi */
    double SOI3tVto;                /* temperature corrected Vto */
    double SOI3tVfbF;               /* temperature corrected Vfb */
    double SOI3tVfbB;               /* temperature corrected Vfb (back gate) */
    double SOI3tSatCur;             /* temperature corrected jnct saturation Cur. */
    double SOI3tSatCur1;             /* temperature corrected jnct saturation Cur. */
    double SOI3tSatCurDens;         /* temperature corrected jnct saturation Cur. density */
    double SOI3tSatCurDens1;         /* temperature corrected jnct saturation Cur. density */
    double SOI3tCbd;                /* temperature corrected B-D Capacitance */
    double SOI3tCbs;                /* temperature corrected B-S Capacitance */
    double SOI3tCjsw;       /* temperature corrected Bulk side Capacitance */
    double SOI3tBulkPot;    /* temperature corrected Bulk potential */
    double SOI3tDepCap;     /* temperature adjusted transition point in */
                            /* the curve matching Fc * Vj */
    double SOI3tVbi;        /* temperature adjusted Vbi diode built-in voltage */

    double SOI3icVBS;   /* initial condition B-S voltage */
    double SOI3icVDS;   /* initial condition D-S voltage */
    double SOI3icVGFS;  /* initial condition GF-S voltage */
    double SOI3icVGBS;  /* initial condition GB-S voltage */
    double SOI3von;
    double SOI3vdsat;
    double SOI3sourceVcrit; /* Vcrit for pos. vds */
    double SOI3drainVcrit;  /* Vcrit for pos. vds */
    double SOI3id;          /* drain current */
    double SOI3ibs;         /* bulk source current */
    double SOI3ibd;         /* bulk drain current */
    double SOI3iMdb;        /* drain bulk impact ionisation current */
    double SOI3iMsb;        /* source bulk impact ionisation cur. (rev mode) */
    double SOI3iPt;         /* heat 'current' in thermal circuit */
    double SOI3gmbs;
    double SOI3gmf;
    double SOI3gmb;
    double SOI3gds;
    double SOI3gt;          /* change of channel current wrt deltaT */
    double SOI3gdsnotherm;  /* gds0 at elevated temp - ac use only) */
    double SOI3gMmbs;
    double SOI3gMmf;
    double SOI3gMmb;
    double SOI3gMd;
    double SOI3gMdeltaT;
    double SOI3iBJTdb;
    double SOI3gBJTdb_bs;
    double SOI3gBJTdb_deltaT;
    double SOI3iBJTsb;
    double SOI3gBJTsb_bd;
    double SOI3gBJTsb_deltaT;
    double SOI3gPmf;        /* change of Pt wrt vgfs */
    double SOI3gPmb;        /* change of Pt wrt vgbs */
    double SOI3gPmbs;       /* change of Pt wrt vbs */
    double SOI3gPds;        /* change of Pt wrt vds */
    double SOI3gPdT;        /* change of Pt wrt deltaT */
    double SOI3gbd;         /* for body drain current */
    double SOI3gbdT;        /* for body drain current */
    double SOI3gbs;         /* for body source current */
    double SOI3gbsT;        /* for body source current */
    double SOI3capbd;
    double SOI3capbs;
    double SOI3Cbd;
    double SOI3Cbs;
    double SOI3f2d;
    double SOI3f3d;
    double SOI3f4d;
    double SOI3f2s;
    double SOI3f3s;
    double SOI3f4s;
    double SOI3dDT_dVds;    /* sm-sig gT term */
    double SOI3dId_dDT;     /* sm-sig source term */
/*debug stuff*/
    double SOI3debug1;
    double SOI3debug2;
    double SOI3debug3;
    double SOI3debug4;
    double SOI3debug5;
    double SOI3debug6;
/* extra stuff for newer model - msll Jan96 */

/*
 * naming convention:
 * x = vgs
 * y = vbs
 * z = vds
 * cdr = cdrain
 */
    int SOI3mode;       /* device mode : 1 = normal, -1 = inverse */
    int SOI3backstate;  /* indicates charge condition of back surface */
    int SOI3numThermalNodes; /* Number of thermal nodes required */

    unsigned SOI3off:1;  /* non-zero to indicate device is off for dc analysis*/
    unsigned SOI3tempGiven :1;  /* instance temperature specified */
    unsigned SOI3lGiven :1;
    unsigned SOI3wGiven :1;
    unsigned SOI3drainSquaresGiven  :1;
    unsigned SOI3sourceSquaresGiven :1;
    unsigned SOI3dNodePrimeSet  :1;
    unsigned SOI3sNodePrimeSet  :1;
    unsigned SOI3icVBSGiven :1;
    unsigned SOI3icVDSGiven :1;
    unsigned SOI3icVGFSGiven:1;
    unsigned SOI3icVGBSGiven:1;
    unsigned SOI3rtGiven:1;
    unsigned SOI3ctGiven:1;
    unsigned SOI3rt1Given:1;
    unsigned SOI3ct1Given:1;
    unsigned SOI3rt2Given:1;
    unsigned SOI3ct2Given:1;
    unsigned SOI3rt3Given:1;
    unsigned SOI3ct3Given:1;
    unsigned SOI3rt4Given:1;
    unsigned SOI3ct4Given:1;
    unsigned SOI3vonGiven   :1;
    unsigned SOI3vdsatGiven :1;
    unsigned SOI3modeGiven  :1;


    double *SOI3D_dPtr;      /* pointer to sparse matrix element at
                                     * (Drain node,drain node) */
    double *SOI3GF_gfPtr;    /* pointer to sparse matrix element at
                                     * (front gate node,front gate node) */
    double *SOI3S_sPtr;      /* pointer to sparse matrix element at
                                     * (source node,source node) */
    double *SOI3B_bPtr;      /* pointer to sparse matrix element at
                                     * (bulk node,bulk node) */
    double *SOI3GB_gbPtr;    /* pointer to sparse matrix element at
                                     * (back gate node,back gate node) */
    double *SOI3DP_dpPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,drain prime node) */
    double *SOI3SP_spPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,source prime node) */
    double *SOI3D_dpPtr;     /* pointer to sparse matrix element at
                                     * (drain node,drain prime node) */
    double *SOI3GF_bPtr;     /* pointer to sparse matrix element at
                                     * (front gate node,bulk node) */
    double *SOI3GB_bPtr;     /* pointer to sparse matrix element at
                                     * (back gate node,bulk node) */
    double *SOI3GF_dpPtr;    /* pointer to sparse matrix element at
                                     * (front gate node,drain prime node) */
    double *SOI3GB_dpPtr;    /* pointer to sparse matrix element at
                                     * (back gate node,drain prime node) */
    double *SOI3GF_spPtr;    /* pointer to sparse matrix element at
                                     * (front gate node,source prime node) */
    double *SOI3GB_spPtr;    /* pointer to sparse matrix element at
                                     * (back gate node,source prime node) */
    double *SOI3S_spPtr;     /* pointer to sparse matrix element at
                                     * (source node,source prime node) */
    double *SOI3B_dpPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,drain prime node) */
    double *SOI3B_spPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,source prime node) */
    double *SOI3DP_spPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,source prime node) */
    double *SOI3DP_dPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,drain node) */
    double *SOI3B_gfPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,front gate node) */
    double *SOI3B_gbPtr;     /* pointer to sparse matrix element at
                                     * (bulk node,back gate node) */
    double *SOI3DP_gfPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,front gate node) */
    double *SOI3DP_gbPtr;    /* pointer to sparse matrix element at
                                     * (drain prime node,back gate node) */
    double *SOI3SP_gfPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,front gate node) */
    double *SOI3SP_gbPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,back gate node) */
    double *SOI3SP_sPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,source node) */
    double *SOI3DP_bPtr;     /* pointer to sparse matrix element at
                                     * (drain prime node,bulk node) */
    double *SOI3SP_bPtr;     /* pointer to sparse matrix element at
                                     * (source prime node,bulk node) */
    double *SOI3SP_dpPtr;    /* pointer to sparse matrix element at
                                     * (source prime node,drain prime node) */

/** Now for Thermal Node **/

    double *SOI3TOUT_toutPtr;
    double *SOI3TOUT_dpPtr;
    double *SOI3TOUT_gfPtr;
    double *SOI3TOUT_gbPtr;
    double *SOI3TOUT_bPtr;
    double *SOI3TOUT_spPtr;

    double *SOI3GF_toutPtr;
    double *SOI3DP_toutPtr;
    double *SOI3SP_toutPtr;
    
    double *SOI3TOUT_ibrPtr;  /* these are for zero voltage source should */
    double *SOI3IBR_toutPtr;  /* no thermal behaviour be specified */

    double *SOI3B_toutPtr;    /* for impact ionisation current source */

    double *SOI3TOUT_tout1Ptr;
    double *SOI3TOUT1_toutPtr;
    double *SOI3TOUT1_tout1Ptr;
    double *SOI3TOUT1_tout2Ptr;
    double *SOI3TOUT2_tout1Ptr;
    double *SOI3TOUT2_tout2Ptr;
    double *SOI3TOUT2_tout3Ptr;
    double *SOI3TOUT3_tout2Ptr;
    double *SOI3TOUT3_tout3Ptr;
    double *SOI3TOUT3_tout4Ptr;
    double *SOI3TOUT4_tout3Ptr;
    double *SOI3TOUT4_tout4Ptr;


/* indices to the array of SOI(3) noise sources */

#define SOI3RDNOIZ       0
#define SOI3RSNOIZ       1
#define SOI3IDNOIZ       2
#define SOI3FLNOIZ       3
#define SOI3TOTNOIZ      4

#define SOI3NSRCS     5     /* the number of SOI(3) noise sources */

#ifndef NONOISE
    double SOI3nVar[NSTATVARS][SOI3NSRCS];
#else /* NONOISE */
	double **SOI3nVar;
#endif /* NONOISE */
};

#define SOI3states GENstate

#define SOI3vbd  SOI3states+ 0   /* bulk-drain voltage */
#define SOI3vbs  SOI3states+ 1   /* bulk-source voltage */
#define SOI3vgfs SOI3states+ 2   /* front gate-source voltage */
#define SOI3vgbs SOI3states+ 3   /* back gate-source voltage */
#define SOI3vds  SOI3states+ 4   /* drain-source voltage */
#define SOI3deltaT SOI3states+ 5  /* final temperature difference */

#define SOI3qgf SOI3states + 6  /* front gate charge */
#define SOI3iqgf SOI3states +7  /* front gate current */

#define SOI3qgb SOI3states+  8  /* back gate charge */
#define SOI3iqgb SOI3states+ 9  /* back gate current */

#define SOI3qd SOI3states+  10 /* drain charge */
#define SOI3iqd SOI3states+ 11 /* drain current */

#define SOI3qs SOI3states+  14 /* body charge */
#define SOI3iqs SOI3states+ 15 /* body current */

#define SOI3cgfgf SOI3states+     16 
#define SOI3cgfd SOI3states+      17 
#define SOI3cgfs SOI3states+      18 
#define SOI3cgfdeltaT SOI3states+ 19 

#define SOI3cdgf SOI3states+      20 
#define SOI3cdd SOI3states+       21 
#define SOI3cds SOI3states+       22 
#define SOI3cddeltaT SOI3states+  23 

#define SOI3csgf SOI3states+      24 
#define SOI3csd SOI3states+       25 
#define SOI3css SOI3states+       26 
#define SOI3csdeltaT SOI3states+  27 

#define SOI3cgbgb SOI3states +    28
#define SOI3cgbsb SOI3states +    29
#define SOI3cgbdb SOI3states +    30

#define SOI3qbd SOI3states+    31  /* body-drain capacitor charge */
#define SOI3iqbd SOI3states+   32  /* body-drain capacitor current */

#define SOI3qbs SOI3states+    33  /* body-source capacitor charge */
#define SOI3iqbs SOI3states+   34  /* body-source capacitor current */

#define SOI3qt SOI3states+       35      /* Energy or 'charge' associated with ct */
#define SOI3iqt SOI3states+      36      /* equiv current source for ct */
#define SOI3qt1 SOI3states+       37      /* Energy or 'charge' associated with ct */
#define SOI3iqt1 SOI3states+      38      /* equiv current source for ct */
#define SOI3qt2 SOI3states+       39      /* Energy or 'charge' associated with ct */
#define SOI3iqt2 SOI3states+      40      /* equiv current source for ct */
#define SOI3qt3 SOI3states+       41      /* Energy or 'charge' associated with ct */
#define SOI3iqt3 SOI3states+      42      /* equiv current source for ct */
#define SOI3qt4 SOI3states+       43      /* Energy or 'charge' associated with ct */
#define SOI3iqt4 SOI3states+      44      /* equiv current source for ct */

#define SOI3qBJTbs SOI3states+    45
#define SOI3iqBJTbs SOI3states+   46

#define SOI3qBJTbd SOI3states+    47
#define SOI3iqBJTbd SOI3states+   48

#define SOI3cBJTbsbs SOI3states+     49
#define SOI3cBJTbsdeltaT SOI3states+ 50

#define SOI3cBJTbdbd SOI3states+     51
#define SOI3cBJTbddeltaT SOI3states+ 52

#define SOI3idrain SOI3states+ 53  /* final drain current at timepoint (no define) */

#define SOI3deltaT1 SOI3states+ 54  /* final temperature difference */
#define SOI3deltaT2 SOI3states+ 55  /* final temperature difference */
#define SOI3deltaT3 SOI3states+ 56  /* final temperature difference */
#define SOI3deltaT4 SOI3states+ 57  /* final temperature difference */
#define SOI3deltaT5 SOI3states+ 58  /* final temperature difference */

// SRW - interpolation
#define SOI3a_id SOI3states + 59
#define SOI3a_ibd SOI3states + 60
#define SOI3a_ibs SOI3states + 61

#define SOI3numStates 62

struct sSOI3model : sGENmodel
{
    sSOI3model()        { memset(this, 0, sizeof(sSOI3model)); }
    sSOI3model *next()  { return ((sSOI3model*)GENnextModel); }
    sSOI3instance *inst() { return ((sSOI3instance*)GENinstances); }

    double SOI3tnom;        /* temperature at which parameters measured */
    double SOI3latDiff;
    double SOI3jctSatCurDensity;    /* input - use tSatCurDens (jnct)*/
    double SOI3jctSatCurDensity1;    /* input - use tSatCurDens1 (jnct)*/
    double SOI3jctSatCur;   /* input - use tSatCur (jnct Is)*/
    double SOI3jctSatCur1;   /* input - use tSatCur1 (jnct Is)*/
    double SOI3drainResistance;
    double SOI3sourceResistance;
    double SOI3sheetResistance;
    double SOI3transconductance;    /* (KP) input - use tTransconductance */
    double SOI3frontGateSourceOverlapCapFactor;
    double SOI3frontGateDrainOverlapCapFactor;
    double SOI3frontGateBulkOverlapCapFactor;
    double SOI3backGateSourceOverlapCapFactor;
    double SOI3backGateDrainOverlapCapFactor;
    double SOI3backGateBulkOverlapCapFactor;
    double SOI3frontOxideCapFactor; /* Cof   NO DEFINES      */
    double SOI3backOxideCapFactor;  /* Cob       OR          */
    double SOI3bodyCapFactor;       /* Cb       FLAGS        */
    double SOI3C_bb;                /* Cb in series with Cob */
    double SOI3C_fb;                /* Cb in series with Cof */
    double SOI3C_ssf;               /* q*NQFF */
    double SOI3C_ssb;               /* q*NQFB */
    double SOI3C_fac;		    /* C_ob/(C_ob+C_b+C_ssb) */
    double SOI3vt0;    /* input - use tVto */
    double SOI3vfbF;   /* flat-band voltage. input - use tVfbF */
    double SOI3vfbB;   /* back flat-band voltage. input - use tVfbB */
    double SOI3gamma;   /* gamma */
    double SOI3gammaB;   /* back gamma */
    double SOI3capBD;   /* input - use tCbd */
    double SOI3capBS;   /* input - use tCbs */
    double SOI3sideWallCapFactor;   /* input - use tCjsw */
    double SOI3bulkJctPotential;    /* input - use tBulkPot */
    double SOI3bulkJctSideGradingCoeff; /* MJSW */
    double SOI3fwdCapDepCoeff;          /* FC */
    double SOI3phi; /* input - use tPhi */
    double SOI3vbi; /* input - use tVbi */
    double SOI3lambda;
    double SOI3theta;
    double SOI3substrateDoping;          /* Nsub */
    double SOI3substrateCharge;          /* Qb  - no define/flag */
    int SOI3gateType;        /* +1=same, -1=different, 0=Al */
    double SOI3frontFixedChargeDensity;
    double SOI3backFixedChargeDensity;
    double SOI3frontSurfaceStateDensity;
    double SOI3backSurfaceStateDensity;
    double SOI3frontOxideThickness;
    double SOI3backOxideThickness;
    double SOI3bodyThickness;
    double SOI3surfaceMobility; /* input - use tSurfMob */
    double SOI3oxideThermalConductivity;
    double SOI3siliconSpecificHeat;
    double SOI3siliconDensity;
    double SOI3fNcoef;
    double SOI3fNexp;
/* new stuff for newer model - msll Jan96 */
    double SOI3sigma; /* DIBL factor */
    double SOI3chiFB;   /* temperature coeff of flatband voltage */
    double SOI3chiPHI;  /* temperature coeff of PHI */
    double SOI3deltaW; /* narrow width effect factor */
    double SOI3deltaL; /* short channel effect factor */
    double SOI3vsat;   /* input - saturation velocity, use tVsat */
    double SOI3TVF0;   /* internal use - precalculation of exp to save time */
    double SOI3k;      /* thermal exponent for mobility factor */
    double SOI3lx;     /* channel length modulation factor */
    double SOI3vp;     /* channel length modulation empirical voltage */
    double SOI3eta;    /* Imp. ion. field adjustment factor */
    double SOI3alpha0;   /* 1st impact ionisation coeff */
    double SOI3beta0;   /* 2nd impact ionisation coeff */
    double SOI3lm;     /* impact ion. drain region length cf LX */
    double SOI3lm1;    /* impact ion. drain region coeff */
    double SOI3lm2;    /* impact ion. drain region coeff */
    double SOI3etad;   /* diode ideality factor */
    double SOI3etad1;   /* 2nd diode ideality factor */
    double SOI3chibeta; /* temp coeff of BETA0 */
    double SOI3chid;    /* temp factor for junction 1 */
    double SOI3chid1;   /* temp factor for junction 2 */
    int    SOI3dvt;     /* switch for temp dependence of vt in diodes */
    int    SOI3nLev;    /* level switch for noise model */
    double SOI3betaBJT; /* beta for Eber Moll BJT model */
    double SOI3tauFBJT;   /* forward BJT transit time */
    double SOI3tauRBJT;   /* reverse BJT transit time */
    double SOI3betaEXP;
    double SOI3tauEXP;
    double SOI3rsw;      /* source resistance width scaling factor */
    double SOI3rdw;      /* drain resistance width scaling factor */
    double SOI3minimumFeatureSize;     /* minimum feature size of simulated process technology */
    double SOI3vtex;       /* Extracted threshold voltage */
    double SOI3vdex;       /* Drain bias at which vtex extracted */
    double SOI3delta0;     /* Surface potential factor for vtex conversion */
    double SOI3satChargeShareFactor;     /* Saturation region charge sharing factor */
    double SOI3nplusDoping;     /* Doping concentration of N+ or P+ regions */
    double SOI3rta;     /* thermal resistance area scaling factor */
    double SOI3cta;     /* thermal capacitance area scaling factor */

    int SOI3type;       /* device type : 1 = nsoi,  -1 = psoi */

    unsigned SOI3typeGiven  :1;
    unsigned SOI3latDiffGiven   :1;
    unsigned SOI3jctSatCurDensityGiven  :1;
    unsigned SOI3jctSatCurDensity1Given  :1;
    unsigned SOI3jctSatCurGiven :1;
    unsigned SOI3jctSatCur1Given :1;
    unsigned SOI3drainResistanceGiven   :1;
    unsigned SOI3sourceResistanceGiven  :1;
    unsigned SOI3sheetResistanceGiven   :1;
    unsigned SOI3transconductanceGiven  :1;
    unsigned SOI3frontGateSourceOverlapCapFactorGiven    :1;
    unsigned SOI3frontGateDrainOverlapCapFactorGiven :1;
    unsigned SOI3frontGateBulkOverlapCapFactorGiven  :1;
    unsigned SOI3backGateSourceOverlapCapFactorGiven    :1;
    unsigned SOI3backGateDrainOverlapCapFactorGiven :1;
    unsigned SOI3backGateBulkOverlapCapFactorGiven  :1;
    unsigned SOI3subsBiasFactorGiven  :1;
    unsigned SOI3bodyFactorGiven      :1;
    unsigned SOI3vt0Given   :1;
    unsigned SOI3vfbFGiven  :1;
    unsigned SOI3vfbBGiven  :1;
    unsigned SOI3gammaGiven :1;
    unsigned SOI3gammaBGiven :1;
    unsigned SOI3capBDGiven :1;
    unsigned SOI3capBSGiven :1;
    unsigned SOI3sideWallCapFactorGiven   :1;
    unsigned SOI3bulkJctPotentialGiven  :1;
    unsigned SOI3bulkJctSideGradingCoeffGiven   :1;
    unsigned SOI3fwdCapDepCoeffGiven    :1;
    unsigned SOI3phiGiven   :1;
    unsigned SOI3lambdaGiven    :1;
    unsigned SOI3thetaGiven     :1;
    unsigned SOI3substrateDopingGiven   :1;
    unsigned SOI3gateTypeGiven  :1;
    unsigned SOI3frontFixedChargeDensityGiven   :1;
    unsigned SOI3backFixedChargeDensityGiven   :1;
    unsigned SOI3frontSurfaceStateDensityGiven   :1;
    unsigned SOI3backSurfaceStateDensityGiven  :1;
    unsigned SOI3frontOxideThicknessGiven   :1;
    unsigned SOI3backOxideThicknessGiven   :1;
    unsigned SOI3bodyThicknessGiven   :1;
    unsigned SOI3surfaceMobilityGiven   :1;
    unsigned SOI3tnomGiven  :1;
    unsigned SOI3oxideThermalConductivityGiven  :1;
    unsigned SOI3siliconSpecificHeatGiven  :1;
    unsigned SOI3siliconDensityGiven :1;
    unsigned SOI3fNcoefGiven :1;
    unsigned SOI3fNexpGiven :1;
/* extra stuff for newer model - msll Jan96 */
    unsigned SOI3sigmaGiven                :1;
    unsigned SOI3chiFBGiven                :1;
    unsigned SOI3chiPHIGiven               :1;
    unsigned SOI3deltaWGiven               :1;
    unsigned SOI3deltaLGiven               :1;
    unsigned SOI3vsatGiven                 :1;
    unsigned SOI3kGiven                    :1;
    unsigned SOI3lxGiven                   :1;
    unsigned SOI3vpGiven                   :1;
    unsigned SOI3useLAMBDA                 :1;
    unsigned SOI3etaGiven                  :1;
    unsigned SOI3alpha0Given               :1;
    unsigned SOI3beta0Given                :1;
    unsigned SOI3lmGiven                   :1;
    unsigned SOI3lm1Given                  :1;
    unsigned SOI3lm2Given                  :1;
    unsigned SOI3etadGiven                 :1;
    unsigned SOI3etad1Given                :1;
    unsigned SOI3chibetaGiven              :1;
    unsigned SOI3chidGiven                 :1;
    unsigned SOI3chid1Given                :1;
    unsigned SOI3dvtGiven                  :1;
    unsigned SOI3nLevGiven                 :1;
    unsigned SOI3betaBJTGiven              :1;
    unsigned SOI3tauFBJTGiven              :1;
    unsigned SOI3tauRBJTGiven              :1;
    unsigned SOI3betaEXPGiven              :1;
    unsigned SOI3tauEXPGiven               :1;
    unsigned SOI3rswGiven                  :1;
    unsigned SOI3rdwGiven                  :1;
    unsigned SOI3minimumFeatureSizeGiven   :1;
    unsigned SOI3vtexGiven                 :1;
    unsigned SOI3vdexGiven                 :1;
    unsigned SOI3delta0Given               :1;
    unsigned SOI3satChargeShareFactorGiven :1;
    unsigned SOI3nplusDopingGiven          :1;
    unsigned SOI3rtaGiven                  :1;
    unsigned SOI3ctaGiven                  :1;
};

} // namespace SOI3
using namespace SOI3;


#ifndef NSOI3
#define NSOI3 1
#define PSOI3 -1
#endif

// device parameters
enum {
    SOI3_W = 1,
    SOI3_L,
    SOI3_AS,
    SOI3_AD,
    SOI3_PS,
    SOI3_PD,
    SOI3_NRS,
    SOI3_NRD,
    SOI3_OFF,
    SOI3_IC,
    SOI3_IC_VBS,
    SOI3_IC_VDS,
    SOI3_IC_VGFS,
    SOI3_IC_VGBS,
    SOI3_W_SENS,
    SOI3_L_SENS,
    SOI3_IB,
    SOI3_IGF,
    SOI3_IGB,
    SOI3_IS,
    SOI3_POWER,
    SOI3_TEMP,

    SOI3_DNODE,
    SOI3_GFNODE,
    SOI3_SNODE,
    SOI3_GBNODE,
    SOI3_BNODE,
    SOI3_DNODEPRIME,
    SOI3_SNODEPRIME,
    SOI3_TNODE,
    SOI3_BRANCH,
    SOI3_SOURCECONDUCT,
    SOI3_DRAINCONDUCT,
    SOI3_VON,
    SOI3_VFBF,
    SOI3_VDSAT,
    SOI3_SOURCEVCRIT,
    SOI3_DRAINVCRIT,
    SOI3_ID,
    SOI3_IBS,
    SOI3_IBD,
    SOI3_GMBS,
    SOI3_GMF,
    SOI3_GMB,
    SOI3_GDS,
    SOI3_GBD,
    SOI3_GBS,
    SOI3_CAPBD,
    SOI3_CAPBS,
    SOI3_CAPZEROBIASBD,
    SOI3_CAPZEROBIASBDSW,
    SOI3_CAPZEROBIASBS,
    SOI3_CAPZEROBIASBSSW,
    SOI3_VBD,
    SOI3_VBS,
    SOI3_VGFS,
    SOI3_VGBS,
    SOI3_VDS,
    SOI3_QGF,
    SOI3_IQGF,
    SOI3_QGB,
    SOI3_IQGB,
    SOI3_QD,
    SOI3_IQD,
    SOI3_QS,
    SOI3_IQS,
    SOI3_QBD,
    SOI3_IQBD,
    SOI3_QBS,
    SOI3_IQBS,
    SOI3_CGFGF,
    SOI3_CGFD,
    SOI3_CGFS,
    SOI3_CGFDELTAT,
    SOI3_CDGF,
    SOI3_CDD,
    SOI3_CDS,
    SOI3_CDDELTAT,
    SOI3_CSGF,
    SOI3_CSD,
    SOI3_CSS,
    SOI3_CSDELTAT,
    SOI3_L_SENS_REAL,
    SOI3_L_SENS_IMAG,
    SOI3_L_SENS_MAG,
    SOI3_L_SENS_PH,
    SOI3_L_SENS_CPLX,
    SOI3_W_SENS_REAL,
    SOI3_W_SENS_IMAG,
    SOI3_W_SENS_MAG,
    SOI3_W_SENS_PH,
    SOI3_W_SENS_CPLX,
    SOI3_L_SENS_DC,
    SOI3_W_SENS_DC,
    SOI3_RT,
    SOI3_CT,
    // extra stuff for newer model - msll Jan96
    SOI3_VFBB,
    SOI3_RT1,
    SOI3_CT1,
    SOI3_RT2,
    SOI3_CT2,
    SOI3_RT3,
    SOI3_CT3,
    SOI3_RT4,
    SOI3_CT4
};

// model parameters
enum {
    SOI3_MOD_VTO = 1000,
    SOI3_MOD_VFBF,
    SOI3_MOD_KP,
    SOI3_MOD_GAMMA,
    SOI3_MOD_PHI,
    SOI3_MOD_LAMBDA,
    SOI3_MOD_THETA,
    SOI3_MOD_RD,
    SOI3_MOD_RS,
    SOI3_MOD_CBD,
    SOI3_MOD_CBS,
    SOI3_MOD_IS,
    SOI3_MOD_PB,
    SOI3_MOD_CGFSO,
    SOI3_MOD_CGFDO,
    SOI3_MOD_CGFBO,
    SOI3_MOD_CGBSO,
    SOI3_MOD_CGBDO,
    SOI3_MOD_CGB_BO,
    SOI3_MOD_CJ,
    SOI3_MOD_MJ,
    SOI3_MOD_CJSW,
    SOI3_MOD_MJSW,
    SOI3_MOD_JS,
    SOI3_MOD_TOF,
    SOI3_MOD_TOB,
    SOI3_MOD_TB,
    SOI3_MOD_LD,
    SOI3_MOD_RSH,
    SOI3_MOD_U0,
    SOI3_MOD_FC,
    SOI3_MOD_NSUB,
    SOI3_MOD_TPG,
    SOI3_MOD_NQFF,
    SOI3_MOD_NQFB,
    SOI3_MOD_NSSF,
    SOI3_MOD_NSSB,
    SOI3_MOD_NSOI3,
    SOI3_MOD_PSOI3,
    SOI3_MOD_TNOM,
    SOI3_MOD_KF,
    SOI3_MOD_AF,
    SOI3_MOD_KOX,
    SOI3_MOD_SHSI,
    // extra stuff for newer model - msll Jan96
    SOI3_MOD_SIGMA,
    SOI3_MOD_CHIFB,
    SOI3_MOD_CHIPHI,
    SOI3_MOD_DELTAW,
    SOI3_MOD_DELTAL,
    SOI3_MOD_VSAT,
    SOI3_MOD_K,
    SOI3_MOD_LX,
    SOI3_MOD_VP,
    SOI3_MOD_ETA,
    SOI3_MOD_ALPHA0,
    SOI3_MOD_BETA0,
    SOI3_MOD_LM,
    SOI3_MOD_LM1,
    SOI3_MOD_LM2,
    SOI3_MOD_ETAD,
    SOI3_MOD_ETAD1,
    SOI3_MOD_IS1,
    SOI3_MOD_JS1,
    SOI3_MOD_CHIBETA,
    SOI3_MOD_VFBB,
    SOI3_MOD_GAMMAB,
    SOI3_MOD_CHID,
    SOI3_MOD_CHID1,
    SOI3_MOD_DVT,
    SOI3_MOD_NLEV,
    SOI3_MOD_BETABJT,
    SOI3_MOD_TAUFBJT,
    SOI3_MOD_TAURBJT,
    SOI3_MOD_BETAEXP,
    SOI3_MOD_TAUEXP,
    SOI3_MOD_RSW,
    SOI3_MOD_RDW,
    SOI3_MOD_FMIN,
    SOI3_MOD_VTEX,
    SOI3_MOD_VDEX,
    SOI3_MOD_DELTA0,
    SOI3_MOD_CSF,
    SOI3_MOD_DSI,
    SOI3_MOD_NPLUS,
    SOI3_MOD_RTA,
    SOI3_MOD_CTA
};

#endif // SOI3DEFS_H

