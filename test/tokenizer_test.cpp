#include <catch2/catch.hpp>

#include <tokenizer.h>

#include <sstream>

TEST_CASE("Tokenizer simple", "[tokenizer][simple]") {
    std::stringstream ss{"*/12+3.45-6,75"};
    Tokenizer tokenizer{&ss};

    REQUIRE(!tokenizer.Eof());

    REQUIRE(tokenizer.GetTokenAndNext() == TokenType::kMul);
    REQUIRE(tokenizer.GetTokenAndNext() == TokenType::kDiv);

    REQUIRE(tokenizer.GetValue() == 12.0);
    REQUIRE(tokenizer.GetTokenAndNext() == TokenType::kNumber);
    
    REQUIRE(tokenizer.GetTokenAndNext() == TokenType::kAdd);

    REQUIRE(tokenizer.GetValue() == 3.45);
    REQUIRE(tokenizer.GetTokenAndNext() == TokenType::kNumber);

    REQUIRE(tokenizer.GetTokenAndNext() == TokenType::kSub);

    REQUIRE(tokenizer.GetValue() == 6.75);
    REQUIRE(tokenizer.GetTokenAndNext() == TokenType::kNumber);

    REQUIRE(tokenizer.GetToken() == TokenType::kEof);
    REQUIRE(tokenizer.Eof());
}

TEST_CASE("Invalid float", "[tokenizer][invalid]") {
    auto input = GENERATE(as<std::string>{}, "12.", "34,", ".56", "7.+");
    std::stringstream ss{input};
    REQUIRE_THROWS_AS(Tokenizer{&ss}, std::runtime_error);
}

TEST_CASE("Tokenizer nullptr", "[tokenizer][invalid]") {
    REQUIRE_THROWS_AS(Tokenizer{nullptr}, std::invalid_argument);
}