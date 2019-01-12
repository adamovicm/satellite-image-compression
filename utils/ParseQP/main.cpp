/********************************************************
 * This program parses results gained from ChangeQP and 
 * exports them to a single txt file.
 * 
 * Marko Adamovic
 * 13.08.2018.
 * v2.0 
 ********************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    // Parameters
    int QP_start = -48; // starting QP value. default -48
    int QP_end = 51; // final QP value. default 51
    int QP_step = 6; // step of QP. default 3

    // output directory with results. don't forget to add / at the end!
    std::string output_dir = "D:/master/satelite_image_compression/output/";

    // vector of output directories with config file names to go through 
    // don't forget to add / at the end!
    std::vector<std::string> cfg_dir = 
    {
        //"encoder_intra_main_rext_sat/",
        "encoder_lowdelay_main_rext_sat_p/",
        "encoder_lowdelay_main_rext_sat_b/"
    };

	std::string st;

    for (int cfg = 0; cfg < cfg_dir.size(); ++cfg)
    {
        for (int QP = QP_start; QP <= QP_end; QP += QP_step)
        {
			//st = cfg_dir[cfg].substr(0, cfg_dir[cfg].size() - 4);
			std::string output_enc_dir = output_dir + cfg_dir[cfg] + "enc/";

            std::string filename = output_enc_dir +  "QP_" + std::to_string(QP) + ".txt";
            std::fstream input_file(filename);
            
            if (!input_file.is_open())
            {
                std::cout << std::endl << "ERROR while opening input file" << std::endl;
                return -1;
            }

            std::string PSNR;
            std::string file_size;
            std::string time;
            std::string line;

            while (std::getline(input_file, line))
            {
                // PSNR
                std::size_t found = line.find("  a  ");
                if (found != std::string::npos)
                {
                    line.erase(0, found + 16);
                    while (line[0] == ' ')
                        line.erase(0, 1);
                    PSNR = line;
                }

                // File size
                found = line.find("Bytes written to file: ");
                if (found != std::string::npos)
                {
                    line.erase(0, 23);
                    found = line.find(" (");
                    if (found != std::string::npos)
                        line.erase(found, line.length() - found);
                    file_size = line;
                }

                // Time
                found = line.find("Total Time: ");
                if (found != std::string::npos)
                {
                    line.erase(0, 13);
                    while (line[0] == ' ')
                        line.erase(0, 1);
                    line.erase(line.length() - 5, 5);
                    time = line;
                }
            }

            // Results
            std::string output_result = output_dir + cfg_dir[cfg] + "global_enc_results.txt";
            std::ofstream output_file(output_result, std::ofstream::app);
            if (!output_file.is_open())
            {
                std::cout << std::endl << "ERROR while opening output file" << std::endl;
                return -1;
            }

            output_file << QP << "\t" << file_size << "\t" << PSNR << "\t" << time << std::endl;
        }
    }
    
    return 0;
}