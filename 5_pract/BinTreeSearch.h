#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Node.h"
#include "BinaryFile.h"

using namespace std;

class BinTreeSearch : public BinaryFile {
public:
	int key;
	Node* root;
	int rotate_count = 0;
public:
	// Генерация бинарного дерева поиска по данным из бинарного файла
	BinTreeSearch() {};
	BinTreeSearch(string namebf) {
		fstream bf(namebf, ios::binary | ios::in); // поток для чтения из бинарного файла
		if (!bf) return;

		// инициализация корня
		Railway r;

		int len = sizeof(Railway);
		bf.read((char*)&r, len);
		while (!bf.eof()) {
			root = addEl(root, r);
			bf.read((char*)&r, len);
		}
		bf.close();
	}

	// Распечатывание дерева
	void print(Node* el, int c) {
		if (!el) return;
		c -= 5;
		print(el->left_child, c);
		c -= 5;
		for (int i = 0; i < c; i++) {
			cout << " ";
		}
		cout << el->obj.num_train << endl;
		if (el->right_child) {
			c += 5;
		}
		print(el->right_child, c);
		return;
	}

	// Поиск по ключу с корнем p
	Node* search(Node* p, Railway* key) {
		if (key->num_train < p->obj.num_train) {
			search(p->left_child, key);
		} else if (key->num_train > p->obj.num_train) {
			search(p->right_child, key);
		} else if (key->num_train == p->obj.num_train) {
			return p;
		} else {
			return nullptr; // ключ не найден
		}
	}
	// Высота дерева
	unsigned char height(Node* p) {
		return p ? p->height : 0;
	}
	int bfactor(Node* p) {
		return height(p->right_child) - height(p->left_child);
	}
	// Фикс высоты в св-вах
	void fixheight(Node* p) {
		unsigned char hl = height(p->left_child);
		unsigned char hr = height(p->right_child);
		p->height = (hl > hr ? hl : hr) + 1;
	}
	// Правый поворот дерева
	Node* rotateRight(Node* p) {
		rotate_count++;
		Node* q = p->left_child;
		p->left_child = q->right_child;
		q->right_child = p;
		fixheight(p);
		fixheight(q);
		return q;
	}
	// Левый поворот дерева
	Node* rotateLeft(Node* q) {
		rotate_count++;
		Node* p = q->right_child;
		q->right_child = p->left_child;
		p->left_child = q;
		fixheight(q);
		fixheight(p);
		return p;
	}
	Node* balance(Node* p) {
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right_child) < 0)
				p->right_child = rotateRight(p->right_child);
			return rotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left_child) > 0)
				p->left_child = rotateLeft(p->left_child);
			return rotateRight(p);
		}
		return p; // балансировка не нужна
	}
	// Вставка ключа k в дерево с корнем p
	Node* addEl(Node* p, Railway k) {
		if (!p) return new Node(k);
		if (k.num_train < p->obj.num_train)
			p->left_child = addEl(p->left_child, k);
		else
			p->right_child = addEl(p->right_child, k);

		return balance(p);
	}
	// Поиск узла с минимальным ключом в дереве p 
	Node* getMin(Node* p) {
		return p->left_child ? getMin(p->left_child) : p;
	}
	// удаление узла с минимальным ключом из дерева p
	Node* deleteMin(Node* p) {
		if (p->left_child == 0)
			return p->right_child;
		p->left_child = deleteMin(p->left_child);
		return balance(p);
	}
	// удаление ключа k из дерева p
	Node* deleteEl(Node* p, Railway k) {
		if (!p) return 0;
		if (k.num_train < p->obj.num_train)
			p->left_child = deleteEl(p->left_child, k);
		else if (k.num_train > p->obj.num_train)
			p->right_child = deleteEl(p->right_child, k);
		else //  k == p->key 
		{
			Node* q = p->left_child;
			Node* r = p->right_child;
			delete p;
			if (!r) return q;
			Node* min = getMin(r);
			min->right_child = deleteMin(r);
			min->left_child = q;
			return balance(min);
		}
		return balance(p);
	}

	void printRotateCount() {
		cout << "Rotate count = " << rotate_count << '\n';
	}

	int exec() {
		string file_bin_name = "";
		string file_name = "";

		cout << "input file name:\n";
		cin >> file_name;
		cout << "input file bin name:\n";
		cin >> file_bin_name;

		cout << "1. addEl element in BinarySearchTree\n";
		cout << "2. deleteEl element in BinarySearchTree\n";
		cout << "3. Find element in BinarySearchTree\n";
		cout << "4. Print tree\n";
		cout << "5. Generate binary file\n";
		cout << "6. Print binary file\n";
		cout << "7. Search key in bin fIle\n";
		cout << "8. direct access to the licence in bin file\n";
		cout << "9. delete registration\n";
		cout << "Choose operation:\n";
		int x;
		cin >> x;

		int num_train;
		int index;
		Railway r;

		BinTreeSearch tree(file_bin_name);



		switch (x) {
		case 1:
			cout << "Create RegSmallBuisness object:\n";
			cout << "Input number of license:\n";
			cin >> r.num_train;
			cout << "Input name:\n";
			cin >> r.start_place;
			cout << "Input founder:\n";
			cin >> r.end_place;
			cout << "Input active_lic:\n";
			cin >> r.time;
			addEl(tree.root, r);
			break;
		case 2:
			cout << "Create RegSmallBuisness object:\n";
			cout << "Input number of license:\n";
			cin >> r.num_train;
			cout << "Input name:\n";
			cin >> r.start_place;
			cout << "Input founder:\n";
			cin >> r.end_place;
			cout << "Input active_lic:\n";
			cin >> r.time;
			deleteEl(tree.root, r);
			break;
		case 3:
			cout << "Create RegSmallBuisness object:\n";
			cout << "Input number of license:\n";
			cin >> r.num_train;
			cout << "Input name:\n";
			cin >> r.start_place;
			cout << "Input founder:\n";
			cin >> r.end_place;
			cout << "Input active_lic:\n";
			cin >> r.time;
			search(tree.root, &r);
			break;
		case 4:
			print(tree.root, tree.height(tree.root) * 5 + 5);
			break;
		case 5:
			CreateBinFile(file_name, file_bin_name);
			cout << "File created\n";
			break;
		case 6:
			outBinFile(file_bin_name);
			break;
		case 7:
			cout << "Input number of license\n";
			cin >> num_train;
			searchKeyInBinFIle(file_bin_name, num_train);
			break;
		case 8:
			cout << "Input index of notice\n";
			cin >> index;
			directAccess_to_the_licenceInBinFile(file_bin_name, index, r);
			break;
		case 9:
			cout << "Input number of license\n";
			cin >> num_train;
			delete_reg(file_bin_name, num_train);
			break;
		}
		return 0;
	}
};