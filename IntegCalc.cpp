/*
Numerical integration calculator that integrates a function with a given domain.
Uses trapezoidal and Simpson's.
Made by Yousef Sayes (@ScampiShibboleth)

Consider the following for this program:
    ~ This file REQUIRES the use of Lewis Van Winkle's (@codeplea) TinyExpr repo 
    ~ This calculator _only_ accepts single variable expressions in x (i.e. y^2 is an error, x^2 is not, x^2+5*y is an error, x^2+5*x is not) 
    ~ You may either enter your inputs in the command line or as standard input
    ~ For command line, the order will be in the form of "./<executable> <expression> <lower bound> <upper bound> <# of subsections>"
    ~ For standard input, simply call "./<executable>"
    ~ If your lower bound is unintentionally higher than your upper bound, simply flip the sign as per the proprty of integrals
    ~ DO NOT enter formulas with singularities within the given range, you will likely receive an incorrect answer
    ~ It is recommeded to surround your expression in double quotes when entering using the command line, though it is not essential
    ~ 
*/
#include <iostream>
#include <string>
#include <ios>
#include <stdio.h>
#include <stdlib.h>
#include "tinyexpr.h"

int main(int argc, char* argv[]){
    char* expr;
    std::string preExpr;
    double lower;
    double upper;
    int subsect;

    if(argc == 1){
        std::cout << "Enter expression: ";
        std::cin >> preExpr;
        expr = &preExpr[0];

        std::cout << "Enter lower bound: ";
        std::cin >> lower;

        std::cout << "Enter upper bound: ";
        std::cin >> upper;

        std::cout << "Enter amount of subsections desired: ";
        std::cin >> subsect;
    }else if (argc < 5){
        std::cerr << "Insufficient inputs, please re-enter values.";
        exit(1);
    }else{
        expr = argv[1];

        char* ptrLower;
        lower = strtod(argv[2], &ptrLower);

        char* ptrUpper;
        upper = strtod(argv[3], &ptrUpper);

        subsect = atoi(argv[4]);
    }

    double x;
    te_variable vars[] = {"x", &x};

    int err;
    te_expr* n = te_compile(expr, vars, 2, &err);

    if(n){
        double delta = (upper - lower)/subsect;
        double deltTrape = delta/2;
        double deltSimp = delta/3;
        double areaTrape{0.0};
        double areaSimp{0.0};
        
        for(int i = 0; i < subsect+1; ++i){
            x = lower + (i*delta);
            if(i == 0 || i == subsect){
                areaTrape += deltTrape*te_eval(n);
            }else{
                areaTrape += 2*deltTrape*te_eval(n);
            }   
        }
        
        switch (subsect%2){
            //Even cases of subintervals will use the typical composite Simpson's rule
            case 0:
                for(int i = 0; i < subsect+1; ++i){
                    x = lower + (i*delta);
                    if(i == 0 || i == subsect){
                        areaSimp += deltSimp*te_eval(n);
                    }else if(i%2 == 1){
                        areaSimp += deltSimp*4*te_eval(n);
                    }else{
                        areaSimp += deltSimp*2*te_eval(n);
                    }
                }
             break;

            //Odd cases of subintervals will use typical composite Simpson's rule for the first n-3 
            //intervals and then use Simpson's 3/8 formula for the final three subintervals        
            case 1:
                double secondSimp = 0.0;
                for(int i = 0; i < subsect-2; ++i){
                    x = lower + (i*delta);
                    if(i == 0 || i == subsect-3){
                        areaSimp += deltSimp*te_eval(n);
                    }else if(i%2 == 1){
                        areaSimp += deltSimp*4*te_eval(n);
                    }else{
                        areaSimp += deltSimp*2*te_eval(n);
                    }
                }

                for(int i = subsect-3; i < subsect+1; ++i){
                    x = lower + (i*delta);
                    if(i == subsect-3 || i == subsect){
                        secondSimp += te_eval(n);
                    }else{
                        secondSimp += 3*te_eval(n);
                    }
                }

                areaSimp += (3.0/8)*delta*secondSimp;

             break;
        }

        std::cout << "Trapezoidal Area: " << areaTrape << '\n';
        std::cout << "Simpson's Area: " << areaSimp << '\n';
    }else{
        printf("Error in formula:\n\t%s\n", expr);
        printf("\t%*s^", err-1, "");
    }
}