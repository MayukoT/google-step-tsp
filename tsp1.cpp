#include<iostream>
#include<map>
#include<cstdio>
#include<cerrno>
#include<cmath>

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
  for(int i=0; i<datanum; i++){
    tdis+= distance(m[order[i]].x, m[order[i]].y, m[order[i+1]].x, m[order[i+1]].y);
    cout << tdis << endl;
    cout << "/* message */" << endl;
  }
  return tdis;
}

//the order to pass the point
int* makeorder(int* order){
  for (int i = 0; i < datanum; i++) {
    order[i]= i;
  }
  return order;
}

//main
int main(int argc, char *argv[]) {

  map<int, Location> city;

  FILE* fp=fileopen(argv[1]);
  fileread(fp, city);

  int order[datanum];
  float result = sumdist(city, makeorder(order));

  cout<< result << endl;

  fclose(fp);

  return 0;
}
