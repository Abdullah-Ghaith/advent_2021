#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cmath>
using namespace std;

#define MAX_FISSURES 500
#define MAX_X 2000
#define MAX_Y 2000

class fissure{
    public:
       uint16_t x1;
       uint16_t y1;
       uint16_t x2;
       uint16_t y2;

       fissure(uint16_t x1_i, uint16_t y1_i, uint16_t x2_i, uint16_t y2_i)
       {
           x1 = x1_i;
           y1 = y1_i;
           x2 = x2_i;
           y2 = y2_i;
       }
       fissure()
       {
           x1 = 0;
           y1 = 0;
           x2 = 0;
           y2 = 0;
       } 

       void set_coords(uint16_t x1_i, uint16_t y1_i, uint16_t x2_i, uint16_t y2_i)
       {
           x1 = x1_i;
           y1 = y1_i;
           x2 = x2_i;
           y2 = y2_i;
       }

};

class ocean_floor{
    private:
        uint64_t fissures_recorded;
        uint64_t answer;
        vector<fissure> fissures;
        vector<uint64_t> tile_counts_x;
        vector<uint64_t> tile_counts_y;
    public:
       ocean_floor()
       {
           fissures_recorded = 0;
           answer = 0;
           for(int i = 0; i < MAX_FISSURES; i++)
           {
               fissures.push_back(fissure());
           }
           for(int i = 0; i < MAX_X; i++)
           {
               tile_counts_x.push_back(0);
               tile_counts_y.push_back(0);
           }
       }
       void record_fissure()
       {
           bool straight_line = (fissures[fissures_recorded].x1 == fissures[fissures_recorded].x2 || fissures[fissures_recorded].y1 == fissures[fissures_recorded].y2);
           if(straight_line)
           {
              for(int x = min(fissures[fissures_recorded].x1, fissures[fissures_recorded].x2); x < abs((fissures[fissures_recorded].x1 - fissures[fissures_recorded].x2)); x++)
              {
                  tile_counts_x[x]++;
              }
              for(int y = min(fissures[fissures_recorded].y1, fissures[fissures_recorded].y2); y < abs((fissures[fissures_recorded].y1 - fissures[fissures_recorded].y2)); y++)
              {
                  tile_counts_y[y]++;
              }
           }

           fissures_recorded++;
       }

       void adv5_ans()
       {
           for(int x = 0; x < MAX_X; x++)
           {
               for(int y = 0; y < MAX_Y; y++)
               {
                   if(tile_counts[x][y] >= 2)
                   {
                      answer++;
                   }
               }
           }

           cout << answer;
       }
};


void reset_s_vector(vector<string>* passed_vector)
{
    int vector_size = passed_vector->size();
    for(int i = 0; i < vector_size; i++)
    {
        passed_vector->pop_back();
    }
}

int main()
{
    string x1_string, y1_string, x2_string, y2_string;
    ifstream data_file;
    vector<string> coords_string;
    vector<fissure> fissures_vec;
    uint16_t num_fissures = 0;
    data_file.open("adv5_data.txt");

    uint64_t total_overlaps = 0;

    for (int i = 0; i < MAX_FISSURES; i++) 
    {
       fissures_vec.push_back(fissure());
    }
    
    while(!data_file.eof())
    {
       getline(data_file, x1_string, ',');
       getline(data_file, y1_string, '-');
       getline(data_file, x2_string, ',');
       x2_string.erase(0,1);
       getline(data_file, y2_string);
       fissures_vec[num_fissures].set_coords(stoi(x1_string), stoi(y1_string), stoi(x2_string), stoi(y2_string));
       num_fissures++;
    }

    ocean_floor oc_floor;
    //oc_floor.set_up_fissures_vec(fissures_vec);
    for (int curr_fiss = 0; curr_fiss < num_fissures; curr_fiss++)
    {
      //oc_floor.record_fissure();
    }
    //oc_floor.adv5_ans();

    data_file.close();


}
