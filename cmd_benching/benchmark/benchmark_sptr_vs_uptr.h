#include <benchmark/benchmark.h>
#include <memory>

template <typename T>
void create_destroy(benchmark::State& state) {
  for (auto _ : state) {
    T ptr = T(new size_t(3));
    benchmark::DoNotOptimize(ptr);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_TEMPLATE(create_destroy, std::unique_ptr<size_t>);
BENCHMARK_TEMPLATE(create_destroy, std::shared_ptr<size_t>);
