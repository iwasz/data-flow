/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "CommonSources.h"

namespace flow {

void Const::process ()
{
        if (repeat || (!repeat && !fired)) {
                outputs[0].put (value);
                fired = true;
        }
}

void Const::reset ()
{
        Source::reset ();
        fired = false;
}

} // namespace
