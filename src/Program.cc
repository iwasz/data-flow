/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Program.h"
#include "core/INode.h"

namespace flow {

void Program::step ()
{
        for (flow::INode *node : nodes) {
                if (node->inputsOk () && node->outputsOk ()) {
                        node->process ();
                }
        }
}

/*****************************************************************************/

void Program::run ()
{
        while (true) {
                step ();
        }
}

} // namespace
