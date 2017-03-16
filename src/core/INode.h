/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_INODE_H
#define DATA_FLOW_INODE_H

#include <ReflectionParserAnnotation.h>
#include <core/Object.h>
#include <vector>

namespace flow {

class Arc;
class Program;

/**
 * @brief The INode struct
 */
struct __tiliae_reflect__ INode : public Core::Object {

#ifndef SMALL_FOOTPRINT
        virtual ~INode ();
#else
        virtual ~INode () {}
#endif

        virtual void process () = 0;
        virtual bool inputsOk () const = 0;
        virtual bool outputsOk () const = 0;

        virtual void addOutput (int i, Arc *a) = 0;
        virtual void setInput (int i, Arc *a) = 0;

#ifndef SMALL_FOOTPRINT
        virtual void disconnectOutput (Arc *a) = 0;
        virtual void disconnectInput (Arc *a) = 0;
        virtual void setProgram (Program *value) { program = value; }
private:
        Program *program = nullptr;
#endif
};

#ifndef SMALL_FOOTPRINT
typedef std::vector<INode *> NodeVector;

#endif

} // namespace

#endif // INODE_H
