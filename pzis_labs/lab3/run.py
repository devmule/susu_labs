import json
from Decryptor import Decryptor

with open('dict.json') as json_file:
    dictionary = json.load(json_file)
json_file.close()

command = ''  # command user write
IS_RUN = True

print('\nlist of commands:\n'
      '1) decode - decode word from file \'encoded\' and write to file \'decoded\'\n'
      '2) encode < ENCODE TYPE > - encode, where type is in [caesar, vigenere, playfair]')
print('dictionary length =', len(dictionary), '\n')
while IS_RUN:
    command = input('#> ').strip()
    com_words = command.split(' ')

    if com_words[0] == 'decode':
        # todo make
        print('\nDONE!\n')
        IS_RUN = False

    elif com_words[0] == 'encode':
        if len(com_words) >= 2:
            if com_words[1] == 'caesar':
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Decryptor.caesar_encode(decoded_file.read()))
                print('\nDONE!\n')
                IS_RUN = False
            elif com_words[1] == 'vigenere':
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Decryptor.vigenere_encode(decoded_file.read()))
                print('\nDONE!\n')
                IS_RUN = False
            elif com_words[1] == 'playfair':
                decoded_file = open('decoded.txt', 'r')
                encoded_file = open('encoded.txt', 'w')
                encoded_file.write(Decryptor.playfair_encode(decoded_file.read()))
                print('\nDONE!\n')
                IS_RUN = False
            else:
                print('\nunknown encoder \'%s\'\n' % com_words[1])
        else:
            print('\nempty encoder type\n')
    else:
        print('\nunknown command \'%s\'\n' % com_words[0])
