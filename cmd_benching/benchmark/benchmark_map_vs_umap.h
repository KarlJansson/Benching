#pragma once
#include <benchmark/benchmark.h>
#include <algorithm>
#include <map>
#include <unordered_map>

namespace map_vs_unordered {
void ____Map_vs_Unordered_Benchmarks____(benchmark::State& state) {
  for (auto _ : state) {
  }
}

template <typename T>
void update(benchmark::State& state) {
  T map;
  for (auto i = state.range(0); --i;) map[i] = i;

  auto key = 0;
  for (auto _ : state) {
    map[key++ % state.range(0)] = 23;
    benchmark::DoNotOptimize(map);
    benchmark::ClobberMemory();
  }
}

template <typename T>
void lookup_existing(benchmark::State& state) {
  T map;
  for (auto i = state.range(0); --i;) map[i] = i;

  size_t key = 0;
  for (auto _ : state) {
    auto itr = map.find(key++ % state.range(0));
    benchmark::DoNotOptimize(itr);
    benchmark::ClobberMemory();
  }
}

template <typename T>
void lookup_missing(benchmark::State& state) {
  T map;
  for (auto i = state.range(0); --i;) map[i] = i;

  auto key = 0;
  for (auto _ : state) {
    auto r = map.find(state.range(0) + key++);
    benchmark::DoNotOptimize(r);
    benchmark::ClobberMemory();
  }
}
}  // namespace map_vs_unordered
