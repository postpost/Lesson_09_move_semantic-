#include <iostream>
#include <string>
#include<vector>

class big_integer {
private:
	std::string digits_ = "";
	int length;

public:
	//�����������_1
	big_integer(std::string str): digits_{str}
	{
		length = str.length();
	}
	//�����������_2
	big_integer() {

	}
	//����������
	~big_integer() {
		//delete[] ptr_;
	}
	//����������� ����������� (move ctr)
	big_integer(big_integer&& other) {
		
		int n = digits_.size();
		for (int i = n - 1; i >= 0; --i) {
			digits_.push_back(other.digits_[i]);
		}
		digits_ = other.digits_;
		other.digits_ = nullptr;
	}
	//������������ �������� ������������ (move assignment)
	big_integer& operator=(big_integer&& other) {
		if (this == &other)
			return *this;
		length = other.length;
		digits_ = other.digits_;
		other.digits_ = nullptr;
		return *this;
	}

	//�������� �������� ���� ������� �����
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
			last_a = i < length ? digits_[length - i] - '0' : 0;
			last_b = i < other.length ? other.digits_[other.length - i] - '0' : 0;
			//sum of two last digits
			res = char((last_a + last_b + carry) % 10 + '0') + res;
			//if num > 9 then carry will be 1st digit
			carry = (last_a + last_b + carry) / 10;
		}
		if (carry)
			res = char(carry + '0') + res;
		return big_integer(res);
	}

	//�������� ��������� �� ����������� ����� (������)
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

	////�������� ��������� �� ����������� ����� (�����)
	//friend big_integer operator*(big_integer& left, big_integer& right) {
	//	int BASE = 1e9;
	//	std::vector<int> vc;
	//	big_integer res;
	//	vc.resize(left.digits_.size()+ right.digits_.size());
	//	/*if (vc.size() == 1) {
	//		res = left.digits_[0] * right.digits_[0];
	//		return big_integer(res);
	//	}
	//	*/
	//	for (int i = 0; i < left.digits_.size(); ++i) {
	//		int carry = 0;
	//		for (int j = 0; j < right.digits_.size(); ++j) {
	//			vc[i + j] += carry + left.digits_[i] * right.digits_[j];
	//			carry = vc[i + j] / 10;
	//			vc[i + j] %= 10;
	//			}
	//		vc.push_back(carry);
	//	}
	//	res.digits_.resize(vc.size());
	//	for (int i = 0; i < vc.size(); ++i)
	//		res.digits_[i] = vc[i];
	//	return res;
	//};

	//�������� ��������� ���� ������� �����
	friend big_integer& operator*=(big_integer& left, const big_integer& right) {
		if (NULL(left) || NULL(right))
			return left;
		int n = left.digits_.size(), m = right.digits_.size();
		std::vector<int> vi(n + m, 0);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				vi[i + j] += (left.digits_[i]) * (right.digits_[j]);
			}
		}
		n += m;
		left.digits_.resize(vi.size());
		for (int k, i = 0, t = 0; i < n; ++i) {
			k = t + vi[i];
			vi[i] = k % 10;
			t = k / 10;
			left.digits_[i] = vi[i];
		}
		for (int i = n - 1; i >= 1 && !vi[i]; ++i)
			left.digits_.pop_back();
		return left;
	}

	friend big_integer operator* (const big_integer& left, const big_integer& right) {
		big_integer temp;
		temp.digits_ = left.digits_;
		temp *= right;
		return temp;
	}

	//���������� ��������� ������ �� �����
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
	auto num_2 = big_integer("5643269487");
	auto mult0 = num_1 * num_2;
	std::cout << '\n' << result << std::endl; // 193099
	std::cout << "mult_0: " << mult0 << std::endl;
	return 0;
}