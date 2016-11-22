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

namespace flow {

class Program {
public:

        void addNode (INode *n) { nodes.push_back (n); }
        void run ();

private:
        NodeVector nodes;
};

} // namespace

#endif // PROGRAM_H
