
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


#include <iostream>
#include <fstream>
#include <cmath> 
#include "slist.h"
#include <string>

using namespace std;

class Airport
{
public:
    string code;
    double   longitude;
    double   latitude;
    double  distance;
  Airport* next;
    
};



void simpleSortTotal(Airport* s[], int c);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void append(Airport** thinger, string code, double longt, double lat, double distance);
double AUSdistance(double lat2d, double lon1d);
// also add the append and the dist from AUS function thingys
void simpleSortTotal(Airport* thinger, int size);


int main()
{
    ifstream infile;
    int i=0;
    char cNum[255] ;
    string temp;
    Airport* thinger = NULL;			// Replace array with Linked List
    int   airportCount;
    //Airport* a[13500];
    
    infile.open ("airport-codes_US.csv", ifstream::in);
    if (infile.is_open())
    {
        int   c=0;
        while (infile.good())
        {
          infile.getline(cNum, 256, ',');
          string temp(cNum);

          
          if(temp != "ident" && temp.length() !=0)
          {
            string code = temp;  
              infile.getline(cNum, 256, ',');
            infile.getline(cNum, 256, ',');
            infile.getline(cNum, 256, ',');

            double longt = atof(cNum);
            infile.getline(cNum, 256, ',');
             double lat = atof(cNum);
            infile.getline(cNum, 256, '\n');

            double distance = AUSdistance(lat, longt);
            append(&thinger, code, longt, lat, distance);
          
            
            // infile.getline(airportArr[c]->code, 256, ',');
            
            // airportArr[c]->longitude = atof(cNum);
            // infile.getline(cNum, 256, '\n');
            // airportArr[c]->latitude = atof(cNum);

            // // if (!(c % 1000))
            //     cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;

            /*
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;                               
            }
            */

            
            i++ ;
            c++;
        }
          else{
            infile.getline(cNum, 256, '\n');
          }
        }
        airportCount = c-1;
        infile.close();


      simpleSortTotal(thinger, airportCount);

      int count = 0;
    //      for (int c=0; c < airportCount; c++)
    //         if (!(c % 1000))
    //         {
    //             cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
    //             cout << airportArr[c+1]->code << " long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;
    //             cout <<"Distance between " << airportArr[c]->code << " and " << airportArr[c+1]->code << " is "
    //               << distanceEarth( airportArr[c]->longitude, airportArr[c]->latitude , airportArr[c+1]->longitude, airportArr[c+1]->latitude) << endl;
    //         }



    // }

      string far_code = "";
      double far_distance = 0.0;

      while(thinger != NULL){
        if(thinger->distance < 160.934){
          cout<<thinger->code<<" "<<thinger->distance<<endl;
        }

        if(thinger->distance > far_distance){
          far_distance = thinger->distance;
          far_code = thinger->code;
        }
        thinger = thinger->next;
        count++;
      }
      cout << far_code << " farthest distance: " << far_distance << endl;
        
      }
    else
    {
        cout << "Error opening file";
    }


  return(0);
 


    
}



#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


double AUSdistance(double lat1, double lon1){
  return(distanceEarth(lat1, lon1, 30.19449997, -97.66989899));
}
/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void append(Airport** thinger, string code, double longt, double lat, double distance){
  struct Airport* createNode = new Airport;

  struct Airport *last = *thinger;

  createNode->code = code;
  createNode->longitude = longt;
  createNode->latitude = lat;
  createNode->distance = distance;

  createNode->next = NULL;

  if(*thinger == NULL){
    *thinger = createNode;
    return;
  }

  while(last->next != NULL)
    last = last->next;

  
  last->next = createNode;
  return;
  
}

/*
	Provide sort routine on linked list
*/

void simpleSortTotal(Airport* thinger, int size){
  Airport* p = thinger;
  Airport* q = thinger;

  for(int i = 0; i<size; i++){
    for(int j = 0; j<size -1; j++){
      if(p->distance < q->distance){
        double t1 = p->distance;
        string t2 = p->code;
        p->distance = q->distance;
        q->distance = t1;

        p->code = q->code;
        q->code = t2;
    }
      q = q->next;
  }
    q = thinger;
    p = thinger->next;
    for(int l = 0; l<i; l++){
      p = p->next;
    }
  }
}

