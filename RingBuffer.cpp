#include "RingBuffer.h"
#include"defaultHeader.h"

int RingBuffer::Enqueue(char* data, size_t size)
{
	// zero data
    if (size == 0) 
		return 0;

	// buffer overflow
	if (write + size % MAX_BUFFER > MAX_BUFFER - abs(write - read) && read != write)
		return -1;

	// process enqueue
	if (write + size > MAX_BUFFER) {
		memcpy_s(buffer + write, MAX_BUFFER - write, data, MAX_BUFFER - write);
		memcpy_s(buffer, read, data, size - (MAX_BUFFER - write));
		write = size - (MAX_BUFFER - write);
	}
	else {
		memcpy_s(buffer + write, size, data, size);
		write = write + size;
	}

    return size;
}

int RingBuffer::Dequeue(char* data, size_t size)
{
	// zero data
	if (size == 0)
		return 0;

	// empty
	if (read == write)
		return -1;

	// buffer underflow
	if (size > abs(write - read))
		return -2;

	// process dequeue
	if (read + size > MAX_BUFFER) {
		memcpy_s(data, size, buffer + read, MAX_BUFFER - read);
		memcpy_s(data + MAX_BUFFER - read, size - (MAX_BUFFER - read), buffer, size - (MAX_BUFFER - read));

		ZeroMemory(buffer+read, MAX_BUFFER - read);
		ZeroMemory(buffer, size - (MAX_BUFFER - read));
		read = size - (MAX_BUFFER - read);
	}
	else {
		memcpy_s(data, size, buffer + read, size);

		ZeroMemory(buffer+read, size);
		read = read + size;
	}

    return size;
}

int RingBuffer::Peek(char* data, size_t size)
{
	// zero data
	if (size == 0)
		return 0;

	// empty
	if (read == write)
		return -1;

	// buffer overflow
	if (size > abs(write - read))
		return -2;

	// process
	if (read + size > MAX_BUFFER) {
		memcpy_s(data, size, buffer+read, MAX_BUFFER - read);
		memcpy_s(data + MAX_BUFFER - read, size - (MAX_BUFFER - read), buffer, size - (MAX_BUFFER - read));
	}
	else 
		memcpy_s(data, size, buffer + read, size);

	return size;
}

void RingBuffer::Commit(size_t len)
{
	write += len;
	write %= MAX_BUFFER;
}

char* RingBuffer::GetBuffer()
{
	return &buffer[write];
}

int RingBuffer::GetFreeSize()
{
	if (read > write)
		return read - write;
	return MAX_BUFFER - write;
}
