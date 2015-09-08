#ifndef PhysElem
#define PhysElem

#include "Geo.h"


class Force                         //in Newton
{
	private:
    Point  *application;
    Vector direction;
	

	public:
	//Constructors and destructor
	Force();
	~Force();

	//Accessors
	Vector getDirection();
    Point *getApplicationPoint(); //returns a pointer to the application point

	//Display
	void show();

	//Modifier
	void setDirection (Vector V);
    void setApplication(Point &P);
    void setApplication(Point *P);
	void nullify();
	
    Force operator +(Force B);
    Force operator -();
//	Vector operator *( Vector A, Vector B ); //produit vectoriel
//	Vector operator *( double a, Vector B ); //produit scalaire
};

class Acceleration                    // m/s²
{
	private:
    Point  *application;
	Vector direction;
	

	public:
	//Constructors and destructor
	Acceleration();
	Acceleration(Force F, double mass);				// valid for point element
	~Acceleration();
	
	
	//Accessors
	Vector getDirection();
    Point *getApplicationPoint();

	//Display
	void show();

	//Modifier
	void setDirection (Vector V);
    void setApplication(Point *P);
	void nullify();
	
//	Vector operator +( Vector A, Vector B );
//	Vector operator *( Vector A, Vector B ); //produit vectoriel
//	Vector operator *( double a, Vector B ); //produit scalaire
};

class Velocity                    // m/s
{
	private:
    Point  *application;
	Vector direction;
	

	public:
	//Constructors and destructor
	Velocity();
	~Velocity();
	
	
	//Accessors
	Vector getDirection();
    Point *getApplicationPoint();

	//Display
	void show();

	//Modifier
	void setDirection (Vector V);
	
	void setDirection (double x, double y, double z);
	
    void setApplication(Point *P);
	void nullify();
	
//	Vector operator +( Vector A, Vector B );
//	Vector operator *( Vector A, Vector B ); //produit vectoriel
//	Vector operator *( double a, Vector B ); //produit scalaire
};

struct timedForce  //all public
{
    double startTime;
    double endTime;
    Force F;
};


#endif
