#pragma once
#include  <string>
#include <memory>
#include "vector.hh"
using namespace std;

/*!
 * \brief Kalasa opisujaca obiekt_sceny
 *
 *klasa abstrakcyjna z której dziedziczy dron i bryly, klasa bierze udział przy badaniu kolizji
 */

class Obiekt_Sceny
{

public:

virtual bool czy_kolizja(shared_ptr <Obiekt_Sceny> ob)=0;
virtual std::string get_nazwa()=0;
virtual bool Zapis()=0;
virtual Vector<3> get_srodek()=0;
virtual double promien()=0;
};




