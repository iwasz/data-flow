/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_SINK_H
#define DATA_FLOW_SINK_H

#include "INode.h"
#include "Arc.h"

namespace flow {

class Sink : public INode {
public:
        virtual ~Sink () {}
        bool inputsOk () const { return input->isFull (); }
        bool outputsOk () const { return true; }

        // protected:
        Arc *input;
};

} // namespace

#endif // SINK_H
