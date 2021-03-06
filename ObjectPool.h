#pragma once
#include<concurrent_queue.h>
#include<iostream>

// class T에 Reset() 정의 필요

template<class T>
class ObjectPool
{
private:
	Concurrency::concurrent_queue<T*> m_objects;
	int m_poolSize = 0;
public:
	ObjectPool() = default;
	ObjectPool(int);
	~ObjectPool();
	void Init(int);
	T* GetObj();
	void ReturnObj(T*);
	int GetPoolSize();
	int GetObjectsCount();
};

template<class T>
ObjectPool<T>::ObjectPool(int poolSize)
{
	m_poolSize = poolSize;
	for (int i = 0; i < m_poolSize; ++i)
		m_objects.push(new T);
}

template<class T>
ObjectPool<T>::~ObjectPool()
{
	if (m_poolSize == 0)
		return;
	T* tmpObj;
	for (int i = 0; i < m_poolSize; ++i) {
		m_objects.try_pop(tmpObj);
		delete tmpObj;
	}
}

template<class T>
void ObjectPool<T>::Init(int poolSize)
{
	m_poolSize = poolSize;
	for (int i = 0; i < m_poolSize; ++i)
		m_objects.push(new T);
}

template<class T>
T* ObjectPool<T>::GetObj()
{
	T* tmpObj;
	if (m_objects.try_pop(tmpObj)) {
		std::cout << "m_objects - " << m_objects.unsafe_size() << std::endl;
		return tmpObj;
	}

	return nullptr;
}

template<class T>
void ObjectPool<T>::ReturnObj(T* obj)
{
	obj->Reset();
	m_objects.push(obj);
	std::cout << "m_objects - " << m_objects.unsafe_size() << std::endl;
}

template<class T>
int ObjectPool<T>::GetPoolSize()
{
	return m_poolSize;
}

template<class T>
int ObjectPool<T>::GetObjectsCount()
{
	return m_objects.unsafe_size();
}
