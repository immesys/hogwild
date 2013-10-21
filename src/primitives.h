/**
 * All operations and datatypes that are taken for granted at a 
 * high level are defined and implemented here. This includes 
 * fixed point arithmetic
 */
 
#ifndef __primitives_h__
#define __primitives_h__

#include <stdint.h> 
#include <stdio.h>

typedef int64_t hw_int; 
typedef uint8_t* hw_pixel;


extern unsigned int primitive_type_check_violations;

typedef struct
{
    hw_pixel **dat;
    uint16_t width;
    uint16_t height;   
} hw_image;


//These are used in the functions that are going to be ported. 
void _check_s_warns(hw_int v, int size, char* valname, char* file, int line);
void _check_u_warns(hw_int v, int size, char* valname, char* file, int line);
hw_int _nonsat_signed_add(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _nonsat_unsigned_add(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _sat_signed_add(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _sat_unsigned_add(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _nonsat_signed_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _nonsat_unsigned_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _sat_signed_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _sat_unsigned_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line);
hw_int _nonsat_signed_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, unsigned int postshift, unsigned int out_size, char* file, int line);
hw_int _nonsat_unsigned_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, unsigned int postshift, unsigned int out_size, char* file, int line);
hw_int _sat_signed_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, unsigned int postshift, unsigned int out_size, char* file, int line);
hw_int _sat_unsigned_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, unsigned int postshift, unsigned int out_size, char* file, int line);
hw_int _nonsat_signed_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, char* file, int line);
hw_int _nonsat_unsigned_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, char* file, int line);
hw_int _sat_signed_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, char* file, int line);
hw_int _sat_signed_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, char* file, int line);
#define CHK_S_TYPE(val, sz) _check_s_warns((val), (sz), #sz, __FILE__, __LINE__)
#define CHK_U_TYPE(val, sz) _check_u_warns((val), (sz), #sz, __FILE__, __LINE__)
#define P_ADD(lhs, rhs, size) _nonsat_signed_add((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_UADD(lhs, rhs, size) _nonsat_unsigned_add((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_SAT_ADD(lhs, rhs, size) _sat_signed_add((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_SAT_UADD(lhs, rhs, size) _sat_unsigned_add((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_SUB(lhs, rhs, size) _nonsat_signed_subtract((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_USUB(lhs, rhs, size) _nonsat_unsigned_subtract((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_SAT_SUB(lhs, rhs, size) _sat_signed_subtract((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_SAT_USUB(lhs, rhs, size) _sat_unsigned_subtract((lhs), (rhs), (size), __FILE__, __LINE__)
#define P_MULT(lhs, rhs, insize, compsize, shift, outsize) _nonsat_signed_multiply((lhs), (rhs), (insize), (compsize), (shift), (outsize), __FILE__, __LINE__)
#define P_UMULT(lhs, rhs, insize, compsize, shift, outsize) _nonsat_unsigned_multiply((lhs), (rhs), (insize), (compsize), (shift), (outsize), __FILE__, __LINE__)
#define P_SAT_MULT(lhs, rhs, insize, compsize, shift, outsize) _sat_signed_multiply((lhs), (rhs), (insize), (compsize), (shift), (outsize), __FILE__, __LINE__)
#define P_SAT_UMULT(lhs, rhs, insize, compsize, shift, outsize) _sat_unsigned_multiply((lhs), (rhs), (insize), (compsize), (shift), (outsize), __FILE__, __LINE__)
#define P_DIV(lhs, rhs, insize, outsize) _nonsat_signed_divide((lhs), (rhs), (insize), (outsize), __FILE__, __LINE__)
#define P_UDIV(lhs, rhs, insize, outsize) _nonsat_unsigned_divide((lhs), (rhs), (insize), (outsize), __FILE__, __LINE__)
#define P_SAT_DIV(lhs, rhs, insize, outsize) _sat_signed_divide((lhs), (rhs), (insize), (outsize), __FILE__, __LINE__)
#define P_SAT_UDIV(lhs, rhs, insize, outsize) _sat_unsigned_divide((lhs), (rhs), (insize), (outsize), __FILE__, __LINE__)

#endif

