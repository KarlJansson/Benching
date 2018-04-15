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
}  // namespace shared_vs_unique
