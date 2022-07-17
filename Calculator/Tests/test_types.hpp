#ifndef TEST_CALCULATOR_TEST_TYPES_HPP
#define TEST_CALCULATOR_TEST_TYPES_HPP


class TestNumberExtractingInvalid
{
public:
    std::string source;
    std::size_t extract_from;
};

class TestNumberExtractingValid : public TestNumberExtractingInvalid
{
public:
    std::string right_response;
};


#endif //TEST_CALCULATOR_TEST_TYPES_HPP
