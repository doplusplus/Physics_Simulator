#include "MaterialElement.h"
#include "PhysicalElement.h"
#include <iostream>

//Constructors & destructor-------------------------------
	MaterialElement::MaterialElement()
	{}
	
	MaterialElement::MaterialElement(Point p, double masse , double charge_)
	{
		Position = p;  // does a shallow copy of P
		Mass = masse;
        Charge = charge_;
	}
	
	MaterialElement::~MaterialElement()
	{}
	
//Accessors---------------------------------------------
    Point * MaterialElement::pointerToPosition()
    {
     Point *pos= NULL;
        pos = &Position;
     return pos;
	}


    double MaterialElement::getMass()
	{
        return Mass;
    }


//Display-----------------------------------------------
	void MaterialElement::consoleShow()
	{
		Position.show();
		std::cout<<"mass: "<<Mass<<'\n';
	}

//Modifier----------------------------------------------
	void MaterialElement::setPosition(Point &P)
	{
		Position = P;
	}
 
	void MaterialElement::setPosition(double x, double y, double z)
	{
        Position.set(x,y,z);
	}
	
	void MaterialElement::setMass(double m)
	{
        Mass=m;
	}

//Simulation tool-------------------------------------
	void MaterialElement::update(double dt) //computes and updates the state of the element at t+dt
	{ 
	  Acceleration a;
		a = getAcceleration();
		updateSpeedandPosition(a, dt);
	
	}
	
	Acceleration MaterialElement::getAcceleration()
	{
	  Acceleration a;
        a.nullify();
	  
	  Vect V = NetForce.getDirection();
		
        if( Mass != 0 )
			{
                V = V / Mass;
                a.setDirection(V);
			}
		else
			{
				std::cout<<"** No mass no accs :-( **"<<'\n';
			}	
	
	  return a;
	}
	
	void MaterialElement::updateSpeedandPosition(Acceleration a, double dt)
	{
	  double Vx,Vy,Vz,X,Y,Z;
		
     //Initial speeds
        Vx = V.getDirection().getX();
        Vy = V.getDirection().getY();
        Vz = V.getDirection().getZ();	
		
     //Double integration of the accelerations gives final positions
        X = 0.5*a.getDirection().getX()*dt*dt + Vx*dt + Position.getX();
        Y = 0.5*a.getDirection().getY()*dt*dt + Vy*dt + Position.getY();
        Z = 0.5*a.getDirection().getZ()*dt*dt + Vz*dt + Position.getZ();
        Position.set(X,Y,Z);
		
     //integration of the accelerations gives final speeds
        Vx = a.getDirection().getX()*dt + V.getDirection().getX();
        Vy = a.getDirection().getY()*dt + V.getDirection().getY();
        Vz = a.getDirection().getZ()*dt + V.getDirection().getZ();
        V.setDirection(Vx,Vy,Vz);
	}
	
