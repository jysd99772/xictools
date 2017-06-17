
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
 * Ginterf Graphical Interface Library                                    *
 *                                                                        *
 *========================================================================*
 $Id: xfig.h,v 2.17 2010/07/09 02:41:26 stevew Exp $
 *========================================================================*/

#ifndef XFIG_H
#define XFIG_H

#include "graphics.h"
#include "pixtab.h"
#include <stdio.h>

// Driver for xfig output
//
// Call with "-f filename -w width -h height -x left_marg -y top_marg"
//
// dimensions are in inches (float format)

namespace ginterf
{
    extern HCdesc XFdesc;

    class XFdev : public GRdev
    {
    public:
        XFdev()
        {
            name = "XF";
            ident = _devXF_;
            devtype = GRhardcopy;
            data = 0;
        }

        friend struct XFparams;

        void RGBofPixel(int, int *r, int *g, int *b)    { *r = *g = *b = 0; }

        bool Init(int*, char**);
        GRdraw *NewDraw(int);

    private:
        HCdata *data;       // internal private data struct
    };

    struct XFparams : public HCdraw
    {
        XFparams()
            {
                dev = 0;
                fp = 0;
                lastx = lasty = -1;
                linestyle = 0;
                fillpattern = -1;
                color = 0;
                numcolors = 0;
                depth = 0;
            }
        virtual ~XFparams() { }

        void Halt();
        void ResetViewport(int, int);
        void DefineViewport();
        void Dump(int)                      { }
        void Pixel(int, int);
        void Pixels(GRmultiPt*, int);
        void Line(int, int, int, int);
        void PolyLine(GRmultiPt*, int);
        void Lines(GRmultiPt*, int);
        void Box(int, int, int, int);
        void Boxes(GRmultiPt*, int);
        void Arc(int, int, int, int, double, double);
        void Polygon(GRmultiPt*, int);
        void Zoid(int, int, int, int, int, int);
        void Text(const char*, int, int, int, int = -1, int = -1);
        void TextExtent(const char*, int*, int*);
        void SetColor(int);
        void SetLinestyle(const GRlineType*);
        void SetFillpattern(const GRfillType*);
        void DisplayImage(const GRimage*, int, int, int, int);
        double Resolution();

        XFdev *dev;
        FILE *fp;
        int lastx;
        int lasty;
        int linestyle;
        int fillpattern;
        int color;
        int numcolors;
        int depth;
        ptab ctab;
    };
}

#endif

