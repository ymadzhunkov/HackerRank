#pragma once
#include <cstdint>
#include <array>

class CyclicHash {
    class CharacterHash {
      public:
        explicit CharacterHash(uint32_t maxval);
        std::array<uint32_t, 256> hashvalues;
    };
    uint32_t mask(int bits) const {
        uint32_t x = static_cast<uint32_t>(1) << (bits - 1);
        return x ^ (x - 1);
    }

    void fastleftshiftn(uint32_t &x) const {
        x = ((x & maskn) << myr) | (x >> (wordsize - myr));
    }

    void fastleftshift1(uint32_t &x) const {
        x = ((x & mask1) << 1) | (x >> (wordsize - 1));
    }

    uint32_t getfastleftshift1(uint32_t x) const {
        return ((x & mask1) << 1) | (x >> (wordsize - 1));
    }
    void eat(unsigned char inchar) {
        fastleftshift1(hashvalue);
        hashvalue ^= hasher.hashvalues[inchar];
    }

  public:
    // myn is the length of the sequences, e.g., 3 means
    // that you want to hash sequences of 3 characters
    // mywordsize is the number of bits you which to receive
    // as hash values, e.g., 19 means that the hash values
    // are 19-bit integers
    CyclicHash(int myn, int mywordsize = 19)
        : hashvalue(0), n(myn), wordsize(mywordsize),
          hasher(mask(wordsize)), mask1(mask(wordsize - 1)),
          myr(n % wordsize), maskn(mask(wordsize - myr)) {}

    uint32_t update(unsigned char outchar,
                    unsigned char inchar) {
        uint32_t z(hasher.hashvalues[outchar]);
        fastleftshiftn(z);
        hashvalue = getfastleftshift1(hashvalue) ^ z ^
                    hasher.hashvalues[inchar];
        return hashvalue;
    }

    uint32_t init(const char *a) {
        for (uint32_t k = 0; k < n; ++k) eat(a[k]);
        return hashvalue;
    }


  private:
    uint32_t hashvalue;
    int n;
    const int wordsize;
    CharacterHash hasher;
    const uint32_t mask1;
    const int myr;
    const uint32_t maskn;
};

