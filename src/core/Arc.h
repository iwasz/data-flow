/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_ARC_H
#define DATA_FLOW_ARC_H

#include <ReflectionParserAnnotation.h>

namespace flow {

struct INode;

// TODO other types as well (along with strings).
// template <typename T>
class __tiliae_reflect__ Arc {
public:
        Arc () : value (0), initialValue (0), full (false), initialFull (false) {}
#ifndef SMALL_FOOTPRINT
        ~Arc () { disconnect (); }
#endif

        /// Sets initial value and makes this Arc full.
        void init (int i) __tiliae_no_reflect__
        {
                value = initialValue = i;
                full = initialFull = true;
        }

        /// Clears initial value and makes this Arc empty.
        void clear () { full = initialFull = false; }

        /// Restores the initial value.
        void reset ()
        {
                value = initialValue;
                full = initialFull;
        }

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

#ifndef SMALL_FOOTPRINT
        INode *getNodeInputSide () const { return nodeInputSide; }
        void setNodeInputSide (INode *value) { nodeInputSide = value; }

        INode *getNodeOutputSide () const { return nodeOutputSide; }
        void setNodeOutputSide (INode *value) { nodeOutputSide = value; }

        /// Dosconnects both sides
        void disconnect ();
#endif

private:
        int value;
        int initialValue;

        bool full;
        bool initialFull;
#ifndef SMALL_FOOTPRINT
        INode *nodeInputSide = nullptr;
        INode *nodeOutputSide = nullptr;
#endif
};

} // namespace

#endif // ARC_H
