#include <cstdint>
#include <vector>
#include <algorithm>
#include <iostream>
#include "mmheap.h"

using namespace std;

using namespace minmaxheap;

mmheap::mmheap(uint32_t capacity)
{
  _arr = new int32_t[capacity + 1];
  _size = 0;
  _capacity = capacity;
}

mmheap::~mmheap()
{
  if (_size != 0)
    {
      delete []_arr;
      _size = 0;
      _capacity = 0;
    }
}

void mmheap::buildHeap (const std::vector<int32_t> &vals)
{
  _arr = new int32_t[_capacity + 1];
  _size = 0;
   for (uint32_t i = 0; i < vals.size(); i++)
  {
    insert(vals[i]);
  }
  //  for(int i = 1; i < _size; i++)
  //{cout<<_arr[i]<<",";}
  //cout<<endl;
  //printHeap();
}

int32_t mmheap::getMin() const
{
  if (_size == 0)
    return 0;
  printHeap();
  return _arr[1];
}

int32_t mmheap::getMax () const
{
  if (_size == 0)
    return 0;
  if (_size == 1)
    return _arr[1];
  if (_size == 2)
    return _arr[2];
  if (_arr[2] > _arr[3])
    return _arr[2];
  else
    return _arr[3];
}

void mmheap::insert (int32_t val)
{
  if (_size < _capacity)
    {
      _size += 1;
      //      cout << _size << "<-" << endl;
      _arr[_size] = val;

      //      for(int i = 1; i <= _size; i++)
      //{cout<<_arr[i]<<",";}
      //cout<<endl;
      
      percolateUp(_size);
      
      //for(int i = 1; i <= _size; i++)
      //{cout<<_arr[i]<<",";}
      //cout<<endl;
    }
}

void mmheap::deleteMin()
{
  if (_size < 1)
    return;
  else
    {
      swap(_arr[1], _arr[_size]);
      _size -= 1;
      percolateDown(1);
    }
}

void mmheap::deleteMax()
{
  //  for (int i=1;i<_size;i++)
  //{cout<<_arr[i]<<",";}  //cout<<endl;
  //  printHeap();
  if (_size < 1)
    return;
else  if (_size <= 2)
    _size -= 1;
 else if (_arr[2] > _arr[3])
    {
      //      printHeap();
      swap(_arr[2], _arr[_size]);
      _size -= 1;
      // printHeap();
      cout << _size << endl;
      percolateDown(2);
      //          printHeap();
    }
 else if (_arr[3] > _arr[2])
    {
      //printHeap();
      swap(_arr[3], _arr[_size]);
      //printHeap();
      _size -= 1;
      cout << _size<< endl;
      percolateDown(3);
      //printHeap();
    }
  //printHeap();
  //for (int i=1;i<_size;i++)
  //{cout<<_arr[i]<<",";}
  //cout<<endl;
}

bool mmheap::isAtMinLevel (uint32_t index) const
{
  return (int) (log(index) / log(2)) % 2 == 0;
}

void mmheap::percolateDown (uint32_t index)
{
  if (isAtMinLevel(index))
    percolateDownMin(index);
  else
    percolateDownMax(index);
}

void mmheap::percolateDownMin (uint32_t index)
{
  if (index == 0 || index > _size)
    return;
  uint32_t children = index * 2;
  uint32_t grandchild = index * 4;
  if (grandchild < _size)
  {
    uint32_t min = index * 4;
    for (uint32_t i = 4 * index; i <= 4 * index + 3; i++)
    {
      if (i <= _size && _arr[i] < _arr[min])
		    min = i;
    }
    uint32_t min2 = index * 2;
    for (uint32_t i = 2 * index; i <= 2 * index + 1; i++)
      {
	if (i<=_size && _arr[i] < _arr[min2])
	  min2 = i;
      }
    if (_arr[min2] < _arr[min])
      min = min2;
    //cout << _arr[min]<<endl;
	  if (min / 4 == index)
    {
      if (_arr[min] < _arr[index])
      {
		    swap(_arr[min], _arr[index]);
		    uint32_t parent = min / 2;
		    if (parent != 0)
        {
          if (_arr[min] > _arr[parent])
		        swap(_arr[min], _arr[parent]);
        }
		    percolateDownMin(min);
		  }
    }
	  else if (min / 2 == index)
    {
      if (_arr[min] < _arr[index])
		    swap(_arr[min], _arr[index]);
    }
	}
}

void mmheap::percolateDownMax (uint32_t index)
{
  if (index == 0 || index > _size)
    return;
  uint32_t children = index * 2;
  uint32_t grandchild = index * 4;
  if (grandchild <= _size)
  {
    uint32_t max = index * 4;
    for (uint32_t i = 4 * index; i <= 4 * index + 3; i++)
    {
      if (i <= _size && _arr[i] > _arr[max])
        max = i;
    }
    uint32_t max2 = index * 2;
    for (uint32_t i = 2 * index; i <= 2 * index + 1; i++)
    {
      if (i<=_size && _arr[i] > _arr[max2])
	max2 = i;
    }
    if (_arr[max2]>_arr[max])
      max = max2;
    if (max / 4 == index)
    {
      if (_arr[max] > _arr[index])
      {
        swap(_arr[max], _arr[index]);
        uint32_t parent = max / 2;
        if (parent != 0)
        {
          if (_arr[max] < _arr[parent])
            swap(_arr[max], _arr[parent]);
        }
        percolateDownMax(max);
      }
    }
    else if (max / 2 == index)
    {
      if (_arr[max] > _arr[index])
        swap(_arr[max], _arr[index]);
    }
  }
}

void mmheap::percolateUp (uint32_t index)
{
  if (index == 0 || index > _size)
    return;
  uint32_t parent = index / 2;
  if (isAtMinLevel(index))
  {
    if (parent >= 1 && _arr[index] > _arr[parent])
    {
      swap(_arr[index], _arr[parent]);
      percolateUpMax(parent);
    }
    else
      percolateUpMin(index);
  }
  else
  {
    if (parent >= 1 && _arr[index] < _arr[parent])
    {
      swap(_arr[index], _arr[parent]);
      percolateUpMin(parent);
    }
    else
      percolateUpMax(index);
  }
}

void mmheap::percolateUpMin (uint32_t index)
{
  uint32_t grandparent = index / 4;
  if (grandparent >= 1)
    {
      if (_arr[index] < _arr[grandparent])
	{
	  swap(_arr[index], _arr[grandparent]);
	  percolateUpMin(grandparent);
	}
    }
}

void mmheap::percolateUpMax (uint32_t index)
{
  uint32_t grandparent = index / 4;
  if (grandparent >= 1)
    {
      if (_arr[index] > _arr[grandparent])
	{
	  swap(_arr[index], _arr[grandparent]);
	  percolateUpMax(grandparent);
	}
    }
}

void mmheap::printHeap() const
{
  int level = 0;
  string output = "";
  for(int i = 1; i<=_size; i++)
  {
    if(i >= static_cast<int>(exp2(level)))
    {
     output += "\n";
     level++;
    }
    output += to_string(_arr[i]) + " ";      
  }
    cout << "heap: ";
    cout << output << endl;
    cout << "size: ";
    cout << _size << endl;
}
