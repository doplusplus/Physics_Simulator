#include "PhysicalElement.h"
#include <iostream>

//-------------------------- Instanciated Vector ------------------------------------

//Constructors and destructor
InstanciatedVect::InstanciatedVect()
{}

InstanciatedVect::InstanciatedVect(Vect V)
{
	Point P;
	P.nullify();
	application = &P; 
	direction = V;
}

InstanciatedVect::InstanciatedVect(Point P, Vect V)
{
	application = &P;
	direction = V;
}

InstanciatedVect::~InstanciatedVect()
{}

//Accessors
Vect InstanciatedVect::getDirection() { return direction; } //**

Point *InstanciatedVect::getApplicationPoint() //returns a pointer to the application point**
{
	return application;
}

//Display
void InstanciatedVect::show()
{
	std::cout << "Direction:" << '\n';
	direction.show();

	std::cout << "Application point:" << '\n';
	application->show();
}

//Modifier
void InstanciatedVect::setDirection(Vect V)     //**
{ direction.set(V); }

void InstanciatedVect::setDirection(double x, double y, double z)
{ direction.set(x,y,z); }


void InstanciatedVect::setApplication(Point *P)
{ application = P; }

void InstanciatedVect::nullify()
{
	direction.nullify();
	application->nullify();
}




//-------------------------- Forces ------------------------------------

	//Constructors and destructor
	Force::Force()
	{}

	Force::Force(Point P, Vect V) : InstanciatedVect(P,V)
	{}

	Force::~Force()
	{}
		
	//Display
	void Force::show()
	{
		std::cout << "   ---- Force ----   " << '\n';
		InstanciatedVect::show();
	}
	
	
    Force Force::operator +(Force B ) //returns the sum of 2 forces applying to their middlepoint
    {
	 Force F;
        F.setDirection(getDirection() + B.getDirection());
		F.getApplicationPoint()->set(*getApplicationPoint() + *(B.getApplicationPoint()));
     return F;
    }

    Force Force::operator -()
    {
	 Force F; Vect V;
        double x=this->getDirection().getX();
        double y=this->getDirection().getY();
        double z=this->getDirection().getZ();

        x=-x;y=-y;z=-z;

        V.set(x,y,z);
        F.setDirection(V);
        F.setApplication( getApplicationPoint());
     return F;
    }



//-------------------------- Acceleration ------------------------------------
//Constructors and destructor
	Acceleration::Acceleration()
	{}
	
	Acceleration::Acceleration(Force Resultant, double mass) 
	{// returns the linear acceleration of the center of gravity of an object given its mass and resultant
	
        application = Resultant.getApplicationPoint();
		direction = Resultant.getDirection() / mass;
	}
	
	Acceleration::~Acceleration()
	{}
	
	//Display
	void Acceleration::show()
	{
		std::cout << "   ---- Acceleration ----   " << '\n';
		InstanciatedVect::show();
	}
	


//-------------------------- Velocity ------------------------------------
//Constructors and destructor
	Velocity::Velocity()
	{}
	
	Velocity::~Velocity()
	{}
	
	//Display
	void Velocity::show()
	{
		std::cout << "   ---- Velocity ----   " << '\n';
		InstanciatedVect::show();
	}
