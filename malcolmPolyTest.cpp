#include <iostream>
#include "poly.h"


using namespace coen79_lab5;
/*
void printP(polynomial& p){
	std::cout << "Polynomial: ";
	unsigned int degree = p.degree();
	while(degree < 30){
		std::cout << coefficient(degree) << "x^"<< degree << " + ";
		degree = previous_term(degree);
		}
	}
	std::cout << std::endl;
}
*/
int main(){
	polynomial p1(3, 3);
	polynomial p2(p1), p3, p4, p5;
	p2.assign_coef(2.2, 0);
	p2.assign_coef(1.5, 10);
	p2.trim();
	
	std::cout << "RUNNING ..... \n";
	p1.assign_coef(2, 2);
	p1.assign_coef(-4, 0);
	p1.add_to_coef(10, 2);
	p1.add_to_coef(1, 1);
	std::cout << p1;
	p3 = p1;
	p3 = 1.2;
	p3 = p1.antiderivative();
	/*std::cout << "x^3 coefficient of p1 is: " << p1.coefficient(3) << std::endl; 
	std::cout << "degree of p1: " << p1.degree() << std::endl;
	p1.add_to_coef(-3, 3);
	std::cout << "degree of p1: " << p1.degree() << std::endl;
	p3 = p3.derivative();
	polynomial p4, p5;
	p5 = p4.derivative();
	double p30 = p3.eval(0), p31 = p3.eval(1);
	unsigned int next_term = p3.next_term(0);
	next_term = p3.next_term(3);
	next_term = p3.previous_term(1);
	next_term = p3.previous_term(0);
	double di = p3.definite_integral(0, 0);
	di = p3.definite_integral(0, 1);
	*/
	p4 = p3+p2;
	std::cout << p3;
	std::cout << p2;
	std::cout << p4;
	
	/*p2 = p1.antiderivative();
	printP(p2);
	p3 = p2.derivative();


	//evaluate with ()
	std::cout << "p1(-1)" << p1(1) << std::endl;
       	std::cout << "p2(2)" << p2(2) << std::endl;	
	p2 = p1*p3;
	printP(p2);
	p1 = p2+p2;
	printP(p1);
	p2 = p2 - p2;
	printP(p2);

	p1.clear();
	std::cout << "Is P1 0? " << p1.is_zero() << std::endl;
*/
}
