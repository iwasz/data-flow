/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DATA_FLOW_INODE_H
#define DATA_FLOW_INODE_H

#include <vector>

namespace flow {

struct INode {
        virtual ~INode () {}
        virtual void process () = 0;
        virtual bool inputsOk () const = 0;
        virtual bool outputsOk () const = 0;
};

typedef std::vector<INode *> NodeVector;

} // namespace

#endif // INODE_H
