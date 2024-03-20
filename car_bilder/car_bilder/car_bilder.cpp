// car_bilder.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<map>
using namespace std;

// базовый класс для летального устройства
class Aircraft
{
public:
	Aircraft(string type) {aircraftType = type;};
	virtual ~Aircraft(){}
private:
	// тип летательного устройства
	string aircraftType;
	// хранилище информации об устройстве
	map<string, string> parts;
public:
	// получение информации о конкретной части устройства
	string GetPart(const string& key) {
		if (!CheckForPart(key)) {
			throw "There is no such key!";
		}
		return parts[key];
	}
	// установка значения для конкретной части устройства
	void SetPart(const string& key, const string& value) {
		parts[key] = value;
	}
	// проверка на наличие части
	bool CheckForPart(const string& key) {
		return parts.find(key) != parts.end() ? true : false;
	}
	// отображение информации об летательном устройстве
	void Show() {
		cout << "\n====================\n";

		cout << "Aircraft Type:" << aircraftType << endl;

		cout << "Frame:" << parts["frame"] << endl;

		cout << "Engine:" << parts["engine"] << endl;

		cout << "Wheels:" << parts["wheels"] << endl;

		cout << "Doors:" << parts["doors"] << endl;
	}
};

class AircraftBuilder
{
public:
	AircraftBuilder() {}
	virtual ~AircraftBuilder() {}
protected:
	Aircraft* aircraft;
public:
	Aircraft* GetAircraft() {
		return aircraft;
	}

	virtual void BuildFrame() = 0;

	virtual void BuildEngine() = 0;

	virtual void BuildWheels() = 0;

	virtual void BuildDoors() = 0;

	virtual void BuildWings() = 0;

};

// Класс строителя для самолета.
class PlaneBuilder : public AircraftBuilder
{
public:

	virtual void BuildFrame() = 0;

	virtual void BuildEngine() = 0;

	virtual void BuildWheels() = 0;

	virtual void BuildDoors() = 0;

	virtual void BuildWings() = 0;

	virtual void BuildTail() = 0; // Добавлен хвост самолета
};

class JetBuilder : public PlaneBuilder
{
public:
	JetBuilder()
	{
		aircraft = new Aircraft("Jet");
	}
	virtual ~JetBuilder() 
	{
		delete aircraft;
	}
public:
	void BuildFrame() {
		aircraft->SetPart("frame", "Jet frame");
	}
	void BuildEngine() {
		aircraft->SetPart("engine", "Jet engine");
	}
	void BuildWheels() {
		aircraft->SetPart("wheels", "3");
	}
	void BuildDoors() {
		aircraft->SetPart("doors", "2");
	}
	void BuildWings() {
		aircraft->SetPart("wings", "2");
	}
	void BuildTail() {
		aircraft->SetPart("tail", "1"); // Добавляем хвост
	}
};

class PropellerBuilder : public PlaneBuilder
{
public:


	PropellerBuilder()
	{
		aircraft = new Aircraft("Propeller");
	}

	virtual ~PropellerBuilder()
	{
		delete aircraft;
	}
public:

	void BuildFrame() {
		aircraft->SetPart("frame", "Propeller frame");
	}

	void BuildEngine() {
		aircraft->SetPart("engine", "Propeller engine");
	}

	void BuildWheels() {
		aircraft->SetPart("wheels", "3");
	}

	void BuildDoors() {
		aircraft->SetPart("doors", "1");
	}

	void BuildWings() {
		aircraft->SetPart("wings", "2");
	}

	void BuildTail() {
		aircraft->SetPart("tail", "1"); // Добавляем хвост
	}
};

class AircraftConstructor
{
public:
	AircraftConstructor()
	{}
	~AircraftConstructor()
	{}
	void Construct(AircraftBuilder* aircraftBuilder)
	{
		aircraftBuilder->BuildFrame();
		aircraftBuilder->BuildEngine();
		aircraftBuilder->BuildWheels();
		aircraftBuilder->BuildDoors();
	}
};

int main() {
	try {
		AircraftBuilder* builder;

		AircraftConstructor* shop = new AircraftConstructor();

		builder = new JetBuilder();
		shop->Construct(builder);
		builder->GetAircraft()->Show();

		delete builder;

		builder = new PropellerBuilder();
		shop->Construct(builder);
		builder->GetAircraft()->Show();

		delete builder;
		delete shop;
	}
	catch (char* str) {
		cout << endl << str << endl;
	}

	return 0;
}
