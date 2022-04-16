#pragma once
#include"defaultHeader.h"
#include"protocol.h"

class RingBuffer
{
private:
	char buffer[MAX_BUFFER]{ 0, };
	int read = 0;
	int write = 0;
public:
	RingBuffer() = default;

	int Enqueue(char* data, size_t size);
	int Dequeue(char* data, size_t size);
	int Peek(char* data, size_t size);
	void Commit(size_t len);
	char* GetBuffer();
	int GetFreeSize();
};

