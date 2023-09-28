#include <iostream>
#include <string>
#include<vector>

class big_integer {
private:
	std::string digits_ = "";
	int length;

public:
	//конструктор_1
	big_integer(std::string str): digits_{str}
	{
		length = str.length();
	}
	//конструктор_2
	big_integer() {

	}
	//деструктор
	~big_integer() {
		//delete[] ptr_;
	}
	//конструктор перемещения (move ctr)
	big_integer(big_integer&& other) noexcept {
		digits_ = std::move(other.digits_);
	}
	//перемещающий оператор присваивания (move assignment)
	big_integer& operator=(big_integer&& other) noexcept {
		if (this == &other)
			return *this;
		length = std::move(other.length);
		digits_ = std::move(other.digits_);
		return *this;
	}

	//оператор сложения двух больших чисел
	big_integer operator+(const big_integer& other) {
		int max_length = 0;
		if (length <= other.length)
			int max_length = other.length;
		else max_length = length;

		std::string res = "";
		int carry = 0; //carry flag
		int last_a = 0, last_b = 0;

		//sum
		for (int i = 0; i < max_length; ++i) {
			last_a = i < length ? digits_[length-1 - i] - '0' : 0;
			last_b = i < other.length ? other.digits_[other.length-1 - i] - '0' : 0;
			//sum of two last digits
			res = char((last_a + last_b + carry) % 10 + '0') + res;
			//if num > 9 then carry will be 1st digit
			carry = (last_a + last_b + carry) / 10;
		}
		if (carry)
			res = char(carry + '0') + res;
		return big_integer(res);
	}

	//оператор умножения на полудлинное число (справа)
	big_integer operator*(const long long& value) {
		int carry = 0;
		int last_digit;
		std::string res = "";
		for (int i = digits_.size() - 1; i >= 0; --i) {
			last_digit = int(digits_[i] - '0') * value + carry;
			carry = last_digit / 10;
			res = char(last_digit % 10 + '0') + res;
		}
		while (carry)
			res = char(carry % 10 + '0') + res;
		carry /= 10;
		return res;
	}

	//оператор умножения на полудлинное число (слева)
	friend big_integer operator*(const long long& left, big_integer& right) {
		int carry = 0;
		int last_digit;
		std::string res = "";
		for (int i = right.digits_.size() - 1; i >= 0; --i) {
			last_digit = int(right.digits_[i] - '0') * left + carry;
			carry = last_digit / 10;
			res = char(last_digit % 10 + '0') + res;
		}
		while (carry)
			res = char(carry % 10 + '0') + res;
		carry /= 10;
		return res;
	};

	//оператор умножения двух больших чисел
	friend big_integer& operator*=(big_integer& left, big_integer& right) {
		if (left.digits_ == "" || left.digits_ == "0")
			return right;
		else if (right.digits_ == "" || right.digits_ == "0")
			return left;
		int n = left.digits_.size(), m = right.digits_.size();
		std::vector<int> vi(n + m, 0);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				//Здесь (left.digits_[i]) и (right.digits_[j]) являются символами
				//вычесть '0' из каждого символа, чтобы получить численное значение
				//иначе это символы ASCII
				vi[i + j] += (left.digits_[i] - '0') * (right.digits_[j] - '0');
			}
		}
		n += m;
		left.digits_.resize(vi.size());
		for (int k, i = 0, t = 0; i < n; ++i) {
			k = t + vi[i];
			vi[i] = k % 10;
			t = k / 10;
			left.digits_[i] = vi[i] + '0'; //vi[i] - это int, и вы пытаетесь присвоить его символьной переменной.
		}
		for (int i = n - 1; i >= 1 && !vi[i]; ++i)
			left.digits_.pop_back();
		left.digits_.shrink_to_fit();
		return left;
	}

	friend big_integer operator* (big_integer& left, big_integer& right) {
		big_integer temp;
		temp.digits_ = left.digits_;
		temp *= right;
		return temp;
	}

	//перегрузка оператора вывода на экран
	friend std::ostream& operator << (std::ostream& os, const big_integer& bi)
	{
		return os << bi.digits_ << std::endl;
	}
};

int main() {

	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");
	auto result = number1 + number2; 
	auto num_1 = big_integer("6459134876312645915375645915243562819842157684951435975462712564565467216417897215674812546818645 ");
	auto num_2 = big_integer("5643269487 ");
	auto mult0 = num_1 * num_2;
	std::cout << '\n' << result << std::endl; // 193099
	std::cout << "mult_0: " << mult0 << std::endl;
	return 0;
}