/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_PROGRAM_H
#define DATA_FLOW_PROGRAM_H

#include "core/INode.h"
#include <ReflectionParserAnnotation.h>
#ifndef SMALL_FOOTPRINT
#include <algorithm>
#include <vector>
#endif

namespace flow {

class __tiliae_reflect__ Program {
public:
#ifndef SMALL_FOOTPRINT
        void removeNode (INode *n) { nodes.erase (std::remove (nodes.begin (), nodes.end (), n), nodes.end ()); }
        void addNode (INode *n)
        {
                nodes.push_back (n);
                n->setProgram (this);
        }
#else
        void addNode (INode *n) { nodes.push_back (n); }
#endif

        void run ();
        void step ();

private:
        NodeVector nodes;
};

} // namespace

#endif // PROGRAM_H
