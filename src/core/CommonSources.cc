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
                output.put (value);
                fired = true;
        }
}

} // namespace
