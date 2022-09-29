import os,sys

if len(sys.argv) != 6:
    print('Wrong number of arguments, input should be: python CombineOutputPrep.py [abs_path_combine_output] [tag_flavor] [tag_year] [tag_nature] [outputname]')
    sys.exit()

def goodMV2(filename):
    if 'M-1_' in filename:
        if '4e-08' in filename or '6e-08' in filename or '8e-08' in filename or '1e-07' in filename or '3e-07' in filename or '5e-07' in filename or '7e-07' in filename or '9e-07' in filename or '2e-06' in filename or '4e-06' in filename or '6e-06' in filename or '8e-06' in filename:
            return False
        if '9e-02' in filename or  '7e-02' in filename or '5e-02' in filename or '3e-02' in filename or '1e-02' in filename or '9e-03' in filename or '7e-03' in filename or '5e-03' in filename or '3e-03' in filename or '1e-03' in filename:
            return False
    elif 'M-2_' in filename:
        if '4e-08' in filename or '6e-08' in filename or '8e-08' in filename or '1e-07' in filename or '3e-07' in filename or '5e-07' in filename or '7e-07' in filename or '9e-07' in filename:
            return False
        if '9e-02' in filename or  '7e-02' in filename or '5e-02' in filename or '3e-02' in filename or '1e-02' in filename or '9e-03' in filename or '7e-03' in filename or '5e-03' in filename or '3e-03' in filename or '1e-03' in filename or '9e-04' in filename or '7e-04' in filename or '5e-04' in filename or '3e-04' in filename or '1e-04' in filename or '9e-05' in filename:
            return False
    elif 'M-3_' in filename:
        if '4e-08' in filename or '6e-08' in filename or '8e-08' in filename or '1e-07' in filename:
            return False
        if '9e-02' in filename or  '7e-02' in filename or '5e-02' in filename or '3e-02' in filename or '1e-02' in filename or '9e-03' in filename or '7e-03' in filename or '5e-03' in filename or '3e-03' in filename or '1e-03' in filename or '9e-04' in filename or '7e-04' in filename or '5e-04' in filename or '3e-04' in filename or '1e-04' in filename or '9e-05' in filename:
            return False
    elif 'M-12_' in filename:
        if '9e-02' in filename or  '7e-02' in filename or '5e-02' in filename or '3e-02' in filename or '1e-02' in filename or '9e-03' in filename or '7e-03' in filename or '5e-03' in filename or '3e-03' in filename or '1e-03' in filename or '9e-04' in filename or '7e-04' in filename or '5e-04' in filename or '3e-04' in filename or '1e-04' in filename or '9e-05' in filename:
            return False
    elif 'M-14_' in filename:
        if '9e-02' in filename or  '7e-02' in filename or '5e-02' in filename or '3e-02' in filename or '1e-02' in filename or '9e-03' in filename or '7e-03' in filename or '5e-03' in filename or '3e-03' in filename or '1e-03' in filename or '9e-04' in filename or '7e-04' in filename or '5e-04' in filename or '3e-04' in filename or '1e-04' in filename or '9e-05' in filename or '7e-05' in filename or '5e-05' in filename or '3e-05' in filename or '1e-05' in filename:
            return False
    return True

combine_files_path = sys.argv[1]
tag_flavor = sys.argv[2]
tag_year   = sys.argv[3]
tag_nature = sys.argv[4]
outputname = sys.argv[5]
txtfilename = combine_files_path + outputname + '.txt'
#txtfilename = outputname + '.txt'
#txtfilename = combine_files_path + combine_files_path.split('/')[-2] + '.txt'
print 'Filling text file: {}'.format(txtfilename)
txtfile = open(txtfilename, 'w')

for root, dirs, files in os.walk(combine_files_path):
    for f in files:
        f_abspath = os.path.abspath(os.path.join(root, f))
        if 'higgsCombine' in f_abspath and '.root' in f_abspath and tag_flavor in f_abspath and tag_year in f_abspath and tag_nature in f_abspath:
            #if goodMV2(f_abspath):
                txtfile.write('{}\n'.format(f_abspath))
txtfile.close()
