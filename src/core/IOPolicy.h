/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_IOPOLICY_H
#define DATA_FLOW_IOPOLICY_H

#include "Arc.h"
#include "Port.h"

namespace flow {

template <uint8_t INPUTS_NO> struct RequireAllFull {
        static bool check (Arc *const *inputs)
        {
                for (int i = 0; i < INPUTS_NO; ++i) {
                        if (!inputs[i] || !inputs[i]->isFull ()) {
                                return false;
                        }
                }

                return true;
        }
};

template <> struct RequireAllFull<1> {
        static bool check (Arc *const *inputs) { return inputs[0] && inputs[0]->isFull (); }
};

/*****************************************************************************/

template <uint8_t OUTPUTS_NO> struct RequireAllFree {
        static bool check (Port const *outputs)
        {
                for (int i = 0; i < OUTPUTS_NO; ++i) {
                        if (!outputs[i].isAllFree ()) {
                                return false;
                        }
                }

                return true;
        }
};

template <> struct RequireAllFree<1> {
        static bool check (Port const *inputs) { return inputs[0].isAllFree (); }
};

} // namespace

#endif // IOPOLICY_H
