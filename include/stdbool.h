#ifndef STDBOOL_H
#define STDBOOL_H

#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L /* bool, true and false are keywords. */ 
#else 
#define bool	_Bool 
#define true	1 
#define false	0 
#endif

#define __bool_true_and_false_are_defined 1

#endif
