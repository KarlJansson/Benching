#include <benchmark/benchmark.h>
#include <map>
#include <unordered_map>

void map_insert(benchmark::State& state) {
  std::map<size_t, size_t> map;
  for (auto i = 0; i < state.range(0); ++i) map[i] = i;

  auto key = 0;
  for (auto _ : state) {
    map[key++ % state.range(0)] = 23;
    benchmark::DoNotOptimize(state.iterations());
    benchmark::ClobberMemory();
  }
}

BENCHMARK(map_insert)->Range(8, 8 << 10);
