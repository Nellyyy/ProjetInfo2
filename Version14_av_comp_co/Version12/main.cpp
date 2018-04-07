#include "grman/grman.h"
#include <iostream>
#include <string>

#include "graph.h"

int main()
{

    bool finn=false, fin=false, finn2=false, gauche=false, fin_inna1=false, choix1=false, choix2=false, ev=false;
    int cpt=0, s=0, s1=13, s2=13, cpt_inna=0, chaine=4, a=0;
    bool nelly1 =false, nelly2=false;
    int cptt=0;
    std::string nom="", nom_fic_som="", nom_fic_ar="", nom_fic_idx_arc="";
    Sommet s3, s4;
    std::vector<Graph> g;
    Graph g_temp;

    g.push_back(g_temp);
    g.push_back(g_temp);

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )




    while ( !key[KEY_ESC] )
    {
        if(chaine==4)
        {
            std::cout << "Entrer le reseau trophique a explorer :\n(Taper 'pics' pour graphe Ocean, 'pics2' pour graphe Savane)\n";
            std::cin >> nom;

            if(nom=="pics")
            {
                nom_fic_som="chaine/donnees_sommets1.txt";
                nom_fic_ar="chaine/relations1.txt";
                chaine=0;
            }
            else if(nom=="pics2")
            {
                nom_fic_som="chaine2/donnees_sommets2.txt";
                nom_fic_ar="chaine2/relations2.txt";
                chaine=1;
            }

            /// A appeler en 1er avant d'instancier des objets graphiques etc...
            grman::init();

            /// Le nom du répertoire où se trouvent les images à charger
            grman::set_pictures_path(nom);

            /// Un exemple de graphe
            if(nom=="pics" && !choix1)
            {
                a++;
                choix1=true;
                g[chaine].make_example(nom_fic_som, nom_fic_ar);
            }
            else if(nom=="pics2" && !choix2)
            {
                a++;
                choix2=true;
                g[chaine].make_example(nom_fic_som, nom_fic_ar);
            }
        }

        if(cpt>=1)
            cpt++;
        if(cpt_inna>=1)
            cpt_inna++;
        if(cptt>=1)
            cptt++;

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g[chaine].ajouter_sommet(chaine);
        g[chaine].evolution_pop(&ev);

        ///afficher map aretes
        //g.afficher_aretes();

        ///ajouter arete

        g[chaine].ajouter_arete(&finn, &finn2, &gauche, &cptt, &s1, &s2);

        g[chaine].supp_arete(&fin_inna1, &cpt_inna, &s);

        g[chaine].supprimer_sommet(&fin, &cptt);

        ///connexe
        g[chaine].connexe(&nelly1, &nelly2);

        g[chaine].update(&chaine);

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        if(cpt>=51)
            cpt=50;
    }

    if(a>1)
    {
        g[0].enregistrer_donnees_som("chaine/donnees_sommets1.txt");
        g[0].enregistrer_donnees_ar("chaine/relations1.txt");
        g[1].enregistrer_donnees_som("chaine2/donnees_sommets2.txt");
        g[1].enregistrer_donnees_ar("chaine2/relations2.txt");
    }
    else
    {
        g[chaine].enregistrer_donnees_som(nom_fic_som);
        g[chaine].enregistrer_donnees_ar(nom_fic_ar);
    }


    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


