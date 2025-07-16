#pragma once
#include <stdint.h>

using Bitset = uint32_t;

class Bitmask
{
    public:
        Bitmask();
        Bitmask(const Bitset& l_bits):bits(l_bits){}

        Bitset GetMask()const{ return bits;}
        void SetMask(const Bitset& l_val){bits = l_val;}

        bool Matches(const Bitmask& l_bits, const Bitset l_relevant = 0)
        {
            return (l_relevant ? (l_bits.GetMask()&l_relevant) == (bits&l_relevant):
            l_bits.GetMask() == bits);
        }

        bool GetBit(const unsigned int& l_pos)const
        {
            return (bits&(1<<l_pos));
        }

        void TurnOnBit(const unsigned int& l_pos)
        {
            bits |= 1 << l_pos;
        }

        void TurnOnBits(const Bitset& l_bits)
        {
            bits |= l_bits;
        }

        void ClearBit(const unsigned int& l_pos)
        {
            bits &= ~(1<<l_pos);
        }

        void ToggleBit(const unsigned int& l_pos)
        {
            bits ^= 1 << l_pos;
        }

        void Clear(){bits = 0;}
    private:
        Bitset bits;
};