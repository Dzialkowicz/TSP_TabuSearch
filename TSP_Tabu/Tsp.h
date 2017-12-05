#pragma once
#ifndef TSP_H
#define	TSP_H
#define NOMINMAX
#define EULER 2.71828182845904523536

#include <algorithm>
#include <chrono>
#include <ctime>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>
//#include <Windows.h>
#include "TabooQueue.h"

using namespace std;


class Tsp
{
public:
	Tsp();
	Tsp(int No_cities);
	Tsp(const Tsp& orig);
	virtual ~Tsp();

	void simulatedAnnealing(double start_temperature, double end_temperature, double temperature_reduction_rate);
	void dspAdjacencyMatrix();
	void chgNoCities(int new_No_cities);
	void loadFromTextfile(string filename);
	void saveToTextfile(string filename);
	int getNoCities() { return No_cities; }
	int setOptimalInitialTemperature();

	void tabooSearch(int queueLength, bool stopCriteria, int value_of_stop_criteria);
	
private:

	void mainDiagonalMirroring();
	void randDistanceFromAdjacencyMatrix(int start_interval, int end_interval);
	void generateRandomPermutation(int * array);
	void generateRandomPermutation(vector<int> &array);
	void dspCityCombination(int * combination_of_cities, int sum_of_distance);
	void dspCityCombination(vector <int> combination_of_cities, int sum_of_distance);
	int sumOfDistanceBetweenCities(int * combination_of_cities);
	int sumOfDistanceBetweenCities(vector <int> combination_of_cities);
	double probabilityFunction(double temperature, int actual_distance, int proposed_distance);
	double generateRandomDouble(double start_interval, double end_interval);
	int generateRandomInteger(int start_interval, int end_interval);
	void copyArray(int * source, int * copy);
	void stepFunction(int * combination_of_cities);
	void initArrayWithIndex(int * array);

	void stepFunctionTabu(int * combination_of_cities, int miasto_poczatkowe, int miasto_docelowe);
	void max_No_movements(vector<movement> max_range, int *positions, TabooQueue * queue);
	bool ifTaboo(vector<movement> max_range);

	unsigned int rand_variable;
	int No_cities;
	vector<vector <int>> adjacency_matrix;
};

#endif	//TSP_H
