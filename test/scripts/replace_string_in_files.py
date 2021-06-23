import os,sys

def replace_string_in_file(filename, old_string, new_string):
    print('changing {}'.format(filename))
    with open(filename, 'r') as file :
        filedata = file.read()
    
    filedata = filedata.replace(old_string, new_string)
    
    with open(filename, 'w') as file :
        file.write(filedata)


old_string = 'POGTightID_unparametrized_LowAndHighMass'
new_string = 'unparametrized_LowAndHighMass'
print('changing {} to {}'.format(old_string, new_string))
for i in range(1, len(sys.argv)):
    replace_string_in_file(sys.argv[i], old_string, new_string)


#alternative script if i just want to make copies of certain files with slightly different names
#for i in range(1, len(sys.argv)):
#    old_name = sys.argv[i]
#    new_name = old_name.replace('2017', '1718')
#    os.system('cp {} {}'.format(old_name, new_name))
