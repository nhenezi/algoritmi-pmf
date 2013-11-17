#include"cp_problem.h"

/* Inicijalizacija prostora tocaka
/ Opis : Sporija varijanta inicijalizacije prostora jer pazi da se ne pojave dvije iste tocke.
/        Koriste se gotove strukture za skup
/ Parametri: prazno polje tocaka, dimenzija prostora, broj tocaka
/ Vraca: referencu na tocke (kontrola kopiranja)
*/
void randPointInSpace(vector<vector<double> >& points, int spaceDimension, int numberOfPoints)
{
	srand(time(0));
  int i,j;
	set<vector<double> > pom_set;
  vector<double> point;
  while(pom_set.size() < numberOfPoints)
  {
    for(j = 0; j < spaceDimension; j++)
    	point.push_back((double)(rand()%10000000)/24); 
		pom_set.insert(point);
    point.clear();
  }
  set<vector<double> >::iterator s;
	for(s = pom_set.begin(); s != pom_set.end(); s++)
		points.push_back(*s);
}

/* Racunanje udaljenosti izmedu tocaka
/  Opis: Ovisno o odabranoj normi racuna udaljenost
/  Parametri: tocka, tocka
/  Vraca: double vrijednost za udaljenost
*/
double dist(vector<double> &a, vector<double> &b)
{
	double result = 0.0;
	
	       /*max norma*/
	/*
	for(int i = 0; i < a.size(); i++)
	{ 	
		double pom = abs(a[i] - b[i]);
		if(result < pom) result = pom;
	}
	*/
	        /*1-norma*/
	/*
	for(int i = 0; i < a.size(); i++)
		result+= abs(a[i]-b[i]);
	}
	*/
	          /*2-norma*/	
	for (int i = 0; i <a.size(); i++) 
		result+=(a[i]-b[i])*(a[i]-b[i]);	
	result = sqrt(result);
	
	return result;
}

/* Nativni algoritam za racunanje udaljenosti
/ Opis: Slozenost n^2 dvije petlje i provjerava svakog sa svakim
/ Parametri: skup tocaka
/ Vraca: par koji sadrzi par najblizih tocaka i udaljenost
*/
pair<pair<vector<double>, vector<double> >, double > bruteForceAlghoritm(vector<vector<double> >& points)
{
	pair<vector<double>, vector<double> > minPoints;
	double minDistance = dist(points[0], points[1]);
	minPoints = make_pair(points[0],points[1]);
	for(int i = 0; i < points.size(); i++)
	{
		for(int j = i+1; j < points.size(); j++)
		{ 
			dist(points[i],points[j]);
			double pom_result = dist(points[i], points[j]);
			if(pom_result < minDistance)
			{
				minDistance = pom_result;
				minPoints = make_pair(points[i], points[j]);
			}
		}
	}
	return make_pair(minPoints,minDistance);
}
