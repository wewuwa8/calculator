#include <catch2/catch.hpp>

#include <parser.h>

#include <sstream>
#include <iostream>

TEST_CASE("Parser simple 10", "[parser][simple]") {
    auto input = GENERATE(as<std::string>{}, 
        "4+6",
        "2*5",
        "-2*-1*5",
        "--10",
        "20/--2",
        "3++7",
        "(10)",
        "10",
        "2,5*4",
        "2 + 2 * 4",
        "25 / 5 + 5",
        "((10))",
        "(-((-(10))))",
        "(5)*(2)"
    );
    std::stringstream ss{input};
    Tokenizer tokenizer{&ss};
    Parser parser(&tokenizer);
    REQUIRE(parser.Evaluate() == 10);
}


TEST_CASE("Empty", "[parser][simple]") {
    std::stringstream ss{""};
    Tokenizer tokenizer{&ss};
    Parser parser(&tokenizer);
    REQUIRE(parser.Evaluate() == 0);
}

TEST_CASE("Parser nullptr", "[parser][invalid]") {
    REQUIRE_THROWS(Parser{nullptr});
}

TEST_CASE("Invalid syntax", "[parser][invalid]") {
    auto input = GENERATE(as<std::string>{}, 
        "((3)",
        "2(3)",
        ")",
        "5)",
        "(3 * 7 - 14) + ",
        "/ 2",
        "5 / 0",
        "5 / (1 - 1)",
        "* 4",
        "(* 4)",
        "(5)(2)",
        "1.0 / "
        "12.0 + (5 / )"
        "55,6 * ()",
        "8 * "
    );
    std::stringstream ss{input};
    Tokenizer tokenizer{&ss};
    Parser parser(&tokenizer);
    REQUIRE_THROWS(parser.Evaluate());
}