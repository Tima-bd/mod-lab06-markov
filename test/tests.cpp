// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <ctime>

#include "textgen.h"

TEST(gen_tests, prefix_size) {
    std::stringstream ss("Этот текст создан для проверки и тестирования.");

    MarkovGenerator gen;

    EXPECT_EQ(gen.ReadState(ss, 3).size(), 3);
}

TEST(gen_tests, prefix_suffix) {
    std::stringstream ss("Этот текст создан для проверки и тестирования.");

    MarkovGenerator gen;

    gen.ReadState(ss, 2);

    Prefix prefix;

    prefix.push_back("состоящий");
    prefix.push_back("из");

    EXPECT_TRUE(gen.hasPrefix(prefix));

    EXPECT_EQ(gen[prefix][0], "более,");
}

TEST(gen_tests, correct_suffix_single) {
    std::stringstream ss("Этот текст создан для проверки и тестирования.");

    MarkovGenerator gen;

    Prefix start = gen.ReadState(ss, 2);

    unsigned state = 10;

    EXPECT_EQ(std::get<0>(gen.getNextSuffix(start, &state)), "состоящий");
}

TEST(gen_tests, correct_suffix_multiple) {
    std::stringstream ss("Этот текст создан для проверки и тестирования."
                "А в этом тексте есть повторяющиеся префиксы");

    MarkovGenerator gen;

    Prefix start = gen.ReadState(ss, 2);

    unsigned state = time(nullptr);

    std::string result = std::get<0>(gen.getNextSuffix(start, &state));

    EXPECT_TRUE(result == "состоящий" || result == "имеющий");
}

TEST(gen_tests, generate_n_words) {
    std::stringstream ss("Этот текст создан для проверки и тестирования.");

    MarkovGenerator gen;

    Prefix start = gen.ReadState(ss, 2);
    unsigned state = time(nullptr);
    std::stringstream out_ss;

    gen.write(out_ss, start, &state, 5);

    std::stringstream read_out_ss(out_ss.str());
    std::string check;

    read_out_ss >> check;
    EXPECT_EQ(check, "Этот");

    read_out_ss >> check;
    EXPECT_EQ(check, "текст,");

    read_out_ss >> check;
    EXPECT_EQ(check, "создан");

}
