/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdint>
#include <unistd.h>

namespace flow {

// template <typename T>
class Arc {
public:
        Arc () : full (false) {}
        Arc (int i) : value (i), full (true) {}

        bool isFull () const { return full; }

        int get ()
        {
                full = false;
                return value;
        }

        void put (int i)
        {
                value = i;
                full = true;
        }

private:
        int value;
        bool full;
};

class Port {
public:
        Port (uint8_t arcNo) : arcNo (arcNo), arcs (new Arc *[arcNo]) {}
        ~Port () { delete[] arcs; }

        bool isAllFree () const;
        void put (int i);

        // private:
        uint8_t arcNo;
        Arc **arcs;
};

bool Port::isAllFree () const
{
        for (int i = 0; i < arcNo; ++i) {
                if (arcs[i]->isFull ()) {
                        return false;
                }
        }
        return true;
}

void Port::put (int v)
{
        for (int i = 0; i < arcNo; ++i) {
                arcs[i]->put (v);
        }
}

struct INode {
        virtual ~INode () {}
        virtual void process () = 0;
        virtual bool inputsOk () const = 0;
        virtual bool outputsOk () const = 0;
};

typedef std::vector<INode *> NodeVector;

// TODO specjalizacja dla 1
template <uint8_t INPUTS_NO> struct RequireAllFull {
        static bool check (Arc *const *inputs)
        {
                for (int i = 0; i < INPUTS_NO; ++i) {
                        if (!inputs[i]->isFull ()) {
                                return false;
                        }
                }

                return true;
        }
};

// TODO specjalizacja dla 1
template <uint8_t OUTPUTS_NO> struct RequireAllFree {
        static bool check (Port *const *inputs)
        {
                for (int i = 0; i < OUTPUTS_NO; ++i) {
                        if (!inputs[i]->isAllFree ()) {
                                return false;
                        }
                }

                return true;
        }
};

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy = RequireAllFull<INPUTS_NO>> class AbstractNode : public INode {
public:
        virtual ~AbstractNode () {}
        virtual bool inputsOk () const { return InputStrategy::check (inputs); }
        virtual bool outputsOk () const { return RequireAllFree<OUTPUTS_NO>::check (outputs); }

        // protected:
        Arc *inputs[INPUTS_NO];
        Port *outputs[OUTPUTS_NO];
};

class Add : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        // void process () { outputs[0]->put (inputs[0]->get () + inputs[1]->get ()); }
        void process ()
        {
                int a = inputs[0]->get ();
                int b = inputs[1]->get ();
                //                std::cout << "[" << a << "] + [" << b << "] = [" << std::endl;
                outputs[0]->put (a + b);
        }
};

class Copy : public AbstractNode<1, 1, RequireAllFull<1>> {
public:
        void process () { outputs[0]->put (inputs[0]->get ()); }
};

class Source : public INode {
public:
        virtual ~Source () {}
        bool inputsOk () const { return true; }
        bool outputsOk () const { return output->isAllFree (); }

        // protected:
        Port *output;
};

class Const : public Source {
public:
        Const (int i) : value (i) {}
        virtual ~Const () {}
        void process () { output->put (value); }

private:
        int value;
};

class Sink : public INode {
public:
        virtual ~Sink () {}
        bool inputsOk () const { return input->isFull (); }
        bool outputsOk () const { return true; }

        // protected:
        Arc *input;
};

class Console : public Sink {
public:
        virtual ~Console () {}
        void process ()
        {
                sleep (1);
                std::cerr << input->get () << std::endl;
        }
};
}

void run (flow::NodeVector *nodes)
{
        while (true) {
                for (flow::INode *node : *nodes) {
                        if (node->inputsOk () && node->outputsOk ()) {
                                node->process ();
                        }
                }
        }
}

void simpleAdd ()
{

        flow::NodeVector nodes;

        flow::Const c1 (2);
        flow::Const c2 (3);
        flow::Add a;
        flow::Console l;

        nodes.push_back (&l);
        nodes.push_back (&c1);
        nodes.push_back (&a);
        nodes.push_back (&c2);

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

        run (&nodes);
}

void fibonacci ()
{

        flow::NodeVector nodes;

        flow::Copy c2;
        flow::Copy c1;
        flow::Add a;
        flow::Console l;

        nodes.push_back (&l);
        nodes.push_back (&c1);
        nodes.push_back (&a);
        nodes.push_back (&c2);

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

        run (&nodes);
}

int main (int argc, char **argv) { fibonacci (); }
