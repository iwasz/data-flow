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
#include <vector>
#include <memory.h>

namespace flow {

class Arc;
#define MAX_ARCS_PER_PORT 10

/**
 * @brief The Port class
 */
class Port {
public:
#ifndef SMALL_FOOTPRINT
        Port () {}
#else
        Port () : arcNo (0), arcs (new Arc *[MAX_ARCS_PER_PORT]) { bzero (arcs, sizeof (Arc *) * MAX_ARCS_PER_PORT); }
#endif
        void addArc (Arc *a);

        // Rest of the class
        ~Port () { /*delete[] arcs;*/}

        bool isAllFree () const;
        void put (int i);

#ifndef SMALL_FOOTPRINT
        void disconnect (Arc *a);
#endif

//private:

#ifndef SMALL_FOOTPRINT
        std::vector <Arc *> arcs;
#else
        uint8_t arcNo;
        Arc **arcs;
#endif
};

} // namespace

#endif // PORT_H
