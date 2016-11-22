/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef COMMONSINKS_H
#define COMMONSINKS_H

#include <iostream>
#include <unistd.h>
#include "Sink.h"
#include "Port.h"
#include "Arc.h"

namespace flow {

class Console : public Sink {
public:
        virtual ~Console () {}
        void process ()
        {
                sleep (1);
                std::cerr << input->get () << std::endl;
        }
};

} // namespace

#endif // COMMONSINKS_H
