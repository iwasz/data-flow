/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Program.h"
#include "core/Core.h"

/*
 * Dynamiczne API, czyli ułatwienia, które stosujemy na hoście :
 * - łączenia nodów : kiedy dodaję output to alokacja pamięci.
 * - Metody sprawdzające czy wejścia i wyjścia są połączone,
 * - Czy połączenie się powiedzie (semantyka).
 *
 * Na targecie tego API ma nie być (albo function-sections usunie,
 * albo zrobić macro). Na targecie API ma tworzyć z góry ustaloną
 * liczbę pól w tabelach (bo przecież wiemy ile każdy node ma wejść
 * i wyjść podłączonych.
 */

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
        flow::Arc a1;
        a1.init (0);
        c2.addOutput (0, &a1);

        // c1 dolne
        flow::Arc a2;
        a2.init (1);
        flow::Arc a3;
        a3.init (1);
        c1.addOutput (0, &a3);
        c1.addOutput (0, &a2);

        // add
        flow::Arc a4;
        flow::Arc a5;
        a5.init (1);
        a.addOutput (0, &a4);
        a.addOutput (0, &a5);

        c1.setInput (0, &a4);
        c2.setInput (0, &a2);
        a.setInput (0, &a1);
        a.setInput (1, &a3);
        l.setInput (0, &a5);

        program.run ();
}

int main (int argc, char **argv) { fibonacci (); }
