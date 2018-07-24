#pragma once

#include <unordered_map>
#include <iostream>  

using std::unordered_map;
using std::ostream;


template <class T>
class IHT {
private:
	unsigned long size;
	unsigned long over_full_count;
	unordered_map<int, unsigned long> dictionary;

public:
	IHT(unsigned long size_val) {
		this->size = size_val;
		this->over_full_count = 0;
		std::cout << "IHT constructor called..." << std::endl;
	}

	friend ostream& operator<<(ostream& os, const IHT& obj) {
		os << "Collision table : ";
		os << " size:" << obj.size;
		os << " overfullCount:" << obj.over_full_count;
		os << " dictionary:" << obj.dictionary.size() << " items";
		return os;
	}

	unsigned long count() {
		return dictionary.size();
	}

	bool fullp() {
		return dictionary.size();
	}

	unsigned long getIndex(T& obj, bool read_only) {
		int hash_value = obj.getHash();
		if (dictionary.find(hash_value) != dictionary.end()) return dictionary[hash_value];
		else if (read_only) return 0;
		unsigned long c = this->count();
		if (c > size) {
			if (over_full_count == 0) {
				std::cout << "IHT full, starting to allow collisions";
			}
			over_full_count++;
			return hash_value%size;
		}
		else {
			dictionary[hash_value] = c;
			return c;
		}
	}

};
