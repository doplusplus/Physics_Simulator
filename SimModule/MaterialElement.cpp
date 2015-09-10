#include "MaterialElement.h"
#include "PhysicalElement.h"
#include <iostream>

//Constructors & destructor-------------------------------
	MaterialElement::MaterialElement()
	{}
	
	MaterialElement::MaterialElement(Point P, double masse , double charge_)
	{
		position = P;  // does a shallow copy of P
		mass = masse;
        charge = charge_;
	}
	
	MaterialElement::~MaterialElement()
	{}
	
//Accessors---------------------------------------------
    Point * MaterialElement::pointerToPosition()
    {
     Point *pos= NULL;
        pos = &position;
     return pos;
	}


    double MaterialElement::getMass()
	{
        return mass;
    }


//Display-----------------------------------------------
	void MaterialElement::consoleShow()
	{
		position.show();
		std::cout<<"mass: "<<mass<<'\n';
	}

//Modifier----------------------------------------------
	void MaterialElement::setPosition(Point &P)
	{
	 position = P;
	}
 
	void MaterialElement::setPosition(double x, double y, double z)
	{
        position.place(x,y,z);
	}
	
	void MaterialElement::setMass(double m)
	{
        mass=m;
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
	  
	  Vector V = netForce.getDirection();
		
        if( mass != 0 )
			{
                V = V*( 1 / mass);
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
        Vx = V.getDirection().getx();
        Vy = V.getDirection().gety();
        Vz = V.getDirection().getz();	
		
     //Double integration of the accelerations gives final positions
        X = 0.5*a.getDirection().getx()*dt*dt + Vx*dt + position.getX();
        Y = 0.5*a.getDirection().gety()*dt*dt + Vy*dt + position.getY();
        Z = 0.5*a.getDirection().getz()*dt*dt + Vz*dt + position.getZ();
        position.place(X,Y,Z);
		
     //integration of the accelerations gives final speeds
        Vx = a.getDirection().getx()*dt + V.getDirection().getx();
        Vy = a.getDirection().gety()*dt + V.getDirection().gety();
        Vz = a.getDirection().getz()*dt + V.getDirection().getz();
        V.setDirection(Vx,Vy,Vz);
	}
	
