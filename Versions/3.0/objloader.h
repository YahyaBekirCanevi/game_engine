#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "transform.h"

using namespace std;

class FileReader {
private:
	string fileName;
	ifstream file;
	vector<string> lines;
	void read() {
		if (!file.is_open()) {
			cout << "Error to open File" << endl;
			return;
		}
		string line;
		while (getline(this->file, line)) {
			size_t t = line.find(' ');
			string l = line.substr(0, t);
			if (l == "v" || l == "vt" || l == "vn" || l == "f") {
				this->lines.push_back(line);
			}
		}
		cout << "Readed" << endl;
		file.close();
	}
public:
	FileReader(string _fileName) : fileName(_fileName) {
		string ext = "";
		if (size_t find = fileName.rfind('.')) {
			ext = fileName.substr(find + 1, fileName.length() - find - 1);

			if (ext == "obj") {
				this->file.open(this->fileName);
				this->read();
			}
			else {
				cout << ext << " is unwanted file type" << endl;
			}
		}
		else exit(0);
		cout << "Constructed" << endl;
	}
	~FileReader() {
		if(file.is_open()) file.close();
		fileName = "";
		lines.clear();
	}
	void print() {
		for (string line : lines) {
			cout << line << "\n";
		}
	}
	void loadObj(vector<vec3>& out_coordinates, vector<vec3>& out_uvs, vector<vec3>& out_normals) {
		vector<int> vertexIndices, uvIndices, normalIndices;
		vector<vec3> coordinates, uvs, normals;
		for (string v : this->lines) {
			if (v[0] == 'v' && v[1] == ' ') {
				vec3 _v;
				sscanf(v.c_str(), "v %f %f %f", &_v.x, &_v.y, &_v.z);
				coordinates.push_back(_v);
			}
			else if (v[0] == 'v' && v[1] == 't') {
				vec3 _vt;
				sscanf(v.c_str(), "vt %f %f", &_vt.x, &_vt.y);
				_vt.z = 0;
				uvs.push_back(_vt);
			}
			else if (v[0] == 'v' && v[1] == 'n') {
				vec3 _vn;
				sscanf(v.c_str(), "vn %f %f %f", &_vn.x, &_vn.y, &_vn.z);
				normals.push_back(_vn);
			}
			else if (v[0] == 'f' && v[1] == ' ') {
				int vertexIndex[3], uvIndex[3], normalIndex[3];
				sscanf(v.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1],
					&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		for (int i = 0; i < (int)vertexIndices.size(); i++) {
			out_coordinates.push_back(coordinates[vertexIndices[i] - 1]);
		}
		for (int i = 0; i < (int)uvIndices.size(); i++) {
			out_uvs.push_back(uvs[uvIndices[i] - 1]);
		}
		for (int i = 0; i < (int)normalIndices.size(); i++) {
			out_normals.push_back(normals[normalIndices[i] - 1]);
		}
		vertexIndices.clear();
		uvIndices.clear();
		normalIndices.clear();
		coordinates.clear();
		uvs.clear();
		normals.clear();
	}
};