#include <gtest/gtest.h>
#include <benchmark/benchmark.h>
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/core/fstring.hxx>
#include <FE/core/hash.hpp>

// robin hood
#include <robin_hood.h>




TEST(hash, all)
{
	
}


void std_hash_benchmark(benchmark::State& state_p)
{
	std::hash<std::string> l_hasher;
	static std::string l_string = "_NODISCARD_ _CONSTEXPR20_ _FORCE_INLINE_ count<char> count_chars(const char* string_p, const char target_p) noexcept";
	benchmark::DoNotOptimize(l_string);

	for (auto _ : state_p)
	{
		auto l_result = l_hasher(l_string);
		benchmark::DoNotOptimize(l_result);
	}
}

BENCHMARK(std_hash_benchmark);


void city_hash_benchmark(benchmark::State& state_p)
{
	auto l_content = "_NODISCARD_ _CONSTEXPR20_ _FORCE_INLINE_ count<char> count_chars(const char* string_p, const char target_p) noexcept";
	size_t l_length = FE::algorithm::string::length(l_content);
	benchmark::DoNotOptimize(l_content);
	benchmark::DoNotOptimize(l_length);


	for (auto _ : state_p)
	{
		auto l_result = CityHash64(l_content, l_length);
		benchmark::DoNotOptimize(l_result);
	}
}

BENCHMARK(city_hash_benchmark);


void robin_hood_hash_benchmark(benchmark::State& state_p)
{
	const char* l_content = "_NODISCARD_ _CONSTEXPR20_ _FORCE_INLINE_ count<char> count_chars(const char* string_p, const char target_p) noexcept";
	size_t l_length = FE::algorithm::string::length(l_content);
	benchmark::DoNotOptimize(l_content);
	benchmark::DoNotOptimize(l_length);

	for (auto _ : state_p)
	{
		auto l_result = robin_hood::hash_bytes(l_content, l_length);
		benchmark::DoNotOptimize(l_result);
	}
}

BENCHMARK(robin_hood_hash_benchmark);