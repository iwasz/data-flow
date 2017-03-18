/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MATHNODES_H
#define MATHNODES_H

#include "AbstractNode.h"
#include "Arc.h"
#include "Port.h"

namespace flow {

class __tiliae_reflect__ Add : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        void process () { outputs[0].put (inputs[0]->get () + inputs[1]->get ()); }
};

class __tiliae_reflect__ Sub : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        void process () { outputs[0].put (inputs[0]->get () - inputs[1]->get ()); }
};

class __tiliae_reflect__ Mul : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        void process () { outputs[0].put (inputs[0]->get () * inputs[1]->get ()); }
};

class __tiliae_reflect__ Div : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        // TODO What if divided by 0?
        void process () { outputs[0].put (inputs[0]->get () / inputs[1]->get ()); }
};

} // namespace

#endif // MATHNODES_H
