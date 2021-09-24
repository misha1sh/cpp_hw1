#include <gtest/gtest.h>

#include <src/big_number.h>

using big_num::BigNumber;

TEST(BigNumber, ToStringShort) {
    BigNumber bigNumber("123");

    EXPECT_EQ(bigNumber.ToString(), "123");
}

TEST(BigNumber, ToStringLong) {
    BigNumber bigNumber("1234567891234000000000000000010000000000000000000000003456789");

    EXPECT_EQ(bigNumber.ToString(), "1234567891234000000000000000010000000000000000000000003456789");
}

TEST(BigNumber, ToStringLongNegative) {
    BigNumber bigNumber("-123456789000000000");

    EXPECT_EQ(bigNumber.ToString(), "-123456789000000000");
}

TEST(BigNumber, SumBothPositive) {
    BigNumber bigNumber("12935923958092385902350");
    BigNumber bigNumber2("5715912375972130957");

    EXPECT_EQ((bigNumber + bigNumber2).ToString(), "12941639870468358033307");
}

TEST(BigNumber, Compare) {
    BigNumber bigNumber("100000000000000");
    BigNumber bigNumber2("2000000001");

    EXPECT_TRUE(bigNumber > bigNumber2);
}

TEST(BigNumber, CompareNegative) {
    BigNumber bigNumber("-100000322323113333333000000000");
    BigNumber bigNumber2("-122131233213122000000001");

    EXPECT_TRUE(bigNumber <= bigNumber2);
}

TEST(BigNumber, CompareGreatherOrEq) {
    BigNumber bigNumber("12312421124214214");
    BigNumber bigNumber2("12312421124214214");

    EXPECT_TRUE(bigNumber >= bigNumber2);
}

TEST(BigNumber, CompareEq) {
    BigNumber bigNumber("-123123123");
    BigNumber bigNumber2("-123123123");

    EXPECT_TRUE(bigNumber >= bigNumber2);
}

TEST(BigNumber, SumPositiveSmallNegative) {
    BigNumber bigNumber("5329755436249032452344");
    BigNumber bigNumber2("-1246342631421412515");

    EXPECT_EQ((bigNumber + bigNumber2).ToString(), "5328509093617611039829");
}

TEST(BigNumber, SumPositiveBigNegative) {
    BigNumber bigNumber("6904895486546854690854680934235");
    BigNumber bigNumber2("-124634263152235325235235235235235235421412515");

    EXPECT_EQ((bigNumber + bigNumber2).ToString(), "-124634263152228420339748688380544380740478280");
}

TEST(BigNumber, SumBigNegativePositive) {
    BigNumber bigNumber("-42191248218421787124321213214124");
    BigNumber bigNumber2("421124214241241");

    EXPECT_EQ((bigNumber + bigNumber2).ToString(), "-42191248218421786703196998972883");
}

TEST(BigNumber, SubBothPositive) {
    BigNumber bigNumber("858235895238952389");
    BigNumber bigNumber2("2355233252352352353252355532");

    EXPECT_EQ((bigNumber - bigNumber2).ToString(), "-2355233251494116458013403143");
}

TEST(BigNumber, SubZero) {
    BigNumber bigNumber("-0");
    BigNumber bigNumber2("0");

    EXPECT_EQ((bigNumber - bigNumber2).ToString(), "0");
}