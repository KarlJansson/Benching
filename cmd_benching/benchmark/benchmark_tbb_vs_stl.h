#pragma once

#include <tbb/tbb.h>

#include <execution>

namespace tbb_vs_stl {
void ____Tbb_vs_Stl_Benchmarks____(benchmark::State& state) {
  for (auto _ : state) {
  }
}

void tbb_parallel(benchmark::State& state) {
  std::atomic<int> acc{0};
  std::vector<int> col(20000, 1);
  for (auto _ : state) {
    tbb::parallel_for(size_t(0), col.size(), [&](size_t i) { acc += col[i]; });
    benchmark::DoNotOptimize(col);
    benchmark::DoNotOptimize(acc);
    benchmark::ClobberMemory();
  }
}

void stl_parallel(benchmark::State& state) {
  std::atomic<int> acc{0};
  std::vector<int> col(20000, 1);
  for (auto _ : state) {
    std::for_each(std::execution::par_unseq, col.begin(), col.end(),
                  [&](auto i) { acc += i; });
    benchmark::DoNotOptimize(col);
    benchmark::DoNotOptimize(acc);
    benchmark::ClobberMemory();
  }
}
}  // namespace tbb_vs_stl
