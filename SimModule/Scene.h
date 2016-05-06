#ifndef SCENE
#define SCENE

#include <unordered_set>
#include "MaterialElement.h"


class Scene
{
	friend class Model;
	friend class Model2;
public:

	//Constructors and destructor
	Scene();
	Scene(std::unordered_set<MaterialElement*> content);
	~Scene();

	//Display
	void consoleShow() const;

	//Operators
	bool operator ==(Scene s) const;
	std::vector<double> streamCoordinate()
	{
		std::vector<double> res;
		std::vector<double> temp;
		for (auto elmt : Content)
		{
			temp = elmt->streamCoord();
			res.insert(res.begin(), temp.begin(), temp.end());
		}
		return res;
	}

private:
	std::unordered_set<MaterialElement*> Content;
	double Time = 0;
	
	void addMatPoint(MaterialPoint *Mp);
	void addSolid(Solid *Content) {};
	
	void forwardTime(double dt);
};


#endif