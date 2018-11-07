/* 
 * File:   utilities.h
 * Author: qiuf
 *
 * Created on November 7, 2018, 10:35 AM
 */

#ifndef UTILITIES_H
#define	UTILITIES_H

#include <math.h>

static uint8_t logTwo(uint8_t input){
    return (uint8_t)(log((double)input) / log(2));
}

#endif	/* UTILITIES_H */

