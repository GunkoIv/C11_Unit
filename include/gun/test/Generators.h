#ifndef GUN_TEST_GENERATORS_H_
#define GUN_TEST_GENERATORS_H_

#include "IGenerator.h"

#include <cstring>
#include <random>
#include <ctime>

#define DECL_GEN(GeneratorName,ReturnTypeMacros) \
class GeneratorName : public gun::test::GeneratorBase<ReturnTypeMacros> { \
    using ReturnType = ReturnTypeMacros; 

#define GEN_END };

#define GENERATOR(VarName,GeneratorType,GenArgs...) \
static GeneratorType VarName ## generator(GenArgs); \
{ \
    static bool isFirstTimeCall = (addGenerator( & VarName ## generator), true); \
    UNUSED_VAR(isFirstTimeCall); \
} \
if (VarName ## generator.isNeedReInit()) { \
    VarName ## generator = GeneratorType(GenArgs); \
} \
auto VarName = VarName ## generator.Get() 

#define BOUND_GENERATOR(BoundVarName,VarName,GeneratorType,GenArgs...) \
static GeneratorType VarName ## generator(GenArgs); \
{ \
    static bool isFirstTimeCall = (BoundVarName ## generator.attach( & VarName ## generator), true); \
    UNUSED_VAR(isFirstTimeCall); \
} \
if (VarName ## generator.isNeedReInit()) { \
    VarName ## generator = GeneratorType(GenArgs); \
    BoundVarName ## generator.attach( & VarName ## generator); \
} \
auto VarName = VarName ## generator.Get() 

namespace Generators {
namespace {
 
    struct rnd_char_gen {
        rnd_char_gen(char const* range = "abcdefghijklmnopqrstuvwxyz0123456789")
            : range(range), len(std::strlen(range)) { }

        char operator ()() const {
            return range[static_cast<std::size_t>(std::rand() * (1.0 / (RAND_MAX + 1.0 )) * len)];
        }
    private:
        char const* range;
        std::size_t len;
    };

} // unname namespace

DECL_GEN(StringGen, std::string) 
    unsigned int m_min;
    unsigned int m_max;
public:
    StringGen(unsigned int number, unsigned int minLength, unsigned int maxLength)
        : GeneratorBase(number)
        , m_min(minLength)
        , m_max(maxLength)
    {
        std::srand(std::time(0)); // use current time as seed for random generator
        setMaxLength(number);
    }

    ReturnType getNewElement() {
        std::string str{};
        std::random_device seeder;
        std::mt19937 rng(seeder());
        std::uniform_int_distribution<int> gen(m_min, m_max);
        unsigned int len = gen(rng);
        str.resize(len);
        std::generate(str.begin(), str.end(), rnd_char_gen());
        return str;
    }
GEN_END

template<typename NumericType = int>
DECL_GEN(RangeType, NumericType) 
    NumericType m_current = 0;
    NumericType m_last;
    NumericType m_step = 1;
public:
    RangeType(unsigned int to)
        : m_last(to)
    {}

    RangeType(unsigned int from, unsigned int to, unsigned int step = 1)
        : m_current(from)
        , m_last(to)
        , m_step(step)
    {}

    ReturnType getNewElement() {
        auto result = m_current;
        m_current += m_step;
        return result;
    }

    bool areThereElements() {
        return m_current <= m_last;
    }

GEN_END

using Range = RangeType<>;

} //namespace Generators

#endif //GUN_TEST_GENERATORS_H_
