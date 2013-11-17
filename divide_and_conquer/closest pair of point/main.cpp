#include"cp_problem.h"
#include<pthread.h>

int sort_position; // pomocna varijabla za sortiranje po komponentama
vector<vector<double> > points; //polje tocaka

/* Funkcija za pomoc pri sortiranju
/  Opis: uvjet za sortiranje prema ne ugradjenom pravilu
/  Parametri: dvije tocke
/  Vraca: true ako je prva tocka manja od druge inace false
*/
bool my_sort(vector<double> a, vector<double> b)
{
	return (a[sort_position] < b[sort_position]);
}

double dsecnd (void) {
    return (double)( clock( ) ) / CLOCKS_PER_SEC;
}

/* Rekurzivni algoritam za par najblizih tocaka
/ Opis: Ocekuje sortirana polja prema x i y kordinati. Dijeli na dva dijela i provjerava delta okolinu oko medijana gdje je djelio.
/       Slozenost u najboljem slucaju nlg(n), vrijedi zbog nekih teorema na delta okolinu
/ Parametri: sortirana olja tocaka po x i y
/ vraca: par koji sadrzi par najblizih tocaka i njihovu udaljenost
*/
pair<pair<vector<double>, vector<double> >, double> TwoDimAlg(vector<vector<double> >& xpoints, vector<vector<double> >& ypoints)
{
  vector<vector<double> > xL, xR, yL, yR, yS;
	vector<double> xM;
	pair<vector<double>, vector<double> >closestPair, pairL, pairR, minPair;
	double dR, dL, dmin, closest;

	if(xpoints.size() <= 50)
		return bruteForceAlghoritm(xpoints);
	else
	{	
		for(int i = 0; i < xpoints.size(); i++)
		{
			if(i < xpoints.size()/2)
				xL.push_back(xpoints[i]);
			else
				xR.push_back(xpoints[i]);
		}
		xM = xpoints[xpoints.size()/2 - 1];

		for(int i = 0; i < ypoints.size(); i++)
		{
			if(xM[0] >= ypoints[i][0])
				yL.push_back(ypoints[i]);
			else
				yR.push_back(ypoints[i]);
		}
		pair<pair<vector<double>, vector<double> >, double> pom1,pom2;
		pom1 = TwoDimAlg(xL, yL);
		pairL = pom1.first;
		dL = pom1.second;
		pom2 = TwoDimAlg(xR, yR);
		pairR = pom2.first;
		dR = pom2.second;
		dmin = dR;
		minPair = pairR;
		if(dL < dR)
		{
			dmin = dL;
			minPair = pairL;
		}
		for(int i = 0; i < ypoints.size(); i++)
			if(abs(xM[0] - ypoints[i][0]) < dmin)
				yS.push_back(ypoints[i]);
		closest = dmin;
		closestPair = minPair;
		for( int i = 0; i < yS.size() - 1; i++)
		{
			int k = i+1;
			while( k < yS.size() && abs(yS[k][1] - yS[i][1]) < dmin )
			{
				if(dist(yS[k],yS[i]) < closest)
				{
					closest = dist(yS[k],yS[i]);
					closestPair = make_pair(yS[k],yS[i]);
				}
				k++;
			}
		}
		return make_pair(closestPair,closest);
	}
}

/* Algoritam za pronalazenje dvije najblize tocke na pravcu
/  Opis: Sotirano polje tocaka u 1D se u vremenu O(n) moze provjeriti i vidjeti gdje je najmanja udaljenost
/  Parametri: polje tocaka koje je sortirano
/  Vraca: par najblizih tocaka i njihovu udaljenost
*/
pair<pair<vector<double>, vector<double> >, double> oneDim()
{
	sort(points.begin(),points.end(),my_sort);
	double distanca = points[1][0] - points[0][0] ;
	pair<vector<double>, vector<double> > pom_pair;
	pom_pair = make_pair(points[1], points[0]);
	double pom;
	for(int i = 1; i < points.size()-1; i++)
	{
		pom = points[i+1][0] - points[i][0];
		if(pom < distanca)
		{
			distanca = pom;
			pom_pair = make_pair(points[i+1], points[i]);
		}
	}
	return make_pair(pom_pair,distanca);
}

/* Dio koji djeli posao po procesorima
/  Opis: Ideja je da dretve u isto vrijeme obavljaju poslove nad disjunktnim skupovima tocaka
         Nacin obavljanja posla moze biti bilo kojim od algoritama
*/
#define P 100 
vector<pair<pair<vector<double>, vector<double> >, double> > threadPair(P);
static pthread_barrier_t *barijere,barijera_za_poravnanje;
struct Data{
	int index,number;
};

void *thread_main(Data *const d)
{
		pthread_barrier_wait(&barijera_za_poravnanje);  
		vector<vector<double> > xp,yp;
		for(int i = (d->number/P)*d->index; i < (d->number/P)*(d->index+1); i++)
			xp.push_back(points[i]);
		yp = xp;
		sort(yp.begin(),yp.end(),my_sort);
		threadPair[d->index] = TwoDimAlg(xp,yp);
		//threadPair[d->index] = bruteForceAlghoritm(xp);
}

/* Glavna funkcija koja testira*/
int main(int argc, char* argv[]) // in command line insert spaceDimension and numberOfPoints, respectively
{
  if( argc != 3 )
  {
    cout<<"number of arguments is not correct"<<endl;
    return EXIT_FAILURE;
  }
	int spaceDimension,numberOfPoints;
  
  sscanf(argv[1],"%d",&spaceDimension);
  sscanf(argv[2],"%d",&numberOfPoints);
  
  randPointInSpace(points, spaceDimension, numberOfPoints);
 	cout<<" Stvorio sam tocke"<<endl;	
	pair<pair<vector<double>, vector<double> >, double> closestPair1, closestPair2;
	double t1, t2, time;
	//t1 = dsecnd();
	/*closestPair1 = bruteForceAlghoritm(points);
  t2 = dsecnd();
	time = t2 - t1;
	cout<< time <<endl;*/
	
	vector<vector<double> > xpoints = points, ypoints = points;
	/*t1 = dsecnd();*/
	sort_position = 0;
	sort(xpoints.begin(),xpoints.end(),my_sort);
	sort_position = 1;
	sort(ypoints.begin(),ypoints.end(),my_sort);
	points = xpoints;
  /***********Closest pair*********************************/
	/*cout<< " brute force"<<endl;
	for(int i = 0; i < spaceDimension; i++)
		cout<<closestPair1.first.first[i]<<",";
	cout<<" and ";

	for(int i = 0; i< spaceDimension; i++)
		cout<<closestPair1.first.second[i]<<",";
	cout<<"  Distance = "<<closestPair1.second<<"     Time = "<<time<<endl;
	*/
	/*****************recursive********************************
	//t1 = dsecnd();
 	//closestPair2 = oneDim();
	closestPair2 = TwoDimAlg(xpoints, ypoints);
	t2 = dsecnd();
	time = t2 - t1;
	cout<<time<<endl;
	/*for(int i = 0; i < spaceDimension; i++)
		cout<<closestPair2.first.first[i]<<",";
	cout<<" and ";

	for(int i = 0; i< spaceDimension; i++)
		cout<<closestPair2.first.second[i]<<",";
	
	cout<<"  Distance = "<<closestPair2.second<<"         Time = "<<time<<endl;

  /*************Print all points*******************************
  for(int i=0;i<points.size();i++){
    for(int j=0;j<points[i].size();j++)
      cout<<points[i][j]<<", ";
    cout<<endl;}*/

	/**************** threads**********************************/
	pthread_t *pth;
	Data *dat;
	pthread_barrier_init(&barijera_za_poravnanje,NULL,P);
	if (!(pth = (pthread_t*)malloc(P * sizeof(pthread_t)))) 
 	{
  	cout<<"Greska pri stvaranju dretvi!"<<endl;
    return EXIT_FAILURE;
 	} 
	
	for(int i = 0; i < P; i++)
	{
		if (!(dat = (Data*)malloc(sizeof(Data)))) 
    {
      cout<<"Greska pri stvaranju struktura!"<<endl;
      return EXIT_FAILURE;
    }
		
		dat->number = numberOfPoints;
		dat->index = i;
		
		if (pthread_create(pth + i, NULL, (void*(*)(void*))thread_main, dat)) 
    {
      cout<<"Greska pri pokretanju dretve!"<<endl;
      return EXIT_FAILURE;
    }
	}
	t1 = dsecnd();
	for (int i = 0; i < P; ++i) 
  {
    if (pthread_join(pth[i], NULL)) 
    {
      cout<<"Join error!"<<endl;
      return EXIT_FAILURE;
    }
	}
	t2 = dsecnd();
	cout<<endl<<t2-t1<<endl;

  return 0;
}	
