#include <stdio.h>
#include <atomic>

int main(int argc, char** argv)
{
	std::atomic<int> value;
	value = 5;

	return value.load();
}
