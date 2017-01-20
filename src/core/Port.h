/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_PORT_H
#define DATA_FLOW_PORT_H

#include <cstdint>
#include <memory.h>

namespace flow {

class Arc;
#define MAX_ARCS_PER_PORT 10

/**
 * @brief The Port class
 */
class Port {
public:
        // Static API used on µC
        // Port (uint8_t arcNo) : arcNo (arcNo), arcs (new Arc *[arcNo]) { bzero (arcs, sizeof (Arc *) * arcNo); }

        // Runtime/dynamic API, not used on µC.
        Port () : arcNo (0), arcs (new Arc *[MAX_ARCS_PER_PORT]) { bzero (arcs, sizeof (Arc *) * MAX_ARCS_PER_PORT); }
        void addArc (Arc *a);
        void removeArc (Arc *a);

        // Rest of the class
        ~Port () { /*delete[] arcs;*/}

        bool isAllFree () const;
        void put (int i);

        // private:
        uint8_t arcNo;
        Arc **arcs;
};

} // namespace

#endif // PORT_H
