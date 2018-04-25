#pragma once
#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

namespace casting {
void ____Casting_Benchmarks____(benchmark::State &state) {
  for (auto _ : state) {
  }
}

class A {
 public:
  virtual ~A() {}
};

class B1 : public A {
 public:
  virtual ~B1() {}
  int print() { return 1; }
};

class B2 : public A {
 public:
  virtual ~B2() {}
  int print() { return 2; }
};

class C1 : public B1 {
 public:
};

class C2 : public B1 {
 public:
};

class C3 : public B2 {
 public:
};

volatile static int count = 0;
void static_casting(benchmark::State &state) {
  A *raw_ptr = new C1;
  count = 0;
  for (auto _ : state) {
    auto casted_ptr = static_cast<C1 *>(raw_ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
  delete raw_ptr;
}

void dynamic_casting(benchmark::State &state) {
  A *raw_ptr = new C1;
  count = 0;
  for (auto _ : state) {
    auto casted_ptr = dynamic_cast<C1 *>(raw_ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
  delete raw_ptr;
}

void dynamic_pointer_casting(benchmark::State &state) {
  auto ptr = std::make_shared<C2>();
  count = 0;
  for (auto _ : state) {
    auto casted_ptr = std::dynamic_pointer_cast<C2>(ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
}

void static_pointer_casting(benchmark::State &state) {
  auto ptr = std::make_shared<C2>();
  count = 0;
  for (auto _ : state) {
    auto casted_ptr = std::static_pointer_cast<C2>(ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
}
}  // namespace casting
