#include <inttypes.h>
#include <stdlib.h>

namespace avr
{
    template <typename T>
    class
        vector
    {
    private:
        uint16_t _size;
        T *_array;

    public:
        vector() : _size{0}
        {
            _array = (T *)malloc(sizeof(T) * _size);
        }
        void push_back(T element)
        {
            uint16_t oldSize = _size;
            T *oldArray = _array;

            _size++;
            _array = (T *)malloc(sizeof(T) * _size);

            for (uint16_t i = 0; i < oldSize; i++)
            {
                _array[i] = oldArray[i];
            }
            _array[oldSize] = element;
            free(oldArray);
        }
        void erase(uint16_t index)
        {
            uint16_t oldSize = _size;
            T *oldArray = _array;

            _size--;
            _array = (T *)malloc(sizeof(T) * _size);

            for (uint16_t i = 0; i < oldSize; i++)
            {
                if (i != index)
                {
                    _array[i] = oldArray[i];
                }
            }

            free(oldArray);
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
            free(_array);
        }
    };
}; // namespace avr
