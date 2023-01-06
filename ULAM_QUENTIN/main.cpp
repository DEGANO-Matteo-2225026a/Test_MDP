#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <cstdlib>
#include <sstream>

using namespace std;

typedef vector<unsigned> vUInt;
typedef vector<vUInt> mUInt;

void affichTab (const vUInt & tab) {
    for (const auto & i : tab)
        cout << i << "-";
    cout << endl;
}

void affichTab (const mUInt & tab) {
    for (const auto & i : tab) {
        for (const auto & j : i)
            cout << j << " ";
        cout << endl;
    }
}

vUInt genNbPremiers (const unsigned & n) {
    vUInt tab (n);

    for (size_t i (0) ; i < tab.size() ; ++i)
        tab[i] = i + 1;

    for (size_t i (1) ; i < tab.size() ; ++i) {
        if (tab[i] == 0) continue;
        size_t j (tab[i] + i);
        while (j < tab.size()) {
            tab[j] = 0;
            j += tab[i];
        }
    }

    size_t posAInserer (2);

    for (size_t i (2) ; i < tab.size() ; ++i) {
        if (tab[i] == 0) continue;
        tab[posAInserer] = tab[i];
        posAInserer += 1;
    }
    tab.resize(posAInserer);
    return tab;
}

void genMatSpirale (mUInt & mat) {
    size_t i (mat.size()/2), j (mat.size()/2);
    unsigned numTour (1), nbAInserer (2);
    mat[i][j++] = 1;

    for ( ; nbAInserer < mat.size() * mat.size() ; ) {
        // haut
        for (unsigned k (0) ; k < 2 * numTour ; ++k) {
            mat[i][j] = nbAInserer++;
            --i;
        }
        ++i;
        --j;

        // gauche
        for (unsigned k (0) ; k < 2 * numTour ; ++k) {
            mat[i][j] = nbAInserer++;
            --j;
        }
        ++i;
        ++j;

        // bas
        for (unsigned k (0) ; k < 2 * numTour ; ++k) {
            mat[i][j] = nbAInserer++;
            ++i;
        }
        --i;
        ++j;

        // droite
        for (unsigned k (0) ; k < 2 * numTour ; ++k) {
            mat[i][j] = nbAInserer++;
            ++j;
        }

        ++numTour;
    }
}

void genMatUlam (mUInt & mat, const vUInt & tabPremiers) {

    for (vector<unsigned> & ligne : mat) {
        for (unsigned & val : ligne) {
            if (binary_search(tabPremiers.begin(), tabPremiers.end(), val))
                val = 0;
        }
    }
}

void imgPpm(const mUInt & mat) {
    ofstream ofs ("img.ppm");
    ofs << "P3" << '\n';
    ofs << mat.size() << ' ' << mat.size() << '\n';
    ofs << "255" << '\n' << '\n';
    string c1 ("255 0 0 ");
    const string c2 ("0 0 0 ");
    for (auto & i : mat) {

        for (auto & j : i) {
            ostringstream oss;
            oss << rand()%255 << ' ' << rand()%255 << ' ' << rand()%255 << ' ';
            c1 = oss.str();
            ofs << (j == 0 ? c1 : c2);
        }
        ofs << '\n';
    }
}

int main()
{
    srand(time(NULL));
    size_t n (1001);
    vUInt tab;
    mUInt mat (n, vector<unsigned>(n, 0));
    tab = genNbPremiers(n*n);
    genMatSpirale(mat);
    genMatUlam(mat, tab);
    imgPpm(mat);
    return 0;
}
