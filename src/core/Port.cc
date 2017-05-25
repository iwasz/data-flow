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
#include <algorithm>

namespace flow {

bool Port::isAllFree () const
{
#ifndef SMALL_FOOTPRINT
        for (Arc *a : arcs) {
                if (a->isFull ()) {
                        return false;
                }
        }
#else
        for (int i = 0; i < arcNo; ++i) {
                if (arcs[i] && arcs[i]->isFull ()) {
                        return false;
                }
        }
#endif
        return true;
}

/*****************************************************************************/

void Port::put (int v)
{
#ifndef SMALL_FOOTPRINT
        for (Arc *a : arcs) {
                a->put (v);
        }
#else
        for (int i = 0; i < arcNo; ++i) {
                arcs[i]->put (v);
        }
#endif
}

/*****************************************************************************/

void Port::addArc (Arc *a)
{
#ifndef SMALL_FOOTPRINT
        arcs.push_back (a);
#else
        if (arcNo + 1 >= MAX_ARCS_PER_PORT) {
                throw Exception ("To many arcs in port");
        }

        arcs[arcNo++] = a;
#endif
}

/*****************************************************************************/

#ifndef SMALL_FOOTPRINT
void Port::disconnect (Arc *a) { arcs.erase (std::remove (arcs.begin (), arcs.end (), a), arcs.end ()); }

void Port::reset ()
{
        for (Arc *a : arcs) {
                a->reset ();
        }
}

#endif

} // namespace
