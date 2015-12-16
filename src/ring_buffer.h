/*
 * rung_buffer.h
 *
 *  Created on: Dec 16, 2015
 *      Author: schaefer
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

template<int size, class DATA_T>
  class RingBuffer
  {
  public:
    RingBuffer (void) :
	pointer (0)
    {
      for (unsigned i = 0; i < size; ++i)
	values[i] = 0;
    }

    DATA_T
    getValueAt (unsigned position)
    {
      return values[map (position)];
    }

    void
    pushValue (DATA_T value)
    {
      setValueAt (0, value);
      ++pointer;
      if (pointer >= size)
	pointer = 0;
    }

    unsigned
    GetSize (void)
    {
      return size;
    }
  private:
    unsigned
    map (unsigned position)
    {
      return (position + pointer) % size;
    }
    void
    setValueAt (unsigned position, DATA_T value)
    {
      values[map (position)] = value;
    }

    unsigned pointer;
    DATA_T values[size];
  };

#endif /* RING_BUFFER_H_ */
