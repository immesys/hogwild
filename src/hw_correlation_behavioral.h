#ifndef __hw_correlation_behavioral_h__
#define __hw_correlation_behavioral_h__

#include "primitives.h"
typedef struct
{
    hw_int *data;
    
    /**
     * Where to start in data (in hw_ints)
     */
    hw_int offset;
    
    /**
     * How many elements to skip between each column
     */
    hw_int column_stride;
    
    /**
     * How many elements to skip between each row.
     * This is not how many _rows_ to skip. You can
     * use this to get a window out of a buffer.
     */
    hw_int row_stride;
    
    /**
     * Element vector offset in each element
     */
    hw_int ev_offset;
    
    /**
     * Element vector length
     */
    hw_int ev_length;
    
    hw_int width;
    hw_int height;
    
} strided_buffer_t;

void hw_correlate(strided_buffer_t &img, strided_buffer_t &kernel, strided_buffer_t &out, hw_int num_ev);

#endif
