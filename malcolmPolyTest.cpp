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
	polynomial p2(p1);
	p2.assign_coef(2.2, 0);
	p2.assign_coef(1.5, 10);
	p2.trim();
	
	std::cout << "RUNNING ..... \n";
	/*printP(p1);
	p1.assign_coef(2, 2);
	printP(p1);
	p1.assign_coef(-4, 0);
	printP(p1);
	p1.add_to_coef(10, 2);
	printP(p1);
	p1.add_to_coef(1, 1);
	printP(p1);
	p2 = p1.antiderivative();
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
