#include <iostream>
#include <vector>

template<class T>

std::vector<T> move_vectors(std::vector<T>& source, std::vector<T>& dest) {
	if (source == dest) {
		return source;
	}
	//std::cout << "Moved...\n";
	//dest.resize(source.size());
	//for (auto it = source.begin(); it != source.end(); ++it){
	//	dest.push_back(*it);
	//	}
	dest = std::move(source);
	return dest;
};

int main() {
	std::vector <std::string> one = { "test_string1", "test_string2" };
	std::vector <std::string> two;
	//receive pointer
	std::cout << "&one: " << one.data() << "\t&two: " << two.data() << std::endl;
	move_vectors(one, two);
	//check elements in two
	for (auto el : two) {
		std::cout << el << " ";
	}
	//check pointers
	std::cout << "\n&one: " << one.data() << "\t&two: " << two.data() << std::endl;

	return 0;
}