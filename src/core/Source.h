/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_SOURCE_H
#define DATA_FLOW_SOURCE_H

#include "INode.h"
#include "Port.h"

namespace flow {

class Source : public INode {
public:
        virtual ~Source () {}
        bool inputsOk () const { return true; }
        bool outputsOk () const { return output.isAllFree (); }
        void addOutput (int, Arc *a) { output.addArc (a); }
        void setInput (int, Arc *) {}

        // protected:
        Port output;
};

} // namespace

#endif // SOURCE_H
