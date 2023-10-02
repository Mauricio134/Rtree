#include <string>
#include <vector>
#include <iostream>
#include "RTree.h"

using namespace std;

void print(const int& command, vector<vector<vector<pair<int, int>>>>& objects_n, string& output) {
	output.resize(0);
	output = command;

	switch (command)
	{
	case 0:// OBJECTS
		output += "|" + to_string(objects_n[0].size());
		for (auto& polygon : objects_n[0]) {
			output += "|" + to_string(polygon.size());

			for (auto& point : polygon) {
				output += "|" + to_string(point.first) + "|" + to_string(point.second);
			}
		}
		break;

	case 1: //MBRS:
		cout << " number of (objects) :" << to_string(objects_n.size()) << endl;
		output += "|" + to_string(objects_n.size());
		for (auto& objects : objects_n) {
			output += "|" + to_string(objects.size());
			cout << " number of polygons :" << to_string(objects.size()) << endl;
			for (auto& polygon : objects) {
				output += "|" + to_string(polygon.size());
				cout << " number of points :" << to_string(polygon.size()) << endl;
				for (auto& point : polygon) {
					output += "|" + to_string(point.first) + "|" + to_string(point.second);
					cout << "   point:" << to_string(point.first) << " | " << to_string(point.second) << endl;

				}
			}
			cout << endl << "--------------------" << endl;
		}
		break;
	default:
		output += "|0";
		break;
	}

	output += "|END";
	cout << output;
}

void print_pair(vector<pair<int, int>> output) {
	for (auto& x : output)
	{
		cout << x.first << " ; " << x.second << " - ";
	}
}

int main(int argc, char* argv[])
{
	vector<vector<pair<int, int>>> vpoints;


	float coord[16] = { 20, 59, 20, 43, 50, 58 , 48,67, 105, 68, 74, 64, 83, 40, 104, 54 };

	vector<pair<int, int>> points;
	for (int i = 0; i < 16; i += 2) {
		pair<int, int> A;
		A.first = coord[i];
		A.second = coord[i + 1];
		points.push_back(A);
	}
	for (unsigned int i = 0; i < 8; i += 2) {
		//v_points.insertpush_back(A);          
		vector<pair<int, int>>  sub1(&points[i], &points[i + 2]);
		vpoints.push_back(sub1);

	}




	RTree rtree;

	string output;
	vector<vector<pair<int, int>>> objects;

	vector<vector<vector<pair<int, int>>>> objects_n;

	for (auto& x : vpoints)
	{
		cout << "inserting " << x.size() << ": ";
		print_pair(x);
		Rect rect = rtree.MBR(x);
		rtree.Insert(rect.m_min, rect.m_max, x);
		cout << endl;
	}
	//Rect rect = rtree.MBR(vpoints[0]);
	 //rtree.Insert(rect.m_min, rect.m_max, vpoints[0]);
	rtree.getMBRs(objects_n);
	print(1, objects_n, output);
	cout << endl;
	rtree.LEAF_();

	cout << rtree.S(104,54) << endl;

	return 0;
}