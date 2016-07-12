#ifndef GEO_H
#define GEO_H

#include <functional>
#include <vector>
#include <string>
//==================================== CartesianElement ====================================
class CartesianElement
{
public:
	CartesianElement();
	CartesianElement(double x, double y, double z);
	CartesianElement(const CartesianElement &C);
	virtual ~CartesianElement();


	//Display
	void show() const;

	//Algebraic operator

	CartesianElement operator-() const;
	CartesianElement operator *(double a) const;			// multiplication by a scalar
	CartesianElement operator /(double a) const;			// division by a scalar, exception thrown if null 

	friend CartesianElement operator +(const CartesianElement &A, const CartesianElement &B);
	friend CartesianElement operator -(const CartesianElement &A, const CartesianElement &B);
	friend bool operator <(const CartesianElement &left, const CartesianElement &right);

	//logical operator	
	friend bool operator ==(const CartesianElement &left, const CartesianElement &right);




	std::string getDescription() const
	{
		return "x: " + std::to_string(X) + "y: " + std::to_string(Y) + "z: " + std::to_string(Z) + "\n";
	}

	std::vector<double> coordStream() const
	{
		std::vector<double> res;
		res.push_back(X);
		res.push_back(Y);
		res.push_back(Z);
		return res;
	}

protected:
	double X;
	double Y;
	double Z;
};

//==================================== Point ====================================
class Vect;
class Point : public CartesianElement
{
public:
	Point();
	Point(double x, double y, double z);
	Point(CartesianElement C);
	Point(Vect V);				//At the non null extremity of V 
	Point(Point P, Vect V);		//At the image of P translated by V 
	~Point();

private:
	void move(double dx, double dy, double dz);

};

//==================================== Vect ====================================

class Vect : public CartesianElement
{
	friend	std::function<Vect(Vect, double)> operator+ (std::function<Vect(Vect, double)>, std::function<Vect(Vect, double)>);
	friend	std::function<Vect(Vect, Vect)> operator+ (std::function<Vect(Vect, Vect)> a, std::function<Vect(Vect, Vect)> b);

public:
	Vect();
	Vect(double x, double y, double z);
	Vect(CartesianElement C);
	Vect(Point A, Point B);
	~Vect();

	Vect operator ^(const Vect &B) const;			// Vectorial multiplication
	double operator *(const Vect &B) const;			// dot product	
	Vect multiplyMemberwise(const Vect &B) const;
	Vect absMultiplyMemberwise(const Vect &B) const;
	Vect operator *(double a) const;

	double norm() const;
	Vect unitVector() const;
	Vect null() { return Vect(0, 0, 0); }

	//   member Time or space functions
	static Vect constant(Vect V, double var) { return Vect(0,0,0); };
	static Vect linear(Vect V, double var) { return V*var; };
	static Vect Quadratic(Vect V, double var) { return V*var*var; };

	static double Vconstant(Vect V, Vect var) { return 0.0; };
	static double Vlinear(Vect V, Vect var) { return V*var; };
	static double VQuadratic(Vect V, Vect var) { return V*var.absMultiplyMemberwise(var); };
};










#endif
