
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
 $Id: misc.h,v 2.65 2015/06/20 01:58:12 stevew Exp $
 *========================================================================*/

/***************************************************************************
JSPICE3 adaptation of Spice3e2 - Copyright (c) Stephen R. Whiteley 1992
Copyright 1990 Regents of the University of California.  All rights reserved.
Authors: 1986 Wayne A. Christopher
         1992 Stephen R. Whiteley
****************************************************************************/

#ifndef MISC_H
#define MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "lstring.h"


//
// Standard definitions.
//

#define BSIZE_SP  2048

#define EXIT_NORMAL 0
#define EXIT_BAD    1

#ifndef SPMIN
#define SPMIN(a,b) ((a) < (b) ? (a) : (b))
#define SPMAX(a,b) ((a) > (b) ? (a) : (b))
#endif

// time.cc
extern char *datestring();
extern unsigned long millisec();
extern double seconds();

// wrspice.cc
extern void fatal(int);
extern struct sRnd Rnd;

#endif // MISC_H

