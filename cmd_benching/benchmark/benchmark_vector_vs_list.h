#include <benchmark/benchmark.h>
#include <algorithm>
#include <list>
#include <vector>

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

BENCHMARK_TEMPLATE(find_missing, std::vector<size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(find_missing, std::list<size_t>)->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(find_existing, std::vector<size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(find_existing, std::list<size_t>)->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(push_back, std::vector<size_t>);
BENCHMARK_TEMPLATE(push_back, std::list<size_t>);
