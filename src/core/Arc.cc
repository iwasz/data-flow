/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Arc.h"
#include "INode.h"

namespace flow {

#ifndef SMALL_FOOTPRINT
void Arc::disconnect ()
{
        if (nodeInputSide) {
                nodeInputSide->disconnectInput (this);
        }

        if (nodeOutputSide) {
                nodeOutputSide->disconnectOutput (this);
        }
}

/*****************************************************************************/

void Arc::notify ()
{
        if (observer) {
                if (full) {
                        observer->onValueChange (Core::Variant (value));
                }
                else {
                        observer->onValueChange (Core::Variant ());
                }
        }
}

#endif

} // namespace flow
