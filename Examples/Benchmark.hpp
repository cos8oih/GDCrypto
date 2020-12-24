#ifndef _GDCRYPTO_BENCHMARK_HPP
#define _GDCRYPTO_BENCHMARK_HPP

#include <chrono>

namespace gdcrypto
{
	class Benchmark
	{
		long long m_Start;

		long long now()
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	public:
		void start()
		{
			m_Start = now();
		}

		void reset() { start(); }

		long long delta()
		{
			return now() - m_Start;
		}
	};
}

#endif /* _GDCRYPTO_BENCHMARK_HPP */