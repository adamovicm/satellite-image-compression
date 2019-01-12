import os
import numpy as np
from matplotlib import pyplot as plt

# GLOBAL DATA
zoom = 100
zoom_negative = -5

# JPEG 2000 DATA
jdata_dir = 'g:\\master\\desktop_verzije_programa\\data\\j2k'
jresult_file = 'total_psnr.txt'
jimage_file_name = 'j2k_results'

# HEVC DATA
hdata_dir = 'g:\\master\\desktop_verzije_programa\\data\\'
hevc_mod_1 = 'encoder_intra_main_rext_sat'
hevc_mod_2 = 'encoder_lowdelay_main_rext_sat_p'
#hevc_mod_3 = 'encoder_lowdelay_main_rext_sat_b'
hresults_file = 'global_enc_results.txt'
num_of_frames = 10
image_width = 7801
image_height = 7911
image_bitdepth = 16


# JPEG 2000
path = os.path.join(jdata_dir, jresult_file)
jPSNR = np.loadtxt(path, dtype=float, delimiter='\t', usecols=1)
jcompression_ratio = np.loadtxt(path, dtype=float, delimiter='\t', usecols=2)

plot_path = os.path.join(jdata_dir, (jimage_file_name + '.jpg'))
fig = plt.figure('JPEG 2000')
plt.plot(jcompression_ratio, jPSNR, 'r', label='')
plt.xlabel('Compression Ratio')
plt.ylabel('PSNR')
plt.title('JPEG 2000')
plt.legend()
plt.savefig(plot_path)
plt.show()

plot_path = os.path.join(jdata_dir, (jimage_file_name + '_' + str(zoom) + '.jpg'))
fig = plt.figure('JPEG 2000 zoom')
plt.plot(jcompression_ratio, jPSNR, 'r', label='')
plt.xlim(zoom_negative, zoom)
plt.xlabel('Compression Ratio')
plt.ylabel('PSNR')
plt.title('JPEG 2000 - zoom')
plt.legend()
plt.savefig(plot_path)
plt.show()


# HEVC INTRA
path = os.path.join(hdata_dir, hevc_mod_1)
path = os.path.join(path, hresults_file)
hPSNR_intra = np.loadtxt(path, dtype=float, delimiter='\t', usecols=2)
hcompressed_size_intra = np.loadtxt(path, dtype=int, delimiter='\t', usecols=1)
original_size = image_width * image_height * image_bitdepth / 8
hratio_intra = original_size/hcompressed_size_intra

plot_path = os.path.join(hdata_dir, hevc_mod_1)
plot_path = os.path.join(plot_path, (hevc_mod_1 + '.jpg'))
fig = plt.figure('HEVC Intra')
plt.plot(hratio_intra, hPSNR_intra, 'b', label='')
plt.xlabel('Compression Ratio')
plt.ylabel('PSNR')
plt.title(hevc_mod_1)
plt.legend()
plt.savefig(plot_path)
plt.show() 

plot_path = os.path.join(hdata_dir, hevc_mod_1)
plot_path = os.path.join(plot_path, (hevc_mod_1 + '_' + str(zoom) +'.jpg'))
fig = plt.figure('HEVC Intra')
plt.plot(hratio_intra, hPSNR_intra, 'b', label='')
plt.xlim(zoom_negative, zoom)
plt.xlabel('Compression Ratio')
plt.ylabel('PSNR')
plt.title(hevc_mod_1 + ' - zoom')
plt.legend()
plt.savefig(plot_path)
plt.show() 

# HEVC INTER P
path = os.path.join(hdata_dir, hevc_mod_2)
path = os.path.join(path, hresults_file)
hPSNR_p = np.loadtxt(path, dtype=float, delimiter='\t', usecols=2)
hcompressed_size_p = np.loadtxt(path, dtype=int, delimiter='\t', usecols=1)
original_size = image_width * image_height * image_bitdepth / 8
hratio_p = original_size/hcompressed_size_p

plot_path = os.path.join(hdata_dir, hevc_mod_2)
plot_path = os.path.join(plot_path, (hevc_mod_2 + '.jpg'))
fig = plt.figure('HEVC Inter p')
plt.plot(hratio_p, hPSNR_p, 'g', label='')
plt.xlabel('Compression Ratio')
plt.ylabel('PSNR')
plt.title(hevc_mod_1)
plt.legend()
plt.savefig(plot_path)
plt.show() 

plot_path = os.path.join(hdata_dir, hevc_mod_2)
plot_path = os.path.join(plot_path, (hevc_mod_2 + '_' + str(zoom) +'.jpg'))
fig = plt.figure('HEVC HEVC Inter p - zoom')
plt.plot(hratio_p, hPSNR_p, 'g', label='')
plt.xlim(zoom_negative, zoom)
plt.xlabel('Compression Ratio')
plt.ylabel('PSNR')
plt.title(hevc_mod_1 + ' - zoom')
plt.legend()
plt.savefig(plot_path)
plt.show() 

# HEVC INTER B


# PLOT ALL
plot_path = hdata_dir + "All_in_one_results.jpg"
fig = plt.figure('All_in_one')
plt.plot(jcompression_ratio, jPSNR, 'r', label='JPEG 2000')
plt.plot(hratio_intra, hPSNR_intra, 'b', label='HEVC Intra')
plt.plot(hratio_p, hPSNR_p, 'g', label='HEVC Inter p')
#plt.plot(hratio_b, hPSNR_b, 'y', label='HEVC Inter b')
plt.xlim(zoom_negative, zoom)
plt.xlabel('Compression Ratio')
plt.ylabel('PSNR')
plt.title('Compression Comparison')
plt.legend()
plt.savefig(plot_path)
plt.show()