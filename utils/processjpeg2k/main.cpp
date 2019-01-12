#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

int main()
{
    int psnr_start = 34;
    int psnr_end = 134;
    int psnr_step = 2;
    int number_of_images = 10;
    int width = 7801;
    int height = 7911;
    int bitdepth = 16;

    std::string openjpeg = "../openjpeg/bin/./";
    std::string snr_program = "../snr/./snr";
    std::string images_dir = "/home/adam/share/tif/";
    std::string output_dir = "/home/adam/share/jp2/";
    std::string raw_dir = "/home/adam/share/raw/";
    std::string results_dir = "/home/adam/share/results/";

    int uncompressed = width * height * bitdepth / 8;

    for(int psnr = psnr_start; psnr <= psnr_end; psnr += psnr_step)
    {
        std::cout << "PSNR: " << psnr << std::endl;
        double total_psnr(0);
        double total_comp_ratio(0);
        double sum_file_size(0);

        for(int image = 1; image <= number_of_images; ++image)
        {
            std::cout << "Image " << image << std::endl;

            std::string jp2_image = output_dir + std::to_string(image) + ".jp2";
            std::string encode = openjpeg + "opj_compress -i " + 
                images_dir + std::to_string(image) + ".TIF -o " + 
                jp2_image + " -q " + std::to_string(psnr);

            std::cout << "Compressing..." << std::endl;
    		system(encode.c_str());

            // decompress jp2 to raw
            std::string raw_image = output_dir + std::to_string(image) + ".RAW";
			std::string decode = openjpeg + "opj_decompress -i " + output_dir + 
                std::to_string(image) + ".jp2 -o " + raw_image;

            std::cout << "Decompressing..." << std::endl;
            system(decode.c_str());

            // compare raws
            std::string compare_file = results_dir + "compare.txt";
            std::string compare = snr_program + " " + raw_dir + std::to_string(image) +
                ".RAW " + raw_image + " " + std::to_string(width) + " " + std::to_string(height) + 
                " " + std::to_string(bitdepth) + " false > " + compare_file;
            
            std::cout << "Comparing RAWs..." << std::endl;
            system(compare.c_str());

            // compression ratio
            double compressed, compression_ratio;
            std::streampos begin, end;

            std::ifstream f1(jp2_image, std::ifstream::binary);
            begin = f1.tellg();
            f1.seekg(0, std::ifstream::end);
            end = f1.tellg();
            f1.close();
            compressed = end - begin;

            sum_file_size += compressed;
            compression_ratio = uncompressed / compressed;


            // save data
            std::cout << "Saving results..." << std::endl;
            std::ifstream compare_results_file(compare_file);
            if(!compare_results_file.is_open())
            {
                std::cout << "ERROR while opening compare.txt file!" << std::endl;
                return -1;
            }

            std::string line;

            std::getline(compare_results_file, line);
            std::size_t found = line.find("PSNR=");
            if(found != std::string::npos)
            {
                line.erase(0, found + 5);
                line.pop_back();
                line.pop_back();
            }
            
            std::string result_file = results_dir + std::to_string(psnr) + ".txt";
            std::ofstream psnr_results(result_file, std::ofstream::out | std::ofstream::app);
            if(!psnr_results.is_open())
            {
                std::cout << std::endl << "ERROR while opening PSNR results file!" << std::endl;
                return -1;
            }

            psnr_results << line << "\t" << compression_ratio << compressed << std::endl;
            psnr_results.close();

            total_psnr += std::stod(line);
            
        }

        // write data for each PSNR
        total_psnr /= number_of_images;
        total_comp_ratio = (number_of_images * uncompressed) / sum_file_size;

        std::ofstream total_psnr_file(results_dir + "total_psnr.txt", std::ofstream::out | std::ofstream::app);
    	if(!total_psnr_file.is_open())
        {
            std::cout << std::endl << "ERROR while opening total_psnr.txt file!" << std::endl;
            return -1;
        }

        total_psnr_file << std::fixed << psnr << "\t" << total_psnr << "\t" << total_comp_ratio << "\t" << sum_file_size << std::endl; // ovde sam dodao fixed
        total_psnr_file.close(); 

        // delete jp2 and raw files
        std::string delete_all = "rm -rf " + output_dir + "*";
        system(delete_all.c_str());
    }

    std::cout << std::endl << std::endl << std::endl;
    std::cout << "Columns in total_psnr.txt file: " << std::endl;
    std::cout << "Set PSNR\tMean PSNR\tMean compression ratio\tSum of file sizes " << std::endl;

    return 0;
}
