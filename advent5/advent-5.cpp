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
       int x1;
       int y1;
       int x2;
       int y2;

       fissure(int x1_i, int y1_i, int x2_i, int y2_i)
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

       void set_coords(int x1_i, int y1_i, int x2_i, int y2_i)
       {
           x1 = x1_i;
           y1 = y1_i;
           x2 = x2_i;
           y2 = y2_i;
       }

};

class ocean_floor{
    private:
       uint64_t curr_fissure;
       uint64_t answer;
       vector<fissure> fissures;
       vector<vector<int>> tile_counts;
    public:
       ocean_floor(vector<fissure> fissures_i)
       {
           curr_fissure = 0;
           answer = 0;
           fissures = fissures_i;
           tile_counts.resize(MAX_X, std::vector<int>(MAX_Y));
       }
       void record_fissures();

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

void ocean_floor::record_fissures()
{
    while(curr_fissure != fissures.size())
        {
           bool straight_line = (fissures[curr_fissure].x1 == fissures[curr_fissure].x2 || fissures[curr_fissure].y1 == fissures[curr_fissure].y2);
           uint64_t counter = 0;
           if(straight_line)
           {
               int x_min = min(fissures[curr_fissure].x1, fissures[curr_fissure].x2);
               for(int x = x_min; counter < (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)); x++)
               {
                   tile_counts[x][fissures[curr_fissure].y1]++;
                   counter++;
                   if(counter == abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2))
                   {
                       tile_counts[x+1][fissures[curr_fissure].y1]++;
                   }
               }
               counter = 0;
               int y_min = min(fissures[curr_fissure].y1, fissures[curr_fissure].y2);
               for(int y = y_min; counter < (abs(fissures[curr_fissure].y1 - fissures[curr_fissure].y2)); y++)
               {
                  tile_counts[fissures[curr_fissure].x1][y]++;
                  counter++;
                  if(counter == abs(fissures[curr_fissure].y1 - fissures[curr_fissure].y2))
                  {
                    tile_counts[fissures[curr_fissure].x1][y+1]++;
                  }
               }
           }
           else //!straight_line
           { 
               int x = fissures[curr_fissure].x1;
               int y = fissures[curr_fissure].y1;
               //x1 > x2, y1 > y2
               if(fissures[curr_fissure].x1 > fissures[curr_fissure].x2 && fissures[curr_fissure].y1 > fissures[curr_fissure].y2)
               {
                   for(int d_counter = 0; d_counter < (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)); d_counter++)
                   {
                       tile_counts[x][y]++;
                       x--;
                       y--;
                       if(d_counter == (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)-1))
                       {
                          tile_counts[x][y]++;
                       }
                   } 
               }
               //x1 > x2, y1 < y2
               if(fissures[curr_fissure].x1 > fissures[curr_fissure].x2 && fissures[curr_fissure].y1 < fissures[curr_fissure].y2)
               {
                   for(int d_counter = 0; d_counter < (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)); d_counter++)
                   {
                       tile_counts[x][y]++;
                       x--;
                       y++;
                       if(d_counter == (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)-1))
                       {
                          tile_counts[x][y]++;
                       }
                   } 
               }
               //x1 < x2, y1 < y2
               if(fissures[curr_fissure].x1 < fissures[curr_fissure].x2 && fissures[curr_fissure].y1 < fissures[curr_fissure].y2)
               {
                   for(int d_counter = 0; d_counter < (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)); d_counter++)
                   {
                       tile_counts[x][y]++;
                       x++;
                       y++;
                       if(d_counter == (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)-1))
                       {
                          tile_counts[x][y]++;
                       }
                   } 
               }
               //x1 < x2, y1 > y2
               if(fissures[curr_fissure].x1 < fissures[curr_fissure].x2 && fissures[curr_fissure].y1 > fissures[curr_fissure].y2)
               {
                   for(int d_counter = 0; d_counter < (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)); d_counter++)
                   {
                       tile_counts[x][y]++;
                       x++;
                       y--;
                       if(d_counter == (abs(fissures[curr_fissure].x1 - fissures[curr_fissure].x2)-1))
                       {
                          tile_counts[x][y]++;
                       }
                   } 
               }
           }

           curr_fissure++;
        }
}


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

    ocean_floor oc_floor(fissures_vec);
    oc_floor.record_fissures();
    
    oc_floor.adv5_ans();

    data_file.close();


}
