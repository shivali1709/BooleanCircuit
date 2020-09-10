#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* and3_Circuit() {
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean* z = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(3);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;

    Boolean* out = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(1);
    outputs[0] = out;

    Gate* A1 = new_AndGate();
    Gate* A2 = new_AndGate();
    Gate** gates = new_Gate_array(2);
    gates[0] = A1;
    gates[1] = A2;

    Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 2, gates);
    Circuit_connect(circuit, x, Gate_getInput(A1, 0));
    Circuit_connect(circuit, y, Gate_getInput(A1, 1));
    Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(A2, 0));
    Circuit_connect(circuit, z, Gate_getInput(A2, 1));
    Circuit_connect(circuit, Gate_getOutput(A2), out);
    return circuit;
}

static char* b2s(bool b) {
    return b ? "T" : "F";
}

//Tests 1 case for 3 inputs and 1 output
static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_setInput(circuit, 2, in2);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}
static void test2In1Out(Circuit* circuit, bool in0, bool in1) {
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_update(circuit);
    bool out0 = Circuit_getOutput(circuit, 0);
    printf("%s %s -> %s\n", b2s(in0), b2s(in1), b2s(out0));
}

//Tests all cases for 3 inputs and 1 output
static void testAllCombo2In1Out(Circuit* circuit){
    test2In1Out(circuit, false, false);
    test2In1Out(circuit, false, true);
    test2In1Out(circuit, true, false);
    test2In1Out(circuit, true, true );
}
//Tests all cases for 3 inputs and 1 output
static void testAllCombo3In1Out(Circuit* circuit){
    test3In1Out(circuit, false, false, false);
    test3In1Out(circuit, false, false, true);
    test3In1Out(circuit, false, true, false);
    test3In1Out(circuit, true, false, false);
    test3In1Out(circuit, true, true, false);
    test3In1Out(circuit, true, false, true);
    test3In1Out(circuit, false, true, true);
    test3In1Out(circuit, true, true, true);
}
//QUestion A
static Circuit* question_A(){
    //Creates 3 inputs and puts the inputs into array for return statement
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean* z = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(3);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;

    //Creates output and puts the output into array for return statement
    Boolean* out = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(1);
    outputs[0] = out;

    //Creates the 4 gates present and asigns them the values and puts the gates into array for return statement
    Gate *NOT = new_Inverter(y);
    Gate *AND_1 = new_AndGate(x, Gate_getOutput(NOT));
    Gate *AND_2 = new_AndGate(y, z);
    Gate *OR = new_OrGate(Gate_getOutput(AND_1), Gate_getOutput(AND_2));
    Gate **gates = new_Gate_array(4);
    gates[0] = NOT;
    gates[1] = AND_1;
    gates[2] = AND_2;
    gates[3] = OR;

    Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 4, gates);
    Circuit_connect(circuit, x, Gate_getInput(AND_1, 0));
    Circuit_connect(circuit, y, Gate_getInput(NOT, 0));
    Circuit_connect(circuit, Gate_getOutput(NOT), Gate_getInput(AND_1, 1));
    Circuit_connect(circuit, y, Gate_getInput(AND_2, 0));
    Circuit_connect(circuit, z, Gate_getInput(AND_2, 1));
    Circuit_connect(circuit, Gate_getOutput(AND_1), Gate_getInput(OR, 0));
    Circuit_connect(circuit, Gate_getOutput(AND_2), Gate_getInput(OR, 1));
    Circuit_connect(circuit, Gate_getOutput(OR), out);

    return circuit;
}
//QUestion B
static Circuit* question_B(){
    //Creates 3 inputs and puts the inputs into array for return statement
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean* z = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(3);
    inputs[0] = x;
    inputs[1] = y;
    inputs[2] = z;

    //Creates output and puts the output into array for return statement
    Boolean* out = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(1);
    outputs[0] = out;

    //Creates the 4 gates present and asigns them the values and puts the gates into array for return statement
    Gate *NOT = new_Inverter();
    Gate *NAND_1 = new_NandGate();
    Gate *NAND_2 = new_NandGate();
    Gate *NOR =new_NorGate();
    Gate **gates = new_Gate_array(4);
    gates[0] = NOT;
    gates[1] = NAND_1;
    gates[2] = NAND_2;
    gates[3] = NOR;

    Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 4, gates);
    Circuit_connect(circuit, x, Gate_getInput(NAND_1, 0));
    Circuit_connect(circuit, y, Gate_getInput(NOT, 0));
    Circuit_connect(circuit, Gate_getOutput(NOT), Gate_getInput(NAND_1, 1));
    Circuit_connect(circuit, y, Gate_getInput(NAND_2, 0));
    Circuit_connect(circuit, z, Gate_getInput(NAND_2, 1));
    Circuit_connect(circuit, Gate_getOutput(NAND_1), Gate_getInput(NOR, 0));
    Circuit_connect(circuit, Gate_getOutput(NAND_2), Gate_getInput(NOR, 1));
    Circuit_connect(circuit, Gate_getOutput(NOR), out);

    return circuit;
}
//Question C

static Circuit* question_C(){
    //Creates 3 inputs and puts the inputs into an array
    Boolean* x = new_Boolean(false);
    Boolean* y = new_Boolean(false);
    Boolean** inputs = new_Boolean_array(2);
    inputs[0]= x;
    inputs[1] = y;

    //Creates output and puts that in an array
    Boolean* out = new_Boolean(false);
    Boolean** outputs = new_Boolean_array(1);
    outputs[0] = out;

    //Creates the 5 gates and asigns them values

    Gate *A = new_AndGate();
    Gate *B = new_Inverter();
    Gate *C = new_Inverter();
    Gate *D = new_AndGate();
    Gate *E = new_OrGate();

    Gate **gates = new_Gate_array(5);
    gates[0] = A;
    gates[1] = B;
    gates[2] = C;
    gates[3] = D;
    gates[4] = E;

    Circuit *circuit = new_Circuit(2, inputs,1, outputs, 5, gates);
    Circuit_connect(circuit, y, Gate_getInput(A,0));
    Circuit_connect(circuit, x, Gate_getInput(A,1));
    Circuit_connect(circuit, x, Gate_getInput(B,0));
    Circuit_connect(circuit, y, Gate_getInput(C,0));
    Circuit_connect(circuit, Gate_getOutput(B), Gate_getInput(D,0));
    Circuit_connect(circuit, Gate_getOutput(C), Gate_getInput(D,1));
    Circuit_connect(circuit, Gate_getOutput(A), Gate_getInput(E,0));
    Circuit_connect(circuit, Gate_getOutput(D), Gate_getInput(E,1));
    Circuit_connect(circuit, Gate_getOutput(E), out);

    return circuit;
}


//Main Method
int main(int argc, char **argv) {
    Circuit* circuit = and3_Circuit();
    printf("The and3 circuit (AND of three inputs):\n");
    printf("Some input(s) false: should be false\n");
    test3In1Out(circuit, true, true, false);
    printf("All inputs true: should be true\n");
    test3In1Out(circuit, true, true, true);

    printf("Question A:\n");
    testAllCombo3In1Out(question_A());
    Circuit_free(question_A());

    printf("Question B:\n");
    Circuit_dump(question_B());
    testAllCombo3In1Out(question_B());
    Circuit_free(question_B());

    printf("Question C:\n");
    Circuit_dump(question_C());
    testAllCombo2In1Out(question_C());
    Circuit_free(question_C());
}