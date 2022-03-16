#pragma once

class MyArray
{
public:
	MyArray(); // 默认构造, 默认100容量
	MyArray(int capacity);
	MyArray(const MyArray& array);
	~MyArray();

	void push_back(int val);

	int get_value(int index) const;

	void set_value(int index, int value);

	int get_size() const;

	int get_capacity() const;

	int& operator[](int index) const;
private:
	int* pAddress{}; // 指向真正存储数据的指针
	int m_Size{}; // 数组大小
	int m_Capacity;
};