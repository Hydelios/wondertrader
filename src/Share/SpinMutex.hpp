#pragma once
#include <atomic>
#include <thread>
#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

class SpinMutex
{
private:
	std::atomic<bool> flag = {false};

public:
	void lock()
	{
		for (;;)
		{
			if (!flag.exchange(true, std::memory_order_acquire))
				break;

			while (flag.load(std::memory_order_relaxed))
			{
#ifdef _MSC_VER
				_mm_pause();
#elif defined(__x86_64__) || defined(__i386__)
				__builtin_ia32_pause();
#elif defined(__aarch64__) || defined(__arm__)
				__asm__ __volatile__("yield" ::: "memory");
#else
				std::this_thread::yield();
#endif
			}
		}
	}

	void unlock()
	{
		flag.store(false, std::memory_order_release);
	}
};

class SpinLock
{
public:
	SpinLock(SpinMutex &mtx) : _mutex(mtx) { _mutex.lock(); }
	SpinLock(const SpinLock &) = delete;
	SpinLock &operator=(const SpinLock &) = delete;
	~SpinLock() { _mutex.unlock(); }

private:
	SpinMutex &_mutex;
};
