#include "RingBuffer.h"
#include"defaultHeader.h"

int RingBuffer::Enqueue(char* data, size_t size)
{
	// zero data
    if (size == 0) 
		return 0;

	// buffer overflow
	if (write + size % BUFFER_SIZE > BUFFER_SIZE - abs(write - read) && read != write)
		return -1;

	// process enqueue
	if (write + size > BUFFER_SIZE) {
		memcpy_s(buffer + write, BUFFER_SIZE - write, data, BUFFER_SIZE - write);
		memcpy_s(buffer, read, data, size - (BUFFER_SIZE - write));
		write = size - (BUFFER_SIZE - write);
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
	if (read + size > BUFFER_SIZE) {
		memcpy_s(data, size, buffer + read, BUFFER_SIZE - read);
		memcpy_s(data + BUFFER_SIZE - read, size - (BUFFER_SIZE - read), buffer, size - (BUFFER_SIZE - read));

		ZeroMemory(buffer+read, BUFFER_SIZE - read);
		ZeroMemory(buffer, size - (BUFFER_SIZE - read));
		read = size - (BUFFER_SIZE - read);
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
	if (read + size > BUFFER_SIZE) {
		memcpy_s(data, size, buffer+read, BUFFER_SIZE - read);
		memcpy_s(data + BUFFER_SIZE - read, size - (BUFFER_SIZE - read), buffer, size - (BUFFER_SIZE - read));
	}
	else 
		memcpy_s(data, size, buffer + read, size);
	
	return size;
}
