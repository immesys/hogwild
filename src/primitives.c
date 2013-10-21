/**
 * All operations and datatypes that are taken for granted at a 
 * high level are defined and implemented here. This includes 
 * fixed point arithmetic
 */

#include <stdint.h> 
#include <stdio.h>
#include "primitives.h"

unsigned int primitive_type_check_violations = 0;

#define SMAX(sz) ((1<<((sz)-1))-1)
#define SMIN(sz) (-(1<<((sz)-1)))
#define UMAX(sz) (1<<((sz)))
#define SCLAMP(v,sz) ( ((v)<SMIN((sz))) ? SMIN((sz)) : ((v)>SMAX((sz))) ? SMAX((sz)) : (v) )
#define UCLAMP(v,sz) ( ((v)<0) ? 0 : ((v)>UMAX((sz))) ? UMAX((sz)) : (v) )
void _check_s_warns(hw_int v, int size, char* valname, char* file, int line)
{
    hw_int min = SMIN(size);
    hw_int max = SMAX(size);
    if (v > max)
    {
        primitive_type_check_violations++;
        fprintf(stderr, "[W] %s OVERFLOWS %d-BIT SIGNED TYPE (%ld > %ld) @ %s:%d\n", 
            valname, size, v, max, file, line);
       
    }
    if (v < min)
    {
        primitive_type_check_violations++;
        fprintf(stderr, "[W] %s UNDERFLOWS %d-BIT SIGNED TYPE (%ld < %ld) @ %s:%d\n", 
            valname, size, v, min, file, line);
    }
}
void _check_u_warns(hw_int v, int size, char* valname, char* file, int line)
{
    hw_int min = 0;
    hw_int max = UMAX(size);
    if (v > max)
    {
        primitive_type_check_violations++;
        fprintf(stderr, "[W] %s OVERFLOWS %d-BIT UNSIGNED TYPE (%ld > %ld) @ %s:%d\n", 
            valname, size, v, max, file, line);
    }
    if (v < min)
    {
        primitive_type_check_violations++;
        fprintf(stderr, "[W] %s UNDERFLOWS %d-BIT UNSIGNED TYPE (%ld < %ld) @ %s:%d\n", 
            valname, size, v, min, file, line);
    }
}
int _check(int v, char* msg, char* file, int line)
{
    if (!v)
    {
        primitive_type_check_violations++;
        fprintf(stderr, "[W] SANITY FAILURE: %s @ %s:%d\n", msg, file, line);
    }
    return v;
}

// ADDITION
/////////////
hw_int _nonsat_signed_add(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs + rhs;
    _check_s_warns(lhs, size, "LHS", file, line);
    _check_s_warns(rhs, size, "RHS", file, line);
    _check_s_warns(rv, size, "NONSAT SIGNED ADD RV", file, line);
    return rv;
}
hw_int _nonsat_unsigned_add(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs + rhs;
    _check_u_warns(lhs, size, "LHS", file, line);
    _check_u_warns(rhs, size, "RHS", file, line);
    _check_u_warns(rv, size, "NONSAT SIGNED ADD RV", file, line);
    return rv;
}
hw_int _sat_signed_add(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs + rhs;
    _check_s_warns(lhs, size, "LHS", file, line);
    _check_s_warns(rhs, size, "RHS", file, line); 
    return SCLAMP(rv,size);
}
hw_int _sat_unsigned_add(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs + rhs;
    _check_u_warns(lhs, size, "LHS", file, line);
    _check_u_warns(rhs, size, "RHS", file, line);
    return UCLAMP(rv,size);
}

// SUBTRACTION
////////////////
hw_int _nonsat_signed_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs - rhs;
    _check_s_warns(lhs, size, "LHS", file, line);
    _check_s_warns(rhs, size, "RHS", file, line);
    _check_s_warns(rv, size, "NONSAT SIGNED SUB RV", file, line);
    return rv;
}
hw_int _nonsat_unsigned_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs - rhs;
    _check_u_warns(lhs, size, "LHS", file, line);
    _check_u_warns(rhs, size, "RHS", file, line);
    _check_u_warns(rv, size, "NONSAT SIGNED SUB RV", file, line);
    return rv;
}
hw_int _sat_signed_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs - rhs;
    _check_s_warns(lhs, size, "LHS", file, line);
    _check_s_warns(rhs, size, "RHS", file, line); 
    return SCLAMP(rv,size);
}
hw_int _sat_unsigned_subtract(hw_int lhs, hw_int rhs, int size, char* file, int line)
{
    hw_int rv = lhs - rhs;
    _check_u_warns(lhs, size, "LHS", file, line);
    _check_u_warns(rhs, size, "RHS", file, line);
    return UCLAMP(rv,size);
}

// MULTIPLICATION
///////////////////
hw_int _nonsat_signed_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, 
                               unsigned int postshift, unsigned int out_size, char* file, int line)
{
    hw_int rv = lhs * rhs;
    _check_s_warns(lhs, in_size, "LHS", file, line);
    _check_s_warns(rhs, in_size, "RHS", file, line);
    _check_s_warns(rv, comp_size, "NONSAT SIGNED MULT INTERMEDIATE", file, line);
    _check(in_size <= comp_size, "INPUT SIZE <= MULTIPLIER_SIZE", file, line);
    _check(out_size <= comp_size, "OUT SIZE <= MULTIPLIER_SIZE", file, line);
    rv >>= postshift;
    _check_s_warns(rv, out_size, "NONSAT SIGNED MULT RESULT", file, line);
    return rv;
}
hw_int _nonsat_unsigned_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, 
                                 unsigned int postshift, unsigned int out_size, char* file, int line)
{
    hw_int rv = lhs * rhs;
    _check_u_warns(lhs, in_size, "LHS", file, line);
    _check_u_warns(rhs, in_size, "RHS", file, line);
    _check_u_warns(rv, comp_size, "NONSAT UNSIGNED MULT INTERMEDIATE", file, line);
    _check(in_size <= comp_size, "INPUT SIZE <= MULTIPLIER_SIZE", file, line);
    _check(out_size <= comp_size, "OUT SIZE <= MULTIPLIER_SIZE", file, line);
    rv >>= postshift;
    _check_u_warns(rv, out_size, "NONSAT UNSIGNED MULT RESULT", file, line);
    return rv;
}
hw_int _sat_signed_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, 
                            unsigned int postshift, unsigned int out_size, char* file, int line)
{
    hw_int rv = lhs * rhs;
    _check_s_warns(lhs, in_size, "LHS", file, line);
    _check_s_warns(rhs, in_size, "RHS", file, line);
    _check_s_warns(rv, comp_size, "SAT SIGNED MULT INTERMEDIATE", file, line);
    _check(in_size <= comp_size, "INPUT SIZE <= MULTIPLIER_SIZE", file, line);
    _check(out_size <= comp_size, "OUT SIZE <= MULTIPLIER_SIZE", file, line);
    rv >>= postshift;
    return SCLAMP(rv, out_size);
}
hw_int _sat_unsigned_multiply(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int comp_size, 
                              unsigned int postshift, unsigned int out_size, char* file, int line)
{
    hw_int rv = lhs * rhs;
    _check_u_warns(lhs, in_size, "LHS", file, line);
    _check_u_warns(rhs, in_size, "RHS", file, line);
    _check_u_warns(rv, comp_size, "SAT UNSIGNED MULT INTERMEDIATE", file, line);
    _check(in_size <= comp_size, "INPUT SIZE <= MULTIPLIER_SIZE", file, line);
    _check(out_size <= comp_size, "OUT SIZE <= MULTIPLIER_SIZE", file, line);
    rv >>= postshift;
    return UCLAMP(rv, out_size);
}

// DIVISION
/////////////
hw_int _nonsat_signed_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, 
                               char* file, int line)
{
    _check_s_warns(lhs, in_size, "LHS", file, line);
    _check_s_warns(rhs, in_size, "RHS", file, line);
    if (!_check(rhs != 0, "DIVISION BY ZERO", file, line))
        return 0;
    hw_int rv = lhs / rhs;
    _check_s_warns(rv, out_size, "NONSAT SIGNED DIVIDE", file, line);
    return rv;
}
hw_int _nonsat_unsigned_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, 
                                 char* file, int line)
{
    _check_u_warns(lhs, in_size, "LHS", file, line);
    _check_u_warns(rhs, in_size, "RHS", file, line);
    if (!_check(rhs != 0, "DIVISION BY ZERO", file, line))
        return 0;
    hw_int rv = lhs / rhs;
    _check_u_warns(rv, out_size, "NONSAT UNSIGNED DIVIDE", file, line);
    return rv;
}
hw_int _sat_signed_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, 
                            char* file, int line)
{
    _check_s_warns(lhs, in_size, "LHS", file, line);
    _check_s_warns(rhs, in_size, "RHS", file, line);
    if (!_check(rhs != 0, "DIVISION BY ZERO", file, line))
        return 0;
    hw_int rv = lhs / rhs;
    return SCLAMP(rv, out_size);
}
hw_int _sat_signed_division(hw_int lhs, hw_int rhs, unsigned int in_size, unsigned int out_size, 
                            char* file, int line)
{
    _check_u_warns(lhs, in_size, "LHS", file, line);
    _check_u_warns(rhs, in_size, "RHS", file, line);
    if (!_check(rhs != 0, "DIVISION BY ZERO", file, line))
        return 0;
    hw_int rv = lhs / rhs;
    return UCLAMP(rv, out_size);
}


