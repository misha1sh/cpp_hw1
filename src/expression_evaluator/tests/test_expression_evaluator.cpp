#include <gtest/gtest.h>
#include <stdexcept>

#include <evaluator.h>

using expression_evaluator::ExpressionsEvaluator;
using big_num::BigNumber;

TEST(ExpressionsEvaluator, Ident) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("1"), BigNumber(1));
}


TEST(ExpressionsEvaluator, UnaryOperator) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("-1"), BigNumber(-1));
}

TEST(ExpressionsEvaluator, UnaryOperatorChain) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("---1"), BigNumber(-1));
    EXPECT_EQ(evaluator.EvaluateExpression("---(--5*-+-3)"),
              BigNumber(-(5*-+-3)));
    EXPECT_EQ(evaluator.EvaluateExpression("-(-+--5+-+3)"),
              BigNumber(-(-+5+-+3)));
}

TEST(ExpressionsEvaluator, BasicSum) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("1+2"), BigNumber(1+2));
}

TEST(ExpressionsEvaluator, BasicMult) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("-6*-34"), BigNumber(-6*-34));
}

TEST(ExpressionsEvaluator, BasicDiv) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("100/5"), BigNumber(100/5));
}

TEST(ExpressionsEvaluator, BasicMod) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("23 % -4"), BigNumber(23 % -4));
}

TEST(ExpressionsEvaluator, BasicCompare) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("1 < 2"), BigNumber(1));
    EXPECT_EQ(evaluator.EvaluateExpression("1 <= 2 - 4"), BigNumber(0));
    EXPECT_EQ(evaluator.EvaluateExpression("3 * 7 == 7 % 4 + 6 * 3"), BigNumber(1));
}


TEST(ExpressionsEvaluator, OperationsPriority) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("100 - 2 * 3"),
              BigNumber(100 - 2 * 3));
    EXPECT_EQ(evaluator.EvaluateExpression("(100 - 2) * 3"),
              BigNumber((100 - 2) * 3));
}

TEST(ExpressionsEvaluator, DiffrentExpressions) {
    ExpressionsEvaluator evaluator{};
    EXPECT_EQ(evaluator.EvaluateExpression("(1 + 4) * -(23 + 4 % 3)"),
              BigNumber((1 + 4) * -(23 + 4 % 3)));
    EXPECT_EQ(evaluator.EvaluateExpression("(23 % -4 * 2 / -3) - 0"),
              BigNumber((23 % -4 * 2 / -3) - 0));
    EXPECT_EQ(evaluator.EvaluateExpression("(1 + 4) * -(23 + 4 % 3)"),
              BigNumber((1 + 4) * -(23 + 4 % 3)));


}


TEST(ExpressionsEvaluator, InvalidExpressionSpaceInNumber) {
    ExpressionsEvaluator evaluator{};
    EXPECT_THROW({
                     try {
                         evaluator.EvaluateExpression("1 2");
                     } catch( const std::logic_error& e ) {
                         EXPECT_STREQ( "Too many numbers", e.what() );
                         throw;
                     }
                 }, std::logic_error );
}

TEST(ExpressionsEvaluator, InvalidExpressionDoubleOperator) {
    ExpressionsEvaluator evaluator{};
    EXPECT_THROW({
                     try {
                         evaluator.EvaluateExpression("1**2");
                     } catch( const std::logic_error& e ) {
                         EXPECT_STREQ( "Operator * is not unary", e.what() );
                         throw;
                     }
                 }, std::logic_error );
}

TEST(ExpressionsEvaluator, InvalidExpressionZeroDivision) {
    ExpressionsEvaluator evaluator{};
    EXPECT_THROW({
                     try {
                         evaluator.EvaluateExpression("1 / 0");
                     } catch( const std::overflow_error& e ) {
                         EXPECT_STREQ( "Divide by zero error", e.what() );
                         throw;
                     }
                 }, std::overflow_error );
}


TEST(ExpressionsEvaluator, InvalidExpression) {
    ExpressionsEvaluator evaluator{};
    EXPECT_THROW({
                     try {
                         evaluator.EvaluateExpression("1 + kek");
                     } catch( const std::logic_error& e ) {
                         EXPECT_STREQ( "Unable to parse expression: `kek`", e.what() );
                         throw;
                     }
                 }, std::logic_error );
}
