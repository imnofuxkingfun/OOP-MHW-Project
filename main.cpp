#include <iostream>
#include <string.h>
#include <vector>

using namespace std;
//MONSTER HUNTER WORLD INSPIRED!

class weapon{
    float base_atk;
    string name;
    float *atk_bonus; //se scaleaza/creste in functie de nr de combo-uri
    int maxCombo; //nr de combo-uri maxima - lungimea de la atk_bonus
    string element; //fiecare arma poate sa aiba o putere elementara
    float elemental_bonus; //bonusul de atk adus la acel element
    bool equipped; //doar un weapon poate fi eqquiped, dar poate sa aiba mai multe weapons

public:
    weapon() //constructor fara parametrii
    { //the basic, default weapon

        this->base_atk = 112;
        this->name = "Sword & Shield";
        this->maxCombo = 4;
        this->atk_bonus = new float[maxCombo];
        this->atk_bonus[0] = 10.5;
        this->atk_bonus[1] = 17.25;
        this->atk_bonus[2] = 22.6;
        this->atk_bonus[3] = 30;
        this->element = "-"; //adica nici un element
        this->elemental_bonus = 0;
        this->equipped = true;

    }

    weapon(float base_atk, string name, float *atk_bonus, int maxCombo, string element,
           float elementalBonus, bool equipped)
    { //constr cu toti parametrii
        this->base_atk = base_atk;
        this->name=name;
        this->maxCombo = maxCombo;
        this->atk_bonus = new float[maxCombo];
        for(int i = 0; i<maxCombo; i++)
        {
            this->atk_bonus[i] = atk_bonus[i];
        }
        this->element = element;
        this->elemental_bonus = elementalBonus;
        this->equipped = equipped;
    }

    weapon(string name, bool equipped)
    {
        this->base_atk = 112;
        this->name = name;
        this->maxCombo = 4;
        this->atk_bonus = new float[maxCombo];
        this->atk_bonus[0] = 10.5;
        this->atk_bonus[1] = 17.25;
        this->atk_bonus[2] = 22.6;
        this->atk_bonus[3] = 30;
        this->element = "-"; //adica nici un element
        this->elemental_bonus = 0;
        this->equipped = equipped;
    }

    weapon(string element, float elemental_bonus)
    {
        this->base_atk = 112;
        this->name = "Sword & Shield";
        this->maxCombo = 4;
        this->atk_bonus = new float[maxCombo];
        this->atk_bonus[0] = 10.5;
        this->atk_bonus[1] = 17.25;
        this->atk_bonus[2] = 22.6;
        this->atk_bonus[3] = 30;
        this->element = element;
        this->elemental_bonus = elemental_bonus;
        this->equipped = true;
    }

    weapon(const weapon &w)//copy constructor
    {
        this->base_atk = w.base_atk;
        this->name=w.name;
        this->maxCombo = w.maxCombo;
        this->atk_bonus = new float[w.maxCombo];
        for(int i = 0; i<w.maxCombo; i++)
        {
            this->atk_bonus[i] = w.atk_bonus[i];
        }
        this->element = w.element;
        this->elemental_bonus = w.elemental_bonus;
        this->equipped = w.equipped;

    }

    //OPERATORI
    weapon& operator=(const weapon &w) //ok deci facem deep copy
    { //adica supraincarcarea op. egal pt clasa weapon
        if(this != &w) //verificam adresele
        { //si daca sunt diferite, copiem

            if (this->atk_bonus != NULL) {
                delete[] this->atk_bonus;
                this->atk_bonus = NULL;
            }

            this->base_atk = w.base_atk;
            this->name=w.name;
            this->maxCombo = w.maxCombo;
            this->element = w.element;
            this->elemental_bonus = w.elemental_bonus;
            this->equipped = w.equipped;
            //daca exista atk bonus, stergem
            if(this->atk_bonus != NULL)
                delete[] this->atk_bonus;
            this->atk_bonus = new float[this->maxCombo];
            for(int i = 0; i<w.maxCombo; i++)
            {
                this->atk_bonus[i] = w.atk_bonus[i];
            }
            //operatorul asteapta o valoarea returnata
            //da toata valoarea, fara * e doar referentiere catre valoare
        }
        return *this;
    }

    weapon& operator++()//mareste maxCombo si atk_bonus cu 1
    {
        float *auxAtkBonus = new float [this->maxCombo];
        for(int i=0; i<this->maxCombo; i++)
            auxAtkBonus[i] = this->atk_bonus[i];
        this->maxCombo++;
        if(this->atk_bonus != NULL)
            delete[] this->atk_bonus;
        this->atk_bonus = new float[this->maxCombo];
        for(int i = 0; i<this->maxCombo-1; i++)
            this->atk_bonus[i] = auxAtkBonus[i];
        this->atk_bonus[maxCombo-1] = 0;
        if(auxAtkBonus != NULL)
            delete[] auxAtkBonus;
        return *this;
    }

    weapon& operator++(int)
    {
        weapon aux = *this;
        ++(*this);//!!
        return aux;
    }

    weapon operator+(weapon w) //concat name and add base-atk
    {
        w.name = this->name+" "+w.name;
        w.base_atk = this->base_atk + w.base_atk;
        if(w.element == "-") //daca al doilea obiect nu are element, ia de la primul
        {
            w.element = this->element;
            w.elemental_bonus = this->elemental_bonus;
        }
        return w;
    }

    weapon operator+(float atk) const//aduna la base atk
    {
        weapon w = *this;//ca sa nu modificam obiectul
        w.base_atk += atk;
        return w;
    }


    weapon operator*(weapon w) //concat name and medie aritmetica la base-atks
    {
        w.name = this->name+"*"+w.name;
        w.base_atk = (this->base_atk + w.base_atk)/2.0;
        if(w.element == "-") //daca al doilea obiect nu are element, ia de la primul
        {
            w.element = this->element;
            w.elemental_bonus = this->elemental_bonus;
        }
        return w;
    }

    weapon operator*(float atk) const//mull la base atk
    {
        weapon w = *this;//ca sa nu modificam obiectul
        w.base_atk *= atk;
        return w;
    }

    bool operator<=(weapon w)//verica daca base atk + el-bonus + combos <= cele din w
    {
        float maxAtk, wmaxAtk;
        maxAtk = this->base_atk + this->elemental_bonus;
        wmaxAtk = w.base_atk + w.elemental_bonus;
        for(int i = 0; i < this->maxCombo; i++)
            maxAtk += this->atk_bonus[i];

        for(int i = 0; i < w.maxCombo; i++)
            wmaxAtk += w.atk_bonus[i];

        if(maxAtk <= wmaxAtk)
            return true;
        return false;

    }

    bool operator==(weapon w) //ce e <= + daca au acelasi element
    {
        float maxAtk, wmaxAtk;
        maxAtk = this->base_atk + this->elemental_bonus;
        wmaxAtk = w.base_atk + w.elemental_bonus;
        for(int i = 0; i < this->maxCombo; i++)
            maxAtk += this->atk_bonus[i];

        for(int i = 0; i < w.maxCombo; i++)
            wmaxAtk += w.atk_bonus[i];

        if(maxAtk == wmaxAtk)
            if(w.element == this->element)
                return true;
        return false;
    }

    int operator[](int index)
    {
        if(index >= 0 && index < this->maxCombo)
            return this->atk_bonus[index];
        throw runtime_error("-invalid index-");
    }

    operator float() const //cast -> si converteste in atk total(de la <=)
    {
        float maxAtk;
        maxAtk = this->base_atk + this->elemental_bonus;
        for(int i = 0; i < this->maxCombo; i++)
            maxAtk += this->atk_bonus[i];

        return maxAtk;
    }


    
    friend istream& operator>>(istream& in, weapon &w);
    friend ostream& operator<<(ostream& in, weapon &w);


    //SETTERS AND GETTERS
    string getName() {
        return this->name;
    }

    void setName(string name) {
        this->name = name;
    }

    float getBaseAtk() { //setter si getter de FLOAT base_atk
        return this->base_atk;
    }

    void setBaseAtk(float baseAtk) {
        base_atk = baseAtk;
    }

    const float *getAtkBonus(){ //de ce e const? //setter si getter de FLOAT* atk bonus
        return this->atk_bonus;
    }

    void setAtkBonus(float *atkBonus){
        if (this->atk_bonus != NULL)
            delete [] this->atk_bonus;
        this->atk_bonus = new float[this->maxCombo];
        for(int i = 0; i < this->maxCombo; i++)
            this->atk_bonus[i] = atkBonus[i];
    }

    int getMaxCombo()  {
        return this->maxCombo;
    }

    void setMaxCombo(int maxCombo) {
        this->maxCombo = maxCombo;
    }

    string getElement(){
        return this->element;
    }

    void setElement( string element){
        this->element = element;
    }

    float getElementalBonus() {
        return this->elemental_bonus;
    }

    void setElementalBonus( float elemental_bonus){
        this->elemental_bonus = elemental_bonus;
    }

    bool getEquipped() {
        return this->equipped;
    }

    void setEquipped(bool equipped){
        this->equipped = equipped;
    }

    //destructor
    ~weapon()
    {
        if(this->atk_bonus != NULL)
            delete[] this->atk_bonus;
    }

    //citire weapon
    void citire() {
        if (this->atk_bonus != NULL) {
            delete[] this->atk_bonus;
            this->atk_bonus = NULL;
        }

        cout<<endl;
        cout<<"Weapon's name:";
        cin.get();
        getline(cin,this->name);//e facut asa ca sa poata avea spatii!
        cout<<"Base Attack:";
        cin>>this->base_atk;
        cout<<"Number of Maximum Combos (min. 2):";
        cin>>this->maxCombo;
        cout<<"Attack bonus per combo:";
        this->atk_bonus = new float [this->maxCombo + 1];
        for(int i = 0; i < this->maxCombo; i++)
            cin>>this->atk_bonus[i];
        cout<<"Weapon element (Insert '-' for None):";
        cin>>this->element;
        if(this->element!="-")
        {
            cout<<"Elemental bonus:";
            cin>>this->elemental_bonus;
        }
        else this->elemental_bonus = 0;

        cout<<"Equip the weapon? [Y/N]";
        char yn;
        cin>>yn;
        if(yn == 'Y' || yn == 'y')
            this->equipped = true;
        else this->equipped = false;
    }

    void afisare()
    {
        cout<<endl;
        cout<<"Weapon's name:"<<this->name<<endl;
        cout<<"Base Attack:"<< this->base_atk<<endl;
        cout<<"Number of Maximum Combos:"<<this->maxCombo<<endl;
        cout<<"Attack bonus per combo:";
        for(int i = 0; i < this->maxCombo; i++)
            cout<<this->atk_bonus[i]<<" ";
        cout<<endl<<"Weapon element:"<<this->element<<endl;
        cout<<"Elemental bonus:"<<this->elemental_bonus<<endl;
        cout<<"The weapon is:";
        if(this-> equipped == true)
            cout<<"equipped"<<endl;
        else cout<<"not equipped"<<endl;
        cout<<endl;
    }




};

///////////////////////////////////////////////////////

class armour{

    string name;//numele armurii
    double def; //valorea de baza de defense a armurii;
    int bonus_def[5]; //pe rand, in ordine de vs:fire, water, thunder, ice, dragon
    bool equipped;

public:
    //CONSTRUCTORS
    armour() //const fara parametrii
    { //the basic, starter armour
        this->name = "Leather";
        this->def = 10;
        this->bonus_def[0] = 10; //in rest sunt 0 //l-as modifica sa fie dinamic dar nu stiu cum sau daca sa il scot de tot?
        for(int i = 1; i <5; i++)
            this->bonus_def[i] = 0;
        this->equipped = true;
    }

    armour( string name, double def, int bonus_def[5], bool equipped)  //const cu toti parametrii
    {
        this->name = name;
        this-> def = def;
        for(int i = 0; i < 5; i++)
            this->bonus_def[i] = bonus_def[i];
        this->equipped = equipped;

    }

    armour(string name)
    {
        this->name = name;
        this->def = 10;
        this->bonus_def[0] = 10; //in rest sunt 0 //l-as modifica sa fie dinamic dar nu stiu cum sau daca sa il scot de tot?
        for(int i = 1; i <5; i++)
            this->bonus_def[i] = 0;
        this->equipped = true;
    }

    armour(double def)
    {
        this->name = "Leather";
        this->def = def;
        this->bonus_def[0] = 10; //in rest sunt 0 //l-as modifica sa fie dinamic dar nu stiu cum sau daca sa il scot de tot?
        for(int i = 1; i <5; i++)
            this->bonus_def[i] = 0;
        this->equipped = true;
    }

    //copy constructor
    armour(const armour &a)
    {
        this->name = a.name;
        this-> def = a.def;
        for(int i = 0; i < 5; i++)
            this->bonus_def[i] = a.bonus_def[i];
        this->equipped = a.equipped;
    }

    //OPERATORI
    armour& operator=(const armour &a) //supraincarcarea op. = pt clasa armour
    {
        if(this != &a)
        {
            this->name = a.name;
            this-> def = a.def;
            for(int i = 0; i < 5; i++)
                this->bonus_def[i] = a.bonus_def[i];
            this->equipped = a.equipped;
        }
        return *this;
    }

    //operatorul ++ nu are sens la clasa asta

    armour operator+(armour a)//concat names, sum def and sum the bonuses
    {
        a.name = this->name+" "+a.name;
        a.def = a.def + this->def;
        for(int i = 0; i < 5; i++)
            a.bonus_def[i] = a.bonus_def[i] + this->bonus_def[i];
        return a;
    }

    armour operator+(double def)//adauga la def
    {
        armour a = *this;
        a.def += def;
        return a;
    }

    armour operator*(armour a)//concat names cu *, medie aritmetica def and bonuses->ca la weapon
    {
        a.name = this->name+"*"+a.name;
        a.def = (a.def + this->def)/2;
        for(int i = 0; i < 5; i++)
            a.bonus_def[i] = (a.bonus_def[i] + this->bonus_def[i])/2;
        return a;
    }

    armour operator*(double def) //mull la def
    {
        armour a = *this;
        a.def *= def;
        return a;
    }

    bool operator>=(armour a)//daca def+bonus <= cele din a (ca la weapon)
    {
        double maxDef, amaxDef;
        maxDef = this->def;
        amaxDef = a.def;
        for(int i=0; i<5; i++)
        {
            maxDef += this->bonus_def[i];
            amaxDef += a.bonus_def[i];
        }
        if(maxDef >= amaxDef)
            return true;
        return false;
    }

    bool operator==(armour a)//ca mai sus dar ==
    {
        double maxDef, amaxDef;
        maxDef = this->def;
        amaxDef = a.def;
        for(int i=0; i<5; i++)
        {
            maxDef += this->bonus_def[i];
            amaxDef += a.bonus_def[i];
        }
        if(maxDef == amaxDef)
            return true;
        return false;
    }

    int operator[](int index)
    {
        if(index >= 0 && index<5)
            return this->bonus_def[index];
        throw runtime_error("-invalid index-");
    }

    operator double() const//def+bonus def
    {
        double maxDef;
        maxDef = this->def;
        for(int i=0; i<5; i++)
        {
            maxDef += this->bonus_def[i];
        }
        return maxDef;
    }
    
    

    friend istream& operator>>(istream& in, armour &a);
    friend ostream& operator<<(ostream& out, armour &a);

    //SETTERS AND GETTERS
    double getDef(){ //setter si getter la DOUBLE def
        return this->def;
    }

    void setDef (double def){
        this -> def = def;
    }

    //destructor - empty bc we have no dynamic variables?
    ~armour(){}

    void citire(){
        cout<<"Armour's Name:";
        cin.get();
        getline(cin,this->name);
        cout<<"Base Defense Value:";
        cin>>this->def;
        cout<<"Bonus Defence:"<<endl<<"vs. Fire:";
        cin>>this->bonus_def[0];
        cout<<"vs. Water:";
        cin>>this->bonus_def[1];
        cout<<"vs. Thunder:";
        cin>>this->bonus_def[2];
        cout<<"vs. Ice:";
        cin>>this->bonus_def[3];
        cout<<"vs. Dragon:";
        cin>>this->bonus_def[4];
        cout<<"Equip the armour? [Y/N]";
        char yn;
        cin>>yn;
        if(yn == 'Y' || yn == 'y')
            this->equipped = true;
        else this->equipped = false;
    }

    void afisare(){
        cout<<"Armour's Name:"<<this->name<<endl;
        cout<<"Base Defense Value:"<<this->def<<endl;
        cout<<"Bonus Defence:"<<endl<<"vs. Fire:"<<this->bonus_def[0];
        cout<<endl<<"vs. Water:"<<this->bonus_def[1];
        cout<<endl<<"vs. Thunder:"<<this->bonus_def[2];
        cout<<endl<<"vs. Ice:"<<this->bonus_def[3];
        cout<<endl<<"vs. Dragon:"<<this->bonus_def[4];

        cout<<endl<<"The armour is:";
        if(this-> equipped == true)
            cout<<"equipped"<<endl;
        else cout<<"not equipped"<<endl;
        cout<<endl;
    }



};

///////////////////////////////////////////////////////

class hunter_appearence{
    char gender;// M sau F
    string hair_color;
    string eye_color[2]; //[0] e pt ochiul stang, [1] pt drept
    int face_shape; //avem n tipuri de fete prestabilite -nr e intre 1 si n
//    int nose_shape;
//    int eyebrow_shape;
//    int eye_shape;
//    int lip_shape;  desi ar avea sens in joc, pt proiect sunt repetitive
//    int voice_pack;

public:
    hunter_appearence() //constructor fara parametrii
    { //default, basic appearence
        this->gender = 'M';
        this->hair_color = "brown";
        this->eye_color[0] = eye_color[1] = "brown";
        this->face_shape=1;
    }

    hunter_appearence(char gender, string hairColor, string eyeColor[2], int faceShape)//const cu toti parametrii//
    {
        this->gender = gender;
        this->hair_color = hairColor;
        this->eye_color[0] = eyeColor[0];
        this->eye_color[1] = eyeColor[1];
        this->face_shape = faceShape;
    }

    hunter_appearence(char gender)
    {
        this->gender = gender;
        this->hair_color = "brown";
        this->eye_color[0] = eye_color[1] = "brown";
        this->face_shape=1;
    }

    hunter_appearence(string hairColor, string eyeColor[2])
    {
        this->gender = 'M';
        this->hair_color = hairColor;
        this->eye_color[0] = eyeColor[0];
        this->eye_color[1] = eyeColor[1];
        this->face_shape=1;
    }

    //copy constructor
    hunter_appearence(const hunter_appearence &ha)
    {
        this->gender = ha.gender;
        this->hair_color = ha.hair_color;
        this->eye_color[0] = ha.eye_color[0];
        this->eye_color[1] = ha.eye_color[1];
        this->face_shape = ha.face_shape;

    }
    
    friend istream& operator>>(istream& in, hunter_appearence& ha);
    friend ostream& operator<<(ostream& out, hunter_appearence& ha);

    //OPERATORI
    //supraincarcarea op = pt clasa hunter_appearence
    hunter_appearence &operator=(const hunter_appearence& ha)
    {
        if(this != &ha)
        {
            this->gender = ha.gender;
            this->hair_color = ha.hair_color;
            this->eye_color[0] = ha.eye_color[0];
            this->eye_color[1] = ha.eye_color[1];
            this->face_shape = ha.face_shape;
        }
        return *this;
    }
    //nici aici ++ nu are sens :( im sorry

    hunter_appearence& operator+(hunter_appearence ha)//aduna culorile de par, amesteca ochii
    {
        ha.hair_color = this->hair_color+" "+ha.hair_color;
        //se pastreaza ochiul stang din this
        ha.eye_color[0] = this->eye_color[0];
        return ha;
    }

    hunter_appearence& operator+(string hair) //concat la hair color
    {
        hunter_appearence ha = *this;
        ha.hair_color = ha.hair_color+" "+hair;
        return ha;
    }

    hunter_appearence& operator*(hunter_appearence ha)//ia ochii si genul lui this
    {
        ha.gender = this->gender;
        ha.eye_color[0] = this->eye_color[0];
        ha.eye_color[1] = this->eye_color[1];
        return ha;
    }

    bool operator<(hunter_appearence ha)//pe face shape number
    {
        if(this->face_shape < ha.face_shape)
            return true;
        return false;
    }

    bool operator==(hunter_appearence ha)//pe face shape number
    {
        if(this->face_shape == ha.face_shape)
            return true;
        return false;
    }

    string operator[](int index)
    {
        if(index>=0 && index < 2)
            return this->eye_color[index];
        throw runtime_error("-invalid index-");
    }

    operator char() const//returneaza gender-ul
    {
        return this->gender;
    }


    //destructor
    ~hunter_appearence(){}

    //citire
    void citire(){
        cout<<"Gender:";
        cin>>this->gender;
        cout<<"Hair Color:";
        cin.get();
        getline(cin, this->hair_color);
        cout<<"Left Eye Color:";
        getline(cin, this->eye_color[0]);
        cout<<"Right Eye Color:";
        getline(cin, this->eye_color[1]);
        cout<<"Face Shape:";
        cin>>this->face_shape;
    }

    void afisare(){
        cout<<"Gender:"<<this->gender;
        cout<<endl<<"Hair Color:"<<this->hair_color;
        cout<<endl<<"Left Eye Color:"<<this->eye_color[0];
        cout<<endl<<"Right Eye Color:"<<this->eye_color[1];
        cout<<endl<<"Face Shape:"<<this->face_shape;
        cout<<endl;
    }


};

//////////////////////////////////////////////////////

class hunter
{
    static int idContor; //contorul pt playerbase
    const int playerId; //unic per player
    bool online;//daca player ul e online
    char* username;
    unsigned int level; //nr intreg care reprez level-ul jucatorului
    int hunted_monsters_number; //cati monstri vanati
    int *hunted_monsters; //lista cu monster id's care au fost vanati
    int weapon_number; //cate weapon uri are
    weapon *weapons; //poate sa aiba mai multe arme
    int armour_number; //cate armuri are
    armour *armours; //poate sa aiba mai multe armuri
    hunter_appearence appearence; //doar una

public:
    //CONSTRUCTORS
    hunter():playerId(idContor++) //constructor fara parametrii
    {
        this->online = false;
        this->username = new char[strlen("guest")+1];
        strcpy(this->username,"Guest");
        this->level = 1;
        this->hunted_monsters_number = 0;
        this->hunted_monsters = NULL;
        this->weapon_number = 1;
        this->weapons = new weapon[2];
        this->weapons[0] = weapon(); //the default weapon
        this->armour_number = 1;
        this->armours = new armour[2];
        this->armours[0] = armour(); //adica constr fara parametrii, la ambele
        this->appearence = hunter_appearence(); //same here
    }

    hunter(bool online, char *username, unsigned int level, int huntedMonstersNumber, int *huntedMonsters, int weaponNumber, weapon *weapons, int armourNumber, armour *armours,
           hunter_appearence appearence):playerId(idContor++)//const cu toti param
    {
        this->online = online;
        this->username = new char[strlen(username)];
        strcpy(this->username, username);
        this->level = level;
        this->hunted_monsters_number = huntedMonstersNumber;
        this->hunted_monsters = new int[huntedMonstersNumber];
        for(int i = 0; i < huntedMonstersNumber; i++)
            this->hunted_monsters[i] = huntedMonsters[i];

        this->weapon_number = weaponNumber;
        this->weapons = new weapon[weaponNumber];
        for(int i = 0; i<weaponNumber; i++)
            this->weapons[i] = weapons[i];

        this->armour_number = armourNumber;
        this->armours = new armour[armourNumber];
        for(int i = 0; i<armourNumber; i++)
            this->armours[i] = armours[i];
        this->appearence = appearence;
    }

    hunter(char* username, unsigned int level):playerId(idContor++)
    {
        this->online = false;
        this->username = new char[strlen(username)];
        strcpy(this->username, username);
        this->level = level;
        this->hunted_monsters_number = 0;
        this->hunted_monsters = NULL;
        this->weapon_number = 1;
        this->weapons = new weapon[2];
        this->weapons[0] = weapon();
        this->armour_number = 1;
        this->armours = new armour[2];
        this->armours[0] = armour();
        this->appearence = hunter_appearence();
    }

    hunter(int weaponNumber, weapon *weapons, int armourNumber, armour *armours):playerId(idContor++)
    {
        this->online = false;
        this->username = new char[strlen("guest")+1];
        strcpy(this->username,"Guest");
        this->level = 1;
        this->hunted_monsters_number = 0;
        this->hunted_monsters = NULL;
        this->weapon_number = weaponNumber;
        this->weapons = new weapon[weaponNumber];
        for(int i = 0; i<weaponNumber; i++)
            this->weapons[i] = weapons[i];

        this->armour_number = armourNumber;
        this->armours = new armour[armourNumber];
        for(int i = 0; i<armourNumber; i++)
            this->armours[i] = armours[i];
        this->appearence = hunter_appearence();
    }

    //copy constructor
    hunter(const hunter &h):playerId(h.playerId)
    {

        this->online = h.online;
        this->username = new char[strlen(h.username)];
        strcpy(this->username, h.username);
        this->level = h.level;
        this->hunted_monsters_number = h.hunted_monsters_number;
        this->hunted_monsters = new int[h.hunted_monsters_number];
        for(int i = 0; i < h.hunted_monsters_number; i++)
            this->hunted_monsters[i] = h.hunted_monsters[i];

        this->weapon_number = h.weapon_number;
        this->weapons = new weapon[h.weapon_number];
        for(int i = 0; i<h.weapon_number; i++)
            this->weapons[i] = h.weapons[i];

        this->armour_number = h.armour_number;
        this->armours = new armour[h.armour_number];
        for(int i = 0; i<h.armour_number; i++)
            this->armours[i] = h.armours[i];
        this->appearence = h.appearence;
    }

    //OPERATORI
    //supraincarcarea op = pt clasa HUNTER
    hunter& operator=(const hunter& h)
    {
        if(this != &h) {
            if (this->username != NULL)
                delete[] this->username;
            if (this->hunted_monsters != NULL)
                delete[] hunted_monsters;
            if (this->weapons != NULL)
                delete[] weapons;
            if (this->armours != NULL)
                delete[] armours;

            this->online = h.online;
            this->username = new char[strlen(h.username)];
            strcpy(this->username, h.username);
            this->level = h.level;
            this->hunted_monsters_number = h.hunted_monsters_number;
            this->hunted_monsters = new int[h.hunted_monsters_number];
            for(int i = 0; i < h.hunted_monsters_number; i++)
                this->hunted_monsters[i] = h.hunted_monsters[i];

            this->weapon_number = h.weapon_number;
            this->weapons = new weapon[h.weapon_number];
            for(int i = 0; i<h.weapon_number; i++)
                this->weapons[i] = h.weapons[i];

            this->armour_number = h.armour_number;
            this->armours = new armour[h.armour_number];
            for(int i = 0; i<h.armour_number; i++)
                this->armours[i] = h.armours[i];
            this->appearence = h.appearence;
        }
        return *this;

    }

    hunter& operator++() //mareste lista hunter-monsters
    {
        int *aux = new int [this->hunted_monsters_number];
        for(int i = 0; i < this->hunted_monsters_number; i++)
            aux[i] = this->hunted_monsters[i];

        if(this->hunted_monsters!=NULL)
            delete[] this->hunted_monsters;
        this->hunted_monsters = new int[this->hunted_monsters_number+1];
        for(int i = 0; i < this->hunted_monsters_number; i++)
            this->hunted_monsters[i]=aux[i];
        this->hunted_monsters[this->hunted_monsters_number] = 0;
        this->hunted_monsters_number++;
        if(aux !=NULL)
            delete[] aux;
        return *this;
    }

    hunter operator++(int)
    {
        hunter h=*this;
        ++(*this);
        return h;
    }

    hunter& operator+(hunter &h)//concat usernames,add level and hunted monsters
    {
        char *name = new char[strlen(this->username) + strlen(h.username)+2];//+2 ca avem si -
        strcpy(name,this->username);
        strcat(name,"-");
        strcat(name,h.username);
        if(h.username!=NULL)
            delete[] h.username;
        h.username = new char[strlen(name)+1];
        strcpy(h.username,name);
        if(name!=NULL)
            delete[] name;

        h.level += this->level;


        return h;

    }

    /*hunter& operator*(hunter &h)//adds weapons and armours  and appearences
    {
        int weaponNr, armourNr;
        weaponNr = this->weapon_number + h.weapon_number;
        armourNr = this->armour_number + h.armour_number;
        weapon *aux = new weapon[weaponNr];
        if(weaponNr > 0){
        for(int i = 0; i <h.weapon_number; i++)
            aux[i] = h.weapons[i];
        for(int i = 0; i<this->weapon_number; i++)
            aux[i+h.weapon_number] = this->weapons[i];

        if(h.weapons!=NULL)
            delete[] h.weapons;
        h.weapons = new weapon[weaponNr];
       for(int i = 0; i < weaponNr; i++)
           h.weapons[i] = aux[i];
        if(aux != NULL)
            delete[] aux;
        }

        armour *aux2 = new armour[armourNr];
        for(int i = 0; i <h.armour_number; i++)
            aux2[i] = h.armours[i];
        for(int i = 0; i<this->armour_number; i++)
            aux2[i+h.armour_number] = this->armours[i];
        if(h.armours!=NULL)
            delete[] h.armours;
        h.armours = new armour[armourNr];
        for(int i = 0; i < armourNr; i++)
            h.armours[i] = aux2[i];
        if(aux2 != NULL)
            delete[] aux2;

       // h.appearence = h.appearence + this->appearence;
        return h;

    }*/ //!! ok so initial asta am vrut sa fac dar
   //ceva crapa si nu mai am energie deci o sa i simplific putin. poate mai incerc dupa

   hunter& operator*(hunter &h)//concats hunted monsters
    {
        int auxnr = this->hunted_monsters_number + h.hunted_monsters_number;
        int *aux = new int[auxnr];
            for (int i = 0; i < h.hunted_monsters_number; i++)
                aux[i] = h.hunted_monsters[i];
            for (int i = 0; i < this->hunted_monsters_number; i++)
                aux[i+h.hunted_monsters_number] = this->hunted_monsters[i];

            h.hunted_monsters_number = auxnr;
            if (h.hunted_monsters != NULL)
                delete[] h.hunted_monsters;
            h.hunted_monsters = new int[auxnr];
            for (int i = 0; i < auxnr; i++)
                h.hunted_monsters[i] = aux[i];

        if(aux!=NULL)
            delete[] aux;

        return h;
    }

    bool operator>(hunter h)//pe level
    {
        if(this->level > h.level)
            return true;
        return false;
    }

    bool operator==(hunter h)//pe level
    {
        if(this->level == h.level)
            return true;
        return false;
    }

    int operator[](int index)
    {
        if(index>=0 && index<this->hunted_monsters_number)
            return this->hunted_monsters[index];
        throw runtime_error("-invalid index-");
    }

    operator char*() const//username pointer
    {
        return this->username;
    }


    friend hunter& operator+(hunter &h, const weapon w);
    friend hunter& operator+(const weapon w, hunter &h);
    friend hunter& operator+(hunter &h, const armour a);
    friend hunter& operator+(const armour a,hunter &h);
    friend hunter& operator/(hunter &h, const weapon w);
    friend hunter& operator/(const weapon w,hunter &h);
    friend hunter& operator/(hunter &h, const armour a);
    friend hunter& operator/(const armour a,hunter &h);
    friend istream &operator>>(istream& in, hunter& h);
    friend ostream& operator<<(ostream& out, hunter& h);

    //SETTERS AND GETTERS - IN PERECHE DE 2

    int getIdContor(){
        return this->idContor;
    }

    const int getPlayerId(){
        return this->playerId;
    }

    bool getOnline() { //getter si setter pt BOOL online
        return this->online;
    }

    void setOnline(bool online) {
        this->online = online;
    }

    const char *getUsername() { //getter si setter pt CHAR* username!
        return this->username;
    }

    void setUsername(char *username) {
        if (this->username != NULL){
            delete[] this->username;
            this->username = NULL;}
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
    }

    unsigned int getLevel() {
        return this->level;
    }

    void setLevel(unsigned int level) {
        this->level = level;
    }


    int getHuntedMonstersNumber() { //getter pt INT nr de monstri vanati
        return this->hunted_monsters_number;
    }

    void setHuntedMonstersNumber(int huntedMonstersNumber) { //setter la ac chestie
        this->hunted_monsters_number = huntedMonstersNumber;
    }

    int *getHuntedMonsters() {
        return this->hunted_monsters;
    }

    void setHuntedMonsters(int *huntedMonsters) {
        if (this->hunted_monsters != NULL){
            delete[] this->hunted_monsters;
            this->hunted_monsters = NULL;}
        this->hunted_monsters = new int[hunted_monsters_number];
        for(int i = 0; i<this->hunted_monsters_number; i++)
            this->hunted_monsters[i] = huntedMonsters[i];
    }

    int getWeaponNumber() {
        return this->weapon_number;
    }

    void setWeaponNumber(int weaponNumber) {
        this->weapon_number = weaponNumber;
    }

    weapon *getWeapons() {
        return this->weapons;
    }

    void setWeapons(weapon *weapons) {
        if (this->weapons != NULL){
            delete[] this->weapons;
            this->weapons = NULL;}

        this->weapons = new weapon[this->weapon_number];
        for(int i = 0; i < this->weapon_number; i++)
            this->weapons[i] = weapons[i];
    }

    int getArmourNumber() {
        return this->armour_number;
    }

    void setArmourNumber(int armourNumber) {
        this->armour_number = armourNumber;
    }

    armour *getArmours() {
        return armours;
    }

    void setArmours(armour *armours) {
        if (this->armours != NULL){
            delete[] this->armours;
            this->armours  =  NULL;}
        this->armours = new armour[this->armour_number];
        for(int i = 0; i < this->armour_number; i++)
            this->armours[i] = armours[i];
    }

    hunter_appearence getAppearence()  {
        return appearence;
    }

    void setAppearence(const hunter_appearence &appearence) {
        this->appearence = appearence;
    }


    //destructor
    ~hunter()
    {
        if (this->username != NULL)
            delete[] this->username;
        if (this->hunted_monsters != NULL)
            delete[] hunted_monsters;
        if (this->weapons != NULL)
            delete[] weapons;
        if (this->armours != NULL)
            delete[] armours;
    }


    //citire si afisare hunter
    void citire()
    {

        if (this->username != NULL){
            delete[] this->username;
            this->username = NULL;}
        if (this->hunted_monsters != NULL){
            delete[] this->hunted_monsters;
            this->hunted_monsters = NULL;}
        if (this->weapons != NULL){
            delete[] this->weapons;
            this->weapons = NULL;}
        if (this->armours != NULL){
            delete[] this->armours;
            this->armours  =  NULL;}


        cout<<"Is the player online? [Y/N]:";
        char yn;
        cin>>yn;
        if(yn == 'Y' || yn == 'y')
            this->online = true;
        else this->online = false;

        cout<<"Username:";
        char s[41];
        cin.get();
        cin.getline(s,40);
        this->username = new char[strlen(s)];
        strcpy(this->username, s);
        cout<<"Level:";
        cin>>this->level;
        cout<<"Number of hunted Monsters:";
        cin>>this->hunted_monsters_number;
        if(this->hunted_monsters_number > 0)
        {
            this->hunted_monsters = new int[this->hunted_monsters_number];
            cout<<"Hunted Monsters' ID:";
            for(int i=0; i<this->hunted_monsters_number; i++)
                cin>>this->hunted_monsters[i];
        }
        cout<<"Weapon Number:";
        cin>>this->weapon_number;
        if(this->weapon_number > 0)
        {
            for(int i = 0; i < this->weapon_number;i++) {
                this->weapons[i] = weapon();
                cout << "Set default weapoon?[Y/N]:";
                cin >> yn;
                if (yn != 'Y')
                    this->weapons[i].citire();
            }
        }
        cout<<endl<<"Armours Number:";
        cin>>this->armour_number;
        if(this->armour_number > 0)
        {
            for(int i = 0; i < this->armour_number;i++) {
                this->armours[i] = armour();
                cout << "Set default armour?[Y/N]:";
                cin >> yn;
                if (yn != 'Y')
                    this->armours[i].citire();
            }
        }
        cout<<endl<<"Hunter Appearence:"<<endl;
        cout<<"Set default appearence?[Y/N]:";
        cin>>yn;
        if(yn != 'Y')
            this->appearence.citire();
    }



    void afisare()
    {
        cout<<endl;
        cout<<"Player ID: "<<this->playerId<<endl;
        cout<<"Online:"<<this->online<<endl;
        cout<<"Username:"<<this->username<<endl;
        cout<<"Level:"<<this->level<<endl;
        cout<<"------"<<endl<<"Number of hunted Monsters:"<<this->hunted_monsters_number<<endl;
        if(this->hunted_monsters_number > 0)
        {
            cout<<"Hunted Monsters' ID:";
            for(int i=0; i<this->hunted_monsters_number; i++)
                cout<<this->hunted_monsters[i]<<" ";
        }
        cout<<endl<<"------"<<endl<<"Weapon Number:"<<this->weapon_number<<endl;
        if(this->weapon_number > 0)
        {
            cout<<"Weapons Owned:"<<endl;
            for(int i=0; i<this->weapon_number; i++)
                this->weapons[i].afisare();
        }
        cout<<endl<<"------"<<endl<<"Armours Number:"<<this->armour_number<<endl;
        if(this->armour_number > 0)
        {
            cout<<"Armours Owned:"<<endl;
            for(int i = 0; i<this->armour_number; i++)
                this->armours[i].afisare();
        }
        cout<<endl<<"------"<<endl<<"Hunter Appearence:";
        this->appearence.afisare();
    }


};

////////////////////////////////////////////////////

class monster_appearence{
    string color;
    int skin_texture; //textura din n texturi disponibile
    float height; //inaltimea
    bool wings; //daca are aripi

public:
    monster_appearence() { //constr fara parametrii
        this->color = "yellow";
        this->skin_texture = 1;
        this->height = 140;
        this->wings = false;
    }

    monster_appearence(string color, int skinTexture, float height, bool wings)
    {//constr cu toti param
        this->color = color;
        this->skin_texture = skinTexture;
        this->height = height;
        this->wings = wings;
    }

    monster_appearence(string color) {
        this->color = color;
        this->skin_texture = 1;
        this->height = 140;
        this->wings = false;
    }

    monster_appearence(float height, bool wings) {
        this->color = "yellow";
        this->skin_texture = 1;
        this->height = height;
        this->wings = wings;
    }

    //copy constructor
    monster_appearence(const monster_appearence &mh)
    {
        this->color = mh.color;
        this->skin_texture = mh.skin_texture;
        this->height = mh.height;
        this->wings = mh.wings;
    }

    //OPERATORI
    //supraincarc. op = pt clasa Monster_appearence
    monster_appearence& operator=(const monster_appearence& mh)
    {
        if(this != &mh)
        {
            this->color = mh.color;
            this->skin_texture = mh.skin_texture;
            this->height = mh.height;
            this->wings = mh.wings;
        }
        return *this;
    }
    //++nu are sens la clasa asta

    monster_appearence& operator+(monster_appearence ma)//aduna inaltimea,textura,
    // string colors, daca una are aripi, o sa aiba aripi
    {
        ma.height = (ma.height + this->height)/2.0;
        ma.skin_texture += this->skin_texture;
        ma.color = this->color+"-"+ma.color;
        if(this->wings == true)
            ma.wings = true;
        return ma;
    }

    monster_appearence& operator+(string color) //concat colors
    {
        monster_appearence ma = *this;
        ma.color = ma.color+"-"+color;
        return ma;
    }

    monster_appearence& operator*(monster_appearence ma)//+ la height, culorile in ord inv
    //daca una nu are aripi, le scoate
    {
        ma.height = (ma.height + this->height);
        ma.color = ma.color+"-"+this->color;
        if(this->wings == false || ma.wings == false)
            ma.wings = false;
        return ma;
    }

    bool operator <(monster_appearence ma)//dupa height
    {
        if(this->height < ma.height)
            return true;
        return false;
    }

    bool operator ==(monster_appearence ma)//dupa height
    {
        if(this->height == ma.height)
            return true;
        return false;
    }
    //[] nu are sens aici
    operator string() const
    {
        return this->color;
    }

    friend istream& operator>>(istream& in, monster_appearence& ma);
    friend ostream& operator<<(ostream& out, monster_appearence& ma);
    
    //destructor
    ~monster_appearence() {}

    //citire si afisare
    void citire()
    {
        cout<<"Color:";
        cin>>this->color;
        cout<<"Skin Texture Index:";
        cin>>this->skin_texture;
        cout<<"Height:";
        cin>>this->height;
        cout<<"Does it have wings? [Y/N]";
        char yn;
        cin>>yn;
        if(yn == 'Y' || yn == 'y')
            this->wings = true;
        else this-> wings = false;
    }

    void afisare()
    {
        cout<<endl;
        cout<<"Color:"<<this->color<<endl;
        cout<<"Skin Texture Index:"<<this->skin_texture;
        cout<<endl<<"Height:"<<this->height;
        cout<<endl<<"Wings:"<<this->wings;
    }



};

////////////////////////////////////////////////////

class monster{
    static int idContor;
    const int monster_id; //si asta, odata pus, sa fie constant
    string name;
    char zone; //zona in care putem gasi monstrul;
    //const int level? ca nu se schimba level ul monstrului? dar nu stiu cum sa implementez
    int hp; //viata
    float atk; //atk power
    string elemental_weakness; //daca arma are acel element, cand este lovit se adauga
    // la atk-ul hunter ului si elemental_bonus
    monster_appearence appearence;
public:
    //CONSTRUCTORS

    monster():monster_id(idContor++) { //constructorul fara parametrii
        //the DEFAULTT monster
        this->name = "Jagras";
        this->zone = 'A'; //first zone
        this->hp = 60;
        this->atk = 45;
        this->elemental_weakness = "Fire";
        this->appearence = monster_appearence();
    }

    monster(string name, char zone, int hp, float atk, string elementalWeakness, monster_appearence appearence):monster_id(idContor++)
    { //const cu toti parametrii
        this->name = name;
        this->zone = zone;
        this->hp = hp;
        this->atk = atk;
        this-> elemental_weakness = elementalWeakness;
        this->appearence = appearence;
    }

    monster(string name):monster_id(idContor++) {
        this->name = name;
        this->zone = 'A'; //first zone
        this->hp = 60;
        this->atk = 45;
        this->elemental_weakness = "Fire";
        this->appearence = monster_appearence();
    }

    monster(string name, char zone, string elemental_weakness):monster_id(idContor++) {
        this->name = name;
        this->zone = zone;
        this->hp = 60;
        this->atk = 45;
        this->elemental_weakness = elemental_weakness;
        this->appearence = monster_appearence();
    }

    //copy constructor
    monster(const monster &m):monster_id(m.monster_id)
    {
        this->name = m.name;
        this->zone = m.zone;
        this->hp = m.hp;
        this->atk = m.atk;
        this-> elemental_weakness = m.elemental_weakness;
        this->appearence = m.appearence;
    }

    //OPERATORI
    //supraincarcarea op= pt clasa monster
    monster &operator=(const monster& m)
    {
        if(this != &m)
        {
            this->name = m.name;
            this->zone = m.zone;
            this->hp = m.hp;
            this->atk = m.atk;
            this-> elemental_weakness = m.elemental_weakness;
            this->appearence = m.appearence;
        }
        return *this;
    }
    //nici aici ++ nu are sens
    
    monster& operator+(monster m)//concat name, add hp, add atk, add appareance
    {
        m.name = this->name+" "+m.name;
        m.hp += this->hp;
        m.atk += this->atk;
        m.appearence = m.appearence + this->appearence;
        return m;
    }
    
    monster& operator+(int hp)//ii adauga viata
    {
        monster m = *this;
        m.hp += hp;
        return m;
    }
    
    monster& operator*(monster m)//*concat name, ma hp si atk, mull appearence
    {
        m.name = this->name+"*"+m.name;
        m.hp = (m.hp+this->hp)/2;
        m.atk = (m.atk+this->atk)/2.0;
        m.appearence = m.appearence * this->appearence;
    }

    bool operator>(monster m) //dupa hp + atk;
    {
        if((this->hp + this->atk)>(m.hp + m.atk))
            return true;
        return false;
    }

    bool operator==(monster m) //dupa hp + atk;
    {
        if((this->hp + this->atk)==(m.hp + m.atk))
            return true;
        return false;
    }
    //[] nu are sens

    operator monster_appearence() //da return la apparence-ul acelui monstru
    {
        return this->appearence;
    }
    
    friend istream &operator>>(istream& in, monster& m);
    friend ostream &operator<<(ostream& out, monster& m);
    
    //SETTERS AND GETTERS
    int getIdContor(){
        return  this->idContor;
    }

    const int getMonsterId(){
        return this->monster_id;
    }


    char getZone() { //getter si setter pt CHAR zone
        return this->zone;
    }

    void setZone(char zone) {
        this->zone = zone;
    }

    //destructor
    ~monster(){}

    //citire si afisare
    void citire()
    {
        cout<<endl;
        cout<<"Monster's Name:";
        cin.get();
        getline(cin,this->name);
        cout<<"Monster's Habitat Zone:";
        cin>>this->zone;
        cout<<"Monster's HP:";
        cin>>this->hp;
        cout<<"Attack Power:";
        cin>>this->atk;
        cout<<"Elemental Weakness:";
        cin>>this->elemental_weakness;
        cout<<"Monster Appearence:";
        cout<<"Set default appearence?[Y/N]:";
        char yn;
        cin>>yn;
        if(yn != 'Y')
            this->appearence.citire();
    }

    void afisare()
    {
        cout<<endl;
        cout<<"Monster's ID:"<<this->monster_id<<endl;
        cout<<"Monster's Name:"<<this->name;
        cout<<endl<<"Monster's Habitat Zone:"<<this->zone;
        cout<<endl<<"Monster's Level:"<<this->hp;
        cout<<endl<<"Attack Power:"<<this->atk;
        cout<<endl<<"Elemental Weakness:"<<this->elemental_weakness;
        cout<<endl<<"-----";
        cout<<endl<<"Monster Appearence:"<<endl;
        this->appearence.afisare();
    }

    
};

////////////////////////////////////////////////////

//hunter + weapon -> adauga weapon la weapon list ->return hunter
hunter& operator+(hunter &h, const weapon w)
{
    //marim lista cu 1
    weapon *aux = new weapon [h.weapon_number];
    for(int i = 0; i < h.weapon_number; i++)
        aux[i] = h.weapons[i];

    if(h.weapons!=NULL)
        delete[] h.weapons;
    h.weapons = new weapon[h.weapon_number +1];
    for(int i = 0; i < h.weapon_number; i++)
        h.weapons[i]=aux[i];
    h.weapon_number++;
    if(aux !=NULL)
        delete[] aux;

    h.weapons[h.weapon_number-1] = w;
    return h;
}
//si comutativ
hunter& operator+(const weapon w, hunter &h)
{
    //marim lista cu 1
    weapon *aux = new weapon [h.weapon_number];
    for(int i = 0; i < h.weapon_number; i++)
        aux[i] = h.weapons[i];

    if(h.weapons!=NULL)
        delete[] h.weapons;
    h.weapons = new weapon[h.weapon_number +1];
    for(int i = 0; i < h.weapon_number; i++)
        h.weapons[i]=aux[i];
    h.weapon_number++;
    if(aux !=NULL)
        delete[] aux;

    h.weapons[h.weapon_number-1] = w;
    return h;
}


//hunter / weapon -> sterge weapon list si pune doar weapon-ul dat ->return hunter
hunter& operator/(hunter &h, const weapon w)
{
    if(h.weapons!=NULL)
        delete[] h.weapons;
    h.weapons = new weapon[1];
    h.weapons[0] = w;
    h.weapon_number = 1;
    return h;
}
//si comutativ
hunter& operator/(const weapon w,hunter &h)
{
    if(h.weapons!=NULL)
        delete[] h.weapons;
    h.weapons = new weapon[1];
    h.weapons[0] = w;
    h.weapon_number = 1;
    return h;
}
//////////////////////////////////////////////////

//hunter + armour -> adauga armour la armour list ->return hunter
hunter& operator+(hunter &h, const armour a)
{
    //marim lista cu 1
    armour *aux = new armour [h.armour_number];
    for(int i = 0; i < h.armour_number; i++)
        aux[i] = h.armours[i];

    if(h.armours!=NULL)
        delete[] h.armours;
    h.armours = new armour[h.armour_number +1];
    for(int i = 0; i < h.armour_number; i++)
        h.armours[i]=aux[i];
    h.armour_number++;
    if(aux !=NULL)
        delete[] aux;

    h.armours[h.armour_number-1] = a;
    return h;
}
//si comutativ
hunter& operator+(const armour a,hunter &h)
{
    //marim lista cu 1
    armour *aux = new armour [h.armour_number];
    for(int i = 0; i < h.armour_number; i++)
        aux[i] = h.armours[i];

    if(h.armours!=NULL)
        delete[] h.armours;
    h.armours = new armour[h.armour_number +1];
    for(int i = 0; i < h.armour_number; i++)
        h.armours[i]=aux[i];
    h.armour_number++;
    if(aux !=NULL)
        delete[] aux;

    h.armours[h.armour_number-1] = a;
    return h;
}

//hunter / armour -> sterge lista, baga doar armura data ->return hunter
hunter& operator/(hunter &h, const armour a)
{
    if(h.armours!=NULL)
        delete[] h.armours;
    h.armours = new armour[1];
    h.armours[0] = a;
    h.armour_number = 1;
    return h;
}
//si comutativ
hunter& operator/(const armour a,hunter &h)
{
    if(h.armours!=NULL)
        delete[] h.armours;
    h.armours = new armour[1];
    h.armours[0] = a;
    h.armour_number = 1;
    return h;
}

/*hunter& operator*(const hunter &hu, hunter &h)//adds weapons and armours  and appearences
{
    int weaponNr, armourNr;
    weaponNr = hu.weapon_number + h.weapon_number;
    armourNr = hu.armour_number + h.armour_number;

    for(int i = h.weapon_number; i <weaponNr; i++)
        h = h + hu.weapons[i];


    for(int i = h.armour_number; i<armourNr; i++)
        h = h + hu.armours[i];

    h.appearence = h.appearence + hu.appearence;
    return h;

}*/ //another try cu aceasu eroare

/////////////////////////////////////////////////////
//supraincarcarea op. de citire si afisare - 2 cate 2
//WEAPON
istream& operator>>(istream& in, weapon &w)
{
    if (w.atk_bonus != NULL) {
        delete[] w.atk_bonus;
        w.atk_bonus = NULL;
    }

    cout<<endl;
    cout<<"Weapon's name:";
    getline(in,w.name);//e facut asa ca sa poata avea spatii!
    cout<<"Base Attack:";
    in>>w.base_atk;
    cout<<"Number of Maximum Combos (min. 2):";
    in>>w.maxCombo;
    cout<<"Attack bonus per combo:";
    w.atk_bonus = new float [w.maxCombo + 1];
    for(int i = 0; i < w.maxCombo; i++)
        in>>w.atk_bonus[i];
    cout<<"Weapon element (Insert '-' for None):";
    in>>w.element;
    if(w.element!="-")
    {
        cout<<"Elemental bonus:";
        in>>w.elemental_bonus;
    }
    cout<<"Equip the weapon? [Y/N]";
    char yn;
    in>>yn;
    if(yn == 'Y' || yn == 'y')
        w.equipped = true;
    else w.equipped = false;
    return  in;
}
ostream& operator<<(ostream& out, weapon &w)
{
    out<<endl;
    out<<"Weapon's name:"<<w.name<<endl;
    out<<"Base Attack:"<< w.base_atk<<endl;
    out<<"Number of Maximum Combos:"<<w.maxCombo<<endl;
    out<<"Attack bonus per combo:";
    for(int i = 0; i < w.maxCombo; i++)
        out<<w.atk_bonus[i]<<" ";
    out<<endl<<"Weapon element:"<<w.element<<endl;
    out<<"Elemental bonus:"<<w.elemental_bonus<<endl;
    out<<"The weapon is:";
    if(w. equipped == true)
        out<<"equipped"<<endl;
    else out<<"not equipped"<<endl;
    out<<endl;
    return out;
}

//ARMOUR
istream& operator>>(istream& in, armour &a)
{
    cout<<"Armour's Name:";
    getline(in,a.name);
    cout<<"Base Defense Value:";
    in>>a.def;
    cout<<"Bonus Defence:"<<endl<<"vs. Fire:";
    in>>a.bonus_def[0];
    cout<<"vs. Water:";
    in>>a.bonus_def[1];
    cout<<"vs. Thunder:";
    in>>a.bonus_def[2];
    cout<<"vs. Ice:";
    in>>a.bonus_def[3];
    cout<<"vs. Dragon:";
    in>>a.bonus_def[4];
    cout<<"Equip the armour? [Y/N]";
    char yn;
    in>>yn;
    if(yn == 'Y' || yn == 'y')
        a.equipped = true;
    else a.equipped = false;

    return in;
}
ostream& operator<<(ostream& out, armour &a)
{
    out<<"Armour's Name:"<<a.name<<endl;
    out<<"Base Defense Value:"<<a.def<<endl;
    out<<"Bonus Defence:"<<endl<<"vs. Fire:"<<a.bonus_def[0];
    out<<endl<<"vs. Water:"<<a.bonus_def[1];
    out<<endl<<"vs. Thunder:"<<a.bonus_def[2];
    out<<endl<<"vs. Ice:"<<a.bonus_def[3];
    out<<endl<<"vs. Dragon:"<<a.bonus_def[4];

    out<<endl<<"The armour is:";
    if(a. equipped == true)
        out<<"equipped"<<endl;
    else out<<"not equipped"<<endl;
    out<<endl;

    return out;
}

//HUNTER APPEARENCE
istream& operator>>(istream& in, hunter_appearence& ha)
{
    cout<<"Gender:";
    in>>ha.gender;
    cout<<"Hair Color:";
    in.get();//nu merge fara bc citeste char inainte,,,cred
    getline(in, ha.hair_color);
    cout<<"Left Eye Color:";
    getline(in, ha.eye_color[0]);
    cout<<"Right Eye Color:";
    getline(in, ha.eye_color[1]);
    cout<<"Face Shape:";
    in>>ha.face_shape;
    return in;
}
ostream& operator<<(ostream& out, hunter_appearence& ha)
{
    out<<"Gender:"<<ha.gender;
    out<<endl<<"Hair Color:"<<ha.hair_color;
    out<<endl<<"Left Eye Color:"<<ha.eye_color[0];
    out<<endl<<"Right Eye Color:"<<ha.eye_color[1];
    out<<endl<<"Face Shape:"<<ha.face_shape;
    out<<endl;
    return out;
}

//HUNTER
istream &operator>>(istream& in, hunter& h)
{
    if (h.username != NULL){
        delete[] h.username;
        h.username = NULL;}
    if (h.hunted_monsters != NULL){
        delete[] h.hunted_monsters;
        h.hunted_monsters = NULL;}
    if (h.weapons != NULL){
        delete[] h.weapons;
        h.weapons = NULL;}
    if (h.armours != NULL){
        delete[] h.armours;
        h.armours  =  NULL;}


    cout<<"Is the player online? [Y/N]:";
    char yn;
    in>>yn;
    if(yn == 'Y' || yn == 'y')
        h.online = true;
    else h.online = false;

    cout<<"Username:";
    char s[41];
    in.get();
    in.getline(s,40);//FARA spatii!
    h.username = new char[strlen(s)];
    strcpy(h.username, s);
    cout<<"Level:";
    in>>h.level;
    cout<<"Number of hunted Monsters:";
    in>>h.hunted_monsters_number;
    if(h.hunted_monsters_number > 0)
    {
        h.hunted_monsters = new int[h.hunted_monsters_number];
        cout<<"Hunted Monsters' ID:";
        for(int i=0; i<h.hunted_monsters_number; i++)
            in>>h.hunted_monsters[i];
    }
    cout<<"Weapon Number:";
    in>>h.weapon_number;
    if(h.weapon_number > 0)
    {
        h.weapons = new weapon[h.weapon_number];
        cout<<"Weapons Owned:"<<endl;
        for(int i=0; i<h.weapon_number; i++)
        {
            h.weapons[i] = weapon();
            cout<<"Set default weapoon?[Y/N]:";
            in>>yn;
            if(yn != 'Y')
                h.weapons[i].citire();
        }
    }
    cout<<endl<<"Armours Number:";
    in>>h.armour_number;
    if(h.armour_number > 0)
    {
        cout<<"Armours Owned:"<<endl;
        h.armours = new armour[h.armour_number];
        for(int i = 0; i<h.armour_number; i++)
        {
            h.armours[i] = armour();
            cout<<"Set default armour?[Y/N]:";
            in>>yn;
            if(yn != 'Y')
                h.armours[i].citire();
        }
    }
    cout<<endl<<"Hunter Appearence:"<<endl;
    cout<<"Set default appearence?[Y/N]:";
    in>>yn;
    if(yn != 'Y')
        h.appearence.citire();
    return in;
}
ostream& operator<<(ostream& out, hunter& h)
{
    out<<endl;
    out<<"Player ID: "<<h.playerId<<endl;
    out<<"Online:"<<h.online<<endl;
    out<<"Username:"<<h.username<<endl;
    out<<"Level:"<<h.level<<endl;
    out<<"------"<<endl<<"Number of hunted Monsters:"<<h.hunted_monsters_number<<endl;
    if(h.hunted_monsters_number > 0)
    {
        out<<"Hunted Monsters' ID:";
        for(int i=0; i<h.hunted_monsters_number; i++)
            out<<h.hunted_monsters[i]<<" ";
    }
    out<<endl<<"------"<<endl<<"Weapon Number:"<<h.weapon_number<<endl;
    if(h.weapon_number > 0)
    {
        out<<"Weapons Owned:"<<endl;
        for(int i=0; i<h.weapon_number; i++)
            h.weapons[i].afisare();
    }
    out<<endl<<"------"<<endl<<"Armours Number:"<<h.armour_number<<endl;
    if(h.armour_number > 0)
    {
        out<<"Armours Owned:"<<endl;
        for(int i = 0; i<h.armour_number; i++)
            h.armours[i].afisare();
    }
    out<<endl<<"------"<<endl<<"Hunter Appearence:";
    h.appearence.afisare();
    return out;
}

//MONSTER APPEARENCE
istream& operator>>(istream& in, monster_appearence& ma)
{
    cout<<"Color:";
    in>>ma.color;
    cout<<"Skin Texture Index:";
    in>>ma.skin_texture;
    cout<<"Height:";
    in>>ma.height;
    cout<<"Does it have wings? [Y/N]";
    char yn;
    in>>yn;
    if(yn == 'Y' || yn == 'y')
        ma.wings = true;
    else ma. wings = false;
    return in;
}
ostream& operator<<(ostream& out, monster_appearence& ma)
{
    out<<endl;
    out<<"Color:"<<ma.color<<endl;
    out<<"Skin Texture Index:"<<ma.skin_texture;
    out<<endl<<"Height:"<<ma.height;
    out<<endl<<"Wings:"<<ma.wings;
    return out;
}

//MONSTER
istream &operator>>(istream& in, monster& m)
{
    cout<<endl;
    cout<<"Monster's Name:";
    getline(in,m.name);
    cout<<"Monster's Habitat Zone:";
    in>>m.zone;
    cout<<"Monster's HP:";
    in>>m.hp;
    cout<<"Attack Power:";
    in>>m.atk;
    cout<<"Elemental Weakness:";
    in>>m.elemental_weakness;
    cout<<"Monster Appearence:"<<endl;
    cout<<"Set default appearence?[Y/N]:";
    char yn;
    in>>yn;
    if(yn != 'Y')
        m.appearence.citire();
    return in;
}
ostream &operator<<(ostream& out, monster& m)
{
    out<<endl;
    out<<"Monster's ID:"<<m.monster_id<<endl;
    out<<"Monster's Name:"<<m.name;
    out<<endl<<"Monster's Habitat Zone:"<<m.zone;
    out<<endl<<"Monster's Level:"<<m.hp;
    out<<endl<<"Attack Power:"<<m.atk;
    out<<endl<<"Elemental Weakness:"<<m.elemental_weakness;
    out<<endl<<"-----";
    out<<endl<<"Monster Appearence:"<<endl;
    m.appearence.afisare();
    return out;
}



int hunter::idContor = 4000;
int monster::idContor = 1; //1 is the default -> incepem sa numaram de la 2, sa nu se suprapuna

int main() {

    //VERIFICARI

   /* monster_appearence m("blue", 5,130, true);
    monster_appearence ma(m);

    monster l("Loki", 'D', 450, 66.9, "Ice", ma);
    monster boki, loki(l);*/

    /*float *p;
    p = new float[3];
    p[0] = 18.5;
    p[1] = 27.45;
    p[2] = 45;
    weapon w1, w2(186.34,"Jagras Switch Axe", p, 3, "Thunder", 36.345, true);
    weapon *weapon_list;
    weapon_list = new weapon[2];
    weapon_list[0] = w1;
    weapon_list[1] = w2;

    armour *armour_list;
    armour_list = new armour[1];
    int def_bonus[5]={5,10,15,5,10};
    armour_list[0] = armour("Metal", 47.87, def_bonus, true);

    int *monster_list;
    monster_list = new int[2];
    monster_list[0] = 1;
    monster_list[1] = 2;
    char *username;
    username = new char[strlen("Dewdrop")+1];
    strcpy(username, "Dewdrop");

    string c[2];
    c[0] = "brown";
    c[1] = "white";
    hunter_appearence ha('X', "gray", c, 3);

    hunter dew(true, username, 4, 2, monster_list, 2,weapon_list, 1, armour_list, ha);*/




    monster jagras, pukei("Pukei Pukei",'B',90,65.6,"Fire", monster_appearence("blue",3,120,true) ); //the deafult monster
    monster kathuli("Ka-thulu",'A',120, 30, "-",monster_appearence("red",2,60.4, false));
    monster dreya("dreya",'C',105,45.5, "Ice",monster_appearence("green",4,190,true));
    hunter steve;//the default
    vector<hunter> playerList; //jucatorii = hunteri
    vector<monster> monsterList; //monstrii sunt deja in ea - avem 4 monstrii :D;
    //playerList.push_back(dew);
    monsterList.push_back(jagras);
    monsterList.push_back(pukei);
    monsterList.push_back(kathuli);
    monsterList.push_back(dreya);

    int runOk = 1;
    while(runOk==1)
    {
        cout<<endl;
        cout<<"Press 1 to enter a hunter.\n";
        cout<<"Press 2 to show the player database.\n";
        cout<<"Press 3 to search a player by ID \n";
        cout<<"Press 4 to change a player's data\n"; //cu set/get ->username, level, appearence;
        cout<<"Press 5 to delete a player from the database.\n";
        cout<<"Press 6 to view details about the monsters slayed by a hunter. \n";//functia fun? sper ca e fun
        cout<<"Press 7 to exit.\n";
        int nr;
        cin>>nr;
        switch(nr)
        {
            case 1:
                {
                    hunter hunter;
                    cin>>hunter;
                    playerList.push_back(hunter);
                    break;
                }
            case 2:
                {
                    for(int i=0; i<playerList.size(); i++)
                        cout<<endl<<playerList[i]<<endl;
                    break;
                }
            case 3:
                {
                    cout<<"Enter Player ID: \n";
                    cout << "ID must be less than: " << steve.getIdContor() << endl;
                    int id, ok = 0;
                    cin >> id;
                    for(int i=0; i<playerList.size(); i++)
                        if(playerList[i].getPlayerId() == id){
                            cout<<playerList[i]<<endl;
                            ok = 1;
                            break;
                        }
                    if(ok == 0)
                        cout<<"This Player Doesn't Exist"<<endl;
                    break;
                    //parcurgere vector pana la gasirea id ului;
                }
            case 4:
                {
                    cout << "What data would you like to change?\n";
                    cout<<"Press 1 to change username\n";
                    cout<<"Press 2 to change level\n";
                    cout<<"Press 3 to change appearence\n";
                    cout<<"Press 4 to add a weapon to the hunter's weapon list\n";
                    cout<<"Press 5 to add an armour to the hunter's armour list\n";
                    int change;
                    cin>>change;
                    switch(change)
                    {
                        case 1:
                        {
                            cout<<"Enter Player ID: \n";
                            cout << "ID must be less than: " << steve.getIdContor() << endl;
                            int id, ok = 0;
                            cin >> id;
                            for(int i=0; i<playerList.size(); i++)
                            {
                                if(playerList[i].getPlayerId() == id)
                                        {
                                    cout<<"Current username: "<<playerList[i].getUsername()<<endl;
                                    cout<<"Insert new username (max 50 characters): ";
                                    char name[51];
                                    cin>>name; //fara spatii
                                    char *username = new char [strlen(name)+1];
                                    strcpy(username,name);
                                    playerList[i].setUsername(username);
                                    ok = 1;
                                    break;
                                }
                            }
                            if(ok==0)
                                cout<<"Player doesn't exist"<<endl;
                            break;
                        }
                        case 2:
                        {
                            cout<<"Enter Player ID: \n";
                            cout << "ID must be less than: " << steve.getIdContor() << endl;
                            int id, ok = 0;
                            cin >> id;
                            for(int i=0; i<playerList.size(); i++)
                            {
                                if(playerList[i].getPlayerId() == id)
                                {
                                    cout<<"Current level: "<<playerList[i].getLevel()<<endl;
                                    cout<<"Insert new level: ";
                                    int lvl;
                                    cin>>lvl;
                                    playerList[i].setLevel(lvl);
                                    ok = 1;
                                    break;
                                }
                            }
                            if(ok==0)
                                cout<<"Player doesn't exist"<<endl;
                            break;
                        }
                        case 3:
                        {
                            cout<<"Enter Player ID: \n";
                            cout << "ID must be less than: " << steve.getIdContor() << endl;
                            int id, ok = 0;
                            cin >> id;
                            for(int i=0; i<playerList.size(); i++)
                            {
                                if(playerList[i].getPlayerId() == id)
                                {
                                    cout<<"Current appearance: ";
                                    playerList[i].getAppearence().afisare();
                                    cout<<endl<<"Insert new appearance: "<<endl;
                                    hunter_appearence ha;
                                    cin>>ha;
                                    playerList[i].setAppearence(ha);
                                    ok = 1;
                                    break;
                                }
                            }
                            if(ok==0)
                                cout<<"Player doesn't exist"<<endl;
                            break;
                        }
                        case 4:{
                            cout<<"Enter Player ID: \n";
                            cout << "ID must be less than: " << steve.getIdContor() << endl;
                            int id, ok = 0;
                            cin >> id;
                            for(int i=0; i<playerList.size(); i++) {
                                if (playerList[i].getPlayerId() == id)
                                {
                                    cout << "Add the default weapon?[Y/N]\n";
                                    char yn;
                                    cin >> yn;
                                    if (yn == 'Y' || yn == 'y')
                                        playerList[i] = playerList[i] + weapon();//adding the default weapon
                                    else if (yn == 'N' || yn =='n')
                                    {
                                        weapon w;
                                        w.citire();
                                        playerList[i] = playerList[i] + w;
                                    }
                                    else cout<<"-invalid input-";
                                    break;
                                }
                            }
                        }
                        case 5:{
                            cout<<"Enter Player ID: \n";
                            cout << "ID must be less than: " << steve.getIdContor() << endl;
                            int id, ok = 0;
                            cin >> id;
                            for(int i=0; i<playerList.size(); i++) {
                                if (playerList[i].getPlayerId() == id)
                                {
                                    cout << "Add the default armour?[Y/N]\n";
                                    char yn;
                                    cin >> yn;
                                    if (yn == 'Y' || yn == 'y')
                                        playerList[i] = playerList[i] + armour();//adding the default weapon
                                    else if (yn == 'N' || yn =='n')
                                    {
                                        armour a;
                                        a.citire();
                                        playerList[i] = playerList[i] + a;
                                    }
                                    else cout<<"-invalid input-";
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
            case 5:
                {
                    cout<<"Enter Player ID: \n";
                    cout << "ID must be less than: " << steve.getIdContor() << endl;
                    int id, ok = 0;
                    cin>>id;
                    for(int i=0; i<playerList.size(); i++)
                    {
                        if(playerList[i].getPlayerId() == id){
                            playerList.erase(playerList.begin()+i);
                            ok = 1;
                        }
                    }
                    if(ok==0)
                        cout<<"Player doesn't exist"<<endl;
                    break;
                }
            case 6:
                {
                    cout<<"Enter Player ID: \n";
                    cout << "ID must be less than: " << steve.getIdContor() << endl;
                    int id, ok = 0;
                    cin>>id;
                    for(int i=0; i<playerList.size(); i++)
                    {
                        if(playerList[i].getPlayerId() == id){
                            int *hunted_monsters, nr;
                            nr=playerList[i].getHuntedMonstersNumber();
                            hunted_monsters=playerList[i].getHuntedMonsters();
                            for(int j = 0; j<nr; j++)
                                for(int k = 0; k<monsterList.size(); k++)
                                    if(hunted_monsters[j] == monsterList[k].getMonsterId())
                                        cout<<endl<<monsterList[k]<<endl;
                            ok = 1;
                        }
                    }
                    if(ok==0)
                        cout<<"Player doesn't exist"<<endl;
                    break;
                }
            case 7:
                {
                    cout << "MONSTER HUNTER WORLD: C++ EDITION\n";
                    cout << "By: Raluca Serba 141\n";
                    runOk = 0;
                    break;
                }
        }
    }


    return 0;
}
