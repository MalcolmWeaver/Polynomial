#include "poly.h"
#include <cassert>
#include <climits>
#include <math.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <climits>

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
		if(size == 1){
			std::cout << "Will not attempt to trim a constant polynomial (degree 0) any further.\n";
			return;
		}
		if(std::abs(poly[size-1] - 0) > MINV){
			return; // if the last element is not zero, you can't delete it
		}
		for(int idx=size-1; idx >= 1; --idx){
		    	if(std::abs(poly[idx] - 0) > MINV){
		        	double* newPoly = new double[idx];
		        	size = idx;
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
		update_current_degree();
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
	
	// do after evaluation function
	double polynomial::definite_integral(double x0, double x1) const{
		polynomial anti_derivative = antiderivative();
		return anti_derivative(x1) - anti_derivative(x0);
	}
	
	void polynomial::update_current_degree(){
		current_degree = size - 1;
		while(std::abs(poly[current_degree] - 0) < MINV && current_degree > 0){
			--current_degree;
		}
		
	}
	
	polynomial polynomial::derivative( ) const{ // does this for reassignment?
		if(current_degree == 0){
			polynomial deriv(0, 0);
			return deriv;
		}
		polynomial deriv(0, current_degree-1); // put garbage into the current_degree -1 position, so that the size is initialized correctly
        	for(int i = 0; i <= current_degree-1; ++i){
            		deriv.poly[i] = (i + 1) * poly[i + 1];
        	}
        	deriv.update_current_degree();
        	return deriv;
	}
	
	double polynomial::eval(double x) const{
		return poly_eval(poly, size, x);
	}
	
	double poly_eval(double* coefficients, int size, double x){
		if(size == 1){return coefficients[0];}
		else{
			return coefficients[0] + x*poly_eval(coefficients+1, size - 1, x);
		}
	}
	
	bool polynomial::is_zero( ) const{
		if(degree() == 0){
			if(std::abs(poly[0]) < MINV){
				return true;
			}
		}
		return false;
	}
	
	unsigned int polynomial::next_term(unsigned int e) const{
		for(unsigned int idx=e+1; idx < size; ++idx){
			if(std::abs(poly[idx] - 0) >= MINV){
				return idx;
			}
		}
		return 0;
	}
	
	unsigned int polynomial::previous_term(unsigned int e) const{
		for(int idx=e-1; idx >= 0; --idx){
			if(std::abs(poly[idx] - 0) >= MINV){
				return idx;
			}
		}
		return UINT_MAX;
	}
	
	// stop it when the size runs out for the smaller p
    	polynomial operator +(const polynomial& p1, const polynomial& p2){
    		//unsigned int big_degree = p1.degree() > p2.degree() ? p1.degree() : p2.degree(), small_degree = p1.degree() < p2.degree() ? p1.degree() : p2.degree();
        	int idx;
        	double tmp_val;
        	if(p1.degree() >= p2.degree()){
        	     	polynomial sum(p1);
        	 	for(idx=0; idx <= p2.degree(); ++idx){
        	 		tmp_val = p2.coefficient(idx);
        	 		sum.add_to_coef(tmp_val, idx);
        	 	}
        	 	sum.update_current_degree();
        	 	return sum;
        	}
        	else{
        		polynomial sum(p2);
        	 	for(idx=0; idx <= p1.degree(); ++idx){
        	 		tmp_val = p1.coefficient(idx);
        	 		sum.add_to_coef(tmp_val, idx);
        	 	}
        	 	sum.update_current_degree();
        	 	return sum;
              	}
        }

	polynomial operator -(const polynomial& p1, const polynomial& p2){
        	polynomial diff, neg_1 = -1;
        	return p1 + (neg_1 * p2);
    	}

    	polynomial operator *(const polynomial& p1, const polynomial& p2){
        	assert(p1.degree( ) + p2.degree( ) <= polynomial::MAXIMUM_DEGREE);
        	polynomial product(0, p1.degree( ) + p2.degree( ));
        	for(int i = 0; i <= p1.degree(); ++i){
            		for(int j = 0; j <= p2.degree(); ++j){
                		product.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            		}
        	}
        	product.update_current_degree();
        	return product;
    	}
	
	// NON-MEMBER OUTPUT FUNCTIONS
    	std::ostream& operator << (std::ostream& out, const polynomial& p){
    		//out << std::fixed;
        	//out << std::setprecision(1);

        	out << p.coefficient(p.degree());
        	//special cases for polynomials of degree 1 and 0
        	if(p.degree() > 1){
            		out << "x^" << p.degree();
        	} else if(p.degree() == 1){
            		out << "x" << " " << (p.coefficient(0) < 0 ? "- " : "+ ") << abs(p.coefficient(0));
			out << std::endl;
        	} else{
        		out << std::endl;	
        		return out;
        	}
		
        	for(int i = p.degree() - 1; i > 1; --i){
            		if(p.coefficient(i) != 0){
                		out << " " << (p.coefficient(i) < 0 ? "- " : "+ ") << abs(p.coefficient(i)) << "x^" << i;
            		}
        	}
        	if(p.coefficient(1) != 0)
            		out << " " << (p.coefficient(1) < 0 ? "- " : "+ ") << abs(p.coefficient(1)) << "x";
        	if(p.coefficient(0) != 0)
            		out << " " << (p.coefficient(0) < 0 ? "- " : "+ ") << abs(p.coefficient(0));
            	out << std::endl;
        	return out;
    	}
}

