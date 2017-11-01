# include <string>
# include <iostream>
using namespace std;
class Sales_dd {
	public:
		// 构造函数
		Sales_dd() = default;
		Sales_dd(const string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n) {
		}
		string isbn() const {return bookNo;}
		Sales_dd & combine(const Sales_dd & sd); // combine(const Sales_data &) 义在类外的成员函数
		int sold_num() const {return units_sold;} 
		double sold_money() const {return revenue;}
	private:
		inline double avg_price() const {return units_sold? revenue/units_sold : -1;}; // avg_price() 定义在类外的成员函数 
		string bookNo;
		int units_sold = 0;
		double revenue = 0.0;
	// 友元 一般集中定义在类的下部或者上部 
	friend ostream &print (ostream &os, const Sales_dd & item);
};

// 类外部定义成员函数 combine
Sales_dd & Sales_dd::combine(const Sales_dd & sd) {
	if (sd.isbn() == isbn()){
		units_sold += sd.units_sold;
		revenue += sd.revenue;
	}
	return *this; // 返回调用该函数的对象 
} 

// 类相关的非成员函数
Sales_dd add(const Sales_dd & d1, const Sales_dd & d2) {
	Sales_dd sum = d1;
	sum.combine(d2);
	return sum;
} 

//ostream &print (ostream &os, Sales_dd item) {
//	os << "ISBN号码:" << item.isbn() << "售出数量:" << item.sold_num()
//	<< "总金额:" << item.sold_money();
////	return os;
//}

ostream &print (ostream &os, const Sales_dd& item) {
	os << "ISBN号码:" << item.bookNo << "售出数量:" << item.units_sold
	<< "总金额:" << item.revenue;
//	return os;
}


int main() {
	Sales_dd a("Miserable World", 5, 19.99);
//	Sales_dd b("Miserable World", 100, 19.99);
//	Sales_dd b("Sunny & Rainny", 1000, 9.99);
	cout << a.isbn() << endl;
	print(cout, a);
//	auto c = add(a, b);
//	print(cout, c);
	
}
