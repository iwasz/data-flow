/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_ABSTRACTNODE_H
#define DATA_FLOW_ABSTRACTNODE_H

#include "Exception.h"
#include "INode.h"
#include "IOPolicy.h"
#include <ReflectionParserAnnotation.h>
#include <cstdint>
#include <memory.h>

namespace flow {

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy = RequireAllFull<INPUTS_NO>> class __tiliae_no_reflect__ AbstractNode : public INode {
public:
        AbstractNode ();
        virtual ~AbstractNode () {}

        virtual bool inputsOk () const { return InputStrategy::check (inputs); }
        virtual bool outputsOk () const { return RequireAllFree<OUTPUTS_NO>::check (outputs); }

        void addOutput (int i, Arc *a);
        void setInput (int i, Arc *a);

        virtual void reset ();

#ifndef SMALL_FOOTPRINT
        void disconnectOutput (Arc *a);
        void disconnectInput (Arc *a);
#endif

        virtual void setObserver (flow::IFlowObserver *o) { this->observer = o; }
        virtual IFlowObserver *getObserver () { return observer; }

protected:
        Arc *inputs[INPUTS_NO];
        Port outputs[OUTPUTS_NO];
        flow::IFlowObserver *observer = nullptr;
};

/*****************************************************************************/

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::AbstractNode ()
{
        memset (inputs, 0, sizeof (Arc *) * INPUTS_NO);
}

/*****************************************************************************/

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> void AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::addOutput (int i, Arc *a)
{
        if (i >= OUTPUTS_NO) {
                throw Exception ("AbstractNode::addOutput : no such port");
        }

        outputs[i].addArc (a);
        a->setNodeOutputSide (this);
}

/*****************************************************************************/

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> void AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::setInput (int i, Arc *a)
{
        if (i >= INPUTS_NO) {
                throw Exception ("AbstractNode::addOutput : no such input");
        }

        inputs[i] = a;
        a->setNodeInputSide (this);
}

/*****************************************************************************/
#ifndef SMALL_FOOTPRINT

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> void AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::disconnectInput (Arc *a)
{
        for (int i = 0; i < INPUTS_NO; ++i) {
                if (inputs[i] == a) {
                        inputs[i] = nullptr;
                }
        }
        a->setNodeInputSide (nullptr);
}

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> void AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::disconnectOutput (Arc *a)
{
        for (int i = 0; i < OUTPUTS_NO; ++i) {
                outputs[i].disconnect (a);
        }
        a->setNodeOutputSide (nullptr);
}

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> void AbstractNode<INPUTS_NO, OUTPUTS_NO, InputStrategy>::reset ()
{
        for (int i = 0; i < INPUTS_NO; ++i) {
                if (inputs[i]) {
                        inputs[i]->reset ();
                }
        }

        for (int i = 0; i < OUTPUTS_NO; ++i) {
                outputs[i].reset ();
        }
}

#endif
} // namespace

#endif // ABSTRACTNODE_H
