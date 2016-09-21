#include "Observer.h"
#include <Algorithm>
#include <numeric>
#include <fstream>

std::string errorFile = "C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\ErrorLog.txt";
//============================= MaterialElement Observer ===============================

Observer::~Observer()
{}

bool Observer::operator ==(const Observer & obs) const
{
	return CenterOfMassPosition == obs.CenterOfMassPosition&&CenterOfMassVelocity == obs.CenterOfMassVelocity		;
}


//============================= MaterialPoint Observer ===============================

MaterialPointObserver::~MaterialPointObserver()
{}
bool MaterialPointObserver::operator ==(const MaterialPointObserver & obs)
{
	return Observer::operator ==(obs) && Element == obs.Element;
}

Point MaterialPointObserver::position(double dt) const
{
	Vect acc = (resultant() + resultant(dt))*0.5;
	try { acc = acc / Element.Mass; }
	catch (std::domain_error e)
	{
		std::ofstream logFile(errorFile, std::ofstream::out);
		if (!logFile.is_open())
		{
			throw std::ios_base::failure("Issue logging errors");
		}
		else 
		{
			logFile << e.what();
		}
	}
	return Point( acc*0.5*dt*dt + CenterOfMassVelocity*dt + CenterOfMassPosition);
}

std::vector<double> MaterialPointObserver::descriptionStream() const
{
	std::vector<double> res;
	std::vector<double> temp = CenterOfMassPosition.coordStream();
	res.insert(res.end(), temp.begin(), temp.end());
	temp = CenterOfMassVelocity.coordStream();
	res.insert(res.end(), temp.begin(), temp.end());
	res.push_back(Element.Mass);
	res.push_back(Element.Charge);
	return res;
}

void MaterialPointObserver::increment(double currentTime, double dt, double precision)
{
	if (dt <= 0) { throw std::invalid_argument("time increment must be strictly positive"); }

	int n = Calc.samplesNb(precision, dt)+1;
	double step = dt / ((double)n);

	std::vector <Vect> Accelerations = resultants(currentTime, step, n);
	std::transform(Accelerations.begin(), Accelerations.end(), Accelerations.begin(),
		[m = Element.Mass](Vect d)->Vect { return d / m; });

	std::vector <Vect> diffVelocity = Calc.finDiffIntegration(Accelerations, step);
	std::transform(diffVelocity.begin(), diffVelocity.end(), diffVelocity.begin(),
		[v0 = CenterOfMassVelocity](Vect d) -> Vect { return d + v0; });
	CenterOfMassVelocity = diffVelocity.back();

	std::vector <Vect> diffPosition = Calc.finDiffIntegration(diffVelocity, step);
	CenterOfMassPosition = CenterOfMassPosition + diffPosition.back();
}

void MaterialPointObserver::incrementRT(double dt)
{
	/*	std::vector <Vect> Accelerations = Element.resultants(dt, 0.1*dt);
		std::transform(Accelerations.begin(), Accelerations.end(), Accelerations.begin(),
			[m = Element.Mass](Vect d)->Vect { return d / m; });

		std::vector <Vect> diffVelocity = Calc.finDiffIntegration(Accelerations,);
		std::transform(diffVelocity.begin(), diffVelocity.end(), diffVelocity.begin(),
			[v0 = CenterOfMassVelocity](Vect d) -> Vect { return d + v0; });
		CenterOfMassVelocity = diffVelocity.back();

		std::vector <Vect> diffPosition = Calc.finDiffIntegration(diffVelocity);
		CenterOfMassPosition = CenterOfMassPosition + diffVelocity.back();
	*/
}

void MaterialPointObserver::addAction(std::shared_ptr<ActionOnPoint> &action)
{
	Element.addAction(action);
}

Vect  MaterialPointObserver::resultant(double t) const
{
	auto Position = Vect(Point(0, 0, 0), CenterOfMassPosition);
	Vect res(0.0, 0.0, 0.0);
	for (auto action : Element.ExternalActions)
	{
		res = res + action->force(Position, t);
	}
	return res;
}

std::vector <Vect>  MaterialPointObserver::resultants(double currentTime, double dt, int n) //n intervals, n+1 points
{
	std::vector <Vect> res = {};
	for (int i = 0; i <= n; i++)
	{
		res.push_back(resultant(currentTime+i*dt));
	}
	return res;
}