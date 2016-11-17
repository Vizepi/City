#pragma once

#include <chrono>
#include <random>

class Random
{

public:

	inline static void Seed(uint64_t seed) { s_instance.m_generator.seed(seed); }
	inline static void Seed(void) { s_instance.m_generator.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count()); }

	inline static int64_t NextInt64(void) { return s_instance.m_dist_64(s_instance.m_generator); }
	inline static int64_t NextInt64(int64_t min, int64_t max) { return std::uniform_int_distribution<int64_t>(min, max)(s_instance.m_generator); }

	inline static uint64_t NextUInt64(void) { return s_instance.m_dist_u64(s_instance.m_generator); }
	inline static uint64_t NextUInt64(uint64_t min, uint64_t max) { return std::uniform_int_distribution<uint64_t>(min, max)(s_instance.m_generator); }

	inline static double NextDouble(void) { return s_instance.m_dist_dbl(s_instance.m_generator); }
	inline static double NextDouble(double min, double max) { return std::uniform_real_distribution<double>(min, max)(s_instance.m_generator); }

	inline static bool NextBool(void) { return s_instance.m_dist_u64(s_instance.m_generator) % 2 == 0; }

private:

	inline Random(void)
		: m_generator(std::chrono::high_resolution_clock::now().time_since_epoch().count())
		, m_dist_64(std::numeric_limits<int64_t>().min(), std::numeric_limits<int64_t>().max())
		, m_dist_u64(std::numeric_limits<uint64_t>().min(), std::numeric_limits<uint64_t>().max())
		, m_dist_dbl(0.0, 1.0)
	{
		
	}

	virtual ~Random(void) { }

	std::mt19937_64 m_generator;
	std::uniform_int_distribution<int64_t> m_dist_64;
	std::uniform_int_distribution<uint64_t> m_dist_u64;
	std::uniform_real_distribution<double> m_dist_dbl;
	
	static Random s_instance;

};