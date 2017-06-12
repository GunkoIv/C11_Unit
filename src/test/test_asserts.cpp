// Кодировка utf-8.
#include "executor.h"
#include "Macroses.h"

TEST_N(Asserts, 200) {
    ASSERT(2 != 5) << 0 << "It's fine I think";
    ASSERT(3 == 5 || 4 == 5) << "It's may be wrong actualy";
    // ASSERT(3 == 5) << std::make_pair(3,2) << " Pretty compile error "; TODO


    // ASSERT(3 <LESS> 5);
    // ASSERT(true <OR> false -AND- false) << "Try that in other frameworks for test:)";
    // ASSERT(false <NE> true);
    // ASSERT(false <EQ> false);
    // ASSERT("byka" < STREQ > "byka");
    // ASSERT(12 *IN* {1, 3, 12});
    // ASSERT(-12 ->* NE);
    // ASSERT(4 LESS_EQ 4);
    // ASSERT(4 LESS 5);
}

TEST(OneMore) {
    ASSERT(false) << 1 <<") Just to see printing user info:" << 2 << ":" << true << ":" << 3.1415926;
}
