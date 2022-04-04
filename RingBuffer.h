#pragma once

constexpr int BUFFER_SIZE = 5001;

class RingBuffer
{
private:
	char buffer[BUFFER_SIZE]{ 0, };
	int read = 0;
	int write = 0;
public:
	RingBuffer() = default;

	int Enqueue(char* data, size_t size);
	int Dequeue(char* data, size_t size);
	int Peek(char* data, size_t size);
};

