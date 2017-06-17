
/*========================================================================*
 *                                                                        *
 *  XICTOOLS Integrated Circuit Design System                             *
 *  Copyright (c) 2005 Whiteley Research Inc, all rights reserved.        *
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
 * This library is available for non-commercial use under the terms of    *
 * the GNU Library General Public License as published by the Free        *
 * Software Foundation; either version 2 of the License, or (at your      *
 * option) any later version.                                             *
 *                                                                        *
 * A commercial license is available to those wishing to use this         *
 * library or a derivative work for commercial purposes.  Contact         *
 * Whiteley Research Inc., 456 Flora Vista Ave., Sunnyvale, CA 94086.     *
 * This provision will be enforced to the fullest extent possible under   *
 * law.                                                                   *
 *                                                                        *
 * This library is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 * Library General Public License for more details.                       *
 *                                                                        *
 * You should have received a copy of the GNU Library General Public      *
 * License along with this library; if not, write to the Free             *
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.     *
 *========================================================================*
 *                                                                        *
 * Misc. Utilities Library                                                *
 *                                                                        *
 *========================================================================*
 $Id: randval.h,v 1.4 2015/04/10 00:54:07 stevew Exp $
 *========================================================================*/

#ifndef RANDVAL_H
#define RANDVAL_H

// In mingw, configure finds a random (from libiberty?) so the
// configure script incorrectly flags random/srandom as present (there
// are no prototypes).  I don't like defining random to rand in
// config.h anyway.  The 16-bit rand() in Windows is beyond pathetic
// and useless for anything serious.

// Update:  The random() from FreeBSD-6.2 is hard-coded for all
// operating systems.  Thus, applications will behave the same across
// platforms, when starting from the same seed.

// The struct allows multiple random number generators to exist in the
// same application, unlike the original code.
//
struct randval
{
    randval();

    void rand_seed(unsigned int);
    unsigned int rand_value();

private:
    unsigned int *fptr;
    unsigned int *rptr;
    unsigned int *state;
    unsigned int *end_ptr;
    int rand_type;
    int rand_deg;
    int rand_sep;
};

#endif

