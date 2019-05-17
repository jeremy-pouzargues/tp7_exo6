#include <iostream>
#include <vector>


using namespace std;

class Pers /* : public IEditable */
   {
       string   myNom;
       unsigned myAge;

     public :
       Pers (const string & nom, unsigned age)
             : myNom (nom), myAge (age) {}

       const string & getNom (void) const noexcept { return myNom; }
       unsigned       getAge (void) const noexcept { return myAge; }

     private :
       ostream & display (ostream & os)  const
       {
           return os << getAge () << " - " << getNom ();

       } // display()

     public :    // ajouté pour faciliter les essais

       friend ostream & operator << (ostream & os, const Pers & p)
       {
           return p.display (os);
       }

   }; // Pers

class ILessThanGen
{
public:
    virtual ~ILessThanGen() {}
    virtual bool operator()(const Pers& p1, const Pers& p2) const = 0;

};

class TriParAgeAsc : public ILessThanGen
{
public:
    virtual ~TriParAgeAsc() {}
    virtual bool operator()(const Pers& p1, const Pers& p2) const
    {
        return p1.getAge() <= p2.getAge();
    }
};

class TriParNomDesc : public ILessThanGen
{
public:
    virtual ~TriParNomDesc() {}
    virtual bool operator()(const Pers& p1, const Pers& p2) const
    {
        return p1.getNom()>= p2.getNom();
    }
};

template <typename Iter_t>
void selectSort (Iter_t deb, Iter_t fin,
                const ILessThanGen& IsInf)
{
    if (fin <= deb) return;

    for ( ; deb < fin - 1; ++deb)
    {
        Iter_t rgMin = deb;
        for (Iter_t j (deb + 1); j < fin; ++j)
            if (IsInf (*j, *rgMin)) rgMin = j;
        swap (*deb, *rgMin);
    }

} // selectSort()

void testLessThanAbstrGen (void)
    {
        cout << "LessThanAbstrGen : \n";

        typedef vector <Pers> CVPers;
        typedef CVPers::size_type IndPers_t;
        CVPers vPers;

        vPers.push_back (Pers ("Charlotte", 21));
        vPers.push_back (Pers ("Alfred",    12));
        vPers.push_back (Pers ("Jean",      42));
        vPers.push_back (Pers ("Noemie",    11));
        vPers.push_back (Pers ("Berthe",    99));
        vPers.push_back (Pers ("Agathe",    29));
        vPers.push_back (Pers ("Sylvain",   42));
        vPers.push_back (Pers ("Pierre",    75));

        cout << "\nTri par age croissant\n\n";

        selectSort (vPers.begin(), vPers.end(), TriParAgeAsc());

        for (const Pers & personne : vPers)
            cout << personne << '\n';

        cout << "\nTri par nom decroissant\n\n";

        selectSort (vPers.begin (), vPers.end (), TriParNomDesc ());

        for (const Pers & personne : vPers)
            cout << personne << '\n';

    } // testLessThanAbstrGen()

int main()
{
   testLessThanAbstrGen();
    return 0;
}

