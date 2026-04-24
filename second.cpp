#include<iostream>
#include<cstdint>

struct ALUResult
{
    uint8_t result;
    //Define Status Flags.
    bool zero, negative, carry, overflow;
};

class ALUSimulator
{
public:
    //Define the opcode.
    enum class Opcode{ADD = 0, SUB = 1, OR = 2, AND = 3, XOR = 4};

    ALUResult compute(uint8_t A, uint8_t B, Opcode op)
    {
        uint16_t tempResult = 0;
        ALUResult res = {0, false, false, false, false};

        switch(op)
        {
            case Opcode::ADD:
                tempResult = (uint16_t)A + B;
                //If tempResult > 1111 1111, carry = 1.
                res.carry = tempResult > 0xff;
                //If A'MSB is different from tempResult, and so does B, overflow = 1.
                res.overflow = ((A ^ tempResult) & (B ^ tempResult)) & 0x80;
                break;

            case Opcode::SUB:
                tempResult = (uint16_t)A - B;
                res.carry = A < B;
                res.overflow = ((A ^ B) & (A ^ tempResult) & 0x80);
                break;

            case Opcode::AND: tempResult = A & B; break;
            case Opcode::OR: tempResult = A | B; break;
            case Opcode::XOR: tempResult = A ^ B; break;
        }

        res.result = (uint8_t)(tempResult & 0xFF);
        res.zero = (res.result == 0);
        //Check the highest bit.
        res.negative = (res.result & 0x80);
        return res;
    }
};