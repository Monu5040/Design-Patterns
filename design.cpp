//singleton
#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
/*Not thread safe
class Singleton {
private:
	Singleton(){}
	static Singleton* p_instance;
public:
	static Singleton* getInstance(){
		if(p_instance == nullptr){
			p_instance = new Singleton;
		}
		return p_instance;
	}

};
Singleton* Singleton::p_instance=nullptr;
int main() {
	Singleton* instance = Singleton::getInstance();
	Singleton* instance1 = Singleton::getInstance();
	cout<<instance<<endl;
	cout<<instance1<<endl;
}*/


// Thread safe
// class Singleton {
// private:
// 	Singleton(){}
// public:
// 	static Singleton& getInstance(){
// 		static Singleton p_instance;
// 		return p_instance;
// 	}
// };

// int main() {
// 	Singleton& instance = Singleton::getInstance();
// 	Singleton& instance1 = Singleton::getInstance();
// 	cout<<&instance<<endl;
// 	cout<<&instance1<<endl;
// }

/* **********Prototype Design Pattern************ */
/*
class Prototype {
public:
	virtual Prototype* clone()=0;
};

class Student: public Prototype{
private:
	
	int roll;
	int id;
public:
	string name;
	Student(string name, int roll, int id):name(name),roll(roll),id(id){}

	Prototype* clone() {
		return new Student(name, roll,id);
	}
};

int main(){
	Prototype* obj = new Student("Monu", 5040, 1);
	// static_cast<Student*>(new_obj): This cast converts the base class pointer (Prototype*) to the derived class pointer (Student*), which allows you to access Student-specific members like name.
	Student* new_obj = static_cast<Student*>(obj->clone());
	cout<<obj<<" "<<new_obj->name<<endl;
}
*/


/* ********* Builder Design Pattern ********* */
/*
class Student;

class StudentBuilder {
public:
	int id;
	string name;
	int roll;
	int marks;
	vector<string>subjects;

	StudentBuilder* setId(int new_id){
		this->id = new_id;
		return this;
	}

	StudentBuilder* setName(string name) {
		this->name = name;
		return this;
	}

	StudentBuilder* setRoll(int roll) {
		this->roll = roll;
		return this;
	}

	StudentBuilder* setMarks(int marks) {
		this->marks = marks;
		return this;
	}
	virtual StudentBuilder* setSubject() = 0;
	Student* build();
};

class EngineerBuilder : public StudentBuilder {
public:
	StudentBuilder* setSubject() override{
		subjects.push_back("VLSI");
		subjects.push_back("Signal");
		return this;
	}
};

class MBABuilder : public StudentBuilder {
public:
	StudentBuilder* setSubject() override{
		subjects.push_back("HR");
		subjects.push_back("Finance");
		return this;
	}
};

class Student {
private:
	int id;
	int marks;
	vector<string>subjects;
public:
	string name;
	int roll;
	Student(StudentBuilder* builder) {
		id = builder->id;
		name = builder->name;
		roll = builder->roll;
		marks = builder->marks;
		subjects = builder->subjects;
	}
};

Student* StudentBuilder:: build() {
	return new Student(this);
}

class Director {
	StudentBuilder* stu_builder;
public:
	
	Director(StudentBuilder* stu_builder) : stu_builder(stu_builder){}

	Student* createEngineerObj(){
		return stu_builder->setSubject()->setMarks(102)->setName("Monu")->build();
	}

	Student* createMBAObj(){
		return stu_builder->setSubject()->setMarks(102)->setName("Monu")->build();
	}

	Student* createStudentObj(string name){
		if(name == "Eng"){
			return createEngineerObj();
		} else if(name == "MBA") {
			return createMBAObj();
		}
		return nullptr;
	}

	

};

int main() {
	StudentBuilder* eng_builder = new EngineerBuilder();
	Director* dir = new Director(eng_builder);
	Student* obj = dir->createStudentObj("Eng");
	cout<<obj->name<<" "<<obj->roll<<endl;
	delete eng_builder;
	delete dir;
	delete obj;
}
*/

/* ******* Factory Design Pattern ******** */
/*
class Shape {
public:
	virtual void draw() = 0;
};

class Circle : public Shape {
public:
	void draw() override {
		cout<<"Drawing Circle"<<endl;
	}
};

class Rectangle : public Shape {
public:
	void draw() override {
		cout<<"Drawing Rectangle"<<endl;
	}
};

class Square : public Shape {
public:
	void draw() override {
		cout<<"Drawing square"<<endl;
	}
};


enum class ShapeType {
	CIRCLE,
	SQUARE,
	RECTANGLE
};

class ShapeFactory {
public:
	Shape* getShape(ShapeType shape) {
		switch(shape) {
			case ShapeType::CIRCLE :
				return new Circle();
			case ShapeType::SQUARE :
				return new Square();
			case ShapeType::RECTANGLE :
				return new Rectangle();
			default:
				return nullptr;
		}
	}
};


int main() {
	ShapeFactory* factory = new ShapeFactory();
	Shape* shape_obj = factory->getShape(ShapeType::CIRCLE);
	shape_obj->draw();
	Shape* shape_obj1 = factory->getShape(ShapeType::SQUARE);
	shape_obj1->draw();

}
*/

/* ********** Abstarct factory ********** */
/*
enum class FactoryType {
	LUXURY,
	NORMAL
};

enum VehicleType {
	BMW,
	MERCEDES,
	ALTO,
	WAGONR
};

class Vehicle {
public:
	virtual int speed() = 0;
	virtual void specialFeature() = 0;
};

class BmwVehicle : public Vehicle {
public:
	int speed() {
		return 250;
	}

	void specialFeature() {
		cout<<"BMW special"<<endl;
	}
};

class MercedesVehicle : public Vehicle {
public:
	int speed() {
		return 350;
	}

	void specialFeature() {
		cout<<"Mercedes special"<<endl;
	}
};

class AltoVehicle : public Vehicle {
public:
	int speed() {
		return 150;
	}

	void specialFeature() {
		cout<<"Alto special"<<endl;
	}
};

class WagonrVehicle : public Vehicle {
public:
	int speed() {
		return 160;
	}

	void specialFeature() {
		cout<<"Wagonr special"<<endl;
	}
};

class VehicleTypeFactory {
public:
	virtual Vehicle* getVehicle(VehicleType) = 0;
};

class LuxuryFactoryVehicle : public VehicleTypeFactory {
public:
	Vehicle* getVehicle(VehicleType type) {
		switch(type) {
			case VehicleType::BMW:
				return new BmwVehicle();
			case VehicleType::MERCEDES:
				return new MercedesVehicle();
			default:
				return nullptr;
		}
	}
};

class OrdinaryFactoryVehicle : public VehicleTypeFactory {
public:
	Vehicle* getVehicle(VehicleType type) {
		switch(type) {
			case VehicleType::ALTO:
				return new AltoVehicle();
			case VehicleType::WAGONR:
				return new WagonrVehicle();
			default:
				return nullptr;
		}
	}
};

class VehicleFactory {
public:
	VehicleTypeFactory* vehicle_fact_type;
	VehicleFactory(VehicleTypeFactory* vehicle_fact_type) : vehicle_fact_type(vehicle_fact_type) {}
};

int main() {
	VehicleTypeFactory* factory_type = new LuxuryFactoryVehicle();
	VehicleFactory* v_factory = new VehicleFactory(factory_type);
	Vehicle* v_obj = v_factory->vehicle_fact_type->getVehicle(VehicleType::BMW);
	cout<<v_obj->speed();
}
*/

/* ******* Structural Design pattern ******* 

	************** 1. Proxy Design Pattern *********** */
/*
class Operation {
public:
	virtual int performOperation(int) = 0;
};

class RealOperation: public Operation {
public:
	int performOperation(int x) override {
		return x+1;
	}

};

class ProxyOperation: public Operation {
private:
	RealOperation* real = nullptr;
	
public:
	RealOperation* createObj() {
		if(real == nullptr) {
			real = new RealOperation();
		}
		return real;
	}

	int performOperation(int x) override {
		cout<<"Performing operation for " <<x<<endl;
		int res = real->performOperation(x);
		cout<<"Operation ended"<<endl;
		return x*2;
	}
};

int main() {
	ProxyOperation* proxy = new ProxyOperation();
	RealOperation* real_obj = proxy->createObj();
	cout<<real_obj->performOperation(5)<<endl;
	cout<<proxy->performOperation(5)<<endl;
}
*/

/*  ******** 2. Bridge Design Pattern ******* */
/*
class Renderer {
public:
	virtual void renderShape(string) = 0;
};

class WindowRenderer: public Renderer {
public:
	void renderShape(string type) {
		cout<<"Drawing "<<type<<" on Window"<<endl;
	}
};

class LinuxRenderer: public Renderer {
public:
	void renderShape(string type) {
		cout<<"Drawing "<<type<<" on Linux"<<endl;
	}
};


class Shape {
protected:
	Renderer* renderer;
public:
	Shape(Renderer* renderer) : renderer(renderer){}
	virtual void draw() = 0;
};

class Circle : public Shape {
public:
	Circle(Renderer* renderer) : Shape(renderer){}
	void draw() override {
		renderer->renderShape("Circle");
	}
};

class Square : public Shape {
public:
	Square(Renderer* renderer) : Shape(renderer){}
	void draw() override {
		renderer->renderShape("Square");
	}
};


int main() {
	Shape* shape = new Circle(new WindowRenderer());
	shape->draw();
}
*/

/* ******* 3. Fascade Design Pattern *******/
/*
class Product {
public:
	string getProduct() {
		return "TV";
	}
};

class Payment {
public:
	void makePayment() {
		cout<<"making payment"<<endl;
	}
};

class Invoice {
public:
	int generateInvoice() {
		return 199;
	}
};

class Notification {
public:
	void sendNotification(int x) {
		cout<<"Product purchsed successfully and price is "<<x<<endl;
	}
};

class FascadeLayer {
private:
	Product* product;
	Payment* payment;
	Notification* notification;
	Invoice* invoice;
public:
	FascadeLayer(){
		product = new Product();
		payment = new Payment();
		notification = new Notification();
		invoice = new Invoice();
	}
	void createOrder() {
		product->getProduct();
		payment->makePayment();
		int price = invoice->generateInvoice();
		notification->sendNotification(price);
	}

};

int main() {
	FascadeLayer* obj = new FascadeLayer();
	obj->createOrder();
}
*/

/* *************4. Adapter Design Pattern *********** */
/*
class WeighMachine {
public:
	int calculateWeightKG(int weight) {
		return weight/1000;
	}
};

class Adapter {
private:
	WeighMachine* machine;
public:
	Adapter(WeighMachine* machine):machine(machine){};

	int calculateWeightGram(int weight) {
		int res = machine->calculateWeightKG(weight);
		return res*1000;
	}

};

int main() {
	Adapter* obj = new Adapter(new WeighMachine());
	cout<<obj->calculateWeightGram(50000000)<<endl;
}
*/

/* ******** 5. Composite Design Pattern ************ */
/*
class FileSystem {
public:
	virtual void ls() = 0;
};

class File : public FileSystem {
private:
	string file;
public:
	File(string file) : file(file){}

	void ls() override {
		cout<<file<<endl;
	}
};

class Directory : public FileSystem {
private:
	vector<FileSystem*> file_obj;
	string name;
public:
	Directory(string name):name(name){}

	void ls() override {
		cout<<name<<"/";
		for(FileSystem* obj : file_obj) {
			obj->ls();
		}
	}
	void addDirectory(FileSystem* obj) {
		file_obj.push_back(obj);
	}
};

int main() {
	FileSystem* file = new File("abc.mp4");
	file->ls();
	Directory* dir_1 = new Directory("LLD");
	dir_1->ls();
	cout<<endl;
	dir_1->addDirectory(file);
	dir_1->ls();

}
*/
/* ******** 6. Decorator Design Pattern ************** */
/*
class BasePizza {
public:
	virtual int price() = 0;
};

class Farmhouse : public BasePizza {
public:
	int price() override {
		return 50;
	}
};

class VegDelight : public BasePizza {
public:
	int price() override {
		return 150;
	}
};

class Margherita : public BasePizza {
public:
	int price() override {
		return 75;
	}
};

class Decorator: public BasePizza {
protected:
	BasePizza* base_pizza;
public:
	Decorator(BasePizza* base_pizza): base_pizza(base_pizza) {}

};

class ExtraCheese:public Decorator {
public:
	ExtraCheese(BasePizza* base_pizza) : Decorator(base_pizza) {}

	int price() {
		return base_pizza->price() + 50;
	}
};

class ExtraChicken : public Decorator {
public:
	ExtraChicken(BasePizza* base_pizza): Decorator(base_pizza){}

	int price() override {
		return base_pizza->price() + 100;
	}
};


int main() {
	BasePizza* pizza = new VegDelight();
	cout<<pizza->price()<<endl;
	Decorator* cheese = new ExtraCheese(pizza);
	cout<<cheese->price()<<endl;
}
*/

/********** Behavioural Design Pattern ***************/
/* ************** Observer Design Pattern***********/
/*
class Observer {
public:
	virtual void productUpdate(int) = 0;
};

class TVObserver: public Observer {
public:
	void productUpdate(int count) override {
		displayOnTV(count);
	}

	void displayOnTV(int count) {
		cout<<"TV display item: "<<count<<endl;
	}
};

class MobileObserver: public Observer {
public:
	void productUpdate(int count) override {
		sendMessage(count);
	}

	void sendMessage(int count) {
		cout<<"Message sent... items : "<<count<<endl;
	}
};


class Observable {
private:
	unordered_set<Observer*>obs_list;
	int item = 0;
public:
	void addObserver(Observer* obs) {
		obs_list.insert(obs);
	}
	void removeObserver(Observer* obs) {
		obs_list.erase(obs);
	}
	int setItem(int count) {
		item = count;
	}
	void notify() {
		if(item != 0) {
			for(Observer* ob : obs_list) {
				ob->productUpdate(item);
			}
		}
	}
};

int main() {
	Observer* obs1 = new TVObserver();
	Observer* obs2 = new MobileObserver();
	Observable* obv = new Observable();
	obv->addObserver(obs1);
	obv->addObserver(obs2);
	obv->notify();
	obv->setItem(5);
	obv->notify();

}
*/

/******* 2. Chain of responsibility ***********/
/*
enum class LogLevel {
	INFO,
	DEBUG,
	WARNING,
	ERROR
};

class Logger {
private:
	Logger* next_logger;
public:
	Logger(Logger* next_logger): next_logger(next_logger) {}

	virtual void log(LogLevel level, string msg) {
		if(next_logger != nullptr) {
			next_logger->log(level, msg);
		}
	}
};


class InfoLogger : public Logger {
public:
	InfoLogger(Logger* next_logger):Logger(next_logger){}

	void log(LogLevel level, string msg) override {
		if(level == LogLevel::INFO) {
			cout<<"Info logger : "<<msg<<endl;
		} else {
			Logger::log(level,msg);
		}
	}
};

class DebugLogger : public Logger {
public:
	DebugLogger(Logger* next_logger):Logger(next_logger){}

	void log(LogLevel level, string msg) override {
		if(level == LogLevel::DEBUG) {
			cout<<"Debug logger : "<<msg<<endl;
		} else {
			Logger::log(level,msg);
		}
	}
};
class ErrorLogger : public Logger {
public:
	ErrorLogger(Logger* next_logger):Logger(next_logger){}

	void log(LogLevel level, string msg) override {
		if(level == LogLevel::ERROR) {
			cout<<"Error logger : "<<msg<<endl;
		} else {
			Logger::log(level,msg);
		}
	}
};

int main() {
	Logger* logger = new Logger(new InfoLogger(new ErrorLogger(new DebugLogger(nullptr))));
	logger->log(LogLevel::DEBUG, "This is my debug logger");
	logger->log(LogLevel::ERROR, "This is my error logger");
	logger->log(LogLevel::INFO, "This is my INFO logger");
}
*/
