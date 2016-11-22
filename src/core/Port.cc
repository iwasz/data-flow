/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Port.h"
#include "Arc.h"

namespace flow {

bool Port::isAllFree () const
{
        for (int i = 0; i < arcNo; ++i) {
                if (arcs[i]->isFull ()) {
                        return false;
                }
        }
        return true;
}

void Port::put (int v)
{
        for (int i = 0; i < arcNo; ++i) {
                arcs[i]->put (v);
        }
}
}
