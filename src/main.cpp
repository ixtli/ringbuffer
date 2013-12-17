#include <iostream>
#include <random>
#include <atomic>
#include <thread>
#include <unistd.h>

#include "linkedlist.h"

#define LOOP_COUNT 50

void consume()
{
	auto rnd = std::default_random_engine(std::random_device{}());
	std::uniform_int_distribution<> dis(10, 100);
	
	for (unsigned i = 0; i < LOOP_COUNT; i++)
	{
		usleep(dis(rnd));
		printf("I'm awake.\n");
	}
}

void produce()
{
	auto rnd = std::default_random_engine(std::random_device{}());
	std::uniform_int_distribution<> dis(10, 100);
	
	for (unsigned i = 0; i < LOOP_COUNT; i++)
	{
		usleep(dis(rnd));
		printf("Producing.\n");
	}
}

int main()
{
	std::thread consumer(consume);
	std::thread producer(produce);
	producer.join();
	consumer.join();

	LinkedList l;
	l.init();

	return 0;
}
