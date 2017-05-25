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
        if (nodes.empty ()) {
                return;
        }

        if (lastRun == nodes.end ()) {
                lastRun = nodes.begin ();
        }

        flow::INode *node = *lastRun++;
        if (node->inputsOk () && node->outputsOk ()) {
                node->process ();
        }
}

/*****************************************************************************/

void Program::run ()
{
        lastRun = nodes.begin ();

        while (true) {
                step ();
        }
}

/*****************************************************************************/

void Program::reset ()
{
        for (flow::INode *node : nodes) {
                node->reset ();
        }
}

} // namespace
