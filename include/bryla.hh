#pragma once
#include   <vector>
#include "matrix.hh"
#include "vector.hh"
#include "Obiekt_Sceny.hh"
/*!
 * \brief Kalasa opisujaca bryle
 *
 *nieniejsza klasa zawiera metody oraz paremetry potrzebne do opisu bryly
 */

class  bryla:public Obiekt_Sceny, public std::enable_shared_from_this<bryla>
{
protected:
int SIZE;
  Vector<3> srodek;
   std::vector<Vector<3>> point;
   std::string nazwa;
   public:
   Vector<3> get_srodek(){return srodek;}
 double promien(){return sqrt(pow(srodek[0]-point[0][0],2) + pow(srodek[1]-point[0][1],2)+pow(srodek[2]-point[0][2],2));}
const   Vector<3> &operator [] (int index) const;
  Vector<3> &operator [] (int index) ;
 bryla operator + (  Vector<3> move);
void move_r(  Vector<3> move);
void rot(Matrix<3> mac);
std::string get_nazwa(){return nazwa;}
bool czy_kolizja(shared_ptr<Obiekt_Sceny> ob)
{
      std::shared_ptr<bryla> self = shared_from_this();
 if (ob != self) {

        Vector<3> srodek_Bryly = get_srodek();
        Vector<3> srodek_Obiektu = ob->get_srodek();
        double l = sqrt(pow(srodek_Bryly[0] - srodek_Obiektu[0], 2) + pow(srodek_Bryly[1] - srodek_Obiektu[1], 2) + pow(srodek_Bryly[2] - srodek_Obiektu[2], 2));
        if (promien() + ob->promien() >= l)
        {
            return true;
        }
 }
    return false;
}
bool Zapis()
{
  std::ofstream  StrmPlikowy;

  StrmPlikowy.open(nazwa);
  if (!StrmPlikowy.is_open())
    {

    return false;
  }

 for(int i=0;i< 8;i++)
    {
    StrmPlikowy<<point[i]<<std::endl;
    if((i+1)%2==0)
      StrmPlikowy<<std::endl;
    }
    StrmPlikowy<<point[0]<<std::endl;
     StrmPlikowy<<point[1]<<std::endl;

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}

};
/*!
 * rotacja bryly                                                          |
 *  Argumenty:                                                                |
 *     \param[in] mac - macie obr                                                 |
 *                                                |
 *                                                                    |
 *    \retval  bryla po obr                              |
 */
void bryla::rot(Matrix<3> mac)
{
    for(int i=0;i< SIZE;i++)
    {
        point[i]=mac*(point[i]-srodek)+srodek;
    }
   
}


/*!
 *  Funktor bryla.                                                                                                                      
 * \param[in] index - index wektora.                                                                                                             
 * \retval Wartosc Bryly w danym miejscu tablicy.                              
 */
const   Vector<3> & bryla::operator [] (int index) const
{
    return point[index];
}
/*!
 *  Funktor Bryly.                                                                                                                      
 * \param[in] index - index wektora.                                                                                                             
 * \retval Wartosc Bryly w danym miejscu tablicy.                              
 */
  Vector<3> & bryla::operator [] (int index) 
{
return point[index];
}
/*!
*  Realizuje dodawanie Wektora do Bryly.                                                                      
 * \param[in]  move- drugi skladnik dodawania.                                         
  * \retval    Sume dwoch skladnikow pointcholkow Bryly i wektora                                                                             
 */
 bryla  bryla::operator + (  Vector<3> move)
{
    
     bryla wynik;
  
    for(int i=0;i< SIZE;i++)
        wynik[i]=point[i]+move;
    return wynik;
    
}

/*!
*  funkcja przesowajaca Bryla o dany wektor                                                                  
 * \param[in]  move- wektor translacjia.   
 * \param this - Bryla                                     
  * \retval   Bryla po przesunueciu                                                                          
 */
void  bryla::move_r(  Vector<3> move)
{
     
     srodek=srodek+move;
    for(int i=0;i< SIZE;i++)
        point[i]=point[i]+move;
 
}





