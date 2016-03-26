/*
 *
 * This file is a part of my arduino development.
 * If you make any modifications or improvements to the code, I would
 * appreciate that you share the code with me so that I might include
 * it in the next release. I can be contacted through paul.torruella@gmail.com

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU GENERAL PUBLIC LICENSE 3.0 license.
 * Please see the included documents for further information.

 * Commercial use of this file and/or every others file from this library requires
 * you to buy a license that will allow commercial use. This includes using the code,
 * modified or not, as a tool to sell products.

 *  The license applies to this file and its documentation.
 *
 *  Created on: 23 févr. 2016
 *  Author: Paul TORRUELLA
 */

#include "MyMath.h"

//isinTable16 in a unnamed namespace to make it unaccessible from outside ...
namespace{
// 91 x 2 bytes ==> 182 bytes
const unsigned int isinTable16[] = { 
 0, 1144, 2287, 3430, 4571, 5712, 6850, 7987, 9121, 10252, 11380, 
 12505, 13625, 14742, 15854, 16962, 18064, 19161, 20251, 21336, 22414, 
 23486, 24550, 25607, 26655, 27696, 28729, 29752, 30767, 31772, 32768, 

 33753, 34728, 35693, 36647, 37589, 38521, 39440, 40347, 41243, 42125, 
 42995, 43851, 44695, 45524, 46340, 47142, 47929, 48702, 49460, 50203, 
 50930, 51642, 52339, 53019, 53683, 54331, 54962, 55577, 56174, 56755, 

 57318, 57864, 58392, 58902, 59395, 59869, 60325, 60763, 61182, 61583, 
 61965, 62327, 62671, 62996, 63302, 63588, 63855, 64103, 64331, 64539, 
 64728, 64897, 65047, 65176, 65286, 65375, 65445, 65495, 65525, 65535, 
 }; 
}

float fastmath::isin(int x)
{
 boolean pos = true;  // positive - keeps an eye on the sign.
 if (x < 0) 
 {
   x = -x;
   pos = !pos;  
 }  
 if (x >= 360) x %= 360;   
 if (x > 180) 
 {
   x -= 180;
   pos = !pos;
 }
 if (x > 90) x = 180 - x;
 if (pos) return isinTable16[x] * 0.0000152590219; // = /65535.0
 return isinTable16[x] * -0.0000152590219 ;
}

float fastmath::icos(int x)
{
 return isin(x+90);
}

float fastmath::itan(int x) 
{
 return isin(x) / icos(x);
}

long fastmath::roundedmap(const long x, const long in_min, const long in_max, const long out_min, const long out_max)
{
  return ((x - in_min) * (out_max - out_min) + (in_max - in_min) / 2) / (in_max - in_min) + out_min;
}
