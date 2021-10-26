#include "poly.h"
#include <cassert>
#include <climits>
#include <math.h>
#include <cmath>
#include <iostream>
#include <algorithm>

#define MINV 0.000001 // if two doubles subtract to less than this value, they are considered equal

namespace coen79_lab5{
	polynomial::polynomial(double c, unsigned int exponent){
		assert(exponent <= MAXIMUM_DEGREE);
		size = 0;
		poly = new double[exponent + 1](); // () initializes to 0s
		size = exponent + 1;
		for(int i = 0; i < size; ++i){
		    	poly[i] = 0;
		}
		poly[exponent] = c;
		update_current_degree();
	}
	    
    	polynomial::~polynomial(){
		delete[] poly;
	}
	    
	polynomial::polynomial(const polynomial& source){
		poly = new double[source.size];
		std::copy(source.poly, source.poly + source.size, poly);
		size = source.size;
		current_degree = source.current_degree;
	}
	
	// Modification MEMBER FUNCTIONS
	void polynomial::reserve(size_t number){
		if(size >= number){
		    	std::cout << "Will not reserve new space because it is not needed\n";
		    	return;
		}
		else{
		    	double * polyCopy = new double[number](); 
		    	std::copy(poly, poly + size, polyCopy);
		    	delete poly;
		    	poly = polyCopy;
		    
		}
	    }

	void polynomial::trim(){
		if(std::abs(poly[size-1] - 0) > MINV){
			return; // if the last element is not zero, you can't delete it
		}
		for(int idx=size-1; idx >= 0; --idx){
		    	if(std::abs(poly[idx] - 0) > MINV){
		        	size = idx;
		        	double* newPoly = new double[idx];
		        	std::copy(poly, poly+idx, newPoly);
		        	delete [] poly;
		        	poly = newPoly;
			}
		}
		update_current_degree();
	}
	    
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		if(exponent >= size){
		    	reserve(exponent + 1);
		    	size = exponent + 1;
		}
		poly[exponent] = coefficient;
		update_current_degree();
    	}

	void polynomial::add_to_coef(double amount, unsigned int exponent){
		assert(exponent <= MAXIMUM_DEGREE);
		if(exponent >= size){
		    	reserve(exponent + 1);
		    	size = exponent + 1;
		}
		poly[exponent] += amount;
		update_current_degree();
	}
	    
	void polynomial::clear(){
		for(int i = 0; i < size; ++i){
		    	poly[i] = 0;
		}
		update_current_degree();
	    }

	// MODIFICATION OPERATORS
	polynomial& polynomial::operator=(const polynomial& source){
		if(&source == this){return *this;}
		delete [] this->poly;
		size = 0;
		this->poly = new double[source.size];
		std::copy(source.poly, source.poly + source.size, poly);
		size = source.size;
		current_degree = source.current_degree;
		return *this;
	}

    	polynomial& polynomial::operator=(double c){
		size = 1;
		poly[0] = c;
		trim();
		return *this;					    		
    	}

	// CONST MEMBER FUNCTIONS
	
	polynomial polynomial::antiderivative() const{
		polynomial ad;
		ad.reserve(size + 1);
		for(int idx=1; idx < size+1; ++idx){
			ad.assign_coef(poly[idx-1]/idx, idx);
		}
		ad.update_current_degree();
		return ad;
	}
	
	
	double polynomial::coefficient(unsigned int exponent) const{
		assert(exponent < size);
		return poly[exponent];
	}
	
	/* do after evaluation function
	double definite_integral(double x0, double x1) const{
		polynomial anti_derivative = antiderivative();
		return anti_deri
	}
	*/
	void polynomial::update_current_degree(){
		current_degree = size - 1;
		while(std::abs(poly[current_degree] - 0) < MINV && current_degree > 0){
			--current_degree;
		}
		
	}
	
	polynomial polynomial::derivative( ) const{
		if(current_degree == 0){
			polynomial deriv(0, 0);
			return deriv;
		}
		polynomial deriv(1, current_degree-1); // put garbage into the current_degree -1 position, so that the size is initialized correctly
        	for(int i = 0; i <= deriv.current_degree; ++i){
            		deriv.poly[i] = (i + 1) * poly[i + 1];
        	}
        	return deriv;
	}
	
	double eval(double x) const
	
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

