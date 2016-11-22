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

namespace flow {

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy = RequireAllFull<INPUTS_NO>> class AbstractNode : public INode {
public:
        virtual ~AbstractNode () {}
        virtual bool inputsOk () const { return InputStrategy::check (inputs); }
        virtual bool outputsOk () const { return RequireAllFree<OUTPUTS_NO>::check (outputs); }

        // protected:
        Arc *inputs[INPUTS_NO];
        Port *outputs[OUTPUTS_NO];
};

} // namespace

#endif // ABSTRACTNODE_H
