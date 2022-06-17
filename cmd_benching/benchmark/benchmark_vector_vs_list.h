#pragma once
#include <benchmark/benchmark.h>

#include <algorithm>
#include <list>
#include <vector>

namespace vector_vs_list {
void ____Vector_vs_List_Benchmarks____(benchmark::State& state) {
  for (auto _ : state) {
  }
}

template <typename T>
void push_back(benchmark::State& state) {
  T col;
  for (auto _ : state) {
    col.push_back(23);
    benchmark::DoNotOptimize(col);
    benchmark::ClobberMemory();
  }
}

template <typename T>
void find_existing(benchmark::State& state) {
  T col;
  for (auto i = state.range(0); --i;) col.push_back(i);

  size_t key = 0;
  for (auto _ : state) {
    auto itr =
        std::find(std::begin(col), std::end(col), key++ % state.range(0));
    benchmark::DoNotOptimize(itr);
    benchmark::ClobberMemory();
  }
}

template <typename T>
void find_missing(benchmark::State& state) {
  T col;
  for (auto i = state.range(0); --i;) col.push_back(i);

  size_t key = 0;
  for (auto _ : state) {
    auto itr =
        std::find(std::begin(col), std::end(col), state.range(0) + key++);
    benchmark::DoNotOptimize(itr);
    benchmark::ClobberMemory();
  }
}
}  // namespace vector_vs_list
