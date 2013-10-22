/**
 * This is purposefully written verbosely to make the inevitable
 * algorithmic problems easier to find.
 */

#include "primitives.h"
#include "hw_correlation_behavioral.h"
#include <stdio.h>


/**
 * Be aware that your output image is obviously bigger than the input images.
 */
void hw_correlate(strided_buffer_t &img, strided_buffer_t &kernel, strided_buffer_t &out, hw_int num_ev)
{
    fprintf(stderr, "Entry %ld x %ld\n",kernel.height, kernel.width);
    int xpos, ypos, kx, ky, ei;
    for (ypos = -kernel.height + 1; ypos < img.height; ypos++)
    {
        for (xpos = -kernel.width + 1; xpos < img.width; xpos++)
        {
            hw_int sum = 0;
            for (ky = 0; ky < kernel.height; ky++)
            {
                for (kx = 0; kx < kernel.width; kx++)
                {
                    for (ei = 0; ei < num_ev; ei++)
                    {
                        fprintf(stderr, "Inner loop ypos=%d xpos=%d ky=%d kx=%d ei=%d ", ypos,xpos,ky,kx,ei);
                        if ((xpos +kx) >= 0 && (ypos+ky) >=0 && (xpos + kx) < img.width && (ypos + ky) < img.height)
                        { 
                            fprintf(stderr, "INSIDE\n");
                            hw_int idxe = (img.offset + //base
                                           img.ev_offset + ei + //element vector
                                           (xpos + kx) * (img.column_stride + img.ev_length) + //horizontal
                                           (ypos + ky) * (img.width * (img.column_stride + img.ev_length) + img.row_stride) //vertical 
                                           );
                            fprintf(stderr, "idxe is %ld\n",idxe);
                            hw_int krne = (kernel.offset + //base
                                           kernel.ev_offset + ei + //element vector
                                           kx * (kernel.column_stride + kernel.ev_length) + //horizontal
                                           ky * (kernel.width * (kernel.column_stride + kernel.ev_length) + kernel.row_stride) //vertical 
                                           );
                            fprintf(stderr, "kerne is %ld\n", krne);
                            hw_int rv = img.data[idxe] * kernel.data[krne];
                            //TODO typechecks
                            sum += rv;       
                        }
                        else
                        {
                            fprintf(stderr, "OUTSIDE\n");
                        }
                    }
                }
            }
            hw_int idx = (out.offset + //base
               out.ev_offset + //element vector
               (xpos + kernel.width - 1) * (out.column_stride + out.ev_length) + //horizontal
               (ypos + kernel.height - 1) * (out.width * (out.column_stride + out.ev_length) + out.row_stride) //vertical 
               );
            fprintf(stderr, "IDX FOR WRITEBACK: %ld\n",idx);
            out.data[idx] = sum;

        }    
    }
}
