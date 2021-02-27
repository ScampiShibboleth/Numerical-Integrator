# Numerical-Integrator
Numerical integration calculator that integrates a function with a given domain. Uses trapezoidal and Simpson's.

# Consider the following:
* This file **REQUIRES** the use of Lewis Van Winkle's (@codeplea) [TinyExpr](https://github.com/codeplea/tinyexpr) repo
* For convenience, I have included copies Lewis's source code (tinyexpr.c and tinyexpr.h)
* This calculator _only_ accepts single variable expressions in x (i.e. y^2 is an error, x^2 is not, x^2+5*y is an error, x^2+5*x is not) 
* You may either enter your inputs in the command line or as standard input
* For command line, the order will be in the form of "./executable expression lower bound upper bound <# of subsections>"
* For standard input, simply call "./executable"
* If your lower bound is unintentionally higher than your upper bound, simply flip the sign as per the proprty of integrals
* DO NOT enter formulas with singularities within the given range, you will likely receive an incorrect answer
* It is recommeded to surround your expression in double quotes when entering using the command line, though it is not essential
