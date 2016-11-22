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

namespace flow {

class Arc;

/**
 * @brief The Port class
 */
class Port {
public:
        Port (uint8_t arcNo) : arcNo (arcNo), arcs (new Arc *[arcNo]) {}
        ~Port () { delete[] arcs; }

        bool isAllFree () const;
        void put (int i);

        // private:
        uint8_t arcNo;
        Arc **arcs;
};

} // namespace

#endif // PORT_H
