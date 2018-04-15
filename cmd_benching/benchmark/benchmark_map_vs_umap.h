#include <benchmark/benchmark.h>
#include <map>
#include <unordered_map>

template <typename T>
void update(benchmark::State& state) {
  T map;
  for (auto i = 0; i < state.range(0); ++i) map[i] = i;

  auto key = 0;
  for (auto _ : state) {
    map[key++ % state.range(0)] = 23;
    benchmark::DoNotOptimize(map);
    benchmark::ClobberMemory();
  }
}

template <typename T>
void lookup_exists(benchmark::State& state) {
  T map;
  for (auto i = 0; i < state.range(0); ++i) map[i] = i;

  auto key = 0;
  for (auto _ : state) {
    auto r = map.find(key++ % state.range(0));
    benchmark::DoNotOptimize(r);
    benchmark::ClobberMemory();
  }
}

template <typename T>
void lookup_missing(benchmark::State& state) {
  T map;
  for (auto i = 0; i < state.range(0); ++i) map[i] = i;

  auto key = 0;
  for (auto _ : state) {
    auto r = map.find(state.range(0) + key++);
    benchmark::DoNotOptimize(r);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_TEMPLATE(lookup_missing, std::map<size_t, size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(lookup_missing, std::unordered_map<size_t, size_t>)
    ->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(lookup_exists, std::map<size_t, size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(lookup_exists, std::unordered_map<size_t, size_t>)
    ->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(update, std::map<size_t, size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(update, std::unordered_map<size_t, size_t>)
    ->Range(8, 8 << 10);
