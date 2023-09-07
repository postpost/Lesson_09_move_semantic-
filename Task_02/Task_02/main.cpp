#include <iostream>
#include <string>

class big_integer {
private:
	int number_;
	int* ptr_;
public:
	//конструктор
	big_integer(std::string str) {
		number_ = stoi(str);
		ptr_ = new int[1];
	}
	//деструктор
	~big_integer() {
		delete[] ptr_;
	}
	//конструктор перемещения (move ctr)
	big_integer(big_integer&& other) {
		number_ = other.number_;
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
	}
	//перемещающий оператор присваивания (move assignment)
	big_integer& operator=(big_integer&& other) {
		if (this == &other)
			return *this;
		delete[] ptr_;
		number_ = other.number_;	
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
		return *this;
	}

	//оператор сложения двух больших чисел
	big_integer operator+(const big_integer& other) {
		number_ = number_ + other.number_;
		std::string str_param = std::to_string(number_);
		return big_integer(str_param);
	}

	//оператор умножения на число (справа)
	big_integer operator*(const int& value) {
		number_ = number_ * value;
		std::string str_param = std::to_string(number_);
		return big_integer(str_param);
	}

	//оператор умножения на число (слева)
	friend big_integer operator*(int value, big_integer& other) {
		int res = value * other.number_;
		std::string str = std::to_string(res);
		return big_integer(str);
	};

	//перегрузка оператора вывода на экран
	friend std::ostream& operator << (std::ostream& os, const big_integer& bi)
	{
		return os << bi.number_ << std::endl;
	}
};

int main() {

	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");
	auto result = number1 + number2; //number1 changed
	auto mult0 = number1*3;
	auto mult1 = 10 * number2;
	std::cout << result; // 193099
	std::cout << "muliply_0: " << mult0 << "multiply_1: " << mult1 << std::endl;
	return 0;
}