#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <cstdlib>
using namespace std;

struct noeud {
  int valeur; 
  noeud *gauche; 
  noeud *droit;
};

class ABR { 

  private:
    noeud *racine;
  public:


    // Initialisation d'une racine avec une valeur
    ABR (noeud *racine,int d)
     {
      racine->valeur = d;
      racine->gauche = NULL;
      racine->droit = NULL;
     }

    ~ABR()
     {
     }

    // Tester sur Valgrind 11 allocs,11 frees,1,320 bytes allocated
    // tester avec l'option valgrind --leack-check=full
    void Destroy(noeud *racine)
     {
      if(racine == NULL)
       {
        return;
       }
      Destroy(racine->gauche);
      Destroy(racine->droit);
      delete(racine);    
     }

    void Inserer(noeud *racine, int d)
     {

      if(d < racine->valeur)
       {
        if(racine->gauche != NULL)
         {
          Inserer(racine->gauche,d);
         }
        else
         {
          racine->gauche = new noeud();
          racine->gauche->valeur = d;
          racine->gauche->droit = NULL;
          racine->gauche->droit = NULL; 
         }
       }
      else if (d >= racine->valeur)
       {
        if(racine->droit != NULL)
         {
          Inserer(racine->droit,d);
         }
        else
         {
          racine->droit = new noeud(); 
          racine->droit->valeur = d;
          racine->droit->gauche = NULL;
          racine->droit->droit = NULL;
         }
       }

     }

    
    noeud *SupprimerMin ( noeud *& r )
    { // on vérifie que l'arbre n'est pas vide
        if ( r->gauche != NULL ) // on continue à gauche
            return SupprimerMin ( r->gauche ) ;
        else // le minimum est trouvé à ce stade
        {
            noeud *temp = r ;
            r = r->droit ;
            return temp ;
        }
    }
    
    void supprimer(noeud *&r,int val)
    {
        if ( r == NULL )
            cout << val << "n'est pas dans l'arbre \n";
        else
            if ( val < r->valeur ) // chercher à gauche
                supprimer ( r->gauche, val ) ;
            else
                if ( val > r->valeur ) // chercher à droite
                    supprimer ( r->droit, val ) ;
                else
                {
                    noeud *temp = r ;
                    if ( r->gauche == NULL ) // a seulement un fils droit
                        r = r->droit ; // faire pointer vers la droite
                    else
                        if ( r->droit == NULL ) // seulement un fils gauche
                            r = r->gauche ;
                        else
                        {
                            // le nœud a deux fils
                            temp = SupprimerMin ( r->droit ) ;
                            // supprime le plus petit du fils droit
                            r->valeur = temp->valeur;
                        }
                    delete temp ;
                }
    }


    void Afficher_Arbre(noeud *racine)
     {
      vector<noeud*> file;
      queue<noeud*> Queue;

         
      if(racine == NULL)
      {
          cout << "Il n'y a plus de noeud" << endl;
          return;
          
      }

      file.push_back(racine);
      Queue.push(racine);

      while(Queue.size() > 0)
       {
        noeud *tmp = Queue.front();
        Queue.pop();
        if(tmp->gauche)
         {
          Queue.push(tmp->gauche);
          file.push_back(tmp->gauche); 
         } 
        if(tmp->droit)
         {
          Queue.push(tmp->droit);
          file.push_back(tmp->droit);
         }
       }

      int taille = file.size()-1;

      while(taille >= 0)
       {
        noeud *fin = file[taille];
        cout << fin->valeur << endl;
        taille = taille -1 ;  
       }
     }

    // Fonction max pour la hauteur
    int max (int a , int b)
     {
      if ( a > b )
       return a;
      else return b;
     }


    int Afficher_hauteur(noeud *racine)
     {
      if (racine == NULL)
       {
        return -1;
       }
      else
       {
        return (1 + max(Afficher_hauteur(racine->gauche),Afficher_hauteur(racine->droit)));
       }
     }

    void Afficher_Ascendant(noeud *racine, int d)
     {

      stack<int> ascendant;
      noeud *tpm = racine;
         
      if(racine == NULL)
      {
          cout << "Il n'y a pas d'ascendant" << endl;
          return;
      }

      while(tpm->valeur != d && tpm != NULL)
       {
        if(d <= tpm->valeur)
         {
          ascendant.push(tpm->valeur);
          tpm = tpm->gauche;
         }
        else
         {
          ascendant.push(tpm->valeur);
          tpm = tpm->droit;
         }
       }

      while(ascendant.empty() != true)
       {
        cout << ascendant.top() << endl;
        ascendant.pop();
       }
     }


    void Archiver (noeud *racine, std::ofstream&  fichier)
     { 
      if(racine == NULL)
       {
        fichier << "/,";
       }
      if(racine != NULL)
       {
        fichier << racine->valeur << ",";
        Archiver(racine->gauche,fichier);
        Archiver(racine->droit,fichier); 
       } 
     }


    void Prefixe(noeud *racine)
     {
      if(racine != NULL)
       {
        cout << racine->valeur << endl;
        Prefixe(racine->gauche);
        Prefixe(racine->droit);
       }
     }
};



int main()
{  
  bool first = true; 
  noeud *racine = new noeud();
  ifstream fichierT("FT.txt",ios::in);
  string ligne;
  ofstream fichier("Sequentielle.txt",ios::out |ios::trunc); 
  string nombre = "";
  getline(fichierT,ligne);

    int x = 2;
    while(ligne[x] != '\0')
    {
        nombre.push_back(ligne[x]);
        x = x + 1;
    }
    
    ABR arbre(racine,std::stoi(nombre));
    cout << "On insere: " << nombre << endl;
    first = false;
    nombre = "";

  if(fichierT)
   {
    while(getline(fichierT,ligne))
     { 
      if(ligne[0] == 'I' && first == false)
       {
        int i = 2;
        while(ligne[i] != '\0')
         {
          nombre.push_back(ligne[i]);
          i = i + 1; 
         }
        arbre.Inserer(racine,std::stoi(nombre));
        cout << "on insere: " << nombre << endl;
        nombre = "";
       }

      if(ligne[0] == 'S')
       {
        int i = 2;
        while(ligne[i] != '\0')
         {
          nombre.push_back(ligne[i]);
          i = i + 1;
         }

        arbre.supprimer(racine,std::stoi(nombre));
        cout << "On supprime: " << nombre << endl;
        nombre = "";

       }
      if(ligne[0] == 'A')
       {
        cout << "L'affichage niveau par niveau est le suivant: " << endl;
        arbre.Afficher_Arbre(racine);
       }
      if(ligne[0] == 'H' && ligne[2] == ':')
       {

        int nb = arbre.Afficher_hauteur(racine);
        cout << "La hauteur est: " << nb << endl;

       }
      if(ligne[0] == 'G')
       {
        int i = 2;
        while(ligne[i] != '\0')
         {
          nombre.push_back(ligne[i]);
          i = i + 1;
         }
        cout << "Les ascendants de: " << nombre << " " << "sont: " << endl;
        arbre.Afficher_Ascendant(racine,std::stoi(nombre));
        nombre = "";
       }
      if(ligne[0] == 'T')
       {
        fichier << "Implementation Sequentielle: Les / sont les fils nuls: "<< endl;
        fichier << "Chaque fils est separe par une virgule. " << endl; 
        arbre.Archiver(racine,fichier);
       } 
     }
   }


}
