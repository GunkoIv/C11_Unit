// Кодировка utf-8.
#include "executor.h"
#include "Macroses.h"
#include "Generators.h"

#define CHECK_CODE_INFO {auto t=CODE_INFO;\
formatPrint("Lets see file:", CODE_INFO.file, " ANd line:", CODE_INFO.line);\
t.printTo(std::cerr, true);t.printTo(std::cout, false);std::cout<<std::endl;}


TEST_N(Asserts, 200) {
    // CHECK_CODE_INFO;
    ASSERT(2 != 5) << 0 << "It's fine I think";
    ASSERT(3 == 5 || 4 == 5 || true) << "It's may be wrong actualy";
    // ASSERT(3 == 5) << std::make_pair(3,2) << " Pretty compile error "; TODO
    // using namespace Cpp11_unit;
    ASSERT(3*2 <LESS> 7-1) << "check working <LESS>";

    // ASSERT(true <OR> false -AND- false) << "Try that in other frameworks for test:)";
    // ASSERT(false <NE> true);
    // ASSERT(false <EQ> false);
    // ASSERT("byka" < STREQ > "byka");
    // ASSERT(12 *IN* {1, 3, 12});
    // ASSERT(-12 ->* NE);
    // ASSERT(4 LESS_EQ 4);
    // ASSERT(4 LESS 5);
    // formatPrint("Finish");
}

TEST(OneMore) {
    ASSERT(false) << 1 <<") Just to see printing user info:" << 2 << ":" << true << ":" << 3.1415926;
}
/*
ax^2 + bx + c = 0;
*/
// #include <cmath>


// std::pair<double, double> getRootQuadResolution(double a, double b, double c) {
//     auto D = b*b - 4*a*c;
//     auto oneRoot = (0 - b - std::sqrt(D)) / (2*a);
//     auto secondRoot = (0 - b + std::sqrt(D)) / (2*a);
//     return {oneRoot, secondRoot};
// }

// TEST(QuadResolution) {
//     // 1x^2 + 2x + 3 = 0;
//     auto a = 1.0;
//     auto c = -3.0;
//     GENERATOR(b, Generators::Range, -10, 10, 2);
//     auto result = getRootQuadResolution(a, b, c);

//     print(result.first, "  ", result.second);
//     ASSERT(result.first * result.second == c / (a));


//     ASSERT((result.first * result.second == c / (a)) && 
//         (result.first + result.second == (0-b) / (a))) << "I check and see usefull infor.";
// }


