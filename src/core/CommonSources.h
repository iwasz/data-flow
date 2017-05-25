/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COMMON_SOURCES_H
#define COMMON_SOURCES_H

#include "Port.h"
#include "Source.h"

namespace flow {

class __tiliae_reflect__ Const : public Source {
public:
        Const () : value (0) {}
        Const (int i) : value (i) {}
        virtual ~Const () {}
        void process ();

        int getValue () const { return value; }
        void setValue (int value) { this->value = value; }

        bool isRepeat () const { return repeat; }
        void setRepeat (bool value) { repeat = value; }

        virtual void reset ();

private:
        int value;
        bool repeat = true;
        bool fired = false;
};

} // namespace

#endif // COMMONSOURCES_H
