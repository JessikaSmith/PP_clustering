// EM.cpp : Defines the entry point for the console application.
//
// EM algorithm 
#include <omp.h>
#include "stdafx.h"
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

// TODO: get rid of number 
const int HEIGHT = 6808;

using namespace std;

class CSVRow
{
public:
	string const& operator[](size_t index) const
	{
		return m_data[index];
	}
	size_t size() const
	{
		return m_data.size();
	}
	void readNextRow(istream& str)
	{
		string         line;
		getline(str, line);
		stringstream   lineStream(line);
		string         cell;

		m_data.clear();
		while (getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		if (!lineStream && cell.empty())
		{
			m_data.push_back("");
		}
	}
private:
	vector<string>    m_data;
};

istream& operator >> (istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
};

class EM
{
private:
	vector<double> initMean(double numClust);
	vector<double> initVariance(double numClust);

public:
	EM(float** matrix, int maxIter);

};


vector<vector<double>> getMatrix(ifstream& file) {
	
	vector<vector<double>> matrix;
	CSVRow  row;
	string line;
	file >> row;
	while (file >> row) {
		vector<double> tempRow;
		for (int i = 1; i < row.size(); i++) {
			tempRow.push_back(stod(row[i]));
		}
		matrix.push_back(tempRow);
	}
	return matrix;
}


// old version
float** getMatrix2(ifstream& file) {

	CSVRow  row;
	file >> row;
	int numElems = row.size();
	float** matrix = 0;
	matrix = new float*[HEIGHT];
	int i = 0;

	while (file >> row)
	{	
		matrix[i] = new float[numElems-1];
		for (int j = 1; j < numElems; j++) {
			matrix[i][j-1] = stod(row[j]);
		}
		i += 1;
	}
	return matrix;
}

void plotSpeedup() {
	return;
}

void measureTime() {
	return;
}

int main()
{
	ifstream file("year_prediction.csv");
	if (!file.is_open()) {
		cout << "No file" << endl;
		return false;
	}
	vector<vector<double>> matrix;
	matrix = getMatrix(file);
	cout << (matrix)[0][0] << endl;

    return 0;
}