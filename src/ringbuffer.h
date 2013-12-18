#ifndef __RINGBUFFER_H_
#define __RINGBUFFER_H_

#include <atomic>
#include <stdlib.h>

template <typename T, size_t Q_SIZE>
class RingBuffer
{
	public:

		// Denote capacity without actually using memory
		enum { CAPACITY = Q_SIZE + 1 };

		RingBuffer() : _tail(0), _head(0) {};
		~RingBuffer() {};

		bool init();

		// Queue mutators. Remember that this implementation is single-producer, single-
		// consumer. So don't use either from more than one thread.
		bool push(const T& item);
		bool pop(T& item);

		// Meta-information about the queue. These  functions require memory locking
		// and unlocking so calling generally incurs the same overhead as the above
		// mutators. To be used for testing and auditing.
		bool wasEmpty() const;
		bool wasFull() const;
		bool isLockFree() const;

	private:

		size_t increment(size_t idx) const;

		std::atomic<size_t> _tail; // Input location
		std::atomic<size_t> _head; // Output location
		
		// Remmber the capacity of the queue is actually SIZE + 1
		T _array[CAPACITY];
};

#pragma mark -
#pragma mark Implementation

template <typename T, size_t Q_SIZE>
bool RingBuffer<T, Q_SIZE>::init()
{
	return (Q_SIZE > 0);
}

template <typename T, size_t Q_SIZE>
bool RingBuffer<T, Q_SIZE>::push(const T& item)
{
	const size_t currentTail = _tail.load(std::memory_order_relaxed);
	const size_t nextTail = increment(currentTail);

	// Are we full?
	if (nextTail == _head.load(std::memory_order_acquire))
		return false;

	_array[currentTail] = item;
	_tail.store(nextTail, std::memory_order_release);
	return true;
}

template <typename T, size_t Q_SIZE>
bool RingBuffer<T, Q_SIZE>::pop(T& item)
{
	const size_t currentHead = _head.load(std::memory_order_relaxed);

	if (currentHead == _tail.load(std::memory_order_acquire))
		return false;

	item = _array[currentHead];
	_head.store(increment(currentHead), std::memory_order_release);
	return true;
}

template <typename T, size_t Q_SIZE>
size_t RingBuffer<T, Q_SIZE>::increment(size_t idx) const
{
	return (idx + 1) % CAPACITY;
}

template <typename T, size_t Q_SIZE>
bool RingBuffer<T, Q_SIZE>::wasEmpty() const
{
	return (_tail.load() == _head.load());
}

template <typename T, size_t Q_SIZE>
bool RingBuffer<T, Q_SIZE>::wasFull() const
{
	const size_t nextTail = increment(_tail.load());
	return (nextTail == _head.load());
}

template <typename T, size_t Q_SIZE>
bool RingBuffer<T, Q_SIZE>::isLockFree() const
{
	return (_tail.is_lock_free() && _head.is_lock_free());
}

#endif // __RINGBUFFER_H_


