#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>

class Histogram
{
public:
        Histogram(int discretize, std::vector<double>& traj, double temperature)
                : discretize_(discretize),
                  traj_(traj),
                  temperature_(temperature)
        {}
        std::vector<double> bins_;
        std::vector<double> free_energy;
        std::vector<double> bin_position;
        void Free_energy();
private:
        int discretize_;
        std::vector<double> traj_;
        double temperature_;
};

void Histogram::Free_energy()
{
    double min_boundary =*min_element(traj_.begin(), traj_.end());
    double max_boundary =*max_element(traj_.begin(), traj_.end());
    int hist_min = std::floor(min_boundary*discretize_);
    int hist_max = std::floor(max_boundary*discretize_+1);
    // Plus one make sure boundary works, since we are using floor function.
    int hist_nbins = hist_max - hist_min;
    // Initialize the bins
    std::vector<double> hist_accum;
    // hist_accum will count the data points in one bins
    for(int i=0; i<hist_nbins; i++)
    {
        hist_accum.push_back(0);
        free_energy.push_back(0);
    }
    for(int i=0; i<hist_nbins; i++)
    {
            bins_.push_back((hist_min+i)/discretize_);
    }
    // Get middle point of bins_
    for(int i=0; i<hist_nbins-1; i++)
            bin_position.push_back((hist_min+0.5+i)/(double)discretize_);

    double weight_datapoint = 1*discretize_/(double)traj_.size();
    int bins_index = 0;
    // Go throught the whole trajectory;
    // Add each data point probability;
    /*
    for(unsigned int i=0; i<traj_.size(); i++)
    {
            while(bins_[bins_index]<traj_[i])
            {
                bins_index += 1;
            }
            hist_accum[bins_index] += weight_datapoint;
            bins_index = 0;
    }
    The Procedure for double loop is too slow, so we change the poistion
    to bins_ index, which directly can add to bin_accum.*/

    // Change the poistion to bins_index;
    std::vector<int> traj_init;
    std::cout<<"Initialing trajectory, its size: "<<traj_.size()<<std::endl;
    for(unsigned int i = 0; i < traj_.size();i++ )
    {
        traj_init.push_back(static_cast<int>(std::floor(traj_[i]*discretize_)));
    }
    for(unsigned int i=0; i<traj_init.size(); i++)
    {
        hist_accum[traj_init[i]-hist_min] += weight_datapoint;
        // Each data point probability = weight_datapoint;
    }
    //Test if sum equal to zero.
    double sum = 0;
    for(auto & p : hist_accum)
            sum += p/discretize_;

    std::cout<<"Initialing trajectory, its size: "<<traj_.size()<<std::endl;



    bins_index = 0;
    // Free energy calculation: U = -k_BTlog(p)
    for(auto & p : hist_accum)
    {
            std::cout<<"Probability: "<<p<<std::endl;
            if(p==0){
                    free_energy[bins_index]=0; 
            }
            else{
                free_energy[bins_index] = -temperature_*log(p);
            }
            bins_index += 1;
    }
}
