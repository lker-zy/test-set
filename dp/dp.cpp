#include <iostream>

using namespace std;

class TestInterface {
public:
	virtual int GetValue () const = 0;
};

class TestConcrete : public TestInterface {
private:
//public:
	int GetValue () const {
		cout << "TestConcrete in private" << endl;
		return 1;
	}
};

class DecorateInterface : public TestInterface {
public:
	DecorateInterface (TestInterface *obj)
		: obj_(obj)
	{

	}

protected:
	TestInterface *obj_;
};

class DecorateConcrete1 : public DecorateInterface {
public:
	DecorateConcrete1 (TestInterface *obj)
		: DecorateInterface(obj)
	{

	}

	int GetValue () const {
		int a = obj_->GetValue();
		return a+1;
	}
};

class DecorateConcrete2 : public DecorateInterface {
public:
	DecorateConcrete2 (TestInterface *obj)
		: DecorateInterface(obj)
	{

	}

	int GetValue () const {
		int a = obj_->GetValue();
		return a+1;
	}
};

#define  unused(x) ((void)(x))
int main(int argc, char **argv) {
	unused(argc);
	unused(argv);

	DecorateConcrete1 deco_obj1(new TestConcrete());
	int v = deco_obj1.GetValue();
	cout << v << endl;

	// 为什么可以这样用(装饰器的嵌套装饰)?
	// 因为装饰器具体类本身也是一个被装饰原始对象，都继承自TestInterface
	DecorateConcrete2 deco_obj2(&deco_obj1);
	int v2 = deco_obj2.GetValue();
	cout << v2 << endl;

	/*
	 * 可见，被装饰的类仍然对外可见
	 * 如果将TestConcrete::GetValue 定义为private成员，则可隐藏之
	 */
	/*
	TestConcrete test;
	int t = test.GetValue();
	cout << t << endl;
	*/

	return 0;

}
