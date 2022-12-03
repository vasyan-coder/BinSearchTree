#include <iostream>
#include <fstream>
#include <vector>
#include "Railway.h"

using namespace std;

class BinaryFile {
public:
    int CreateBinFile(string nametf, string namebf) {
        ifstream itf(nametf);
        if (!itf) return 1;
        fstream bf(namebf, ios::binary | ios::out); //����� ��� ������ � �������� ����
        Railway r;
        while (!itf.eof()) {
            itf >> r.num_train;
            itf.get();
            itf.getline(r.start_place, 20, '\n'); // 2 �������� - ������������ �����, 3 �������� - �����������
            itf.getline(r.end_place, 20, '\n');
            itf.getline(r.time, 20, '\n');
            bf.write((char*)&r, sizeof(Railway)); // 1 - ������ ������, 2 - ������� ������
        }
        itf.close();
        bf.close();
        return 0;
    }
    int outBinFile(string namebf) {
        fstream bf(namebf, ios::binary | ios::in); // ����� ��� ������ �� ��������� �����
        if (!bf) return 1;
        Railway r;
        int len = sizeof(Railway);
        bf.read((char*)&r, len);
        while (!bf.eof()) {
            cout << r.num_train << ' ' << r.start_place << endl;
            cout << r.end_place << ' ' << r.time << endl;
            bf.read((char*)&r, len);
        }
        bf.close();
        return 0;
    }
    // ���������� ����� ������ � ��������� ������
    int searchKeyInBinFIle(string namebf, int num_train) {
        fstream bf(namebf, ios::binary | ios::in); // ����� ��� ������ �� ��������� �����
        if (!bf) return 0;
        Railway r;
        int len = sizeof(Railway);
        bf.read((char*)&r, len);
        int numrecord = 1;
        while (!bf.eof()) {
            if (r.num_train == num_train)
                return numrecord;
            bf.read((char*)&r, len);
            numrecord++;
        }
        bf.close();
        return -1; // ������ � ������ ������� �� �������
    }
    int directAccess_to_the_licenceInBinFile(string namebf, int index_el, Railway& r) {

        fstream bf(namebf, ios::binary | ios::in);
        int kod;
        if (bf.is_open()) {
            int offset = (index_el - 1) * sizeof(Railway);
            bf.seekg(offset, ios::beg);
            bf.read((char*)&r, sizeof(Railway));
            if (!bf.fail()) {
                kod = 0; // ��� ������
            }
            else {
                kod = 1; // ������ (Logical error on i/o operation) ��� (Read/writing error on i/o operation)
            }
        }
        else {
            kod = 2; // ���� �� ��������
        }
        bf.close();
        return kod;
    }
    int delete_reg(string namebf, int num_train) {
        vector<Railway> vector_file;
        fstream bf(namebf, ios::binary | ios::in); // ����� ��� ������ �� ��������� �����
        if (!bf) return 1;
        Railway r;
        int len = sizeof(Railway);
        bf.read((char*)&r, len);
        while (!bf.eof()) {
            if (r.num_train == num_train)
                vector_file.push_back(r);
            bf.read((char*)&r, len);
        }
        bf.close();

        fstream bf2(namebf, ios::binary | ios::out); //����� ��� ������ � �������� ����
        for (int i = 0; i < vector_file.size(); i++)
            bf2.write((char*)&vector_file[i], sizeof(Railway)); // 1 - ������ ������, 2 - ������� ������

        bf2.close();
        return 0;
    }
};