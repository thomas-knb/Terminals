#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include "screen.h"
#include "point.h"
#define N 8 // nombre de terminaux


void initTerminaux(Screen& _screen, Point * _terminaux);
void initCentres(Screen& _screen, std::vector<int> _terminauxNC, Point * _terminaux, Point * _centres, int * _Y, int * _Z);


int main(int argc, char **argv)
{
  std::cerr << "Tapez Q ou C-c dans le terminal pour quitter" << std::endl;

  int i, j;

  Point terminaux[N]; // liste des terminaux
  std::vector<int> terminauxNC(N); // vecteur des indices des terminaux non connectés
  Point centres[N-2]; // liste des centres
  int Y[N*(N-2)]; // Y_ij = Y[(N-2)*i+j]
  int Z[(N-2)*(N-2)]; // Z_ij = Z[(N-2)*i+j]
  Screen screen(500,500);
  sf::Event event;
  std::srand(std::time(nullptr));

  // initialisation de Y et Z
  for (i=0; i<N*(N-2); i++)
    Y[i] = 0;
  for (i=0; i<(N-2)*(N-2); i++)
    Z[i] = 0;

  initTerminaux(screen, terminaux); // initialise et affiche les terminaux
  for (int i=0 ; i<N ; i++)
    terminauxNC[i] = i;
  initCentres(screen, terminauxNC, terminaux, centres, Y, Z); // création "aléatoire" et affichage des centres selon l'algorithme

  // affichage dans le terminal de Y et Z
  std::cout << "Y =" << std::endl;
  for (i=0; i<N; i++) {
    std::cout << "| ";
    for (j=0; j<N-2; j++)
      std::cout << Y[(N-2)*i+j] << " ";
    std::cout << "|" << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Z =" << std::endl;
  for (i=0; i<N-2; i++) {
    std::cout << "| ";
    for (j=0; j<N-2; j++)
      std::cout << Z[(N-2)*i+j] << " ";
    std::cout << "|" << std::endl;
  }

  // gestion de la touche pour quitter
  while(screen.isOpen()) {
    while (screen.pollEvent(event))
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        screen.close();
  }

  return 0;
}


void initTerminaux(Screen& _screen, Point * _terminaux)
{
  // détermination des coordonnées des terminaux selon un octogone régulier
  _terminaux[0].setXY(450, 167); // (1+sqrt(2), 1)
  _terminaux[1].setXY(333, 50); // (1, 1+sqrt(2))
  _terminaux[2].setXY(167, 50); // (-1, 1+sqrt(2))
  _terminaux[3].setXY(50, 167); // (-1-sqrt(2), 1)
  _terminaux[4].setXY(50, 333); // (-1-sqrt(2), -1)
  _terminaux[5].setXY(167, 450); // (-1, -1-sqrt(2))
  _terminaux[6].setXY(333, 450); // (1, -1-sqrt(2))
  _terminaux[7].setXY(450, 333); // (1+sqrt(2), -1)

  // fond blanc
  _screen.rect(0, 0, 500, 500, 0xFFFFFFFF);

  // affichage des terminaux
  std::string zeta = "zt_";
  for (int i=0 ; i<N ; i++) {
    _screen.disc(_terminaux[i].getX(), _terminaux[i].getY(), 10, 0xFF0000FF);
    _screen.text(_terminaux[i].getX() + 5, _terminaux[i].getY() - 30, zeta + std::to_string(i+1), 0x000000FF);
  }
  _screen.render();
  sf::sleep(sf::milliseconds(1000)); // délai d'affichage pour voir l'algorithme étape par étape
}


void initCentres(Screen& _screen, std::vector<int> _terminauxNC, Point * _terminaux, Point * _centres, int * _Y, int * _Z)
{
  int t, t1, t2, idx;
  std::string x = "x_";

  // sélection des 2 terminaux initiaux
  //t1 = std::rand()%N;
  //do {
  //  t2 = std::rand()%N;
  //}
  //while(t1 == t2);
  t1 = 0;
  t2 = 1;

  // création du 1er centre
  _screen.line(_terminaux[t1].getX(), _terminaux[t1].getY(), _terminaux[t2].getX(), _terminaux[t2].getY(), 0x000000FF);
  _centres[0].setXY((_terminaux[t1].getX()+_terminaux[t2].getX())/2, (_terminaux[t1].getY()+_terminaux[t2].getY())/2);
  _Y[(N-2)*t1] = 1;
  _Y[(N-2)*t2] = 1;
  _screen.disc(_centres[0].getX(), _centres[0].getY(), 10, 0x0000FFFF);
  _screen.text(_centres[0].getX() + 5, _centres[0].getY() - 30, x + std::to_string(1), 0x000000FF);
  if (t1 > t2) {
    _terminauxNC.erase(_terminauxNC.begin()+t1);
    _terminauxNC.erase(_terminauxNC.begin()+t2);
  } else {
    _terminauxNC.erase(_terminauxNC.begin()+t2);
    _terminauxNC.erase(_terminauxNC.begin()+t1);
  }
  _screen.render();
  sf::sleep(sf::milliseconds(1000));

  // création des n-3 autres centres
  for (int i=0 ; i<N-3 ; i++) {
    t = std::rand()%(N-3-i); // on choisit aléatoirement un terminal de _terminauxNC, sauf zt_n
    idx = _terminauxNC[t]; // on récupère son indice car il peut différer de son indice dans la liste
    _screen.line(_centres[i].getX(), _centres[i].getY(), _terminaux[idx].getX(), _terminaux[idx].getY(), 0x000000FF);
    _screen.render();
    sf::sleep(sf::milliseconds(1000));
    _centres[i+1].setXY((_centres[i].getX()+_terminaux[idx].getX())/2, (_centres[i].getY()+_terminaux[idx].getY())/2);
    _screen.disc(_centres[i+1].getX(), _centres[i+1].getY(), 10, 0x0000FFFF);
    _screen.text(_centres[i+1].getX() + 5, _centres[i+1].getY() - 30, x + std::to_string(i+2), 0x000000FF);
    _terminauxNC.erase(_terminauxNC.begin()+t);
    _Y[(N-2)*idx+i+1] = 1;
    _Z[(N-2)*i+i+1] = 1;
  }
  _screen.line(_centres[N-3].getX(), _centres[N-3].getY(), _terminaux[_terminauxNC[0]].getX(), _terminaux[_terminauxNC[0]].getY(), 0x000000FF);
  _screen.render();
  sf::sleep(sf::milliseconds(1000));
  _Y[(N-2)*_terminauxNC[0]+N-3] = 1;
}

