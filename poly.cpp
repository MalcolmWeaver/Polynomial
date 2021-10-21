#include "poly.h"
#include <cassert>
#include <climits>
#include <math.h>
#include <cmath>
#include <iostream>
#include <algorithm>

#define MINV 0.000001 // if two doubles subtract to less than this value, they are considered equal

namespace coen79_lab5{
	polynomial::polynomial(double c, unsigned int exponent)
    {
        assert(exponent <= MAXIMUM_DEGREE);
        size = 0;
        poly = new double[exponent + 1];
        size = exponent + 1;
        for(int i = 0; i <= size; ++i){
            poly[i] = 0;
        }
        poly[exponent] = c;
    }
    
    polynomial::~polynomial(){
        delete[] poly;
    }
    
    polynomial::polynomial(const polynomial& source){
        size = source.size;
        current_degree = source.current_degree;
        poly = new double[size];
        std::copy(source.poly, source.poly + source.size, poly);
    }

    void polynomial::reserve(size_t number){
        if(size >= number){
            std::cout << "Will not reserve new space because it is not needed\n";
            return;
        }
        else{
            double * polyCopy = new double[number]; 
            std::copy(poly, poly + size, polyCopy);
            delete poly;
            poly = polyCopy;
        }
    }

    void polynomial::trim(){
        if(poly[size] - 0 > MINV){
            return; // if the last element is not zero, you can't delete it
        }
        for(int idx=size-1; idx >= 0; --idx){
            if(poly[idx] - 0 > MINV){
                size = idx;
                double* newPoly = new double[idx];
                std::copy(poly, poly+idx, newPoly);
                delete [] poly;
                poly = newPoly;
            }
        }
    }
    
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        if(exponent > size){
            reserve(exponent + 1);
            size = exponent + 1;
        }
        poly[exponent] = coefficient;
        if(exponent > current_degree) 
            current_degree = exponent;
    }

    //void polynomial::update_current_degree(){
    //    current_degree = degree();
    //}
        /*
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        i
        poly[exponent] = coefficient;
        if(exponent > current_degree) 
            current_degree = exponent;
    }
        */
}

