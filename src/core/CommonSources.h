/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COMMONSOURCES_H
#define COMMONSOURCES_H

#include "Port.h"
#include "Source.h"

namespace flow {

class __tiliae_reflect__ Const : public Source {
public:
        Const (int i) : value (i) {}
        virtual ~Const () {}
        void process () { output.put (value); }

private:
        int value;
};

} // namespace

#endif // COMMONSOURCES_H
