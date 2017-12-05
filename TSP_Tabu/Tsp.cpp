#include "Tsp.h"
#include <limits>
#include <stdio.h>
#include "myClock.h"
//#include <tchar.h>

Tsp::Tsp()
{

}

Tsp::Tsp(int No_cities) :
	No_cities(No_cities),
	adjacency_matrix(No_cities, vector<int>(No_cities, -1)),
	rand_variable(0)
{
	randDistanceFromAdjacencyMatrix(0, 100);
	mainDiagonalMirroring();
}
Tsp::Tsp(const Tsp& orig)
{
}

Tsp::~Tsp()
{
}





void Tsp::simulatedAnnealing(double start_temperature, double end_temperature, double temperature_reduction_rate)
{
	//Retrieves current system date and time
	//VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

	//Time variables signed 64-bit Integers
	//LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, Time, Frequency;

	//Time.QuadPart = 0;
	//Frequency.QuadPart = 0; //Frequency
	//StartingTime.QuadPart = 0; //Starting Time
	//EndingTime.QuadPart = 0;
	//QueryPerformanceFrequency(&Frequency); //Frequency

	//START TIME
    //QueryPerformanceCounter(&StartingTime); //Starting Time
    
    //Declaring clock
    MyClock myClock;
    
    //MAC TYPE OF START TIME
    myClock.start();

	//Allocating required amount of memory to store No_cities and pointing to that block
	//Free memory by: delete[] combination_of_cities, act_combination_of_cities, best_combination_of_cities
	int *combination_of_cities = new int[No_cities];
	int *act_combination_of_cities = new int[No_cities];
	int *best_combination_of_cities = new int[No_cities];
	
	//Road variables
	int road, act_road, shortest_road;

	//Generate random road between cities of given combination of cities
	generateRandomPermutation(combination_of_cities);
	//Copy this array
	copyArray(combination_of_cities, best_combination_of_cities);

	//Shortest road
	shortest_road = sumOfDistanceBetweenCities(combination_of_cities);

	//Actual road
	act_road = sumOfDistanceBetweenCities(combination_of_cities);

	//start temperature
	double temperature = start_temperature;

	//While given temperature is higher than end temperature
	while (temperature > end_temperature)
	{
		//Do step fuction
		stepFunction(combination_of_cities);

		//The road is sum of distance between cities 
		road = sumOfDistanceBetweenCities(combination_of_cities);

		//If road is less or equal to act_road, or 
		//Generated number from 0.0 to 0.99 is less then probabilityFunction
		if (road <= act_road || generateRandomDouble(0.0, 0.99) < probabilityFunction(temperature, act_road, road))
		{
			//Set road as a new act_road
			act_road = road;

			//If act_road is less than shortest_road
			if (act_road < shortest_road)
				//Set act_road as a new shortest_road
				shortest_road = act_road;
		}

		else
		{
			//Else make next StepFunction
			stepFunction(combination_of_cities);
		}

		//Multiply temperature by reduction_rate
		temperature *= temperature_reduction_rate;

	}
	//Windows type of END TIME
	//QueryPerformanceCounter(&EndingTime);
	//ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	//ElapsedMicroseconds.QuadPart *= 1000000;
	//ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	//Time.QuadPart += ElapsedMicroseconds.QuadPart;
    
    //MAC END TIME
    myClock.stop();

	//Display best combination with the shortest road
	dspCityCombination(best_combination_of_cities, shortest_road);

	//Display algorithm time (TIME = END TIME - START TIME)
	cout << endl << "Czas trwania algorytmu : " << myClock.getTime() << " mikrosekund ." << endl;


	//Freeing alocated memory for algorithm
	delete[] combination_of_cities;
	delete[] best_combination_of_cities;
	delete[] act_combination_of_cities;
}

void Tsp::dspAdjacencyMatrix()
{
	//Display NO_cities
	cout << "Liczba miast: " << No_cities << " ." << endl;
	cout << endl;
	//auto - type of this variable, is type of it's initialization

	//for loop over range
	//displays adjacency matrix
	for (auto row : adjacency_matrix)
	{
		for (auto column : row)
		{
			cout << column << '\t';
		}
		cout << endl;
	}
}

void Tsp::chgNoCities(int new_No_cities)
{
	//Set new No_cities
	No_cities = new_No_cities;

	//Clear adjacency matrix
	adjacency_matrix.clear();

	//Set new adjacency matrix
	adjacency_matrix.resize(new_No_cities, vector <int>(new_No_cities, -1));

	//Randomize distance 
	randDistanceFromAdjacencyMatrix(0, 100);

	//
	mainDiagonalMirroring();

}
void Tsp::loadFromTextfile(string filename)
{
	//Class to operate on input files
	ifstream read_only_file;

	//Open selected Read-Only file
	read_only_file.open(filename);

	//If file opening failed
	if (!read_only_file.is_open())
	{
		cout << "Blad odczytu pliku! " << filename  << endl << endl;
	}
	//Else it succeded
	else
	{
		//Extract No_cities from file
		read_only_file >> No_cities;

		//Clear adjacency matrix
		adjacency_matrix.clear();

		//Set new adjacency matrix 
		adjacency_matrix.resize(No_cities, vector <int>(No_cities, -1));

		//Read/Display from new adjacency matrix
		for (auto &row : adjacency_matrix)
		{
			for (auto &column : row)
			{
				read_only_file >> column;
			}
		}
		cout << filename << " Odczytany poprawnie!" << endl << endl;
	}
	//Close file
	read_only_file.close();
}

void Tsp::saveToTextfile(std::string filename)
{
	//Class to operate on input files
	ofstream save_file;

	//Open selected save file
	save_file.open(filename);

	//If file saving failed
	if (!save_file.is_open())
	{
		cout << "Blad zapisu pliku! " << filename << endl << endl;
	}

	//Save No_cities to save_file
	save_file << No_cities << endl;

	for (auto row : adjacency_matrix)
	{
		for (auto column : row)
		{
			save_file << column << '\t';
		}
		save_file << endl;
	}

	save_file.close();
	cout << filename << " Zapisany poprawnie!" << endl << endl;
}
int Tsp::setOptimalInitialTemperature()
{
	//Define deltas
	int delta = 0, new_delta;
	//Raises number of occurencer by power of 2 
	int No_recurrences = pow(No_cities, 2.0);
	//Allocating memory to store No_cities for first permutation
	int *first_permutation = new int[No_cities];
	//Generate random, first permutation
	generateRandomPermutation(first_permutation);
	//Sum of distance of first permutation
	int first_permutation_sum_of_distance = sumOfDistanceBetweenCities(first_permutation);
	//Allocating memory to store No_cities for temporary permutation
	int *temp_permutation = new int[No_cities];

	//For loop through all recurrences
	for (int i = 0; i < No_recurrences; ++i)
	{
		//Generate random temporary permutation
		generateRandomPermutation(temp_permutation);
		//New delta is temporary sum of distance - first sum of distance (of permutation)
		new_delta = sumOfDistanceBetweenCities(temp_permutation) - first_permutation_sum_of_distance;

		//If new delta is greater than old, set new delta
		if (new_delta > delta)
			delta = new_delta;
	}
	//Free memory and return delta
	delete[] first_permutation;
	delete[] temp_permutation;
	return delta;
}



void Tsp::tabooSearch(int queueLength, bool stop_criteria, int value_of_stop_criteria)

{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//Retrieves current system date and time
	//VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

	//Time variables signed 64-bit Integers
	//LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, Time, Frequency;

	//Time.QuadPart = 0;
	//Frequency.QuadPart = 0; //Frequency
	//StartingTime.QuadPart = 0; //Starting Time
	//EndingTime.QuadPart = 0;
	//QueryPerformanceFrequency(&Frequency); //Frequency

										   //START TIME
//	QueryPerformanceCounter(&StartingTime); //Starting Time
    
    
    //Declaring clock
    MyClock myClock;
    
    //MAC TYPE OF START TIME
    myClock.start();
    
	///////////////////////////////////////////////////////////////////////////////////////////////
	int *combination_of_cities = new int[No_cities];
	int *best_combination_of_cities = new int[No_cities];
	
	//generowanieLosowejPermutacji
	generateRandomPermutation(combination_of_cities);
	int *positions = new int[No_cities];
	

	for (int i = 0; i < No_cities; ++i)
	{
		positions[combination_of_cities[i]] = i;
	}
    //min?
	int shortest_road = numeric_limits<int>::max();

	TabooQueue * tabooQueue = new TabooQueue(queueLength);

	int effective_moves = 0, iterations = 0;
	vector<movement> max_range(No_cities, movement());

	bool continuum;

	if (stop_criteria)
		continuum = effective_moves < value_of_stop_criteria;
	else
		continuum = iterations < value_of_stop_criteria;
    continuum = true;
	while (continuum)
	{

		++iterations;
		max_No_movements(max_range, positions, tabooQueue);

		bool if_Taboo = ifTaboo(max_range);

		int act_road = numeric_limits<int>::max();
		movement act_movement;

		for (int i = 0; i < No_cities - 1; ++i)
		{
			for (int j = i + 1; j < No_cities; ++j)
			{
				if (j > max_range[combination_of_cities[i]].right)
				{
					if (!if_Taboo)
					{
						break;
					}
				}
				else if (i < max_range[combination_of_cities[j]].left && !if_Taboo) continue;

				stepFunction(combination_of_cities);

				int new_road = sumOfDistanceBetweenCities(combination_of_cities);

				if (new_road < act_road)
				{
					act_road = new_road;
					act_movement.left = i;
					act_movement.right = j;
				}

				stepFunction(combination_of_cities);
			}
		}

		tabooQueue->add_mov(movement(combination_of_cities[act_movement.left], combination_of_cities[act_movement.right]));
		stepFunction(combination_of_cities);
		positions[combination_of_cities[act_movement.left]] = act_movement.left;
		positions[combination_of_cities[act_movement.right]] = act_movement.right;

		if (act_road < shortest_road)
		{
			shortest_road = act_road;
			copyArray(combination_of_cities, best_combination_of_cities);
			effective_moves = 0;
		}
		else
		{

			++effective_moves;
		}

		if (stop_criteria)
			continuum = effective_moves < value_of_stop_criteria;
		else
			continuum = iterations < value_of_stop_criteria;
	}
	//////////////////////////////////////////////////////////////////////////TIME
	//QueryPerformanceCounter(&EndingTime);
	//ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	//ElapsedMicroseconds.QuadPart *= 1000000;
	//ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	//Time.QuadPart += ElapsedMicroseconds.QuadPart;
    
     myClock.stop();
	dspCityCombination(best_combination_of_cities, shortest_road);
	cout << endl << "Czas trwania algorytmu : " << myClock.getTime()<< " mikrosekund ." << endl;


	delete[] combination_of_cities;
	delete[] positions;
	delete tabooQueue;

}
void Tsp::stepFunctionTabu(int* combination_of_cities, int city_1, int city_2)
{
	std::swap(combination_of_cities[city_1], combination_of_cities[city_2]);
}

void Tsp::max_No_movements(std::vector<movement> max_range, int * positions, TabooQueue * queue)
{
	for (int i = 0; i < No_cities; ++i)
	{
		max_range[i].left = 0;
		max_range[i].right = No_cities - 1;
	}

	for (int i = 0; i < queue->getLength(); ++i)
	{
		int tL = queue->get(i).left;
		int tR = queue->get(i).right;

		if (tL > 0 && tR >0)
		{
			max_range[tL].left = min(positions[tL], max(positions[tR] + 1, max_range[tL].left));
			max_range[tR].right = max(positions[tR], min(positions[tL] - 1, max_range[tR].right));
		}
	}
}

bool Tsp::ifTaboo(vector<movement> max_range)
{
	for (int i = 0; i < No_cities; ++i)
	{
		if (max_range[i].left != max_range[i].right)
		{
			return false;
		}
	}

	return true;
}

void Tsp::randDistanceFromAdjacencyMatrix(int start_interval, int end_interval)
{
	//Actual time
	auto act_time = chrono::system_clock::now().time_since_epoch().count();

	//(Mersenne Twister) Random Number Generator 32-bit numbers state size 19937bits (name)
	mt19937 RNG(act_time);

	//Random Integers Distribution 
	uniform_int_distribution<int> rand_int_distribution (start_interval, end_interval);

	//Create distance generator by binding rand_int_distribution with RNG
	auto distance_generator = bind(rand_int_distribution, RNG);

	//Generate distance for adjacency_matrix
	for (unsigned row = 0; row < adjacency_matrix.size(); ++row)
	{
		for (unsigned column = row + 1; column < adjacency_matrix.size(); ++column)
		{
			adjacency_matrix[row][column] = distance_generator();
		}
	}
}

void Tsp::mainDiagonalMirroring()
{
	//Make Diagonal Mirroring for Adjacency Matrix 
	for (unsigned row = 0; row < adjacency_matrix.size(); ++row)
	{
		for (unsigned column = row + 1; column < adjacency_matrix.size(); ++column)
		{
			adjacency_matrix[column][row] = adjacency_matrix[row][column];
		}
	}
}

void Tsp::generateRandomPermutation(int* array)
{
	//Generates random permutation
	for (int i = 0; i < No_cities; ++i)
	{
		array[i] = i;
	}

	//Shuffles (array, array + No_cities)
	random_shuffle(array, array + No_cities);

}

void Tsp::generateRandomPermutation(vector<int> &array)
{
	//Another way to generate permutation
	for (int i = 0; i < No_cities; ++i)
	{
		array[i] = i;
	}

	random_shuffle(array.begin(), array.end());
}

void Tsp::dspCityCombination(int* cities_combination, int distance_sum)
{
	//Displays cities_permutation and distance_sum where int*array is a parameter
	cout << endl << "Permutacja: " << endl;
	for (int i = 0; i < No_cities; ++i)
	{
		cout << cities_combination[i] << " -> ";
	}
	cout << endl;
	cout << "Suma odlegosci: " << distance_sum << endl;
}

void Tsp::dspCityCombination(vector <int> cities_combination, int distance_sum)
{
	//Displays cities_permutation and distance_sum where vector<int> is a parameter
	cout << endl << "Permutacja: " << endl;
	for (int i = 0; i < No_cities; ++i)
	{
		cout << cities_combination[i] << " -> ";
	}
	cout << endl;
	cout << "Suma odlegosci: " << distance_sum << endl;
}

int Tsp::sumOfDistanceBetweenCities(int * cities_combination)
{
	//Sums the distance where int* is a parameter
	int distance_sum = 0;
	//For loop through all cities except first
	for (int i = 0; i < No_cities - 1; ++i)
	{
		//distance_sum is sum of cities_combination's of adjacency matrix
		distance_sum += adjacency_matrix[cities_combination[i]][cities_combination[i + 1]];
	}
	//Add distance to first city
	distance_sum += adjacency_matrix[cities_combination[No_cities - 1]][cities_combination[0]];

	return distance_sum;
}
int Tsp::sumOfDistanceBetweenCities(vector <int> cities_combination)
{
	//Sums the distance where vector<int> is a parameter
	int distance_sum = 0;
	for (int i = 0; i < cities_combination.size() - 1; ++i)
	{
		distance_sum += adjacency_matrix[cities_combination[i]][cities_combination[i + 1]];
	}
	distance_sum += adjacency_matrix[cities_combination[No_cities - 1]][cities_combination[0]];

	return distance_sum;
}

double Tsp::probabilityFunction(double temperature, int act_distance, int proposed_distance)
{
	//True if proposed_distance is better than act_distance
	if (proposed_distance <= act_distance)
		return 1;
	else
		//				  ((prop-act)*-2Log(temperature)) 
		//			EULER^(-----------------------------)
		//				  (		     prop				)
		return pow(EULER, (((proposed_distance - act_distance)*((-2)*log(temperature))) / proposed_distance));

}

double Tsp::generateRandomDouble(double start_interval, double end_interval)
{
	//Actual time
	auto act_time = chrono::system_clock::now().time_since_epoch().count() + rand_variable;
	//(Mersenne Twister) Random Number Generator 32-bit numbers state size 19937bits (name)
	mt19937 RNG(act_time);
	//Random Double Distribution 
	uniform_real_distribution<double> rand_double_distribution(start_interval, end_interval);
	//Binds rand_double_distribution and RNG to create real_number_generator
	auto real_number_generator = bind(rand_double_distribution, RNG);

	++rand_variable;

	return real_number_generator();
}



void Tsp::copyArray(int* source, int* copy)
{
	//Copying array
	for (int i = 0; i < No_cities; ++i)
	{
		copy[i] = source[i];
	}
}

void Tsp::stepFunction(int* cities_combination)
{
	//Actual time
	auto act_time = chrono::system_clock::now().time_since_epoch().count() + rand_variable;
	//(Mersenne Twister) Random Number Generator 32-bit numbers state size 19937bits (name)
	mt19937 RNG(act_time);
	//Random Integer Distribution between cities
	uniform_int_distribution<int> rand_integer_distribution(0, No_cities - 1);
	//Binds rand_integer_distribution and RNG to create index_generator
	auto index_generator = bind(rand_integer_distribution, RNG);

	//Take two indexes
	int index_1, index_2;
	//Randomize city
	index_1 = index_generator();

	do
	{
		//Randomize new city
		index_2 = index_generator();
	}
	//Only when the indexes meet
	while (index_1 == index_2);
	//Swap these cities
	swap(cities_combination[index_1], cities_combination[index_2]);

	++rand_variable;
}

void Tsp::initArrayWithIndex(int* array)
{
	//Initialize array of cities
	for (int i = 0; i < No_cities; ++i)
	{
		array[i] = i;
	}
}




