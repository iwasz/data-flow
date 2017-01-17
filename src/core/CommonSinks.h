/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COMMONSINKS_H
#define COMMONSINKS_H

#include "Arc.h"
#include "Port.h"
#include "Sink.h"
#include <iostream>
#include <unistd.h>

namespace flow {

class __tiliae_reflect__ Console : public Sink {
public:
        virtual ~Console () {}
        void process ()
        {
                // sleep (1);
                std::cerr << input->get () << std::endl;
        }
};

} // namespace

#endif // COMMONSINKS_H
