/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COMMONSOURCES_H
#define COMMONSOURCES_H

#include "Source.h"
#include "Port.h"

namespace flow {

class Const : public Source {
public:
        Const (int i) : value (i) {}
        virtual ~Const () {}
        void process () { output->put (value); }

private:
        int value;
};

} // namespace

#endif // COMMONSOURCES_H
