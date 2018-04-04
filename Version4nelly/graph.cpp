#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}

void Graph::ajouter_sommet(bool *fin, bool *fin2, int *cpt)
{
    if((mouse_b&1) && ((mouse_x>=500 && mouse_x<=800) && (mouse_y>=25 && mouse_y<=49)) && !(*fin))
    {
        *fin=true;
        *cpt=1;
    }

    else if((mouse_b&1) && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) && *fin && *cpt>=50)
    {
        Sommet s;
        s.m_coordx=mouse_x;
        s.m_coordy=mouse_y;
        s.m_nom_img="0.jpg";
        s.m_num=m_ordre;

        m_vect_sommets.push_back(s);
        m_ordre+=1;

        add_interfaced_vertex(m_vect_sommets[m_ordre-1].m_num, m_vect_sommets[m_ordre-1].m_taille_pop, m_vect_sommets[m_ordre-1].m_coordx, m_vect_sommets[m_ordre-1].m_coordy, m_vect_sommets[m_ordre-1].m_nom_img);
        *cpt=0;
        *fin=false;
    }


}

///Enregistrer dans un fichier
void Graph::enregistrer_donnees_som()
{
    std::ofstream fichier("donnees_sommets.txt", std::ios::trunc);

    if(fichier)
    {
        fichier << m_ordre << std::endl;

        for(int i=0; i<m_ordre; ++i)
        {
            fichier << m_vect_sommets[i].m_num << " ";
            fichier << m_vect_sommets[i].m_taille_pop << " ";
            fichier << m_vect_sommets[i].m_coordx << " ";
            fichier << m_vect_sommets[i].m_coordy << " ";
            fichier << m_vect_sommets[i].m_nom_img << std::endl;
        }
        fichier.close();
    }
}

///Récupérer dans le fichier
void Graph::recup_donnees_som()
{
    Sommet s;

    std::ifstream fichier("donnees_sommets.txt");

    if(fichier)
    {
        fichier >> m_ordre;

        for(int i=0; i<m_ordre; ++i)
        {
            fichier >> s.m_num;
            fichier >> s.m_taille_pop;
            fichier >> s.m_coordx;
            fichier >> s.m_coordy;
            fichier >> s.m_nom_img;

            m_vect_sommets.push_back(s);
        }
        fichier.close();
    }
}

/// enregister pour les relations (arcs)

///Enregistrer dans le fichier des relations
void Graph::enregistrer_donnees_ar()
{
    std::ofstream fichier("relations.txt", std::ios::trunc);

    if(fichier)
    {
        fichier << m_nb_aretes << std::endl;

        for(int i=0; i<m_nb_aretes; ++i)
        {
            fichier << m_vect_aretes[i].m_num_arete << " ";
            fichier << m_vect_aretes[i].m_from << " ";
            fichier << m_vect_aretes[i].m_to << " ";
            fichier << m_vect_aretes[i].m_weight << std::endl;
        }

        fichier.close();
    }
}

///Récupérer dans le fichier relations
void Graph::recup_donnees_ar()
{
    Edge a;

    std::ifstream fichier("relations.txt");

    if(fichier)
    {
        fichier >> m_nb_aretes;

        for(int i=0; i<m_nb_aretes; ++i)
        {
            fichier >> a.m_num_arete;
            fichier >> a.m_from;
            fichier >> a.m_to;
            fichier >> a.m_weight;

            m_vect_aretes.push_back(a);
        }

        fichier.close();
    }
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 300);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    ///Récupérer les données (coordonnées, taille population, nom de fichier image)
    recup_donnees_som();
    recup_donnees_ar();

    /// Les sommets doivent être définis avant les arcs
    for (int i =0; i<m_ordre; i++)
    {
        add_interfaced_vertex(m_vect_sommets[i].m_num, m_vect_sommets[i].m_taille_pop, m_vect_sommets[i].m_coordx, m_vect_sommets[i].m_coordy, m_vect_sommets[i].m_nom_img);
    }

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...

    for (int i =0; i<m_nb_aretes; i++)
    {
        add_interfaced_edge(m_vect_aretes[i].m_num_arete, m_vect_aretes[i].m_from, m_vect_aretes[i].m_to, m_vect_aretes[i].m_weight);
    }
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    /// OOOPS ! Prendre en compte l'arc ajouté dans la topologie du graphe !
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

///afiicher la map d'arete
void Graph:: afficher_aretes()
{

    for (const auto &elem : m_edges)
    {
        std::cout <<elem.first;
        std::cout <<elem.second.m_from;
        std::cout <<std::endl;
    }

}


void Graph::ajouter_arete(bool *finn, bool *finn2, int *cptt,   Sommet *s1, Sommet *s2)
{
    bool gauche = false;
    bool pgauche = &gauche;


    /// si il clique sur ajouter un sommet
    if((mouse_b&1) && ((mouse_x>=500 && mouse_x<=800) && (mouse_y>=49 && mouse_y<=66)) && !(*finn))
    {
        *finn=true;
        *cptt=1;
        std::cout << "choisissez les deux sommets entre lesquels vous souhaitez ajouter une arete." <<std::endl;
    }

/// si il clique GAUCHE et dans l'ecran sur un sommet
    else if((mouse_b&1) && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) && *finn && *cptt>=50)
    {
        std::cout << "on clique gauche  " <<std::endl;
        ///on recupère les coordonnées de la ou on a clique
        double mouseposx = mouse_x;
        double mouseposy = mouse_y;

        // std::cout << "pos "<<  mouseposx << mouseposy <<std::endl;
        //std::cout << "pos "<<  m_vect_sommets[4].m_coordx << m_vect_sommets[4].m_coordy <<std::endl;


        for (unsigned int i=0; i<m_vect_sommets.size(); ++i)
        {

            /// si il clique sur un sommet
            if ( mouseposy >=m_vect_sommets[i].m_coordy && mouseposy <=m_vect_sommets[i].m_coordy + 100 &&mouseposx>=m_vect_sommets[i].m_coordx-80 && mouseposx <= m_vect_sommets[i].m_coordx +20 )

            {
                //std::cout << "1";
                std::cout << i;
                // std::cout << "hola";


                s1 = &m_vect_sommets[i];
            }
            ///on recupère ce sommet
        }
        pgauche=true;
    }
    /// si il clique DROIT
    if (mouse_b&2 && ((mouse_x>=0 && mouse_x<=800) && (mouse_y>=0 && mouse_y<=600)) && pgauche)
    {
        double mouseposx = mouse_x;
        double mouseposy = mouse_y;


        std::cout << "in clique droit " <<std::endl;

        //std::cout << "pos "<<  mouseposx << mouseposy <<std::endl;
        for (unsigned int y=0; y<m_vect_sommets.size(); ++y)
        {

            /// si il clique sur un sommet
            if ( mouseposx>=m_vect_sommets[y].m_coordx-80 && mouseposx <= m_vect_sommets[y].m_coordx +20 && mouseposy >=m_vect_sommets[y].m_coordy && mouseposy <=m_vect_sommets[y].m_coordy + 100)
            {
                ///on recupère ce sommet
                std::cout << "sommet2"<< m_vect_sommets[y].m_num;

                s2 = &m_vect_sommets[y];
            }
        }

        ///on créer une nouvelle arete du s1 au s2
        Edge e;
        e.m_from= s1->m_num;
        e.m_to=s2->m_num;

        e.m_weight= 0;
        /// on l'ajoute au vecteur d'aretes
        std::cout << "push " <<std::endl;
        m_vect_aretes.push_back(e);
        ///on incrémente le nb d'aretes
        m_nb_aretes+=1;
        ///on l'ajoute à l'interface
        add_interfaced_edge(m_vect_aretes.size(), s1->m_num, s2->m_num, 0 );
        *cptt=0;
        *finn=false;
        pgauche = false;
    }
}
