#pragma once
#include "Gora.hh"
#include "Gran.hh"
#include "Obiekt_Sceny.hh"
#include "Plaskowyz.hh"
#include "dron.hh"
#include "powierzchnia.hh"
#include <list>
#include <memory>
using namespace std;
/*!
 * \brief Kalasa opisujaca scene
 *
 *nieniejsza klasa zawiera metody oraz paremetry potrzebne do opisu scene
 */
#include "../include/lacze_do_gnuplota.hh"
class Scena {
  std::list<shared_ptr<Obiekt_Sceny>> lista_przeszkod;
  std::list<shared_ptr<Dron>> lista_Dronow;
  PzG::LaczeDoGNUPlota Lacze;
  Powierzchnia *dno;
  int nr_ob;

public:
  Scena() {
    double argumentsV2[] = {10.0, 25.0, 10.0};
    double argumentsV3[] = {-100.0, -105.0, -10.0};
    double argumentsV4[] = {100.0, 105.0, 0};

    lista_Dronow.push_front(make_shared<Dron>(0, argumentsV2));
    lista_przeszkod.push_front(*lista_Dronow.begin());
    lista_Dronow.push_front(make_shared<Dron>(1, argumentsV3));
    lista_przeszkod.push_front(*lista_Dronow.begin());
    nr_ob = 3;

    for (std::list<std::shared_ptr<Obiekt_Sceny>>::const_iterator k =
             lista_przeszkod.begin();
         k != lista_przeszkod.end(); k++)
      do {

        argumentsV4[0] = rand() % 700 - 350;
        argumentsV4[1] = rand() % 700 - 350;
        lista_przeszkod.push_front(make_shared<Gran>(
            argumentsV4, 100, 150, 150, "../datasets/obiekt0.dat"));
        Lacze.DodajNazwePliku("../datasets/obiekt0.dat");
        if ((*lista_przeszkod.begin())->czy_kolizja(*k)) {
          lista_przeszkod.erase((lista_przeszkod.begin()));
        }
      } while ((*lista_przeszkod.begin())->czy_kolizja(*k));

    for (std::list<std::shared_ptr<Obiekt_Sceny>>::const_iterator k =
             lista_przeszkod.begin();
         k != lista_przeszkod.end(); k++)

      do {

        argumentsV4[0] = rand() % 700 - 350;
        argumentsV4[1] = rand() % 700 - 350;
        lista_przeszkod.push_front(make_shared<Plaskowyz>(
            argumentsV4, 100, 150, 150, "../datasets/obiekt1.dat"));
        Lacze.DodajNazwePliku("../datasets/obiekt1.dat");
        if ((*lista_przeszkod.begin())->czy_kolizja(*k)) {
          lista_przeszkod.erase((lista_przeszkod.begin()));
        }
      } while ((*lista_przeszkod.begin())->czy_kolizja(*k));
    for (std::list<std::shared_ptr<Obiekt_Sceny>>::const_iterator k =
             lista_przeszkod.begin();
         k != lista_przeszkod.end(); k++)
      do {
        if ((*lista_przeszkod.begin())->czy_kolizja(*k)) {
          lista_przeszkod.erase((lista_przeszkod.begin()));
        }
        argumentsV4[0] = rand() % 400 - 200;
        argumentsV4[1] = rand() % 400 - 200;
        lista_przeszkod.push_front(make_shared<Gora>(
            argumentsV4, 100, 150, 250, "../datasets/obiekt2.dat"));
        Lacze.DodajNazwePliku("../datasets/obiekt2.dat");
      } while ((*lista_przeszkod.begin())->czy_kolizja(*k));

    for (int i = 0; i < 2; i++) {
      Lacze.DodajNazwePliku(
          ("../datasets/prostopadloscian" + std::to_string(i) + ".dat")
              .c_str());
      for (int j = 0; j < 4; j++)
        Lacze.DodajNazwePliku(
            ("../datasets/gra" + std::to_string(i) + std::to_string(j) + ".dat")
                .c_str());
    }
    Lacze.DodajNazwePliku("../datasets/dno.dat");
    Lacze.ZmienTrybRys(PzG::TR_3D);
    // Ustawienie zakresow poszczegolnych osi
    Lacze.UstawZakresY(-400, 400);
    Lacze.UstawZakresX(-400, 400);
    Lacze.UstawZakresZ(-400, 400);
    dno = new Powierzchnia(800, 800, -20, "../datasets/dno.dat");
    dno->Zapis();
  }
  /*!
   * Funkcja opisujaca zapis | Argumenty: |
   *                                                |
   */
  void Zapis() {
    for (std::list<std::shared_ptr<Obiekt_Sceny>>::const_iterator k =
             (lista_przeszkod.begin());
         k != lista_przeszkod.end(); k++) {

      (*k)->Zapis();
    }
    Lacze.Rysuj();
  }

  /*!
   * Funkcja opisująca opcje. | Argumenty: |
   *                                                |
   *     \param [in]        kat - kat                        |
   *            \param [in] nr   - nr drona |
   * \param [in] x  -droga |
   *            \param [in] opc   - opcja |
   */

  void opcja() {
    double argumentsV4[] = {100.0, 105.0, 0};
    int opc;
    double x, a;
    double kat = 0;
    int nr;
    std::cout << "1 normlany lot 2 okregi 3 dodaj przeszkode 4 usun "
              << std::endl;
    std::cin >> opc;
    switch (opc) {
    case 1: {
      int dol = 0;
      std::cout << "podaj nr drona: " << std::endl;
      std::cin >> nr;
      std::cout << "podaj drogę: " << std::endl;
      std::cin >> x;
      std::cout << "podaj kat: " << std::endl;
      std::cin >> kat;
      Lacze.DodajNazwePliku("../datasets/droga.dat");
      std::list<std::shared_ptr<Dron>>::const_iterator nowy =
          lista_Dronow.begin();
      for (int i = 0; i < nr; i++)
        nowy++;

      (*nowy)->okresl_droge(x);
      for (int i = 0; i < 50; i++) {
        (*nowy)->lot_w_gore();
        Zapis();
      }

      (*nowy)->set_kat(kat);
      for (int i = 0; i < kat; i++) {

        (*nowy)->obrot();

        Zapis();
      }

      for (int i = 0; i < x; i++) {
        (*nowy)->przesun();

        Zapis();
      }
      while(x!=0)
      {
      for (std::list<std::shared_ptr<Obiekt_Sceny>>::const_iterator k =
               lista_przeszkod.begin();
           k != lista_przeszkod.end(); k++) {
        if ((*lista_przeszkod.begin())->czy_kolizja(*k)) {
          x = 50;
          break;
        }
        for (dol = 0; dol < 50; dol++) {
          (*nowy)->lot_w_dol();
        }
        x=0;
      }

      for (int i = 0; i < dol; i++) {
        (*nowy)->lot_w_gore();
      }
 for (int i = 0; i < x; i++) {
        (*nowy)->przesun();

        Zapis();
      }
      }

      for (int i = 0; i < 50; i++) {
        (*nowy)->lot_w_dol();
        Zapis();
      }
      Lacze.UsunNazwePliku("../datasets/droga.dat");

    } break;
    case 2: {

      std::cout << "podaj nr drona: " << std::endl;
      std::cin >> nr;
      std::cout << "podaj drogę: " << std::endl;
      std::cin >> x;
      std::cout << "podaj kat: " << std::endl;
      std::cin >> kat;
      std::list<std::shared_ptr<Dron>>::const_iterator nowy =
          lista_Dronow.begin();
      for (int i = 0; i < nr; i++)
        nowy++;

      Lacze.DodajNazwePliku("../datasets/droga.dat");
      (*nowy)->okresl_droge(x);
      for (int i = 0; i < 50; i++) {
        (*nowy)->lot_w_gore();
        Zapis();
      }

      (*nowy)->set_kat(kat);
      for (int i = 0; i < kat; i++) {

        (*nowy)->obrot();

        Zapis();
      }
      for (int i = 0; i < x; i++) {
        (*nowy)->przesun();

        Zapis();
      }

      a = (x * 2) / sqrt(4 + 2 * sqrt(2));
      (*nowy)->okresl_droge(a);
      (*nowy)->set_kat(112);
      for (int i = 0; i < 112; i++) {

        (*nowy)->obrot();

        Zapis();
      }
      for (int i = 0; i < a; i++) {
        (*nowy)->przesun();

        Zapis();
      }
      for (int i = 0; i < 7; i++) {
        (*nowy)->okresl_droge(a);
        (*nowy)->set_kat(45);
        for (int i = 0; i < 45; i++) {

          (*nowy)->obrot();

          Zapis();
        }
        for (int i = 0; i < a; i++) {
          (*nowy)->przesun();

          Zapis();
        }
      }
      (*nowy)->set_kat(112);
      for (int i = 0; i < 112; i++) {

        (*nowy)->obrot();

        Zapis();
      }
      for (int i = 0; i < x; i++) {
        (*nowy)->przesun();

        Zapis();
      }

      for (int i = 0; i < 50; i++) {
        (*nowy)->lot_w_dol();
        Zapis();
      }
      Lacze.UsunNazwePliku("../datasets/droga.dat");
    }

    break;
    case 3:

    {
      argumentsV4[0] = rand() % 400 - 200;
      argumentsV4[1] = rand() % 400 - 200;
      int ob = rand() % 3;

      if (ob == 0) {
        lista_przeszkod.push_front(make_shared<Gora>(
            argumentsV4, 100, 150, 250,
            "../datasets/obiekt" + std::to_string(nr_ob) + ".dat"));
        Lacze.DodajNazwePliku(
            ("../datasets/obiekt" + std::to_string(nr_ob) + ".dat").c_str());
      }
      if (ob == 1) {
        lista_przeszkod.push_front(make_shared<Plaskowyz>(
            argumentsV4, 100, 150, 250,
            "../datasets/obiekt" + std::to_string(nr_ob) + ".dat"));
        Lacze.DodajNazwePliku(
            ("../datasets/obiekt" + std::to_string(nr_ob) + ".dat").c_str());
      }
      if (ob == 2) {
        lista_przeszkod.push_front(make_shared<Gran>(
            argumentsV4, 100, 150, 250,
            "../datasets/obiekt" + std::to_string(nr_ob) + ".dat"));
        Lacze.DodajNazwePliku(
            ("../datasets/obiekt" + std::to_string(nr_ob) + ".dat").c_str());
      }
      nr_ob++;
    }

    break;
    case 4: {
      std::cout << "podaj nr obiektu: " << std::endl;
      std::cin >> nr;
      std::list<std::shared_ptr<Obiekt_Sceny>>::const_iterator k =
          (lista_przeszkod.begin());
      for (int i = 0; i < nr; i++) {
        k++;
      }
      Lacze.UsunNazwePliku((*k)->get_nazwa());
      lista_przeszkod.erase(k);
    } break;
    default:
      break;
    }
  }
};