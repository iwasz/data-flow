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

namespace flow {

#define MAX_INPUT_PORTS 10
#define MAX_OUTPUT_PORTS 10

// template <typename T>
class Arc {
public:
        Arc () : full (false) {}
        Arc (int i) : value (i), full (true) {}

        bool isFull () const { return full; }

        int get ()
        {
                return value;
                full = false;
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
        static bool check (Arc *const *inputs)
        {
                for (int i = 0; i < OUTPUTS_NO; ++i) {
                        if (inputs[i]->isFull ()) {
                                return false;
                        }
                }

                return true;
        }
};

template <uint8_t INPUTS_NO, uint8_t OUTPUTS_NO, typename InputStrategy> class AbstractNode : public INode {
public:
        virtual ~AbstractNode () {}
        virtual bool inputsOk () const { return InputStrategy::check (inputs); }
        virtual bool outputsOk () const { return RequireAllFree<OUTPUTS_NO>::check (outputs); }

        // protected:
        Arc *inputs[INPUTS_NO];
        Arc *outputs[OUTPUTS_NO];
};

class Add : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        void process () { outputs[0]->put (inputs[0]->get () + inputs[1]->get ()); }
};

class Source : public INode {
public:
        virtual ~Source () {}
        bool inputsOk () const { return true; }
        bool outputsOk () const { return !output->isFull (); }

        // protected:
        Arc *output;
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
        void process () { std::cerr << input->get () << std::endl; }
};
}

int main (int argc, char **argv)
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
        c1.output = &a1;
        a.inputs[0] = &a1;

        flow::Arc a2;
        c2.output = &a2;
        a.inputs[1] = &a2;

        flow::Arc a3;
        a.outputs[0] = &a3;
        l.input = &a3;

        while (true) {
                for (flow::INode *node : nodes) {
                        if (node->inputsOk () && node->outputsOk ()) {
                                node->process ();
                        }
                }
        }
}
