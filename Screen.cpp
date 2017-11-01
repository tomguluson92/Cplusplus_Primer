# include <string>
# include <iostream>
# include <vector> 
using namespace std;

class Screen {
	public:
		using pos = string::size_type;
		//typedef string::size_type pos;
		Screen() = default;
		// 不能用成content{ht*wd, c} 仔细想想为啥 
		Screen(pos ht, pos wd, char c): height{ht}, width{wd}, content(ht*wd, c)
		{	}
		
		// set()重载，返回*this
		Screen & set(char);
		Screen & set(pos, pos, char); //可以不写出参数名称 
		
		// 打印display
		void display(ostream &) const; 
		
		//重载成员函数get 隐式内联 
		char get() const {return content[cursor];}
		
		inline char get(pos ht, pos wd) const; //显式内联成员函数 
		
		Screen & move(pos r, pos c);
		
	private:
		pos cursor = 0;
		pos height = 0, width = 0;
		string content;
	
};

inline
Screen & Screen::move(pos a, pos b) {
	pos row = a * width;
	cursor = row + b;
	return *this; // 以左值的形式返回对象 
}

// 在类内部声明为inline 
char Screen::get(pos r, pos c) const {
	pos row = r * width;
	return content[row+c];
}

inline Screen& Screen::set(char c) {
	content[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos a, pos b, char c) {
	content[a*width+b] = c;
	return *this;
}


void Screen::display(ostream &os) const{
	os << "content为：" << content << "当前位置为：" << height << " " << width;
}


int main() {
	Screen sc(5, 5, 'X');
	sc.move(4,0).set('#').display(cout);
	cout << "\n";
	sc.display(cout);
	cout << "\n";
//	cout << sc.get() << endl;
//	sc.display(cout);
	
}
