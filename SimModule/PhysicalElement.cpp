#include "PhysicalElement.h"

#include "Geo.h"
#include <iostream>

//-------------------------- Forces ------------------------------------

	//Constructors and destructor
	Force::Force()
	{}
	Force::~Force()
	{}
	
	//Accessors
	Vector Force::getDirection()
	{ return direction;}
	
    Point *Force::getApplicationPoint()
	{ return application;}
	
	//Display
	void Force::show()
	{
		std::cout<<"Direction:"<<'\n';
		direction.show();
		
		std::cout<<"Application point:"<<'\n';
        application->show();
	}
	
	//Modifier
	void Force::setDirection (Vector V)
	{direction = V;}

    void Force::setApplication(Point *P)
    {application = P;}

	void Force::nullify()
	{direction.nullify();}

    Force Force::operator +(Force B ) //supposes same application point
    {Force F;
        F.setDirection(direction+B.direction);
        F.application= application;
    return F;
    }

    Force Force::operator -()
    {Force F; Vector V;
        double x=this->getDirection().getx();
        double y=this->getDirection().gety();
        double z=this->getDirection().getz();

        x=-x;y=-y;z=-z;

        V.setVector(x,y,z);
        F.setDirection(V);
        F.setApplication( getApplicationPoint());
    return F;
    }

//	Vector Force::operator *( Vector A, Vector B )  //produit vectoriel
//	Vector Force::operator *( double a, Vector B )  //produit scalaire

//-------------------------- Acceleration ------------------------------------
//Constructors and destructor
	Acceleration::Acceleration()
	{}
	
	Acceleration::Acceleration(Force F, double mass) // valid for point element
	{
        application = F.getApplicationPoint();
		direction = F.getDirection()*(1/mass);
	}
	

	Acceleration::~Acceleration()
	{}
	
	//Accessors
	Vector Acceleration::getDirection()
	{ return direction;}
	
    Point *Acceleration::getApplicationPoint()
	{return application;}
	
	//Display
	void Acceleration::show()
	{
		std::cout<<"Direction:"<<'\n';
		direction.show();
		
		std::cout<<"Application point:"<<'\n';
        application->show();
	}
	
	//Modifier
	void Acceleration::setDirection (Vector V)
	{direction = V;}
	
    void Acceleration::setApplication(Point *P)
    {application=P;}
	
	void Acceleration::nullify()
	{direction.nullify();}
	
//	void Acceleration::setApplication(double x, double y, double z)
	
//	Vector Acceleration::operator +( Vector A, Vector B )
//	Vector Acceleration::operator *( Vector A, Vector B )  //produit vectoriel
//	Vector Acceleration::operator *( double a, Vector B )  //produit scalaire



//-------------------------- Velocity ------------------------------------
//Constructors and destructor
	Velocity::Velocity()
	{}
	
	Velocity::~Velocity()
	{}
	
	//Accessors
	Vector Velocity::getDirection()
	{ return direction;}
	
    Point *Velocity::getApplicationPoint()
	{return application;}
	
	//Display
	void Velocity::show()
	{
		std::cout<<"Direction:"<<'\n';
		direction.show();
		
		std::cout<<"Application point:"<<'\n';
        application->show();
	}
	
	//Modifier
	void Velocity::setDirection (Vector V)
	{direction = V;}
	
	void Velocity::setDirection (double x, double y, double z)
	{
		direction.setVector(x,y,z);
	}
	
    void Velocity::setApplication(Point *P)
    {application=P;}
	
	void Velocity::nullify()
	{direction.nullify();}
	
	
//	void Velocity::setApplication(double x, double y, double z)
//	Vector Velocity::operator +( Vector A, Vector B )
//	Vector Velocity::operator *( Vector A, Vector B )  //produit vectoriel
//	Vector Velocity::operator *( double a, Vector B )  //produit scalaire



