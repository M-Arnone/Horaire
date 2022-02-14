#include "Temps.h"


//**********S E T T E R S**********
void Temps::setHeure(int h){
	if(h < 0 || h > 23){
		throw TempsException("heure non comprise entre 0 et 23 !",TempsException::HEURE_INVALIDE);
	}
	heure = h;


}
void Temps::setMinute(int m){
	if(m < 0 || m > 60)
		throw TempsException("minutes non comprises entre 0 et 59 !",TempsException::MINUTE_INVALIDE);
	minute = m;
}


//**********G E T T E R S**********
int Temps::getHeure()const{return heure;}
int Temps::getMinute()const{return minute;}

//**********F U N C T I O N S**********
int Temps::TimeToDuration(const Temps& t){
	int m = (t.getHeure()*60)+t.getMinute();
	return m;
}
Temps Temps::DurationToTime(int a){
	Temps tmp;
	tmp.setHeure(a/60);
	tmp.setMinute(a%60);
	return tmp;
}

//**********C O N S T R U C T O R S**********
Temps::Temps(){
	setHeure(0);
	setMinute(0);
}
Temps::Temps(int m){ 
	if(m < 0 || m > 1439)
		throw TempsException("Depassement !!!",TempsException::DEPASSEMENT);
	Temps tmp = DurationToTime(m);
	setHeure(tmp.getHeure());
	setMinute(tmp.getMinute());
}
Temps::Temps(int h, int m){
	setHeure(h);
	setMinute(m);
}
Temps::Temps(const Temps& t){
	setHeure(t.getHeure());
	setMinute(t.getMinute());
}


//**********O P E R A T O R  O V E R L O A D I N G**********
Temps Temps::operator+(int a){
	return (*this) + Temps(a);
}
Temps Temps::operator+(const Temps& t){
	Temps tmp(*this),tmp2(t);
	int a = TimeToDuration(tmp), b = TimeToDuration(tmp2);
	a += b;
	tmp = Temps(a);
	return tmp;
}
Temps operator+(int a, Temps t){
	return t + Temps(a);
}

Temps Temps::operator-(int a){//Temps - int
	int b = TimeToDuration(*this);
	if(b - a < 0)
		throw TempsException("Depassement !!!",TempsException::DEPASSEMENT);
	b-=a;
	Temps tmp = Temps(b);
	return tmp;
}

Temps operator-(int a, Temps t){//int - Temps
	int b = t.TimeToDuration(t);
	if(a - b < 0)
		throw TempsException("Depassement !!!",TempsException::DEPASSEMENT);
	a-=b;
	Temps tmp = Temps(a);
	return tmp;
}

Temps Temps::operator-(const Temps& t){//Temps - Temps
	return (*this) - TimeToDuration(t);
}
int Temps::compT(const Temps& t){
	if(this->getHeure() < t.getHeure()) return -1;
	if(this->getHeure() > t.getHeure()) return 1;

	if(this->getMinute() < t.getMinute()) return -1;
	if(this->getMinute() > t.getMinute()) return 1;
	return 0;
}

int Temps::operator<(const Temps& t){
	return compT(t) == -1;
}
int Temps::operator>(const Temps& t){
	return compT(t) == 1;
}
int Temps::operator==(const Temps& t){
	return compT(t) == 0;
}

ostream& operator<<(ostream& s, const Temps& t){
	s<<t.getHeure()<<"h";
	if(t.getMinute() == 0)
		s<<"00";
	else
		if(t.getMinute() >= 0 && t.getMinute() <= 9)
			s<<"0"<<t.getMinute();
		else
			s<<t.getMinute();
	return s;
}

istream& operator>>(istream& s, Temps& t){
	int h = 0,m = 0;
	char buffer[400] = {0};
	cout<<endl<<"Heure : ";
	s>>h;
	sprintf(buffer,"%d",h);
	for(unsigned int i = 0; i < strlen(buffer) ;i++){
		if(!isdigit(buffer[i]))
			throw TempsException("Format invalide",TempsException::FORMAT_INVALIDE);
	}
	cout<<"Minute :";
	s>>m;
	sprintf(buffer,"%d",m);
	for(unsigned int i = 0; i < strlen(buffer) ;i++){
		if(!isdigit(buffer[i]))
			throw TempsException("Format invalide",TempsException::FORMAT_INVALIDE);
	}
	t.setHeure(h);
	t.setMinute(m);

	return s;
}

Temps Temps::operator++(){
	(*this) = (*this) + 30;
	return (*this);
}
Temps Temps::operator++(int){
	Temps tmp(*this);
	(*this) = (*this) + 30;
	return tmp;
}

Temps Temps::operator--(){
	(*this) = (*this) - 30;
	return (*this);
}
Temps Temps::operator--(int){
	Temps tmp(*this);
	(*this) = (*this) - 30;
	return tmp;
}



//**********D E S T R U C T O R**********
Temps::~Temps(){}


//**********P R I N T**********
void Temps::Affiche()const{
	if(heure > 0)
		cout<<this->getHeure()<<"h";
	if(minute == 0)
		cout<<"00";
	else
		if(this->getMinute() >= 0 && this->getMinute() <=9)
			cout<<"0"<<this->getMinute();
		else
			cout<<this->getMinute();

	
	cout<<endl;
}

//**********F L U X**********
void Temps::Save(ofstream &fichier) const{
	if(!fichier){
		cout << "Erreur d'ouverture"<<endl;
		exit (1);
	}
	fichier.write((char *)&heure, sizeof(int));
	fichier.write((char *)&minute, sizeof(int));

}
void Temps::Load(ifstream &fichier){
	if(!fichier.rdbuf()->is_open()){
		cout << "Erreur d'ouverture"<<endl;
		exit (1);
	}
	fichier.read((char *)&heure,sizeof(int));
	fichier.read((char *)&minute,sizeof(int));
}