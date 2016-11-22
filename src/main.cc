/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "core/Core.h"
#include "Program.h"



void simpleAdd ()
{

        flow::Program program;

        flow::Const c1 (2);
        flow::Const c2 (3);
        flow::Add a;
        flow::Console l;

        program.addNode (&l);
        program.addNode (&c1);
        program.addNode (&a);
        program.addNode (&c2);

        flow::Arc a1;
        flow::Port p1 (1);
        p1.arcs[0] = &a1;
        c1.output = &p1;
        a.inputs[0] = &a1;

        flow::Arc a2;
        flow::Port p2 (1);
        p2.arcs[0] = &a2;
        c2.output = &p2;
        a.inputs[1] = &a2;

        flow::Arc a3;
        flow::Port p3 (1);
        p3.arcs[0] = &a3;
        a.outputs[0] = &p3;
        l.input = &a3;

        program.run ();
}

void fibonacci ()
{
        flow::Program program;

        flow::Copy c2;
        flow::Copy c1;
        flow::Add a;
        flow::Console l;

        program.addNode (&l);
        program.addNode (&c1);
        program.addNode (&a);
        program.addNode (&c2);

        // c2 górne
        flow::Arc a1 (0);
        flow::Port p1 (1);
        p1.arcs[0] = &a1;
        c2.outputs[0] = &p1;

        // c1 dolne
        flow::Arc a2 (1);
        flow::Arc a3 (1);
        flow::Port p2 (2);
        p2.arcs[0] = &a2;
        p2.arcs[1] = &a3;
        c1.outputs[0] = &p2;

        // add
        flow::Arc a4;
        flow::Arc a5 (1);
        flow::Port p3 (2);
        p3.arcs[0] = &a4;
        p3.arcs[1] = &a5;
        a.outputs[0] = &p3;

        c1.inputs[0] = &a4;
        c2.inputs[0] = &a2;
        a.inputs[0] = &a1;
        a.inputs[1] = &a3;
        l.input = &a5;

        program.run ();
}

int main (int argc, char **argv) { fibonacci (); }
