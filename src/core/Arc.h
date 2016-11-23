/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_ARC_H
#define DATA_FLOW_ARC_H

namespace flow {

// TODO other types as well (along with strings).
// template <typename T>
class Arc {
public:
        Arc () : full (false) {}
        Arc (int i) : value (i), full (true) {}

        bool isFull () const { return full; }

        int get ()
        {
                full = false;
                return value;
        }

        void put (int i)
        {
                value = i;
                full = true;
        }

        // For debugging
        int getValue () const { return value; }

private:
        int value;
        bool full;
};

} // namespace

#endif // ARC_H
