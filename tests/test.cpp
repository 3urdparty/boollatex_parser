#include <gtest/gtest.h>
#include <boollatex_parser/boollatex_parser.hpp>
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    ASSERT_EQ(parseLatex("file.csv"), "file");
}
