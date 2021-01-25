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
