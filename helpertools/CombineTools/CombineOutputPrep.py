import os,sys

if len(sys.argv) != 3:
    print('Wrong number of arguments, input should be: python CombineOutputPrep.py [abs_path_combine_output] [tag]')
    sys.exit()


combine_files_path = sys.argv[1]
tag = sys.argv[2]
txtfilename = combine_files_path + tag + '.txt'
#txtfilename = combine_files_path + combine_files_path.split('/')[-2] + '.txt'
print 'Filling text file: {}'.format(txtfilename)
txtfile = open(txtfilename, 'w')

for root, dirs, files in os.walk(combine_files_path):
    for f in files:
        if 'higgsCombine' in f and '.root' in f and tag in f:
            txtfile.write('{}\n'.format(os.path.abspath(os.path.join(root, f)), f))
txtfile.close()
