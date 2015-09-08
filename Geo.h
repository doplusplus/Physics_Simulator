#ifndef GEO_H
#define GEO_H


//--------------------------------- Point --------------------------------------------------
class Point
{
private:
	double x;
	double y;
	double z;	

public:
	Point();
	Point(double x,double y, double z);
	~Point();

//accessor
    double getX();
    double getY();
    double getZ();


//Display
    void show();

//Modifier
	void setX(double x);
	void setY(double y);
	void setZ(double z);
    void nullify();

//Algebraic operator
    Point operator +( Point B );
    Point operator *( double a); // scalar multiplication

};


//--------------------------------- Vector --------------------------------------------------
class Vector
{	
private:
	double xcomp;
	double ycomp;
	double zcomp;
	
public:
	Vector();
	Vector( double x, double y, double z);
	~Vector();
		
	double getx();
	double gety();
	double getz();

	
	void setVector( double x, double y, double z);
	void setVector( Vector C);
	void nullify();	

		
	Vector operator +( Vector &B );
	Vector operator ^( Vector &B ); // vectorial multiplication
	Vector operator *( double a); // scalar multiplication
    double operator *(  Vector &B); //dot product

    void show();

    Vector unitarized();
    //double norm();
};


	Vector NullVector(); //Neutral element for +




#endif
