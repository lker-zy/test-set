Design Pattern

Decorate Pattern
==============================

类图
------------------------------
![DesignPattern-Decorate](http://hi.csdn.net/attachment/201202/13/0_1329114268YYLk.gif "DesignPattern-Decorate")

Example
------------------------------
### C++

		#include <iostream>

		using namespace std;

		class Component {
		public:
			virtual int GetValue () const = 0;
		};

		class TestComponent : public Component {
		private:
		//public:
			int GetValue () const {
				cout << "TestComponent in private" << endl;
				return 1;
			}
		};

		class DecorateComponent : public Component {
		public:
			DecorateComponent (Component *obj)
				: obj_(obj)
			{

			}

		protected:
			Component *obj_;
		};

		class DecorateConcrete1 : public DecorateComponent {
		public:
			DecorateConcrete1 (Component *obj)
				: DecorateComponent(obj)
			{

			}

			int GetValue () const {
				int a = obj_->GetValue();
				return a+1;
			}
		};

		class DecorateConcrete2 : public DecorateComponent {
		public:
			DecorateConcrete2 (Component *obj)
				: DecorateComponent(obj)
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

			DecorateConcrete1 deco_obj1(new TestComponent());
			int v = deco_obj1.GetValue();
			cout << v << endl;

			// 为什么可以这样用(装饰器的嵌套装饰)?
			// 因为装饰器具体类本身也是一个被装饰原始对象，都继承自Component
			DecorateConcrete2 deco_obj2(&deco_obj1);
			int v2 = deco_obj2.GetValue();
			cout << v2 << endl;

			/*
			 * 可见，被装饰的类仍然对外可见
			 * 如果将TestComponent::GetValue 定义为private成员，则可隐藏之
			 */
			/*
			TestComponent test;
			int t = test.GetValue();
			cout << t << endl;
			*/

			return 0;

		}

### Python

		def args_deco(name):
			def lker_func_deco(func):
				def real_deco(arg):
					print 'deco name:' + name
					print 'func deco prefix'
					ret = func(arg)
					print 'func deco postfix'
				return real_deco
			return lker_func_deco


		@args_deco('deco_1')
		def ok(arg):
			print 'func ok with param:' + arg

		@args_deco('deco_2')
		def fail(arg):
			print 'func fail with param:' + arg

		ok('such a happy day')
		fail('fuck')

讨论: Python 和 C++ 的装饰器有何异同
-------------------------------------
	网上有人说，Python的装饰器和设计模式的装饰器模式不是一个概念，更甚，Python的装饰器根本不是一种设计模式的体现.</br>
	诚然，装饰器在Python里面是作为一个语法元素而存在的，Pyer们可以直接使用它来实现对一个函数对象的装饰功能, 
	而不需要像C++一样.需要自己实现公共基类、装饰类，并将被装饰对象和装饰对象进行绑定</br>

	但仔细思考其本质，他们真的有多大的区别么?以鄙人愚见,其在功能和实现上都是异曲同工，只不过python内置提供，易于使用.</br>

* 带参数的装饰器
	如上述实例python代码，args_deco既是一个带参的装饰器，那C++中是否可以实现此种功能呢？答案当然是:可以。</br>
	如果我们在原有装饰器模式的基础上，在配合工厂模式，通过不同的参数来产生不同的装饰器对象，即可实现与python中同样的功能.</br>
	</br>
	或者，我们也可以通过模板来实现</br>
	</br>
	其实，假设我们把上述python装饰器改写成如下:
		def args_deco(name):
			def lker_func_deco(func):
				def real_deco_1(arg):
					print 'deco name:' + name
					print 'func deco prefix'
					ret = func(arg)
					print 'func deco postfix'

				def real_deco_2(arg):
					print 'real_deco_2'
					print 'func deco prefix'
					ret = func(arg)
					print 'func deco postfix'

				if name == 'deco_1':
					return real_deco_1
				elif name == 'deco_2':
					return real_deco_2
			return lker_func_deco

	是不是有点工厂模式的感觉呢? </br>

* 装饰器的嵌套
	如上述示例代码，两者都可以实现装饰器的嵌套。而就其实现思想来说，也极为相似。上述C++装饰器，之所以可以嵌套，是因为所有装饰器类都是继承自Component，和被装饰类一样，所以，装饰器本身也可以作为被装饰者。Python也差不多，因为装饰器函数本身也是函数对象，所以也可以被装饰。

* 被装饰对象的不可见性
	在Python中，一个函数被装饰之后，原函数对象就不能再被直接使用了，而是被装饰器接管。C++中是否也可以做到呢？像代码中的注释一样，在具体被装饰类的实现中，将虚函数接口实现为private即可，这时候，程序员只能使用装饰器类去使用原对象的功能。</br>
	从这儿也可以看到两者在实现上的异曲同工之处，两者都是将对原对象的功能调用由装饰器对象来代理。Python装饰器通过装饰器函数产生一个新的函数对象并覆盖原函数对象，所以所有对原函数的调用最后都是调用了经过装饰器装饰的逻辑。而在C++中，通过装饰器类来代理被装饰者的功能，同时附加上自己的装饰逻辑。</br>

