#pragma once
#include <benchmark/benchmark.h>
#include <tbb/tbb.h>

#include "benchmark_casting.h"
#include "benchmark_map_vs_umap.h"
#include "benchmark_sptr_vs_uptr.h"
#include "benchmark_tbb_vs_stl.h"
#include "benchmark_vector_vs_list.h"

#define _CASTING_
#define _SHARED_VS_UNIQUE_
#define _MAP_VS_UNORDERED_
#define _VECTOR_VS_LIST_
#define _TBB_VS_STL_

#ifdef _CASTING_
namespace casting {
BENCHMARK(____Casting_Benchmarks____);
BENCHMARK(print_nopoly);
BENCHMARK(print_poly);
BENCHMARK(static_casting);
BENCHMARK(dynamic_casting);
BENCHMARK(static_pointer_casting);
BENCHMARK(dynamic_pointer_casting);
}  // namespace casting
#endif

#ifdef _SHARED_VS_UNIQUE_
namespace shared_vs_unique {
BENCHMARK(____Shared_vs_Unique_Benchmarks____);
BENCHMARK_TEMPLATE(create_destroy, std::unique_ptr<size_t>);
BENCHMARK_TEMPLATE(create_destroy, std::shared_ptr<size_t>);
BENCHMARK(make_shared_create_destroy);
BENCHMARK(make_unique_create_destroy);
BENCHMARK(move_unique_ptr);
BENCHMARK(copy_shared_ptr);
}  // namespace shared_vs_unique
#endif

#ifdef _MAP_VS_UNORDERED_
namespace map_vs_unordered {
BENCHMARK(____Map_vs_Unordered_Benchmarks____);
BENCHMARK_TEMPLATE(lookup_missing, std::map<size_t, size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(lookup_missing, std::unordered_map<size_t, size_t>)
    ->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(lookup_existing, std::map<size_t, size_t>)
    ->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(lookup_existing, std::unordered_map<size_t, size_t>)
    ->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(update, std::map<size_t, size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(update, std::unordered_map<size_t, size_t>)
    ->Range(8, 8 << 10);
}  // namespace map_vs_unordered
#endif

#ifdef _VECTOR_VS_LIST_
namespace vector_vs_list {
BENCHMARK(____Vector_vs_List_Benchmarks____);
BENCHMARK_TEMPLATE(find_missing, std::vector<size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(find_missing, std::list<size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(find_missing, tbb::concurrent_vector<size_t>)
    ->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(find_existing, std::vector<size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(find_existing, std::list<size_t>)->Range(8, 8 << 10);
BENCHMARK_TEMPLATE(find_existing, tbb::concurrent_vector<size_t>)
    ->Range(8, 8 << 10);

BENCHMARK_TEMPLATE(push_back, std::vector<size_t>);
BENCHMARK_TEMPLATE(push_back, std::list<size_t>);
BENCHMARK_TEMPLATE(push_back, tbb::concurrent_vector<size_t>);

}  // namespace vector_vs_list
#endif

#ifdef _TBB_VS_STL_
namespace tbb_vs_stl {
BENCHMARK(____Tbb_vs_Stl_Benchmarks____);
BENCHMARK(tbb_parallel);
BENCHMARK(stl_parallel);
}  // namespace tbb_vs_stl
#endif
