#include <inttypes.h>

template <typename T>
class
    vector
{
private:
    uint16_t _size;
    T *_array;

public:
    vector() : _size{0}, _array{new T[_size]} {}
    void push_back(T element)
    {
        uint16_t oldSize = _size;
        const T *oldArray = _array;

        _size++;
        _array = new T[_size];

        for (uint16_t i = 0; i < oldSize; i++)
        {
            _array[i] = oldArray[i];
        }
        _array[oldSize] = element;
        delete oldArray;
    }
    void erase(uint16_t index)
    {
        uint16_t oldSize = _size;
        const T *oldArray = _array;

        _size--;
        _array = new T[_size];

        for (uint16_t i = 0; i < oldSize; i++)
        {
            if(i != index)
            {
                _array[i] = oldArray[i];
            }
        }

        delete oldArray;
    }
    uint16_t size()
    {
        return _size;
    }
    T &operator[](uint16_t index)
    {
        return _array[index];
    }
    ~vector()
    {
        delete _array;
    }
};
