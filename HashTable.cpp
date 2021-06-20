#include <iostream>
#include <cstring>
using namespace std;


template <class Tkey, class Tvalue>
class HashTable {
	struct ListElem {
		Tkey key;
		Tvalue value;
		ListElem* next;
	};
	class List {
	public:
		ListElem* first;
		List() { first = NULL; }
		void add(Tkey key, Tvalue value) {
			if (!first) {
				first = new ListElem;
				first->key = key;
				first->value = value;
				first->next = NULL;
				return;
			}
			ListElem* tmp = new ListElem;
			tmp->key = key;
			tmp->value = value;
			tmp->next = first;
			first = tmp;
		}
		void delelem(Tkey key) {
			if (!first)
				return;
			if (!first->next) {
				delete first;
				first = NULL;
				return;
			}
			if (first->key == key) {

				first = first->next;
				return;
			}
			ListElem* tmp = first;
			while (tmp) {
				if (key == tmp->next->key) {
					if (tmp->next->next)
						tmp = tmp->next->next;
					else
						tmp->next = NULL;
					delete tmp->next;
				}
				tmp = tmp->next;
			}
		}
		void print() {
			ListElem* tmp = first;
			while (tmp) {
				cout << tmp->value << "  ";
				tmp = tmp->next;
			}
		}
	};
	List* arr;
	int current;
	int size;
	int hashT(Tkey key) {
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;

		for (int sizeOF = 0; sizeOF < sizeof(key); sizeOF++) {
			hash = hash * a + key;
			a *= b;
		}
		return hash % size;
	}
public:
	HashTable() {
		size = 19;
		current = 0;
		arr = new List[size];
	}
	HashTable(int size) {
		arr = new List[size];
		this->size = size;
		current = 0;
	}
	~HashTable() { if (arr) delete[] arr; }
	void add(Tkey key, Tvalue value) {
		if (hashT(key) > size) {
			List* tmp;
			tmp = arr;
			delete[] arr;
			arr = new List[hashT(key) * 2];
			for (int i = 0; i < size; i++)
				arr[i] = tmp[i];
			size = hashT(key) * 2;
		}
		arr[hashT(key)].add(key, value);
		current++;
		if ((current * 100 / size) > 75) {
			int sizetmp = size;
			size *= 3;
			List* tmp;
			tmp = arr;
			arr = new List[size];
			for (int i = 0; i < sizetmp; i++) {
				ListElem* tmpp = tmp[i].first;
				while (tmpp) {
					arr[hashT(tmpp->key)].add(tmpp->key, tmpp->value);
					tmpp = tmpp->next;
				}
			}
			delete[] tmp;
		}
	}
	Tvalue find(Tkey key) {
		if (!arr[hashT(key)].first)
			return NULL;
		if (arr[hashT(key)].first) {
			if (!arr[hashT(key)].first->next)
				if (arr[hashT(key)].first->key == key)
					return arr[hashT(key)].first->value;
				else return NULL;
			else {
				ListElem* tmp = arr[hashT(key)].first;
				while (tmp) {
					if (key == tmp->key)
						return tmp->value;
					tmp = tmp->next;
				}
			}
		}
		return NULL;
	}
	void del(Tkey key) { arr[hashT(key)].delelem(key); }
	void print() {
		for (int i = 0; i < size; i++) {
			if (arr[i].first) {
				cout << i << ") ";
				arr[i].print();
				cout << endl;
			}
		}
	}
};

template <class Tvalue>
class HashTable<const char*, Tvalue> {
	struct ListElem {
		const char* key;
		Tvalue value;
		ListElem* next;
	};
	
	class List {
	public:
		ListElem* first;
		List() { first = NULL; }
		void add(const char* key, Tvalue value) {
			if (!first) {
				first = new ListElem;
				first->key = key;
				first->value = value;
				first->next = NULL;
				return;
			}
			ListElem* tmp = new ListElem;
			tmp->key = key;
			tmp->value = value;
			tmp->next = first;
			first = tmp;
		}
		void delelem(const char* key) {
			if (!first)
				return;
			if (!first->next) {
				delete first;
				first = NULL;
				return;
			}
			if (!strcmp(first->key, key)) {
				first = first->next;
				return;
			}
			ListElem* tmp = first;
			while (tmp) {
				if (!strcmp(tmp->next->key, key)) {
					if (tmp->next->next)
						tmp = tmp->next->next;
					else
						tmp->next = NULL;
					delete tmp->next;
				}
				tmp = tmp->next;
			}
		}
		void print() {
			ListElem* tmp = first;
			while (tmp) {
				cout << tmp->value << "  ";
				tmp = tmp->next;
			}
		}
	};
	List* arr;
	int current;
	int size;
	int	hashT(const char* string) {
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;

		for (; *string; string++) {
			hash = hash * a + (int)(unsigned char)string;
			a *= b;
		}
		return hash % size;
	}
public:
	HashTable() {
		size = 19;
		current = 0;
		arr = new List[size];
	}
	HashTable(int size) {
		arr = new List[size];
		this->size = size;
		current = 0;
	}
	void add(const char* key, Tvalue value) {
		if (hashT(key) > size) {
			List* tmp;
			tmp = arr;
			delete[] arr;
			arr = new List[hashT(key) * 2];
			for (int i = 0; i < size; i++)
				arr[i] = tmp[i];
			size = hashT(key) * 2;
		}
		arr[hashT(key)].add(key, value);
		current++;
		if ((current * 100 / size) > 75) {
			int sizetmp = size;
			size *= 3;
			List* tmp;
			tmp = arr;
			arr = new List[size];
			for (int i = 0; i < sizetmp; i++) {
				ListElem* tmpp = tmp[i].first;
				while (tmpp) {
					arr[hashT(tmpp->key)].add(tmpp->key, tmpp->value);
					tmpp = tmpp->next;
				}
			}
			delete[] tmp;
		}
	}
	Tvalue find(const char* key) {
		if (!arr[hashT(key)].first)
			return NULL;

		if (arr[hashT(key)].first) {
			if (!arr[hashT(key)].first->next)
				if (!strcmp(key, arr[hashT(key)].first->key))
					return arr[hashT(key)].first->value;
				else return NULL;
			else {
				ListElem* tmp = arr[hashT(key)].first;
				while (tmp) {
					if (!strcmp(key, tmp->key))
						return tmp->value;
					tmp = tmp->next;
				}
			}
		}
	}
	void del(const char* key) { arr[hashT(key)].delelem(key); }
	void print() {
		for (int i = 0; i < size; i++) {
			if (arr[i].first) {
				cout << i << ") ";
				arr[i].print();
				cout << endl;
			}
		}
	}
	~HashTable() { if (arr) delete[] arr; }
};


int main()
{
	int arr[10];
	short arr2[10];
	HashTable<int, int> test;
	for (int i = 0; i < 10; i++) {
		arr[i] = rand() % 1000 + 1;
		cout << arr[i] << "  ";
		test.add(arr[i], arr[i]);
	}
	cout << endl;
	test.print();
	test.del(468);

	test.del(465);
	test.del(479);
	test.print();
	cout << "FIND " << test.find(42) << endl;
	/*cout << "CHAR* TEST" << endl;
	HashTable<const char*, int> test2;
	char* abc = new char[40];
	abc = "CHAR* TEST";
	test2.add(abc, 123);
	test2.add("TEST2", 222);
	test2.print();
	test2.del("TEST2");
	test2.print();
	cout << "FIND CHAR " << test2.find("CHAR* TEST");*/
	return 0;
}
