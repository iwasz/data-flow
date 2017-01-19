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

namespace flow {

class __tiliae_reflect__ Program {
public:
        void addNode (INode *n) { nodes.push_back (n); }
        void run ();
        void step ();

private:
        NodeVector nodes;
};

} // namespace

#endif // PROGRAM_H
