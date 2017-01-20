/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Port.h"
#include "Arc.h"
#include "Exception.h"

namespace flow {

bool Port::isAllFree () const
{
        for (int i = 0; i < arcNo; ++i) {
                if (arcs[i] && arcs[i]->isFull ()) {
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

void Port::addArc (Arc *a)
{
        if (arcNo + 1 >= MAX_ARCS_PER_PORT) {
                throw Exception ("To many arcs in port");
        }

        arcs[arcNo++] = a;
}

void Port::removeArc (Arc *a) { throw Exception ("Not implemented"); }
}
