#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    bool finn=false, finn2=false, gauche=false, fin_inna1=false, fin_inna2=false;
    int cpt=0, s=0,cpt_inna=0, compteur = 0;
        bool premier= false, deux=false;

    int cptt=0, v=0;
    Sommet s1;
    Sommet s2;
    Sommet s3;

    std::vector<Edge> incidentes;

    bool click= false;


    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        if(cpt>=1)
            cpt++;
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
       // g.ajouter_sommet();
        ///afficher map aretes
        //g.afficher_aretes();
        ///ajouter arete
        if(cptt>=1)
            cptt++;

            if(cpt_inna>=1)
            cpt_inna++;
g.ar_incidentes(&click, &v);
     //   g.ajouter_arete(&finn, &finn2, &gauche, &cptt, &s1, &s2, &s);

     //   g.supp_arete(&fin_inna1, &fin_inna2, &cpt_inna, &s1, &s2, &s);

        if(compteur>=1)
            compteur++;
//g.supprimer_sommet(&premier, &deux, &compteur, &v);
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        if(cpt>=51)
            cpt=50;
    }

    g.enregistrer_donnees_som();
    g.enregistrer_donnees_ar();

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


