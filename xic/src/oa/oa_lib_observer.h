
/*========================================================================*
 *                                                                        *
 *  XICTOOLS Integrated Circuit Design System                             *
 *  Copyright (c) 2010 Whiteley Research Inc, all rights reserved.        *
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
 $Id: oa_lib_observer.h,v 1.3 2012/12/02 21:59:38 stevew Exp $
 *========================================================================*/

#ifndef OA_LIB_OBSERVER_H
#define OA_LIB_OBSERVER_H


// This class receives notifications regarding the library definitions
// file.
//
class cOAlibObserver : public oaObserver<oaLibDefList>
{
public:
    cOAlibObserver(oaUInt4, oaBoolean = true);

    oaBoolean onLoadWarnings(oaLibDefList*, const oaString&,
        oaLibDefListWarningTypeEnum);
};


// This class receives notifications regarding PCell instantiation.
//
class cOApcellObserver : public oaPcellObserver
{
public:
    cOApcellObserver(int pin, bool enabled = true) :
        oaPcellObserver(pin, enabled) { }

    void onError(oaDesign*, const oaString&, oaPcellErrorTypeEnum);
    void onPreEval(oaDesign*, oaPcellDef*);
    void onPostEval(oaDesign*, oaPcellDef*);
};

#endif

