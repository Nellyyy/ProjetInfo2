#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>

class Sommet
{
public:
    int m_num;
    double m_taille_pop;
    int m_coordx, m_coordy;
    std::string m_nom_img;

    Sommet() {m_num=0; m_taille_pop=0; m_coordx=0; m_coordy=0; m_nom_img="";}
};


#endif // SOMMET_H_INCLUDED
