import os,sys

if len(sys.argv) != 4:
    print('Wrong number of arguments, input should be: python CombineOutputPrep.py [abs_path_combine_output] [tag_flavor] [tag_year]')
    sys.exit()


combine_files_path = sys.argv[1]
tag_flavor = sys.argv[2]
tag_year   = sys.argv[3]
txtfilename = combine_files_path + tag_flavor + tag_year + '.txt'
#txtfilename = combine_files_path + combine_files_path.split('/')[-2] + '.txt'
print 'Filling text file: {}'.format(txtfilename)
txtfile = open(txtfilename, 'w')

for root, dirs, files in os.walk(combine_files_path):
    for f in files:
        f_abspath = os.path.abspath(os.path.join(root, f))
        if 'higgsCombine' in f_abspath and '.root' in f_abspath and tag_flavor in f_abspath and tag_year in f_abspath:
            txtfile.write('{}\n'.format(f_abspath))
txtfile.close()
