class Decryptor:
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    caesar_shift = 3
    vigenere_key = 'vigenere'
    playfair_key = 'playfair'

    playfair_matrix = ''
    playfair_mw = 5

    for letter in playfair_key + alphabet:
        letter = letter.upper()
        if letter == 'J': letter = 'I'
        if letter not in playfair_matrix:
            playfair_matrix += letter
    playfair_mh = int(len(playfair_matrix) / playfair_mw)

    @staticmethod
    def caesar_encode(word: str) -> str:
        new_word = ''
        for letter in word:
            if letter.upper() not in Decryptor.alphabet: continue
            index = (Decryptor.alphabet.index(letter.upper()) + Decryptor.caesar_shift) % len(Decryptor.alphabet)
            new_word += Decryptor.alphabet[index]
        return new_word

    @staticmethod
    def vigenere_encode(word: str) -> str:
        new_word = ''
        for i in range(len(word)):
            if word[i].upper() not in Decryptor.alphabet: continue
            shift_index = Decryptor.alphabet.index(Decryptor.vigenere_key[i % len(Decryptor.vigenere_key)].upper())
            index = (Decryptor.alphabet.index(word[i].upper()) + shift_index) % len(Decryptor.alphabet)
            new_word += Decryptor.alphabet[index]
        return new_word

    @staticmethod
    def playfair_encode(word: str) -> str:
        new_word = ''
        word = word.upper()
        if len(word) % 2: word += 'X'
        for i in range(int(len(word) / 2)):
            a, b = word[i * 2], word[i * 2 + 1]
            if a == b: b = 'X'
            ay, ax = divmod(Decryptor.playfair_matrix.index(a), Decryptor.playfair_mw)
            by, bx = divmod(Decryptor.playfair_matrix.index(b), Decryptor.playfair_mw)
            if ay == by:  # if in one string
                ax = (ax + 1) % Decryptor.playfair_mw
                bx = (bx + 1) % Decryptor.playfair_mw
            elif ax == bx:  # in in one column
                ay = (ay + 1) % Decryptor.playfair_mh
                by = (by + 1) % Decryptor.playfair_mh
            else:  # if in different strings and columns
                bx, ax = ax, bx
            new_word += Decryptor.playfair_matrix[ay * Decryptor.playfair_mw + ax] + \
                        Decryptor.playfair_matrix[by * Decryptor.playfair_mw + bx]
        return new_word


if __name__ == '__main__':
    print(Decryptor.caesar_encode('hello'))  # KHOOR
    print(Decryptor.vigenere_encode('hello'))  # CMRPB
    print(Decryptor.playfair_encode('hello'))  # KGYVSV
