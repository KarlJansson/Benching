#pragma once
#include <benchmark/benchmark.h>
#include <memory>

namespace shared_vs_unique {
template <typename T>
void create_destroy(benchmark::State& state) {
  for (auto _ : state) {
    T ptr = T(new size_t(3));
    benchmark::DoNotOptimize(ptr);
    benchmark::ClobberMemory();
  }
}

void make_unique_create_destroy(benchmark::State& state) {
  for (auto _ : state) {
    auto ptr = std::make_unique<size_t>(size_t(23));
    benchmark::DoNotOptimize(ptr);
    benchmark::ClobberMemory();
  }
}

void make_shared_create_destroy(benchmark::State& state) {
  for (auto _ : state) {
    auto ptr = std::make_shared<size_t>(size_t(23));
    benchmark::DoNotOptimize(ptr);
    benchmark::ClobberMemory();
  }
}

void copy_shared_ptr(benchmark::State& state) {
  auto ptr = std::make_shared<size_t>(size_t(23));
  for (auto _ : state) {
    auto p = ptr;
    benchmark::DoNotOptimize(p);
    benchmark::ClobberMemory();
  }
}

void move_unique_ptr(benchmark::State& state) {
  bool flip = true;
  std::unique_ptr<size_t> p[2];
  p[1] = std::make_unique<size_t>(size_t(23));
  for (auto _ : state) {
    p[flip ? 0 : 1] = std::move(p[flip ? 1 : 0]);
    flip = !flip;
    benchmark::DoNotOptimize(p[flip ? 0 : 1]);
    benchmark::ClobberMemory();
  }
}
}  // namespace shared_vs_unique
