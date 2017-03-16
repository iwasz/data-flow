/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "INode.h"
#include "Program.h"

namespace flow {

#ifndef SMALL_FOOTPRINT
INode::~INode ()
{
        if (program) {
                program->removeNode (this);
        }
}
#endif

} // naamespace
