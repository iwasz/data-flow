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
        Const () : value (0) {}
        Const (int i) : value (i) {}
        virtual ~Const () {}
        void process () { output.put (value); }

        int getValue () const { return value; }
        void setValue (int value) { this->value = value; }

        bool isRepeat () const { return repeat; }
        void setRepeat (bool value) { repeat = value; }

private:
        int value;
        bool repeat;
};

} // namespace

#endif // COMMONSOURCES_H
