/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATAFLOW_EXCEPTION_H_
#define DATAFLOW_EXCEPTION_H_

#include <exception>
#include <string>

namespace flow {

/**
 *
 */
class Exception : public std::exception {
public:

        /**
         * Inicjuje wyjątek napisem.
         */
        Exception (std::string const &s = "") : message (s) {}
        virtual ~Exception () throw () {}

        const char* what() const throw () { return message.c_str(); }

private:

        std::string message;

};

} // namespace

#	endif /* EXCEPTION_H_ */
