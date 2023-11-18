#include<regex>
#include<string>
#include<vector>
#include<regex>
#include<mutex>
#include<exception>
#include<thread>
#include <iostream>
using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Pojas { BIJELI, ZUTI, NARANDZASTI, ZELENI, PLAVI, SMEDJI, CRNI };
enum Dupliranje { BEZ_DUPLIKATA, SA_DUPLIKATIMA };
const char* ispisPojasa[] = { " BIJELI", "ZUTI", "NARANDZASTI", "ZELENI", "PLAVI", "SMEDJI", "CRNI" };
bool ValidirajEmail(string email) {
    return regex_match(email, regex("[0-9][_][a-zA-Z]{3,}[._]?[a-zA-Z]{3,}@(karate|edu.karate).(ba|com|org)"));
}
char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}
template<class T1, class T2, int max = 15>
class Kolekcija {
    T1 _elementi1[max];
    T2 _elementi2[max];
    int* _trenutno;
    Dupliranje _dupliranje;
public:
    Kolekcija(Dupliranje dupliranje = SA_DUPLIKATIMA) {
        _trenutno = new int(0);
        _dupliranje = dupliranje;
    }
    Kolekcija(const Kolekcija& obj) {
        _trenutno = new int(*obj._trenutno);
        _dupliranje = obj._dupliranje;
        for (int i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj) {
            delete _trenutno;
            _trenutno = new int(*obj._trenutno);
            _dupliranje = obj._dupliranje;
            for (int i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
            }
        }
        return *this;
    }
    bool JesuLiIsti(T1 el1, T2 el2) {
        for (int i = 0; i < *_trenutno; i++)
        {
            if (_dupliranje == BEZ_DUPLIKATA && _elementi1[i] == el1 && _elementi2[i] == el2)
                return true;
        }
        return false;
    }
    void AddElement(T1 el1, T2 el2) {
        if (JesuLiIsti(el1, el2))
            throw exception("Ne mozes dodati iste elemente!");
        if (*_trenutno > max)
            throw exception("Ne mozes dodati vise od maksimalnog broja elemenata!");
        _elementi1[*_trenutno] = el1;
        _elementi2[*_trenutno] = el2;
        (*_trenutno)++;
    }
    Kolekcija<int, int> operator()(int pocetak, int kraj) {
        if (kraj > *_trenutno)
            throw exception("Opseg nije validan!");
        Kolekcija<int, int> nova;
        for (int i = pocetak; i <= kraj; i++)
        {
            nova.AddElement(_elementi1[i], _elementi2[i]);
        }
        return nova;
    }

    ~Kolekcija() {
        delete _trenutno; _trenutno = nullptr;
    }

    T1 getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (int i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
};
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj) {
            _dan = new int(*obj._dan);
            _mjesec = new int(*obj._mjesec);
            _godina = new int(*obj._godina);
        }
        return *this;
    }
    bool operator==(Datum obj) {
        return *_godina == *obj._godina && *_mjesec == *obj._mjesec && *_dan == *obj._dan;
    }
    int getDane()const
    {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }
    bool operator>(const Datum drugi)
    {
        return this->getDane() > drugi.getDane();
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }

};
class Tehnika {
    char* _naziv;
    Kolekcija<Datum, int>* _ocjene;
public:
    Tehnika(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<Datum, int>(); 
        if (ocjena > 0)
            AddOcjena(&datum, ocjena);
    }
    Tehnika(const Tehnika& obj) {
        _naziv = GetNizKaraktera(obj._naziv);
        _ocjene = new Kolekcija<Datum, int>(*obj._ocjene);
    }
    Tehnika& operator=(const Tehnika& obj) {
        if (this != &obj) {
            delete[]_naziv;
            _naziv = GetNizKaraktera(obj._naziv);
            _ocjene = new Kolekcija<Datum, int>(*obj._ocjene);
        }
        return *this;
    }
    void AddOcjena(Datum* datum, int ocjena) {
        _ocjene->AddElement(*datum, ocjena);
    }
    float ProsjecnaOcjenaTehnike() {
        float prosjek = 0;
        if (_ocjene->getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _ocjene->getTrenutno(); i++)
        {
            prosjek += _ocjene->getElement2(i);
        }
        return prosjek / _ocjene->getTrenutno();
    }
    bool operator==(Tehnika obj) {
        return strcmp(_naziv, obj._naziv) == 0;
    }
    ~Tehnika() {
        delete[] _naziv; _naziv = nullptr;
        delete _ocjene; _ocjene = nullptr;
    }
    char* GetNaziv()const { return _naziv; }
    Kolekcija<Datum, int> GetOcjene() const { return *_ocjene; }
    friend ostream& operator<<(ostream& COUT, Tehnika& obj) {
        COUT << "Naziv tehnike: " << obj._naziv << endl;
        for (int i = 0; i < obj._ocjene->getTrenutno(); i++)
        {
            COUT << "Ocjena: " << obj._ocjene->getElement2(i) << ", datum: " << obj._ocjene->getElement1(i) << endl;
        }
        COUT << "Prosjecna ocjena za tehniku: " << obj.ProsjecnaOcjenaTehnike() << endl;
        return COUT;
    }
};
class Polaganje {
    Pojas _pojas;
    Kolekcija<Tehnika*, string> _polozeneTehnike;
public:
    Polaganje(Pojas pojas = BIJELI) {
        _pojas = pojas;
    }
    Polaganje(const Polaganje& obj) {
        _pojas = obj._pojas;
        _polozeneTehnike = obj._polozeneTehnike;
    }
    Polaganje& operator=(const Polaganje& obj) {
        if (this != &obj) {
            _pojas = obj._pojas;
            _polozeneTehnike = obj._polozeneTehnike;
        }
        return *this;
    }
    float GetProsjekPojas() {
        float prosjek = 0;
        if (_polozeneTehnike.getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _polozeneTehnike.getTrenutno(); i++)
        {
            prosjek += _polozeneTehnike.getElement1(i)->ProsjecnaOcjenaTehnike();
        }
        return prosjek / _polozeneTehnike.getTrenutno();
    }
    Kolekcija<Tehnika*, string>& GetTehnike() { return _polozeneTehnike; }
    Pojas GetPojas() { return _pojas; }
    friend ostream& operator<< (ostream& COUT, const Polaganje& obj) {
        COUT << ispisPojasa[obj._pojas] << " ";
        for (int i = 0; i < obj._polozeneTehnike.getTrenutno(); i++) {
            COUT << *obj._polozeneTehnike.getElement1(i) << " " << obj._polozeneTehnike.getElement2(i) << endl;
            cout << crt << endl;
        }

        return COUT;
    }

};
mutex muteks;
class KaratePolaznik {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Polaganje> _polozeniPojasevi;
    void SaljemMejl(Pojas pojas, Tehnika tehnika)
    {
        muteks.lock();
        cout << "FROM:info@karate.ba\nTO: " << GetEmail() << "\nPostovani " << GetImePrezime() << ", evidentirana vam je tehnika " << tehnika.GetNaziv() << " za " << ispisPojasa[pojas] << " pojas" << endl;
        cout << "Dosadasnji uspjeh na pojasu " << ispisPojasa[pojas] << " iznosi: ";
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            if (_polozeniPojasevi[i].GetPojas() == pojas)
                cout << _polozeniPojasevi[i].GetProsjekPojas();
        }
        cout << ", a ukupni prosjek na svim pojasevima je -> " << GetUkupniProsjek() << "\nPozdrav.\n\nKARATE Team." << crt;
        muteks.unlock();
    }
public:
    KaratePolaznik(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = ValidirajEmail(emailAdresa) ? emailAdresa : "not set";
        _brojTelefona = brojTelefona;
    }
    KaratePolaznik(const KaratePolaznik& obj) {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
    }
    KaratePolaznik& operator=(const KaratePolaznik& obj) {
        if (this != &obj) {
            delete[]_imePrezime;
            _imePrezime = GetNizKaraktera(obj._imePrezime);
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
        }
        return *this;
    }
    bool PostojeLiIsti(Pojas pojas, Tehnika& tehnika) {
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            if (_polozeniPojasevi[i].GetPojas() == pojas) {
                for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++)
                {
                    if (_polozeniPojasevi[i].GetTehnike().getElement1(j) == &tehnika)
                        return true;
                }
            }
        }
        return false;
    }
    bool AddTehniku(Pojas pojas, Tehnika& tehnika, string napomena = "napomena") {
        if (_polozeniPojasevi.size() == 0 && pojas > 1)
            return false;
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            if ((pojas > _polozeniPojasevi[i].GetPojas() && _polozeniPojasevi[i].GetTehnike().getTrenutno() < 1 && _polozeniPojasevi[i].GetProsjekPojas() < 3.5))
                return false;
            if (_polozeniPojasevi[i].GetPojas() == pojas) {
                if (PostojeLiIsti(pojas, tehnika))
                    return false;

                _polozeniPojasevi[i].GetTehnike().AddElement(&tehnika, napomena);
                thread t1(&KaratePolaznik::SaljemMejl, this, pojas, tehnika);
                t1.join();
                return true;
            }
        }
        Polaganje p(pojas);
        p.GetTehnike().AddElement(&tehnika, napomena);
        _polozeniPojasevi.push_back(p);
        thread t1(&KaratePolaznik::SaljemMejl, this, pojas, tehnika);
        t1.join();
        return true;
    }
    float GetUkupniProsjek() {
        float prosjek = 0;
        if (_polozeniPojasevi.size() == 0)
            return prosjek;
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
            prosjek += _polozeniPojasevi[i].GetProsjekPojas();
        return prosjek / _polozeniPojasevi.size();
    }
    float GetProsjecanBrojDana()
    {
        float prosjek = 0;
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++)
            {
                for (int k = 0; k < _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getTrenutno() - 1; k++)
                {
                    prosjek = _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k).getDane()
                        + _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k + 1).getDane();
                }
                return prosjek / _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getTrenutno();
            }
        }
    }

    Kolekcija<Tehnika*, float>& operator()(Datum prvi, Datum drugi)
    {   
        Kolekcija<Tehnika*, float>* objekat = new Kolekcija<Tehnika*, float>();

        float prosjecanBrojDana = GetProsjecanBrojDana();
        for (int i = 0; i < _polozeniPojasevi.size(); i++)
        {
            for (int j = 0; j < _polozeniPojasevi[i].GetTehnike().getTrenutno(); j++)
            {
                for (int k = 0; k < _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getTrenutno(); k++)
                {
                    if (_polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k) > prvi && drugi > _polozeniPojasevi[i].GetTehnike().getElement1(j)->GetOcjene().getElement1(k))
                    {
                        objekat->AddElement(_polozeniPojasevi[i].GetTehnike().getElement1(j), GetProsjecanBrojDana());
                    }
                }
            }
        }
        return *objekat;

    }
    ~KaratePolaznik() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, KaratePolaznik& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (int i = 0; i < obj._polozeniPojasevi.size(); i++)
            COUT << obj._polozeniPojasevi[i];
        return COUT;
    }
    vector<Polaganje>& GetPolozeniPojasevi() { return _polozeniPojasevi; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }
};
void main() {
    Datum temp,
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(BEZ_DUPLIKATA);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    Tehnika choku_zuki("choku_zuki", datum19062021, 5),
        gyaku_zuki("gyaku_zuki", datum20062021, 5),
        kizami_zuki("kizami_zuki", datum30062021, 2),
        oi_zuki("oi_zuki", datum05072021, 5);

    choku_zuki.AddOcjena(&datum05072021, 3);
    choku_zuki.AddOcjena(&datum05072021, 5);

    cout << choku_zuki << endl;

    if (ValidirajEmail("2_ime.prezime@edu.karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("3_ime_prezime@karate.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("4_imeprezime@karate.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("8_imeprezime@karate.org"))
        cout << "Email validan" << crt;
    if (!ValidirajEmail("2ime.prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;
    if (!ValidirajEmail("5_ime prezime@edu.karate.org"))
        cout << "Email NIJE validan" << crt;


    KaratePolaznik* jasmin = new KaratePolaznik("Jasmin Azemovic", "1_jasmin.azemovic@karate.ba", "033 281 172");
    KaratePolaznik* adel = new KaratePolaznik("Adel Handzic", "2_adel_handzic@edu.karate.ba", "033 281 170");
    KaratePolaznik* emailNotValid = new KaratePolaznik("Ime Prezime", "korisnik@karate.ru", "033 281 170");

  
    if (jasmin->AddTehniku(NARANDZASTI, kizami_zuki, "Napomena 0"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, gyaku_zuki, "Napomena 1"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, kizami_zuki, "Napomena 2"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, oi_zuki, "Napomena 3"))
        cout << "Tehnika uspjesno dodan!" << crt;
    if (jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 4"))
        cout << "Tehnika uspjesno dodan!" << crt;

    if (!jasmin->AddTehniku(ZUTI, choku_zuki, "Napomena 5"))
        cout << "Tehnika NIJE uspjesno dodana!" << crt;

    std::cout << *jasmin << crt;

    Kolekcija<Tehnika*, float> jasminUspjeh = (*jasmin)(Datum(18, 06, 2021), Datum(21, 06, 2021));
    for (int i = 0; i < jasminUspjeh.getTrenutno(); i++)
        cout << *jasminUspjeh.getElement1(i) << " " << jasminUspjeh.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete emailNotValid;

    cin.get();
    system("pause>0");
}