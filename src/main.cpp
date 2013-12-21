#include <iostream>
#include <random>
#include <thread>
#include <unistd.h>
#include <cassert>

#include "ringbuffer.h"

// mark variables unused when they are used specifically for testing
#define _unused(x) ((void)x)

#define LOOP_COUNT 50

void consume()
{
	auto rnd = std::default_random_engine(std::random_device{}());
	std::uniform_int_distribution<> dis(10, 100);
	
	for (unsigned i = 0; i < LOOP_COUNT; i++)
	{
		usleep(dis(rnd));
	}
}

void produce()
{
	auto rnd = std::default_random_engine(std::random_device{}());
	std::uniform_int_distribution<> dis(10, 100);
	
	for (unsigned i = 0; i < LOOP_COUNT; i++)
	{
		usleep(dis(rnd));
	}
}

void testSingleElementQueue()
{
	RingBuffer<bool, 1> fifo;
	
	bool firstValue = true;
	bool secondValue = false;
	bool targetValue = !firstValue;

	// init ok
	assert(fifo.init());

	// Test limits for a single element queue
	assert(fifo.wasEmpty());
	assert(fifo.push(firstValue));
	assert(fifo.wasFull());
	assert(!fifo.wasEmpty());
	assert(!fifo.push(secondValue));
	assert(fifo.pop(targetValue));
	assert(!fifo.wasFull());
	assert(targetValue == firstValue);

	_unused(secondValue);
	_unused(targetValue);
}

void testRemoveFromEmptyQueue()
{
	RingBuffer<double, 10> fifo;
	assert(fifo.wasEmpty());
	assert(!fifo.wasFull());
	double val;
	assert(!fifo.pop(val));
	_unused(val);
}

int main()
{

	testSingleElementQueue();
	testRemoveFromEmptyQueue();

	return 0;
}
