#include "Circle_list.hpp"
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

// Проверяем, что новый список пуст
TEST(CircleListBasic, InitiallyEmpty) {
    Circle_list<int> lst;
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.get_size(), 0u);
}

// После append и prepend элементы на месте
TEST(CircleListBasic, AppendPrependFrontBack) {
    Circle_list<int> lst;
    lst.append(10);
    EXPECT_FALSE(lst.empty());
    EXPECT_EQ(lst.get_size(), 1u);
    EXPECT_EQ(lst.front(), 10);
    EXPECT_EQ(lst.back(), 10);

    lst.append(20);
    EXPECT_EQ(lst.get_size(), 2u);
    EXPECT_EQ(lst.front(), 10);
    EXPECT_EQ(lst.back(), 20);

    lst.prepend(5);
    EXPECT_EQ(lst.get_size(), 3u);
    EXPECT_EQ(lst.front(), 5);
    EXPECT_EQ(lst.back(), 20);
}

// Удаление первого элемента
TEST(CircleListBasic, RemoveFirst) {
    Circle_list<int> lst = {1, 2, 3};
    EXPECT_EQ(lst.get_size(), 3u);

    lst.remove_first(); // убираем 1
    EXPECT_EQ(lst.get_size(), 2u);
    EXPECT_EQ(lst.front(), 2);
    EXPECT_EQ(lst.back(), 3);

    lst.remove_first(); // убираем 2
    EXPECT_EQ(lst.get_size(), 1u);
    EXPECT_EQ(lst.front(), 3);
    EXPECT_EQ(lst.back(), 3);

    lst.remove_first(); // убираем последний элемент
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.get_size(), 0u);
    EXPECT_THROW(lst.front(), std::out_of_range);
    EXPECT_THROW(lst.remove_first(), std::out_of_range);
}

// Итератор итерируется от head до tail один раз
TEST(CircleListIter, ForwardIteration) {
    Circle_list<int> lst = {10, 20, 30, 40};
    std::vector<int> seen;
    for (auto& x : lst) {
        seen.push_back(x);
    }
    std::vector<int> expected = {10, 20, 30, 40};
    EXPECT_EQ(seen, expected);
}

// Конструктор копирования и оператор= копируют данные
TEST(CircleListCopy, CopyConstructorAndAssign) {
    Circle_list<std::string> orig = {"a", "b", "c"};
    Circle_list<std::string> copy1(orig);
    EXPECT_EQ(copy1.get_size(), 3u);
    std::vector<std::string> v1;
    for (auto& s : copy1) v1.push_back(s);
    EXPECT_EQ(v1, (std::vector<std::string>{"a","b","c"}));

    Circle_list<std::string> copy2;
    copy2 = orig;
    EXPECT_EQ(copy2.get_size(), 3u);
    std::vector<std::string> v2;
    for (auto& s : copy2) v2.push_back(s);
    EXPECT_EQ(v2, (std::vector<std::string>{"a","b","c"}));
}

// Конструктор перемещения и оператор= перемещением
TEST(CircleListMove, MoveConstructorAndAssign) {
    Circle_list<int> temp = {1,2,3};
    Circle_list<int> moved1(std::move(temp));
    EXPECT_TRUE(temp.empty());  // источник сброшен
    EXPECT_EQ(moved1.get_size(), 3u);
    std::vector<int> v1;
    for (auto& x : moved1) v1.push_back(x);
    EXPECT_EQ(v1, (std::vector<int>{1,2,3}));

    Circle_list<int> temp2 = {4,5};
    Circle_list<int> moved2;
    moved2 = std::move(temp2);
    EXPECT_TRUE(temp2.empty());
    EXPECT_EQ(moved2.get_size(), 2u);
    std::vector<int> v2;
    for (auto& x : moved2) v2.push_back(x);
    EXPECT_EQ(v2, (std::vector<int>{4,5}));
}

// Оператор <=> и == 
TEST(CircleListCompare, ThreeWayAndEqual) {
    Circle_list<int> a = {1,2,3};
    Circle_list<int> b = {1,2,3};
    Circle_list<int> c = {1,2,4};
    Circle_list<int> d = {1,2};

    // ==, !=
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);

    // <=> сравнение поэлементно
    EXPECT_EQ((a <=> b), std::strong_ordering::equal);
    EXPECT_EQ((a <=> c), std::strong_ordering::less);
    EXPECT_EQ((c <=> a), std::strong_ordering::greater);
    // Длины: d меньше, чем a (т. к. size=2 vs size=3)
    EXPECT_EQ((d <=> a), std::strong_ordering::less);
    EXPECT_EQ((a <=> d), std::strong_ordering::greater);
}
