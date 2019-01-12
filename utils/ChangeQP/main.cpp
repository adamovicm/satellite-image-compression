/*********************************************************************************************
 * This proram starts HM reference code with selected configuration files
 * and selected range of the QP values. 
 * 
 * It puts results in the output directory as text files, separates them in folders 
 * for each configuration and QP. Those files are ready to be parsed using ParseQP program.
 * 
 * WARNING: any existing files in the output directory will be OVERWRITTEN! 
 * So if needed, make backups before starting the program!
 * 
 * Marko Adamovic
 * 13.08.2018.
 * v2.0
 ********************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <windows.h>
#include <filesystem>
#if __cplusplus < 201703L // If the version of C++ is less than 17
 // It was still in the experimental:: namespace
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif

int main()
{
    // Parameters
    int QP_start = -48; // starting QP value. default -48
    int QP_end = 51; // final QP value. default 51
    int QP_step = 6; // step of QP. default 3
    // HEVC reference code (HM) root dir. don't forget to add / at the end!
    std::string HM_root_dir = "C:/Users/Work-Desktop/Desktop/satelite_image_compression/HM-15.0+RExt-8.1/";
    std::string per_sequence_cfg = "sat_ic.cfg"; // name of per-sequence cfg file

	// output directory with results. don't forget to add / at the end!
	std::string output_dir = "C:/Users/Work-Desktop/Desktop/satelite_image_compression/output/"; 
	std::string st;
    // vector of needed encoder config files
    std::vector<std::string> encoder_cfg = 
    {
        "encoder_intra_main_rext_sat.cfg",
		"encoder_lowdelay_main_rext_sat_p.cfg",
		//"encoder_lowdelay_main_rext_sat_b.cfg"
    };

    for (int cfg = 0; cfg < encoder_cfg.size(); ++cfg)
    {
		st = encoder_cfg[cfg].substr(0, encoder_cfg[cfg].size() - 4);
        std::string new_output_enc_dir = output_dir + st + "/enc";
        //new_output_enc_dir.erase(new_output_enc_dir.length() - 4);

		fs::create_directories(new_output_enc_dir.c_str());

        std::string new_output_dec_dir = output_dir + st + "/dec";
        //new_output_dec_dir.erase(new_output_dec_dir.length() - 4);

		fs::create_directories(new_output_dec_dir.c_str());

        for (int QP = QP_start; QP <= QP_end; QP += QP_step)
        {
            // encoder input parameters
            std::string enc = HM_root_dir + "bin/TAppEncoder.exe"
                            " -c " + HM_root_dir + "cfg/" + encoder_cfg[cfg] + 
                            " -c " + HM_root_dir + "cfg/per-sequence/" + per_sequence_cfg +
                            " -q ";
            enc = enc + std::to_string(QP);
         
            // encoder output
            std::string txt_file = new_output_enc_dir + "/QP_" + std::to_string(QP) + ".txt";

            // remove old file if it exists
            remove(txt_file.c_str());
            
            enc = enc + " >> " + txt_file;
            system(enc.c_str());

            // decoder
            std::string dec = HM_root_dir + "bin/TAppDecoder.exe"
                            " -b " + output_dir + "sat_out.bin"
                            " -o " + output_dir + "sat_out.yuv -d 16";
            txt_file = new_output_dec_dir + "/QP_" + std::to_string(QP) + ".txt";

            // remove old file
            remove(txt_file.c_str());

            dec = dec + " >> " + txt_file;
            system(dec.c_str());
        }
    }

    return 0;
}