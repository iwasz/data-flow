/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IFLOWOBSERVER_H
#define IFLOWOBSERVER_H
#ifndef SMALL_FOOTPRINT

#include <core/variant/Variant.h>

namespace flow {

/**
 * Implement this interface if you want to receive nitifications about value changes in
 * Arcs and Nodes.
 */
struct __tiliae_no_reflect__ IFlowObserver {
        virtual ~IFlowObserver () {}
        virtual void onValueChange (Core::Variant const &v) = 0;
};

} // namespace

#endif
#endif // IFLOWOBSERVER_H
