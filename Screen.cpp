# include <string>
# include <iostream>
# include <vector> 
using namespace std;

class Screen {
	public:
		using pos = string::size_type;
		//typedef string::size_type pos;
		Screen() = default;
		// �����ó�content{ht*wd, c} ��ϸ����Ϊɶ 
		Screen(pos ht, pos wd, char c): height{ht}, width{wd}, content(ht*wd, c)
		{	}
		
		// set()���أ�����*this
		Screen & set(char);
		Screen & set(pos, pos, char); //���Բ�д���������� 
		
		// ��ӡdisplay
		void display(ostream &) const; 
		
		//���س�Ա����get ��ʽ���� 
		char get() const {return content[cursor];}
		
		inline char get(pos ht, pos wd) const; //��ʽ������Ա���� 
		
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
	return *this; // ����ֵ����ʽ���ض��� 
}

// �����ڲ�����Ϊinline 
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
	os << "contentΪ��" << content << "��ǰλ��Ϊ��" << height << " " << width;
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
