/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_SOURCE_H
#define DATA_FLOW_SOURCE_H

#include "AbstractNode.h"
#include "Arc.h"
#include "Port.h"

namespace flow {

class __tiliae_reflect__ Source : public AbstractNode <0, 1> {
public:
        virtual ~Source () {}
//        bool inputsOk () const { return true; }
//        bool outputsOk () const { return output.isAllFree (); }
//        void addOutput (int, Arc *a) { output.addArc (a); }
//        void setInput (int, Arc *) {}
//        virtual void reset () { output.reset (); }

#ifndef SMALL_FOOTPRINT
//        void disconnectOutput (Arc *a)
//        {
//                a->setNodeOutputSide (nullptr);
//                output.disconnect (a);
//        }
//        void disconnectInput (Arc *a) {}
#endif

        // protected:
//        Port output;
};

} // namespace

#endif // SOURCE_H
