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

protected:
        Arc *inputs[INPUTS_NO];
        Arc *outputs[OUTPUTS_NO];
};

class Add : public AbstractNode<2, 1, RequireAllFull<2>> {
public:
        void process ();
};

void Add::process () { outputs[0]->put (inputs[0]->get () + inputs[1]->get ()); }
}

using namespace flow;

int main (int argc, char **argv)
{

        NodeVector nodes;

        while (true) {
                for (INode *node : nodes) {
                        if (node->inputsOk () && node->outputsOk ()) {
                                node->process ();
                        }
                }
        }
}
