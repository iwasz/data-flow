/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_COMMONNODES_H
#define DATA_FLOW_COMMONNODES_H

#include "AbstractNode.h"
#include "Port.h"
#include "Arc.h"

namespace flow {

class Add : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        void process () { outputs[0].put (inputs[0]->get () + inputs[1]->get ()); }
};

class Copy : public AbstractNode<1, 1, RequireAllFull<1>> {
public:
        void process () { outputs[0].put (inputs[0]->get ()); }
};

} // namespace

#endif // COMMONNODES_H
