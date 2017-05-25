/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_SINK_H
#define DATA_FLOW_SINK_H

#include "Arc.h"
#include "INode.h"

namespace flow {

class __tiliae_no_reflect__ Sink : public INode {
public:
        virtual ~Sink () {}
        bool inputsOk () const { return input && input->isFull (); }
        bool outputsOk () const { return true; }
        void addOutput (int, Arc *a) {}
        void setInput (int, Arc *a) { input = a; }
        virtual void reset ()
        {
                if (input) {
                        input->reset ();
                }
        }

#ifndef SMALL_FOOTPRINT
        void disconnectOutput (Arc *a) {}
        void disconnectInput (Arc *a)
        {
                a->setNodeInputSide (nullptr);
                input = nullptr;
        }
#endif

        // protected:
        Arc *input = nullptr;
};

} // namespace

#endif // SINK_H
