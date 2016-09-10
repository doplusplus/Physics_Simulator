// ManagedClasses.h
#pragma once

#include "../SimModule/Model.h"
#include <msclr\marshal_cppstd.h>

//#include <string>

using namespace System;


namespace ManagedClasses {

	public ref class ManagedModel
	{
		Model *SimModel;


		// TODO: Add your methods for this class here.
	public:

		typedef double coord[3];

		ManagedModel()
		{
			SimModel = new Model();
		}

		~ManagedModel() { this->!ManagedModel(); }
		!ManagedModel() { delete SimModel; }

		void addMaterialPoint(double x, double y, double z, double Vx, double Vy, double Vz, double mass, double charge_)
		{
			SimModel->addMatPoint(Point(x, y, z), Vect(Vx, Vy, Vz), mass, charge_);
		}

		void addActionPoint(unsigned int elementReference, double Ax, double Ay, double Az)
		{
			SimModel->addActionOnPoint(elementReference, Vect(Ax, Ay, Az));
		}

		void addMaterialRigidSolid(double x, double y, double z, double Vx, double Vy, double Vz, double mass, double charge_)
		{}

		void addActionRigidSolid(unsigned int elementReference, double Ax, double Ay, double Az)
		{}

		/*String^ description()
		{
			String^ result=gcnew String(SimModel->getDescription().c_str());
			return result;
		}*/

		array<double>^ getCoordinates()
		{
			std::vector<double> tempVec = SimModel->getCoordinate();
			const int SIZE = tempVec.size();
			array<double> ^tempArr = gcnew array<double>(SIZE);
			for (int i = 0; i < SIZE; i++)
			{
				tempArr[i] = tempVec[i];
			}
			return tempArr;
		}

		/*void stepSim(double displayStep)
		{
			SimModel->simulate(displayStep);
		}*/

		void SimulateToFileOnly(double duration, double outputStep, double accuracy, String^ target)
		{
		/*	using namespace Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(target)).ToPointer();
			std::string targ = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));*/

			std::string *filelocation = new std::string("C:\\Users\\Doz\\Source\\Repos\\Physics_Simulator\\ConsoleEntryPoint\\IOTestFile.txt");
		//	targ.append( msclr::interop::marshal_as<std::string>(target));
			SimModel->simulate(duration, outputStep, *filelocation, accuracy);
			int a = 4;
			a = 3;

		}
	
		bool RTIncrement(double dt, int SampSize)
		{
			return SimModel->RTIncrement(dt, SampSize);
		}
	};
}
