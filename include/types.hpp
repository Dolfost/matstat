#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include <QString>

enum class Status {
	None,
	Ok,
	Error,
	Warning,
};

const QString exprtkGeneralFunctions = 
				"abs(x), avg(…), ceil(x), clamp(r0,x,r1), equal(x,y), erf(x), erfc(x), exp(x),\n"
				"expm1(x), floor(x), hypot(x,y), iclamp(r0,x,r1), inrange(r0,x,r2), log(x),\n"
				"log10(x), log1p(x), log2(x), logn(x,n), max(…), min(…), mul(…), ncdf(x),\n"
				"not_equal(x,y), pow(x,n), root(x, n), round(x), roundn(x,n), sgn(x), sqrt(x),\n"
				"sum(…), swap(x,y), trunc(x), acos(x), ahosh(x), asin(x), asinh(x), atan(x),\n"
				"atan2(x,y), atanh(x), cos(x), cosh(x), cot(x), csc(x), sec(x), sin(x), sinc(c),\n"
				"sinh(x), tan(x), tanh(x), deg2rad(x), deg2grad(x), rad2deg(x), grad2deg(x)";

#endif // !_TYPES_HPP_
