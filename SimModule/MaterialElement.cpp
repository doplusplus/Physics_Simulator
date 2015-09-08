#include "MaterialElement.h"
#include "PhysicalElement.h"
#include <iostream>

//Constructors & destructor-------------------------------
	MaterialElement::MaterialElement()
	{}
	
	MaterialElement::MaterialElement(Point P, double mass =0, double charge=0)
	{
		setPosition(P);
		setMass(mass);
	}
	
	MaterialElement::~MaterialElement()
	{}
	
//Accessors---------------------------------------------
    Point MaterialElement::*pointerToPosition()
	{
        return &position;
	}
	
    double MaterialElement::getMass()
	{
        return mass;
    }

//Display-----------------------------------------------
	virtual void MaterialElement::consoleShow()
	{
		position.show();
		std::cout<<"mass: "<<mass<<'\n';
	}

//Modifier----------------------------------------------
	void MaterialElement::setPosition(Point &P)
	{
	 position=P;
	}
 
	void MaterialElement::setPosition(double x, double y, double z)
	{
		position.setX(x);
		position.setY(y);
		position.setZ(z);
	}
	
	void setMass(double m)
	{
	 mass=m;
	}

//Simulation tool-------------------------------------
	virtual void MaterialElement::update(double dt) //computes and updates the state of the element at t+dt
	{ 
	  Acceleration a;
		a = getAcceleration();
		updateSpeedandPosition(a, dt);
	
	}
	
	virtual Acceleration MaterialElement::getAcceleration()
	{
	  Acceleration a;
	  a.nullify();
	  
	  Vector V = netForce.getDirection();
		
        if( mPoint.getMass() != 0 )
			{
                V = V*( 1 / mPoint.getMass());
                a.setDirection(V);
			}
		else
			{
				std::cout<<"** No mass no accs :-( **"<<'\n';
			}	
	
	  return a;
	}
	
	virtual void MaterialElement::updateSpeedandPosition(Acceleration a, double dt)
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
        mPoint.setPosition(X,Y,Z);
		
     //integration of the accelerations gives final speeds
        Vx = a.getDirection().getx()*dt + V.getDirection().getx();
        Vy = a.getDirection().gety()*dt + V.getDirection().gety();
        Vz = a.getDirection().getz()*dt + V.getDirection().getz();
        V.setDirection(Vx,Vy,Vz);
	}
	
