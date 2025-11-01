#include <gtest/gtest.h>
#include <../include/seven.hpp>

// --- Тесты конструктора ---
TEST(SevenTest, ConstructorFromString) {
    Seven num("1234");
    EXPECT_EQ(num.Size(), 4);
    std::ostringstream oss;
    oss << num;
    EXPECT_EQ(oss.str(), "1234");
}

TEST(SevenTest, ConstructorFromInitList) {
    Seven num({'1', '2', '3'});
    std::ostringstream oss;
    oss << num;
    EXPECT_EQ(oss.str(), "123");
}

TEST(SevenTest, CopyConstructor) {
    Seven num1("456");
    Seven num2(num1);
    EXPECT_EQ(num1.Size(), num2.Size());
    std::ostringstream oss1, oss2;
    oss1 << num1;
    oss2 << num2;
    EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(SevenTest, MoveConstructor) {
    Seven num1("123");
    Seven num2(std::move(num1));
    EXPECT_EQ(num2.Size(), 3);
    EXPECT_EQ(num1.Size(), 0); // num1 должен стать пустым
}

// --- Тесты операторов сравнения ---
TEST(SevenTest, ComparisonOperators) {
    Seven a("1234");
    Seven b("1234");
    Seven c("1235");
    Seven d("1220");

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(d < a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(c >= a);
}

// --- Тесты арифметики ---
TEST(SevenTest, AdditionSimple) {
    Seven a("3");
    Seven b("2");
    Seven result = a + b;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "5");
}

TEST(SevenTest, AdditionWithCarry) {
    Seven a("6");
    Seven b("3"); // 6 + 3 = 12 (в 7-ричной это 15)
    Seven result = a + b;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "12"); // 6 + 3 = 12(7)
}

TEST(SevenTest, SubtractionSimple) {
    Seven a("5");
    Seven b("3");
    Seven result = a - b;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "2");
}

TEST(SevenTest, SubtractionWithBorrow) {
    Seven a("1000");
    Seven b("1");
    Seven result = a - b;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "666"); // в 7-ричной: 1000 - 1 = 666
}

TEST(SevenTest, IncrementAndDecrement) {
    Seven a("6");
    ++a;
    std::ostringstream oss1;
    oss1 << a;
    EXPECT_EQ(oss1.str(), "10");

    Seven b("10");
    --b;
    std::ostringstream oss2;
    oss2 << b;
    EXPECT_EQ(oss2.str(), "6");
}

// --- Тесты для краевых случаев ---
TEST(SevenTest, EmptyObject) {
    Seven a;
    EXPECT_EQ(a.Size(), 0);
}

TEST(SevenTest, LongNumberAddition) {
    Seven a("666666");
    Seven b("1");
    Seven result = a + b;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "1000000");
}

// --- Тесты с некорректным вводом ---
TEST(SevenTest, InvalidInput) {
    EXPECT_THROW({
        Seven invalid("89"); // недопустимые цифры для 7-ричной системы
    }, std::invalid_argument);
}

// --- Тест на самоприсваивание ---
TEST(SevenTest, SelfAssignment) {
    Seven a("123");
    a = a;
    std::ostringstream oss;
    oss << a;
    EXPECT_EQ(oss.str(), "123");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}