#include "Expression.h"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

TEST(CalculatorTest, SimpleCase) 
{
    std::string str = "-1 + 5 - 3";
    Expression exp(str);
    std::cout << "Expression: " << str << std::endl;
    ASSERT_EQ(1, exp.getValue());
    std::cout << "Result: " << exp.getValue() << std::endl;
}

TEST(CalculatorTest, CaseWithAnySeparators)
{
    std::string str = "-10 + (8 * 2.5) - (3 / 1,5)";
    Expression exp(str);
    std::cout << "Expression: " << str << std::endl;
    ASSERT_EQ(8, exp.getValue());
    std::cout << "Result: " << exp.getValue() << std::endl;
}

TEST(CalculatorTest, LongExpressionCase)
{
    std::string str = "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
    Expression exp(str);
    std::cout << "Expression: " << str << std::endl;
    ASSERT_EQ(11, exp.getValue());
    std::cout << "Result: " << exp.getValue() << std::endl;
}

TEST(CalculatorTest, LongDecimalCase)
{
    std::string str = "5.58 * 7,46";
    Expression exp(str);
    std::cout << "Expression: " << str << std::endl;
    ASSERT_EQ(41.63, exp.getValue());
    std::cout << "Result: " << exp.getValue() << std::endl;
}

TEST(CalculatorTest, WithLettersCase)
{
    std::string str = "1.1 + 2.1 + abc";
    std::cout << "Expression: " << str << std::endl;
    ASSERT_NO_THROW(Expression exp(str)) << "Invalid input: abc";
}

int main (int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

