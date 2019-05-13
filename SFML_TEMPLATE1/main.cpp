#include <iostream>
#include <stdio.h>
#include <thread>
#include <Windows.h>
#include <SFML/Network.hpp>

bool	finished = false,
		answered = false;
std::string answer = "vacia";

void waitingAnswer()
{	
	
	while (!finished)
	{
		std::cin >> answer;
		answered = true;

	}
}

void main()
{
	sf::Clock myClock;

	std::string myQuestions[6] = { "Pregunta 1: Cuantos lados tiene un cuadrado? \n 1.4 \n 2.7 \n 3.2 \n 4.365",
									"Pregunta 2: Cuantos vertices tiene un cuadrado? \n 1.1 \n 2.8 \n 3.En serio, otra vez? \n 4.4",
									"Pregunta 3: Cual es la fecha de lanzamiento de World Of Warcraft? \n 1.2004 \n 2.2005 \n 3.2003 \n 4.2006",
									"Pregunta 4: Creador de la saga Metal Gear Solid? \n 1.Fideo Kojima \n 2.Hideo Kojima \n 3.Video Kojima \n 4.Todas las anteriores",
									"Pregunta 5: Cual es el año de lanzamiento de Diablo 2? \n 1.1996 \n 2.2012 \n 3.2000 \n 4.1998",
									"Pregunta 6: Quien va a sacar un 10 en este ejercicio? \n 1.Sergio \n 2.Sergio Escuder \n 3.Sergio Escuder Gallego \n 4.todas las anteriores son correctas" };

	std::string rightAnswers[6] = {"1","4","1","2","3","4"};

	
	std::thread answerThread(&waitingAnswer);

	int indexQuestion = 0,
		score = 0;

	std::cout << "ESTAS PREPARADO PARA JUGAR??? PULSA ENTER PARA COMENZAR\n" << std::endl;
	bool	asking = true,
			waiting = false;

	while (!finished)
	{
		
		//std::cout << myClock.getElapsedTime().asSeconds() << std::endl;
		switch (indexQuestion)
		{
			case 0:
				if (asking)
				{		
					
					asking = false;
					waiting = true;
					std::cout << myQuestions[indexQuestion] << std::endl;
					myClock.restart();
				}
				if (myClock.getElapsedTime().asSeconds() <= 5 )
				{
					if (answer == rightAnswers[indexQuestion] && answered)
					{
						system("cls");
						score += 5;
						std::cout << "ENHORABUENA, ACERTASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";
						answered = false;
					}
					else if(answer != rightAnswers[indexQuestion] && answered)
					{
						system("cls");
						score--;
						if (score < 0) score = 0;
						std::cout << "OOOOHHHH, FALLASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";

						answered = false;
					}
				}
				else if (myClock.getElapsedTime().asSeconds() > 5)
				{
					system("cls");
					score--;
					indexQuestion++;
					asking = true;
					answer = "vacia";
					
					myClock.restart();
				}		
				
				break;
			case 1:				
				if (asking)
				{					
					asking = false;
					waiting = true;
					std::cout << myQuestions[indexQuestion] << std::endl;
					myClock.restart();
				}
				if (myClock.getElapsedTime().asSeconds() <= 5)
				{
					if (answer == rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score += 5;
						std::cout << "ENHORABUENA, ACERTASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";

						answered = false;
					}
					else if (answer != rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score--;
						if (score < 0) score = 0;
						std::cout << "OOOOHHHH, FALLASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";

						answered = false;
					}
					else if (myClock.getElapsedTime().asSeconds() > 5)
					{
						system("cls");
						score--;
						indexQuestion++;
						asking = true;
						answer = "vacia";

						myClock.restart();

					}
				}
				break;
			case 2:
				if (asking)
				{
					asking = false;
					waiting = true;
					std::cout << myQuestions[indexQuestion] << std::endl;
					myClock.restart();
				}
				if (myClock.getElapsedTime().asSeconds() <= 5)
				{
					if (answer == rightAnswers[indexQuestion] && answered)
					{
						system("cls");
						score += 5;
						std::cout << "ENHORABUENA, ACERTASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";

						answered = false;
					}
					else if (answer != rightAnswers[indexQuestion] && answered)
					{
						system("cls");
						score--;
						if (score < 0) score = 0;
						std::cout << "OOOOHHHH, FALLASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";

						answered = false;
					}
				}
				else if (myClock.getElapsedTime().asSeconds() > 5)
				{
					system("cls");
					score--;
					indexQuestion++;
					asking = true;
					answer = "vacia";

					myClock.restart();
				}
				break;
			case 3:
				if (asking)
				{
					asking = false;
					waiting = true;
					std::cout << myQuestions[indexQuestion] << std::endl;
					myClock.restart();
				}
				if (myClock.getElapsedTime().asSeconds() <= 5)
				{
					if (answer == rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score += 5;
						std::cout << "ENHORABUENA, ACERTASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";
					}
					else if (answer != rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score--;
						if (score < 0) score = 0;
						std::cout << "OOOOHHHH, FALLASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";
					}
				}
				else if (myClock.getElapsedTime().asSeconds() > 5)
				{
					system("cls");
					score--;
					indexQuestion++;
					asking = true;
					answer = "vacia";

					myClock.restart();

					answered = false;
				}
				break;
			case 4:
				if (asking)
				{
					asking = false;
					waiting = true;
					std::cout << myQuestions[indexQuestion] << std::endl;
					myClock.restart();
				}
				if (myClock.getElapsedTime().asSeconds() <= 5)
				{
					if (answer == rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score += 5;
						std::cout << "ENHORABUENA, ACERTASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";
						answered = false;
					}
					else if (answer != rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score--;
						if (score < 0) score = 0;
						std::cout << "OOOOHHHH, FALLASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";
						answered = false;
					}
				}
				else if (myClock.getElapsedTime().asSeconds() > 5)
				{
					system("cls");
					score--;
					indexQuestion++;
					asking = true;
					answer = "vacia";

					myClock.restart();
				}
				break;
			case 5:
				if (asking)
				{
					asking = false;
					waiting = true;
					std::cout << myQuestions[indexQuestion] << std::endl;
					myClock.restart();
				}
				if (myClock.getElapsedTime().asSeconds() <= 5)
				{
					if (answer == rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score += 5;
						std::cout << "ENHORABUENA, ACERTASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";
						finished = true;
						answered = false;
					}
					else if (answer != rightAnswers[indexQuestion] && answered)
					{
						system("cls");

						score--;
						if (score < 0) score = 0;
						std::cout << "OOOOHHHH, FALLASTE!! TU PUNTUACIÓN AHORA ES DE " << score << " PUNTOS.\n" << std::endl;

						waiting = false;
						asking = true;

						indexQuestion++;
						answer = "vacia";
						finished = true;
						answered = false;
					}
				}
				else if (myClock.getElapsedTime().asSeconds() > 5)
				{
					system("cls");
					score--;
					indexQuestion++;
					asking = true;
					answer = "vacia";
					finished = true;
				}
				break;
			default:
				break;
		}
	}
	answerThread.join();
	system("cls");
	std::cout << "GRACIAS POR JUGAR :D \nTU PUNTUACION FINAL HA SIDO DE " << score << " PUNTOS.\n PULSA ENTER PARA TERMINAR" << std::endl;
	system("pause");

}
