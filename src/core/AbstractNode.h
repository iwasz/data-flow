/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_ABSTRACTNODE_H
#define DATA_FLOW_ABSTRACTNODE_H

#include <cstdint>
#include "IOPolicy.h"
#include "INode.h"
#include "Exception.h"

namespace flow {

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy = RequireAllFull<INPUTS_NO>> class AbstractNode : public INode {
public:
        virtual ~AbstractNode () {}
        virtual bool inputsOk () const { return InputStrategy::check (inputs); }
        virtual bool outputsOk () const { return RequireAllFree<OUTPUTS_NO>::check (outputs); }
        void addOutput (int i, Arc *a);
        void setInput (int i, Arc *a);

        // protected:
        Arc *inputs[INPUTS_NO];
        Port outputs[OUTPUTS_NO];
};

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> void AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::addOutput (int i, Arc *a)
{
        if (i >= OUTPUTS_NO) {
                throw Exception ("AbstractNode::addOutput : no such port");
        }

        outputs[i].addArc (a);
}

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> void AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::setInput (int i, Arc *a)
{
        if (i >= INPUTS_NO) {
                throw Exception ("AbstractNode::addOutput : no such input");
        }

        inputs[i] = a;
}

} // namespace

#endif // ABSTRACTNODE_H
