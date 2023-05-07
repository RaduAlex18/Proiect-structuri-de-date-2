#include <iostream>

using namespace std;

constexpr int nivel_maxim = 10;

struct nod
{
    int valoare;
    nod** succesor;

    nod(int nivel, int& valoare)
    {
        succesor = new nod * [nivel + 1];
        memset(succesor, 0, sizeof(nod*) * (nivel + 1));
        this->valoare = valoare;
    }

    ~nod()
    {
        delete[] succesor;
    }
};

class Skip_List
{
private:
    nod* radacina;
    int valoare;
    int nivel;

public:
    Skip_List();
    ~Skip_List();
    void introducere_element(int& valoare_introdusa);
    bool cautare(int& valoare_cautata);
    void stergere_element(int& valoare_stergere);
    void afisare();
};

Skip_List::Skip_List()
{
    radacina = new nod(nivel_maxim, valoare);
    nivel = 0;
}

Skip_List::~Skip_List()
{
    delete radacina;
}


float f_rand()
{
    return (float)rand() / RAND_MAX;
}

int random_level()
{
    static bool incercare = true;
    if (incercare)
    {
        srand((unsigned)time(NULL));
        incercare = false;
    }
    int lvl = (int)(log(f_rand()) / log(1. - (0.5)));

    if (lvl < nivel_maxim)
        return lvl;
    else
        return nivel_maxim;
}


void Skip_List::introducere_element(int& valoare_introdusa)
{
    nod* n = radacina;
    nod* update[nivel_maxim + 1];
    memset(update, 0, sizeof(nod*) * (nivel_maxim + 1));
    for (int i = nivel; i >= 0; i--)
    {
        while (n->succesor[i] != NULL && n->succesor[i]->valoare < valoare_introdusa)
        {
            n = n->succesor[i];
        }
        update[i] = n;
    }
    n = n->succesor[0];
    if (n == NULL || n->valoare != valoare_introdusa)
    {
        int lvl = random_level();
        if (lvl > nivel)
        {
            for (int i = nivel + 1; i <= lvl; i++)
            {
                update[i] = radacina;
            }
            nivel = lvl;
        }
        n = new nod(lvl, valoare_introdusa);
        for (int i = 0; i <= lvl; i++)
        {
            n->succesor[i] = update[i]->succesor[i];
            update[i]->succesor[i] = n;
        }
    }
}

bool Skip_List::cautare(int& valoare_cautata)
{
    nod* nod = radacina;
    for (int i = nivel; i >= 0; i--)
    {
        while (nod->succesor[i] != NULL && nod->succesor[i]->valoare < valoare_cautata)
        {
            nod = nod->succesor[i];
        }
    }
    nod = nod->succesor[0];
    if (nod != NULL && nod->valoare == valoare_cautata)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void Skip_List::stergere_element(int& valoare_stergere)
{
    nod* n = radacina;
    nod* update[nivel_maxim + 1];
    memset(update, 0, sizeof(nod*) * (nivel_maxim + 1));
    for (int i = nivel; i >= 0; i--)
    {
        while (n->succesor[i] != NULL && n->succesor[i]->valoare < valoare_stergere)
        {
            n = n->succesor[i];
        }
        update[i] = n;
    }
    n = n->succesor[0];
    if (n != NULL && n->valoare == valoare_stergere)
    {
        for (int j = 0; j <= nivel; j++)
        {
            if (update[j]->succesor[j] != n)
            {
                break;
            }
            update[j]->succesor[j] = n->succesor[j];
        }
        delete n;
        while (nivel > 0 && radacina->succesor[nivel] == NULL)
        {
            nivel--;
        }
    }
}

void Skip_List::afisare()
{
    nod* n = radacina->succesor[0];
    while (n != NULL)
    {
        cout << n->valoare;
        n = n->succesor[0];
        cout << " ";
    }

    cout << "\n";
}


int main()
{

    Skip_List s;

    while (true)
    {
        int ok;
        cout << "Doresti sa introduci un numar? (apasati 1 pentru a continua ,apasati 0 pentru a iesi)" << "\n";
        cin >> ok;

        if (ok == 1)
        {
            int n;
            cout << "Introdu element: ";
            cin >> n;
            s.introducere_element(n);
            cout << "\n";
        }

        if (ok == 0)
            break;
    }

    s.afisare();

    cout << "\n";

    int verificare;
    cout << "Introdu un numar pentru a vedea daca numarul dat se afla in lista" << "\n";
    cin >> verificare;
    if (s.cautare(verificare))
        cout << "Elementul " << verificare << " se afla in lista" << "\n";
    else
        cout << "Elementul nu se afla in lista" << "\n";

    cout << "\n";

    int verificare_2;
    cout << "Introdu un numar pentru a-l sterge din lista" << "\n";
    cin >> verificare_2;
    if (s.cautare(verificare_2))
    {
        s.stergere_element(verificare_2);
        cout << "Elementul " << verificare_2 << " a fost sters." << "\n";
    }
    else
        cout << "Elementul nu poate fi sters" << "\n";

    cout << "\n";

    s.afisare();
}