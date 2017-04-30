#include "gtest/gtest.h"
#include <cstdio>

#include "ZBE/core/tools/tools.h"

struct A {
    char getA(){return 'a';};
};

struct B {
    char getB(){return 'b';};
};

struct C {
    char getC(){return 'c';};
};

struct D {
    char getD(){return 'd';};
};

struct All : public A, public B, public C, public D{
};

TEST (tools, TypeContainerTest) {
    All all;
    TypeContainer<A,B,C,D> tcABCD(&all,&all,&all,&all);
    TypeContainer<A>* tcA= &tcABCD;
    A* tempA = tcA->get();
    tempA->getA();

    TypeContainer<void> tcVoid(nullptr);
}
