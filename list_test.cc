#include <list>
#include <gtest/gtest.h>
#include "my_allocator.hh"

namespace {
  struct A {
    int i;
    explicit A(int x) : i(x) {}
    bool operator<(const A &x) const { return i < x.i; }
  };

  struct B {
    int i;
    explicit B(int x) : i(x) {}
    bool operator==(const B &x) const { return i == x.i; }
  };
}

TEST(ListTest, ctor_1a) {
  std::list<int> list;

  ASSERT_TRUE(list.empty());
  ASSERT_EQ(static_cast<size_t>(0), list.size());
}

TEST(ListTest, ctor_1b) {
  MyAllocator<int> a;

  std::list<int, MyAllocator<int> > list(a);

  ASSERT_TRUE(list.empty());
  ASSERT_EQ(static_cast<size_t>(0), list.size());
}

TEST(ListTest, ctor_2a) {
  std::list<int> list(3, 1);

  ASSERT_FALSE(list.empty());
  ASSERT_EQ(static_cast<size_t>(3), list.size());
  for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it) {
    ASSERT_EQ(1, *it);
  }
}

TEST(ListTest, ctor_2b) {
  MyAllocator<int> a;

  std::list<int, MyAllocator<int> > list(3, 1, a);

  ASSERT_FALSE(list.empty());
  ASSERT_EQ(static_cast<size_t>(3), list.size());
  for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it) {
    ASSERT_EQ(1, *it);
  }
}

TEST(ListTest, ctor_3a) {
  std::list<int> list1;
  std::list<int>::iterator it;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  list1.push_back(4);
  list1.push_back(5);

  std::list<int> list2(++list1.begin(), --list1.end());

  ASSERT_FALSE(list2.empty());
  ASSERT_EQ(static_cast<size_t>(3), list2.size());
  it = list2.begin();
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(3, *it++);
  ASSERT_EQ(4, *it++);
}

TEST(ListTest, ctor_3b) {
  MyAllocator<int> a;
  std::list<int> list1;
  std::list<int>::iterator it;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  list1.push_back(4);
  list1.push_back(5);

  std::list<int, MyAllocator<int> > list2(++list1.begin(), --list1.end());

  ASSERT_FALSE(list2.empty());
  ASSERT_EQ(static_cast<size_t>(3), list2.size());
  it = list2.begin();
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(3, *it++);
  ASSERT_EQ(4, *it++);
}

TEST(ListTest, ctor_4) {
  std::list<int> list1;
  std::list<int>::iterator it;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  std::list<int> list2(list1);
  
  ASSERT_FALSE(list2.empty());
  ASSERT_EQ(static_cast<size_t>(3), list2.size());
  it = list2.begin();
  ASSERT_EQ(1, *it++);
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(3, *it++);
}

TEST(ListTest, ctor_5) {
  std::list<int>::iterator it;

  std::list<int> list(3);

  ASSERT_FALSE(list.empty());
  ASSERT_EQ(static_cast<size_t>(3), list.size());
  it = list.begin();
  ASSERT_EQ(0, *it++);
  ASSERT_EQ(0, *it++);
  ASSERT_EQ(0, *it++);
}

TEST(ListTest, assign_1) {
  std::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  std::list<int> list2;
  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);
  list2.push_back(7);
  list1.assign(++list2.begin(), --list2.end());
  ASSERT_EQ(static_cast<size_t>(2), list1.size());
  std::list<int>::iterator it = list1.begin();
  ASSERT_EQ(5, *it++);
  ASSERT_EQ(6, *it++);
}

TEST(ListTest, assign_2) {
  std::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  list1.assign(5, 4);
  ASSERT_EQ(static_cast<size_t>(5), list1.size());
  std::list<int>::iterator it = list1.begin();
  ASSERT_EQ(4, *it++);
  ASSERT_EQ(4, *it++);
  ASSERT_EQ(4, *it++);
  ASSERT_EQ(4, *it++);
  ASSERT_EQ(4, *it++);
}

TEST(ListTest, back) {
  std::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(3, list.back());
}

TEST(ListTest, begin) {
  std::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  std::list<int>::iterator it = list.begin();
  ASSERT_EQ(1, *it);
}

TEST(ListTest, end) {
  std::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  std::list<int>::iterator it = list.end();
  --it;
  ASSERT_EQ(3, *it);
}

TEST(ListTest, front) {
  std::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(1, list.front());
}

TEST(ListTest, empty) {
  std::list<int> list;
  ASSERT_TRUE(list.empty());
  list.push_back(1);
  ASSERT_FALSE(list.empty());
  list.pop_back();
  ASSERT_TRUE(list.empty());
}

TEST(ListTest, insert_1) {
  std::list<int> list;
  std::list<int>::iterator it = list.insert(list.begin(), 1);
  ASSERT_EQ(1, *it);
}

TEST(ListTest, push_back) {
  std::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  ASSERT_EQ(static_cast<size_t>(3), list.size());
  std::list<int>::iterator it = list.begin();
  ASSERT_EQ(1, *it++);
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(3, *it++);
}

TEST(ListTest, push_front) {
  std::list<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  std::list<int>::iterator it = list.begin();
  ASSERT_EQ(3, *it++);
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(1, *it++);
}

TEST(ListTest, rbegin) {
  std::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  std::list<int>::reverse_iterator it = list.rbegin();
  ASSERT_EQ(3, *it);
}

TEST(ListTest, rend) {
  std::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  std::list<int>::reverse_iterator it = list.rend();
  --it;
  ASSERT_EQ(1, *it);
}

TEST(ListTest, reverse) {
  std::list<int> list;
  std::list<int>::iterator it;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.reverse();

  it = list.begin();
  ASSERT_EQ(3, *it++);
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(1, *it++);
}

TEST(ListTest, size) {
  std::list<int> list;
  ASSERT_EQ(static_cast<size_t>(0), list.size());
  list.push_back(1);
  ASSERT_EQ(static_cast<size_t>(1), list.size());
  list.push_back(2);
  ASSERT_EQ(static_cast<size_t>(2), list.size());
  list.push_back(3);
  ASSERT_EQ(static_cast<size_t>(3), list.size());
  list.pop_back();
  ASSERT_EQ(static_cast<size_t>(2), list.size());
  list.pop_back();
  ASSERT_EQ(static_cast<size_t>(1), list.size());
  list.pop_back();
  ASSERT_EQ(static_cast<size_t>(0), list.size());
}

TEST(ListTest, sort_1) {
  std::list<int> list;
  std::list<int>::iterator it;

  list.push_back(2);
  list.push_back(3);
  list.push_back(1);

  list.sort();

  it = list.begin();
  ASSERT_EQ(1, *it++);
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(3, *it++);
}

TEST(ListTest, sort_2) {
  std::list<A> list;
  std::list<A>::iterator it;

  list.push_back(A(2));
  list.push_back(A(3));
  list.push_back(A(1));

  list.sort();

  it = list.begin();
  ASSERT_EQ(1, (*it++).i);
  ASSERT_EQ(2, (*it++).i);
  ASSERT_EQ(3, (*it++).i);
}

TEST(ListTest, unique_1) {
  std::list<int> list;
  std::list<int>::iterator it;

  list.push_back(2);
  list.push_back(2);
  list.push_back(3);
  list.push_back(1);
  list.push_back(3);
  list.push_back(3);
  list.push_back(1);

  list.unique();

  it = list.begin();
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(3, *it++);
  ASSERT_EQ(1, *it++);
  ASSERT_EQ(3, *it++);
  ASSERT_EQ(1, *it++);
}

TEST(ListTest, unique_2) {
  std::list<B> list;
  std::list<B>::iterator it;

  list.push_back(B(2));
  list.push_back(B(2));
  list.push_back(B(3));
  list.push_back(B(1));
  list.push_back(B(3));
  list.push_back(B(3));
  list.push_back(B(1));

  list.unique();

  it = list.begin();
  ASSERT_EQ(2, (*it++).i);
  ASSERT_EQ(3, (*it++).i);
  ASSERT_EQ(1, (*it++).i);
  ASSERT_EQ(3, (*it++).i);
  ASSERT_EQ(1, (*it++).i);
}

TEST(ListTest, swap) {
  std::list<int> list1;
  std::list<int> list2;
  std::list<int>::iterator it;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);

  list1.swap(list2);

  it = list1.begin();
  ASSERT_EQ(4, *it++);
  ASSERT_EQ(5, *it++);
  ASSERT_EQ(6, *it++);
  it = list2.begin();
  ASSERT_EQ(1, *it++);
  ASSERT_EQ(2, *it++);
  ASSERT_EQ(3, *it++);
}
