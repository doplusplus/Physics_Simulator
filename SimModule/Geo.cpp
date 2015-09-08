#include "Geo.h"
#include <iostream>
#include <cmath>

//-----------------POINT---------------------------------------------
	Point::Point()
	{
		x=y=z=0;
	}
	
	Point::Point(double xc,double yc, double zc)
	{
		x=xc;
		y=yc;
		z=zc;
	}
	
	Point::~Point()
	{}


//Accessors---------------------------------------------------------------
    double Point::getX()
    {
        return x;
    }

    double Point::getY()
    {
        return y;
    }

    double Point::getZ()
    {
        return z;
    }

    //Display-------------------------------------------------------------------
    void Point::show()
    {
        std::cout<<"x:"<<x<<'\n'<<"y:"<<y<<'\n'<<"z:"<<z<<'\n';
    }


//Modifier-------------------------------------------------------------------
	void Point::setX(double xe)
	{
		x=xe;
	}
	void Point::setY(double ye)
	{
		y=ye;
	}
	
	void Point::setZ(double ze)
	{
		z=ze;
	}
	void Point::place(double xe,double ye, double ze)   //**
	{
		x=xe;
		y=ye;
		z=ze;
	}
	void Point::nullify()                    //**
	{
		x=y=z=0;
	}


//Algebraic operator-------------------------------------------------------------
	Point Point::operator +( Point B )
	{
	 Point P;
		P.setX(x+B.getX());
		P.setY(y+B.getY());
		P.setZ(z+B.getZ());
	 return P;
	}
	
	Point Point::operator *( double a) //multiplication by a scalar
	{
	 Point P;
		P.place(x*a , y*a, z*a);
	 return P;
	}
	
	Point Point::operator /( double a) //scalar division  **
	{
	 Point P;
		P.place(x/a, y/a, z/a);
	 return P;
	}

//.................................End Point......................................
//================================================================================



//================================================================================
//----------------------------------- Vector -------------------------------------
	
//constructors	and destructor
	Vector::Vector()
	{}
	
	Vector::Vector( double x, double y, double z)
	{
		xcomp=x;
		ycomp=y;
		zcomp=z;
	}
	
	Vector::~Vector()
    {}

	
//--------------------Accessors-------------------------------
	
	double Vector::getx()
	{return xcomp;}
	
	double Vector::gety()
	{return ycomp;}
	
	double Vector::getz()
	{return zcomp;}
	
	
//Modifiers----------------------------------------------------	
	
	void Vector::setVector( double x, double y, double z)
	{
		xcomp=x;
		ycomp=y;
		zcomp=z;
	}
	

	void Vector::setVector( Vector C)
	{
		xcomp=C.getx();
		ycomp=C.gety();
		zcomp=C.getz();
	}

	void Vector::nullify()
	{
		setVector(0,0,0);
	}
	
	void Vector::show()
	{
		std::cout<<" x: "<<xcomp <<'\n';
		std::cout<<" y: "<<ycomp <<'\n';
		std::cout<<" z: "<<zcomp <<'\n';
	}
	
	
//Operators definition---------------------------------------------------------
	
	Vector Vector::operator +( Vector &B )
	{Vector v;
		v.xcomp=xcomp+B.xcomp;
		v.ycomp=ycomp+B.ycomp;
		v.zcomp=zcomp+B.zcomp;
		return v;
	}
	
	Vector Vector::operator ^( Vector &B ) //produit vectoriel
	{Vector v;
	
		v.xcomp= ycomp*B.zcomp-zcomp*B.ycomp;
		v.ycomp= zcomp*B.xcomp-xcomp*B.zcomp;
		v.zcomp= xcomp*B.ycomp-ycomp*B.xcomp;
		return v;
	}
	
	Vector Vector::operator * (double a) //multiplication by a scalar
	{Vector v;
		v.xcomp=a*xcomp;
		v.ycomp=a*ycomp;
		v.zcomp=a*zcomp;
		return v;
	}

    double Vector::operator *(Vector &B) //dot product
    {
        double s;
        s=xcomp*B.xcomp+ycomp*B.ycomp+zcomp*B.zcomp;
        return s;
    }

//derived values
    Vector Vector::unitarized()
    {
        Vector u;
        double sq= *this * (*this);

        sq=sqrt(sq);
        u.setVector(getx()/sq,gety()/sq,getz()/sq);

        return u;
    }



