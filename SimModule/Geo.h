#ifndef GEO_H
#define GEO_H

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
	CartesianElement operator +(const CartesianElement &B) const;
	CartesianElement operator-() const;
	CartesianElement operator -(CartesianElement B) const;

	CartesianElement operator *(double a) const;			// multiplication by a scalar
	CartesianElement operator /(double a) const;			// division by a scalar, exception thrown if null 

	bool operator <(CartesianElement C) const
	{
		return (X < C.X) && (Y < C.Y) && (Z < C.Z);
	};
													//logical operator	
	bool operator ==(const CartesianElement &B) const;
	
	std::string getDescription() const
	{
		return "x: " + std::to_string(X) + "y: " + std::to_string(Y) +"z: " + std::to_string(Z)+"\n";
	}

	std::vector<double> coordStream()
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
public:
	Vect();
	Vect(double x, double y, double z);
	Vect(CartesianElement C);
	Vect(Point A, Point B);
	~Vect();

	Vect operator ^(const Vect &B) const;		// Vectorial multiplication
	double operator *(const Vect &B) const;		// dot product	
	Vect operator *(double a) const;

	double norm() const;
	Vect unitVector() const;
	
	
	//   member Time or space functions
	static Vect constant(Vect V, double var) { return V; };
	static Vect linear(Vect V, double var) { return V*var; };
	static Vect timeQuadratic(Vect V, double var) { return V*var*var; };
};












#endif
