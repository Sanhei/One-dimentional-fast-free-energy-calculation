#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "histogram.hpp"
#include "options.hpp"

#define PROGRAM_NAME "Free_energy"
int main(int argc, char** argv)
{
        // Read trajectory
        program_options options;
        options.parse(argc, argv);
        
        

        std::cout<<"File name is "<< options.get("filename")<<std::endl;
        std::string filename=  options.get("filename");//= options.get("filename");
        std::ifstream inputfile;

        inputfile.open(filename);
        std::cout<<"Check point One"<<std::endl;
        if(!inputfile)
        {
                std::cout<<"unable to openfile";
                exit(1);
        }
        double x;
        std::vector<double> trajectory;
        std::cout<<"Reading trajectory"<<std::endl;
        while(inputfile>>x)
        {
                trajectory.push_back(x);
        }

        // Dicretize for histogram bin size: like 1/50;
        int discretize = 50;
        Histogram Free_energy_profile(50, trajectory, 1000);
        std::cout<<"Check point Two"<<std::endl;
        Free_energy_profile.Free_energy();

        //Save file
        std::ofstream file;
        std::string fileformat(".txt");
        file.open("Free_energy"+filename.substr(0, 4)+fileformat);
        for(int i=0; i<Free_energy_profile.bin_position.size(); i++)
        {
                file<<Free_energy_profile.bin_position[i]<<" "<<Free_energy_profile.free_energy[i]<<std::endl;
        }
        file.close();
}


void program_options::parse(int argc, char** argv)
{
    namespace po = boost::program_options;

    po::options_description desc("Program options");
    desc.add_options()
        ("filename", po::value<std::string>()->required(), "trajectory filename")

        ("help", "display this help and exit")
        ;

    try {
        po::command_line_parser parser(argc, argv);
        po::parsed_options parsed(parser.options(desc).run());
        po::store(parsed, vm_);
        

        if (vm_.count("help")) {
            std::cout << "Usage: " PROGRAM_NAME " [OPTION]...\n\n" << desc << std::endl;
            exit(EXIT_SUCCESS);
        }

        po::notify(vm_);
    }
    catch (std::exception const& e) {
        std::cerr << PROGRAM_NAME ": " << e.what() << "\n\n";
        std::cerr << "Try `" PROGRAM_NAME " --help' for more information." << std::endl;
        exit(EXIT_FAILURE);
    }
}
