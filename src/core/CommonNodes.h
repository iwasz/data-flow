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
#include "Arc.h"
#include "Port.h"

namespace flow {

class __tiliae_reflect__ Copy : public AbstractNode<1, 1, RequireAllFull<1>> {
public:
        void process () { outputs[0].put (inputs[0]->get ()); }
};

} // namespace

#endif // COMMONNODES_H
