#include<iostream>
using namespace std;

void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}
class MinHeap
{
public:
	int capacity;
	int heap_size;
	int *heap_data;
	MinHeap(int capacity)
	{
		this->heap_size = 0;
		this->capacity = capacity;
		this->heap_data = new int[capacity];
	}

	int parent(int i)
	{ 
		return (i-1)/2; 
	}

	int left(int i)
	{
		return (2*i + 1); 
	}

	int right(int i)
	{
		return (2*i + 2);
	}
	int getMin()
	{
		return heap_data[0];
	}
	void Heapify(int i)
	{
		int l = left(i);
		int r = right(i);
		int smallest = i;
		if (l < heap_size && heap_data[l] < heap_data[i])
			smallest = l;
		if (r < heap_size && heap_data[r] < heap_data[smallest])
			smallest = r;
		if (smallest != i)
		{
			swap(&heap_data[i], &heap_data[smallest]);
			Heapify(smallest);
		}
	}
	int pop_minimum()
	{
		if (heap_size <= 0)
			return +999999999;
		if (heap_size == 1)
		{
			heap_size--;
			return heap_data[0];
		}

		int root = heap_data[0];
		heap_data[0] = heap_data[heap_size-1];
		heap_size--;
		Heapify(0);

		return root;
	}
	void decrease_item(int i, int new_val)
	{
		heap_data[i] = new_val;
		while (i != 0 && heap_data[parent(i)] > heap_data[i])
		{
		swap(&heap_data[i], &heap_data[parent(i)]);
		i = parent(i);
		}
	}
	void delete_item(int i)
	{
		decrease_item(i, -999999999);
		pop_minimum();
	}
	void insert_item(int k)
	{
		if (heap_size == capacity)
		{
			cout << "\nOverflow Error\n";
			return;
		}
		heap_size++;
		int i = heap_size - 1;
		heap_data[i] = k;
		while (i != 0 && heap_data[parent(i)] > heap_data[i])
		{
			swap(&heap_data[i], &heap_data[parent(i)]);
			i = parent(i);
		}
	}
};

int main()
{
	MinHeap h(11);
	h.insert_item(3);
	h.insert_item(2);
	h.delete_item(1);
	h.insert_item(15);
	h.insert_item(5);
	h.insert_item(4);
	h.insert_item(45);
	cout << h.pop_minimum() << " ";
	cout << h.getMin() << " ";
	h.decrease_item(2, 1);
	cout << h.getMin();
	return 0;
}
