#include<iostream>
#include<map>
#include<cstdio>

struct Location {
  float x;
  float y;
};


using namespace std;

int main(int argc, char const *argv[]) {

  map<int, Location> city;

  FILE* fp=std::fopen(argv[1],"r");

  float x=0;
  float y=0;
  int i=0;
  while (fscanf(fp,"%f%f\n",&x,&y)){
    Location buf;
    buf.x= x;
    buf.y= y;
    city.insert(pair<int,Location>(i,buf));
    i++;
  }
  cout<<"read" <<endl;
/*for (int j = 0; j < i; j++) {
  cout<<city[j]<<endl;
}*/

  float result=0;
//calc distance
for (int k = 0; k < i; k++) {
  float x1=0; //insert pair of x and y
  float y1=0;
  float x2=0;
  float y2=0;
  result+= ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
  cout<< result << endl;

  fclose(fp);

  return 0;
}
