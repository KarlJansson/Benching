#pragma once
#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>
#include <sstream>

namespace casting {
void ____Casting_Benchmarks____(benchmark::State &state) {
  for (auto _ : state) {
  }
}

class Base {
 public:
};

template <typename T>
class NoPoly_Template : public Base {
 public:
  int print() { return static_cast<T *>(this)->print(); }
};

class A_NoPoly : public NoPoly_Template<A_NoPoly> {
 public:
  int print() { return 1; }
};

class B_NoPoly : public NoPoly_Template<B_NoPoly> {
 public:
  int print() { return 1; }
};

class A {
 public:
  virtual ~A() {}
  virtual int print() = 0;
};

class B1 : public A {
 public:
  int print() override { return 1; }
};

class B2 : public A {
 public:
  int print() override { return 2; }
};

volatile static int count = 0;
void print_nopoly(benchmark::State &state) {
  count = 0;
  auto a_nopoly = std::make_unique<A_NoPoly>();
  for (auto _ : state) {
    count += a_nopoly->print();
    benchmark::DoNotOptimize(count);
    benchmark::ClobberMemory();
  }
}

void print_poly(benchmark::State &state) {
  count = 0;
  std::unique_ptr<A> a_poly = std::make_unique<B1>();
  for (auto _ : state) {
    count += a_poly->print();
    benchmark::DoNotOptimize(count);
    benchmark::ClobberMemory();
  }
}

void static_casting(benchmark::State &state) {
  count = 0;
  A *raw_ptr = new B1;
  for (auto _ : state) {
    auto casted_ptr = static_cast<B1 *>(raw_ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
  delete raw_ptr;
}

void dynamic_casting(benchmark::State &state) {
  count = 0;
  A *raw_ptr = new B1;
  for (auto _ : state) {
    auto casted_ptr = dynamic_cast<B1 *>(raw_ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
  delete raw_ptr;
}

void dynamic_pointer_casting(benchmark::State &state) {
  count = 0;
  auto ptr = std::make_shared<B2>();
  for (auto _ : state) {
    auto casted_ptr = std::dynamic_pointer_cast<B2>(ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
}

void static_pointer_casting(benchmark::State &state) {
  count = 0;
  auto ptr = std::make_shared<B2>();
  for (auto _ : state) {
    auto casted_ptr = std::static_pointer_cast<B2>(ptr);
    count += casted_ptr->print();
    benchmark::DoNotOptimize(casted_ptr);
    benchmark::ClobberMemory();
  }
}
}  // namespace casting
