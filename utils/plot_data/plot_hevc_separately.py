import os
import numpy as np
from matplotlib import pyplot as plt

data_dir = 'g:\\master\\desktop_verzije_programa\\data\\'
hevc_mods = ['encoder_intra_main_rext_sat' ,  'encoder_lowdelay_main_rext_sat_p']
results_file_name = 'global_enc_results.txt'
num_of_frames = 10
image_width = 7801
image_height = 7911
image_bitdepth = 16

for mod in hevc_mods:
    path = os.path.join(data_dir, mod)
    path = os.path.join(path, results_file_name)
    PSNR = np.loadtxt(path, dtype=float, delimiter='\t', usecols=2)
    compressed_size = np.loadtxt(path, dtype=int, delimiter='\t', usecols=1)
    original_size = image_width * image_height * image_bitdepth / 8
    ratio = original_size/compressed_size

    plot_path = os.path.join(data_dir, mod)
    plot_path = os.path.join(plot_path, (mod + '.jpg'))

    fig1 = plt.figure('Results')
    plt.plot(ratio, PSNR, label='')
    plt.xlabel('Ratio')
    plt.ylabel('PSNR')
    plt.title(mod)
    plt.legend()
    plt.savefig(plot_path)
    plt.show() 


    plot_path = os.path.join(data_dir, mod)
    plot_path = os.path.join(plot_path, (mod + '_100.jpg'))

    fig2 = plt.figure('Results')
    plt.plot(ratio, PSNR, label='')
    plt.xlim(-5, 105)
    plt.xlabel('Ratio')
    plt.ylabel('PSNR')
    plt.title(mod)
    plt.legend()
    plt.savefig(plot_path)
    plt.show() 
