#include<iostream>
#include<map>
#include<cstdio>
#include<cerrno>
#include<cmath>
#include<cfloat>

using namespace std;

//where the point is
struct Location {
  float x;
  float y;
};

int datanum =0;

//open
FILE* fileopen(char* name){
  FILE* fp=std::fopen(name,"r");
  if(!fp){
    perror("open");
    exit(EXIT_FAILURE);
  }
  return fp;
}

//calculate distance
float distance(float ax, float ay, float bx, float by){
  float dis = pow(ax-bx,2.0)+pow(ay-by,2.0);
  dis= sqrt(dis);
  return dis;
}

//readfile and make map
void fileread(FILE* fp, map <int,Location> &m){
  float x=0;
  float y=0;
  char dummy1, dummy2;
  int i=0;
  fscanf(fp, "%c,%c",&dummy1, &dummy2);
  while (fscanf(fp,"%f,%f\n",&x,&y)!=EOF){
    Location buf;
    buf.x= x;
    buf.y= y;
    m.insert(pair<int,Location>(i,buf));
    i++;
    datanum++;
  }
}

//calculate total diatance
float sumdist(map<int, Location> &m, int* order){
  float tdis=0;
  for(int i=0; i<datanum-1; i++){
    tdis+= distance(m[order[i]].x, m[order[i]].y, m[order[i+1]].x, m[order[i+1]].y);
  }
  tdis+= distance(m[order[0]].x, m[order[0]].y, m[order[datanum-1]].x, m[order[datanum-1]].y);
  return tdis;
}

int found=0;

//search the nearest point (switch left and right)
int searchminswitch(map<int, Location> &m, char* checked, Location given, int swit){
  int minkey=-1;
  float mindis = FLT_MAX;

  for(int i=0; i<datanum; i++){
    if(checked[i]!=1){
      if(swit==0){// go right
          if(given.x <= m[i].x){
            float ab= distance(given.x, given.y, m[i].x, m[i].y); //absolute value
            if(ab<mindis){
              minkey= i;
              mindis=ab;
            }
            found = 1;
          }
      }
      if(swit==1){// go left
        if(given.x >= m[i].x){
          float ab= distance(given.x, given.y, m[i].x, m[i].y); //absolute value
          if(ab<mindis){
            minkey= i;
            mindis=ab;
          }
          found=1;
      }
    }
  }
  }
  return minkey;
}

//search the nearest point (from given point)
int searchmin(map<int, Location> &m, char* checked, Location given){
  int minkey=-1;
  float mindis = FLT_MAX;

  for(int i=0; i<datanum; i++){
    if(checked[i]!=1){
      float abu= distance(given.x, given.y, m[i].x, m[i].y); //absolute value
      if(abu<mindis){
        minkey= i;
        mindis=abu;
      }
    }
  }
  return minkey;
}

//the order to pass the point
int* makeorder(int* order, map<int, Location> &m, int start){
  char checked[datanum];//when the point is checked, 1
  int nextp;
  int swit=0;

  for (int i = 0; i < datanum-1; i++) {
    found=0;
    order[i]= start;
    checked[start]=1;
    nextp =searchminswitch(m, checked, m[start], swit);
    if(found==1){
      start = nextp;
      cout << "go next" << endl;
    }
    if(found==0){
      swit=!swit;
      i--;
      cout << "switch" << endl;
    }
  }
  order[datanum-1]= nextp;

  return order;
}

//main
int main(int argc, char *argv[]) {

  map<int, Location> city;

  FILE* fp=fileopen(argv[1]);
  fileread(fp, city);

  Location zero= {0.0, 0.0};

  int order[datanum];
  char dum[datanum];
  int start= searchmin(city, dum, zero);

  float result = sumdist(city, makeorder(order, city, start));

  cout<< result << endl;

  fclose(fp);

  return 0;
}
