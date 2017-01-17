/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_INODE_H
#define DATA_FLOW_INODE_H

#include <core/Object.h>
#include <vector>

namespace flow {

class Arc;

/**
 * @brief The INode struct
 */
struct INode : public Core::Object {
        virtual ~INode () {}
        virtual void process () = 0;
        virtual bool inputsOk () const = 0;
        virtual bool outputsOk () const = 0;
        virtual void addOutput (int i, Arc *a) = 0;
        virtual void setInput (int i, Arc *a) = 0;
};

typedef std::vector<INode *> NodeVector;

} // namespace

#endif // INODE_H
