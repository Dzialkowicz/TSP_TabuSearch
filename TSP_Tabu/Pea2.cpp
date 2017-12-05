//#include "stdafx.h"
#include <iostream>
#include <memory>
#include <cstdlib>
#include "Tsp.h"
#include "TabooQueue.h"


bool isNumber(const string&);

int main(int argc, char** argv)
{
	unique_ptr <Tsp> problem_instance;
	string No_cities_opt;
	string menu_opt;
	char submenu_opt;
	string filename;
	//int No_cities = 3;


	while (true)
	{
		cout << "TSP" << endl;
		cout << "Podaj liczbe miast wieksza od 2: ";
		getline(cin, No_cities_opt);

		if (isNumber(No_cities_opt))
		{
			int No_cities = atoi(No_cities_opt.c_str());
			if (No_cities > 2)
			{
				problem_instance = unique_ptr<Tsp>(new Tsp(No_cities));
				break;
			}
			else
			{
				cout << endl << "Zle dane!" << endl << "Sprobuj ponownie !" << endl;
				//system("pause");
				//system("cls");
				continue;
			}
		}
		else
		{
			cout << endl << "Zle dane!" << endl << "Sprobuj ponownie !" << endl;
			//system("pause");
			//system("cls");
		}
	}
	system("cls");

	while (true)
	{
		if (menu_opt[0] == 'q')
		{
			cout << "Program zakonczony!" << endl;
			system("pause");
			break;
		}

		cout << "Wybrano " << problem_instance->getNoCities() << " miast." << endl;
		cout << endl;
		cout << "MENU:" << endl;
		cout << "A --- Wygeneruj nowa instancje problemu;" << endl;
		cout << "B --- Wczytaj instancje z pliku ;" << endl;
		cout << "C --- Zapisz instancje do pliku ;" << endl;
		cout << "D --- Wyswietl macierz sasiedztwa;" << endl;
		cout << "E --- Algorytm Symulowanego Wyzarzania;" << endl;
		cout << "F --- Algorytm Tabu Search;" << endl;
		cout << "Q --- Wyjscie." << endl;


		cout << endl << "Podaj opcje: ";
		getline(cin, menu_opt);
		cout << endl;

		switch (menu_opt[0])
		{
		case 'a':
		{
					cout << "Podaj liczbe miast wieksza od 2: ";
					getline(cin, No_cities_opt);

					if (isNumber(No_cities_opt))
					{
						int No_cities = atoi(No_cities_opt.c_str());

						if (No_cities > 2)
						{
							problem_instance = unique_ptr<Tsp>(new Tsp(No_cities));
							cout << "Instancja wygenerowana! " << endl;
							//system("pause");
							//system("cls");
							break;
						}
						else
						{
							cout << endl << "Zle dane!" << endl << "Sprobuj ponownie !" << endl;
							//system("pause");
							//system("cls");
							break;
						}
					}
					else
					{
						cout << endl << "Zle dane!" << endl << "Sprobuj ponownie !" << endl;
						//system("pause");
						//system("cls");
					}
					break;
		}
		case 'b':
		{
					cout << "Podaj nazwe pliku: ";
					getline(cin, filename);
					problem_instance->loadFromTextfile(filename);
					system("pause");
					system("cls");
					break;
		}

		case 'c':
		{
					cout << "Podaj nazwe pliku: ";
					getline(cin, filename);
					problem_instance->saveToTextfile(filename);
					system("pause");
					system("cls");
					break;
		}
		case 'd':
		{
					problem_instance->dspAdjacencyMatrix();
					//system("pause");
					//system("cls");
					break;
		}
		case 'e':
		{
					double start_temperature, end_temperature, temperature_reduction_rate;
					cout << "Algorytm symulowanego wyzarzania :" << endl;
					//cout << "Podaj temperature koncowa z przedzialu (0:x): ";
					end_temperature = 400;
					cout << endl << "Podaj wspolczynnik obnizania temperatury z przedzialu (0:1): ";
					cin >> temperature_reduction_rate;
					cout << endl;

					start_temperature = problem_instance->setOptimalInitialTemperature();
					problem_instance->simulatedAnnealing(start_temperature, end_temperature, temperature_reduction_rate);

					system("pause");
					system("cls");
					break;
		}
		case 'f':
		{
					
					bool stop_criteria;
					int value_of_stop_criteria = 150;
					int queueLength;

					string user_value;

					
						system("cls");
						cout << "Algorytm Przeszukiwania Tabu :" << endl;
						cout << "Podaj dlugosc Kolejki Tabu:" << endl;
						cin >> queueLength;
						cin.sync();
						cout << "Wybierz kryterium koncowe: " << endl;
						cout << "a) Liczba nieefektywnych krokow" << endl;
						cout << "b) Liczba iteracji" << endl;

						cin >>submenu_opt;
						switch (submenu_opt)
						{
						case 'a':
						{
									stop_criteria = 1;
									cout << "Wybrano a) Liczba nieefektywnych krokow" << endl;
									cout << "Podaj wartosc kryterium: (domyslnie: 50) " << endl;
									getline(cin, user_value);
									if (isNumber(user_value))
										value_of_stop_criteria = atoi(user_value.c_str());
									//right_choice = true;
									//system("pause");
									//system("cls");
									break;
						}
						case 'b':
						{
									stop_criteria = 0;
									cout << "Wybrano b) Liczba iteracji" << endl;
									cout << "Podaj wartosc kryterium: (domyslnie: 50) " << endl;
									getline(cin, user_value);
									if (isNumber(user_value))
										value_of_stop_criteria = atoi(user_value.c_str());
									//right_choice = true;
									//system("pause");
									//system("cls");
									break;
						}
						default:
						{
								   cout << "Nie ma takiej opcji!" << endl;
								   system("pause");
								   system("cls");
								   break;
						}
						}
					

					problem_instance->tabooSearch(queueLength, stop_criteria, value_of_stop_criteria);

					system("pause");
					system("cls");
					break;
		}

		case 'q':
		{
					system("cls");
					break;
		}
		default:
		{
				   cout << "Nie ma takiej opcji! Podaj litere z przedzialu a-f" << endl;
				   system("pause");
				   system("cls");
				   break;
		}

		}

	}
	return 0;
}

bool isNumber(const string& model)
{
	for (char sign : model)
	{
		if (!isdigit(sign))
			return 0;
	}
	return 1;
}

