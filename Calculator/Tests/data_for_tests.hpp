#ifndef TEST_CALCULATOR_DATA_FOR_TESTS_HPP
#define TEST_CALCULATOR_DATA_FOR_TESTS_HPP

#include "./types_for_tests.hpp"


const TestNumberExtractingValid valid_strings_for_extracting_numbers[]{
        {"with number 12.52 and 12300", 12, "12.52"},
        {"with number 12.52 and 12300", 13, "2.52"},
        {"with number 12.52 and 12300", 15, "52"},
        {"with number 12.52 and 12300", 22, "12300"},
        {"111111111111111111111111111", 0,  "111111111111111111111111111"},
        {"891011121314151617181920212", 1,  "91011121314151617181920212"},
        {"12,22 + 56.78 - 85.45 / 85",  0,  "12,22"},
        {"12,22 + 56.78 - 85.45 / 85",  8,  "56.78"},
        {"12,22 + 56.78 - 85.45 / 85",  16, "85.45"},
        {"12,22 + 56.78 - 85.45/85",    16, "85.45"},
        {"12,22 + 56.78 - 85.45 / 85",  24, "85"},
        {"1fyhtyhty",                   0,  "1"},
        {"1",                           0,  "1"},
        {"aaa1",                        3,  "1"},
};

const TestNumberExtractingBase invalid_strings_for_extracting_numbers[]{
        {"with number 12.52 and 12300",   11},
        {"with number 12.52 and 12300",   17},
        {"with number 12.52 and 12300",   30},
        {"with number 12.52 and 12.30.0", 22},
        {"1.2.3.4",                       0},
        {"1.2.3.4",                       1},
        {"1.2.3.4",                       2},
        {"1.2.3.4",                       3},
        {"1.2+.35.5",                     4},
        {"1.2+.35.5",                     3},
        {"1.2+.35.5",                     3},
        {"1.2,6+.35.5",                     0},
};


const TestNumberConvertingValid valid_strings_for_converting_to_numbers[]{
        {"with number 12.52 and 12300", 12, 12.52},
        {"with number 12.52 and 12300", 13, 2.52},
        {"with number 12.52 and 12300", 15, 52},
        {"with number 12.52 and 12300", 22, 12300},
        {"1111", 0,  1111},
        {"9101", 0,  9101},
        {"12,22 + 56.78 - 85.45 / 85",  0,  12.22},
        {"12,22 + 56.78 - 85.45 / 85",  8,  56.78},
        {"12,22 + 56.78 - 85.45 / 85",  16, 85.45},
        {"12,22 + 56.78 - 85.45/85",    16, 85.45},
        {"12,22 + 56.78 - 85.45 / 85",  24, 85},
        {"1fyhtyhty",                   0,  1},
        {"1",                           0,  1},
        {"aaa1",                        3,  1},
};


const std::string correct_sequences_with_brackets[] {
    "(5 + 5)  + (5 + 5)",
    "((()))((()))<<<>>>{{{}}}[[[]]](test)",
    "{(((5 + 6 * 8) * 5 + [5 + 6]) * 8)(((40^2 + 1) - 5) / 5)}{{{5 + 5} + 5} + 5}[[[0] + 0 ] + 0 ](test())",
     "(5 + 5)+(6+6)+[(5 + 6 * 9) / ((7 * 2022))]",
     "({[<({[<>]})>]})",
     "(())(((((<>{}[])))))[[[]]]"
};

const std::string invalid_sequences_with_brackets[] {
        "(5 + 5)  + (5 + 5))",
        "((()))((()))<<<>>{{{}}}[[[]]](test)",
        "{(((5 + 6 * 8) * 5 + [5 + 6]) * 8)((40^2 + 1) - 5) / 5)}{{{5 + 5} + 5} + 5}[[[0] + 0 ] + 0 ](test())",
        "(5 + 5)+(6+6)+[(5 + 6 * 9) / ((7 * 2022})]",
        "({[<>({[<>]})>]})",
        "(())(((((<>{}[]))))[[[]]]"
};


const TestRemovingSpaces sentences_with_space_symbols[] {
        {"some string without spaces", "somestringwithoutspaces"},
        {"    some string without spaces", "somestringwithoutspaces"},
        {"some string    without spaces", "somestringwithoutspaces"},
        {"   some    string without    spaces    ", "somestringwithoutspaces"},
        {"   1  + 2   + 3   +   4 + 5 + (((5) + 5 ))", "1+2+3+4+5+(((5)+5))"},
        {"1+2+3+4+5+(((5)+5))", "1+2+3+4+5+(((5)+5))"},
        {"1 +2+ 3+4+5 +(((5\n)+\t5))", "1+2+3+4+5+(((5)+5))"},
};

const TestCalculatorComputings tasks[] {
        {"6 + 5 + 4 + 3 + 2 + 1", 21},
        {"6 + 5 + 4 + 3 + 2 * 2", 22},
        {"6 + (5 * 4) + 3 - 2 - 1", 26},
        {"6 + 5 + 4 + 3 + 2 + 1", 21},
};
#endif //TEST_CALCULATOR_DATA_FOR_TESTS_HPP
