#include <gtest/gtest.h>
#include <stdexcept>

#include <big_number.h>

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

    EXPECT_GT(bigNumber, bigNumber2);
}

TEST(BigNumber, CompareNegative) {
    BigNumber bigNumber("-100000322323113333333000000000");
    BigNumber bigNumber2("-122131233213122000000001");

    EXPECT_LE(bigNumber, bigNumber2);
}

TEST(BigNumber, CompareGreatherOrEq) {
    BigNumber bigNumber("12312421124214214");
    BigNumber bigNumber2("12312421124214214");

    EXPECT_GE(bigNumber, bigNumber2);
}

TEST(BigNumber, CompareEq) {
    BigNumber bigNumber("-123123123");
    BigNumber bigNumber2("-123123123");

    EXPECT_EQ(bigNumber, bigNumber2);
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

TEST(BigNumber, MulShort) {
    BigNumber bigNumber("12345");
    BigNumber bigNumber2("54345");

    EXPECT_EQ((bigNumber * bigNumber2).ToString(), "670889025");
}

TEST(BigNumber, MulLong) {
    BigNumber bigNumber("253853428462346243600000543858435848528500");
    BigNumber bigNumber2("3246342623469324962394693469234969234692346932462364");

    EXPECT_EQ((bigNumber * bigNumber2).ToString(),
              "824095204931135711949477387916228692211010318495377824452421556447971825677085522231031374000");
}

TEST(BigNumber, MulLeftNegative) {
    BigNumber bigNumber("-12345");
    BigNumber bigNumber2("54345");

    EXPECT_EQ((bigNumber * bigNumber2).ToString(), "-670889025");
}

TEST(BigNumber, MulRightNegative) {
    BigNumber bigNumber("12345");
    BigNumber bigNumber2("-54345");

    EXPECT_EQ((bigNumber * bigNumber2).ToString(), "-670889025");
}

TEST(BigNumber, MulBothNegative) {
    BigNumber bigNumber("-12345");
    BigNumber bigNumber2("-54345");

    EXPECT_EQ((bigNumber * bigNumber2).ToString(), "670889025");
}

TEST(BigNumber, MulZeroLeft) {
    BigNumber bigNumber("-0");
    BigNumber bigNumber2("123");

    EXPECT_EQ((bigNumber * bigNumber2).ToString(), "0");
}

TEST(BigNumber, MulZeroRight) {
    BigNumber bigNumber("32");
    BigNumber bigNumber2("0");

    EXPECT_EQ((bigNumber * bigNumber2).ToString(), "0");
}



TEST(BigNumber, ConvertToInt) {
    BigNumber bigNumber("1234");

    EXPECT_EQ((bigNumber + 5).ToString(), "1239");
}

TEST(BigNumber, ConvertToNegativeInt) {
    BigNumber bigNumber("1234");

    EXPECT_EQ((bigNumber + -5).ToString(), "1229");
}

TEST(BigNumber, ConvertToInt64) {
    BigNumber bigNumber("1234");

    EXPECT_EQ((bigNumber + (1LL << 35)).ToString(), "34359739602");
}

TEST(BigNumber, ConvertToUInt64) {
    BigNumber bigNumber("1234");

    EXPECT_EQ((bigNumber + (1ULL << 63)).ToString(), "9223372036854777042");
}

TEST(BigNumber, DivShort) {
    BigNumber bigNumber("4124124");
    BigNumber bigNumber2("43");

    EXPECT_EQ((bigNumber / bigNumber2).ToString(), "95909");
}

TEST(BigNumber, DivLongShort) {
    BigNumber bigNumber("1204591856180955699178493854");
    BigNumber bigNumber2("42");

    EXPECT_EQ((bigNumber / bigNumber2).ToString(), "28680758480498945218535567");
}


TEST(BigNumber, DivLong) {
    BigNumber bigNumber("253853428462346243600000543858435142002140214021400124021402140214214002140848528500"
                        "502350230520350235023050235032095019509109501920194012940120491284901284091284012804");
    BigNumber bigNumber2("12345678912581255");

    EXPECT_EQ((bigNumber / bigNumber2).ToString(),
              "205621278716109220615365488419691629272304719586840309396714410362898703161493545839829595862898896"
              "57280446888580925768312011927891292587003713191874891");
}

TEST(BigNumber, DivEqual) {
    BigNumber bigNumber("235123523523523515151515151515");
    BigNumber bigNumber2("235123523523523515151515151515");

    EXPECT_EQ((bigNumber / bigNumber2).ToString(), "1");
}


TEST(BigNumber, DivLeftZero) {
    BigNumber bigNumber("0");
    BigNumber bigNumber2("4121");

    EXPECT_EQ((bigNumber / bigNumber2).ToString(), "0");
}


TEST(BigNumber, DivRightZero) {
    BigNumber bigNumber("4121");
    BigNumber bigNumber2("0");
    EXPECT_THROW({
        try {
            bigNumber / bigNumber2;
        } catch( const std::overflow_error& e ) {
            EXPECT_STREQ( "Divide by zero error", e.what() );
            throw;
        }
    }, std::overflow_error );
}

TEST(BigNumber, DivLeftNegative) {
    BigNumber bigNumber("-1231241245125125125122512512499");
    BigNumber bigNumber2("37");

    EXPECT_EQ((bigNumber / bigNumber2).ToString(), "-33276790408787165543851689527");
}


TEST(BigNumber, ModShort) {
    BigNumber bigNumber("4124124");
    BigNumber bigNumber2("43");

    EXPECT_EQ((bigNumber % bigNumber2).ToString(), "37");
}

TEST(BigNumber, ModLongShort) {
    BigNumber bigNumber("1204591856180955699178493854");
    BigNumber bigNumber2("42");

    EXPECT_EQ((bigNumber % bigNumber2).ToString(), "40");
}


TEST(BigNumber, ModLong) {
    BigNumber bigNumber("253853428462346243600000543858435142002140214021400124021402140214214002140848528500"
                        "502350230520350235023050235032095019509109501920194012940120491284901284091284012804");
    BigNumber bigNumber2("12345678912581255");

    EXPECT_EQ((bigNumber % bigNumber2).ToString(),
              "6411749452244599");
}

TEST(BigNumber, ModEqual) {
    BigNumber bigNumber("235123523523523515151515151515");
    BigNumber bigNumber2("235123523523523515151515151515");

    EXPECT_EQ((bigNumber % bigNumber2).ToString(), "0");
}


TEST(BigNumber, ModLeftZero) {
    BigNumber bigNumber("0");
    BigNumber bigNumber2("4121");

    EXPECT_EQ((bigNumber % bigNumber2).ToString(), "0");
}


TEST(BigNumber, ModRightZero) {
    BigNumber bigNumber("4121");
    BigNumber bigNumber2("0");
    EXPECT_THROW({
                     try {
                         bigNumber % bigNumber2;
                     } catch( const std::overflow_error& e ) {
                         EXPECT_STREQ( "Divide by zero error", e.what() );
                         throw;
                     }
                 }, std::overflow_error );
}


TEST(BigNumber, ModLeftNegative) {
    BigNumber bigNumber("-12312412451251251251222512512499");
    BigNumber bigNumber2("37");

        EXPECT_EQ((bigNumber % bigNumber2).ToString(), "-22");
}

TEST(BigNumber, ModRightNegative) {
    BigNumber bigNumber("10000000000000000000000000000");
    BigNumber bigNumber2("-777777777777777777777");

    EXPECT_EQ((bigNumber % bigNumber2).ToString(), "666666666666676666666");
}

TEST(BigNumber, ModBothNegative) {
    BigNumber bigNumber("-10000000000000000000000000000");
    BigNumber bigNumber2("-777777777777777777777");

    EXPECT_EQ((bigNumber % bigNumber2).ToString(), "-666666666666676666666");
}


TEST(BigNumber, InputOperator) {
    BigNumber bigNumber;
    std::stringstream input("1234444149149149149149");
    input >> bigNumber;

    EXPECT_EQ(bigNumber.ToString(), "1234444149149149149149");
}

TEST(BigNumber, OutputOperator) {
    BigNumber bigNumber("1234444149149149149149");
    std::stringstream output;
    output << bigNumber;

    EXPECT_EQ(output.str(), "1234444149149149149149");
}