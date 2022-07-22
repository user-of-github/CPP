#ifndef TEST_CALCULATOR_TYPES_FOR_TESTS_HPP
#define TEST_CALCULATOR_TYPES_FOR_TESTS_HPP


class TestNumberExtractingBase
{
public:
    std::string source {};
    std::size_t extract_from {};
};

class TestNumberExtractingValid : public TestNumberExtractingBase
{
public:
    std::string right_response {};
};

class TestNumberConvertingValid : public TestNumberExtractingBase
{
public:
    double right_response {};
};


struct TestRemovingSpaces
{
    const std::string source;
    const std::string result;
};

struct TestCalculatorComputings
{
    const std::string source;
    const double result;
};


#endif //TEST_CALCULATOR_TYPES_FOR_TESTS_HPP
