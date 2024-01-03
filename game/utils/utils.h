#pragma once

#include <string.h>
#include <stdint.h>

#include "types.h"

/// @brief array_remove_at removes an item from an array at the given index by swapping it with the last item in the array.
/// Mainly used for arrays that don't need to be sorted, and for data that can't be just directly swapped.
/// @param array the target array
/// @param index the index of the item to be removed
/// @param size the size of the array before removal
/// @param item_size the size of one element
/// @return returns the new size of the array (size - 1) or the given size if nothing was done
static inline int array_remove_at(void* array, int index, int size, int item_size) {
    if (index < 0 || index >= size) {
        return size;
    }

    int last_index = size - 1;
    if (index != last_index) {
        memcpy((byte*)array + index * item_size, (byte*)array + last_index * item_size, item_size);
    }

    return last_index;
}