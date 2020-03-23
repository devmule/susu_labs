class Encoder:
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ .,!?'

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
            if letter.upper() not in Encoder.alphabet: continue
            index = (Encoder.alphabet.index(letter.upper()) + Encoder.caesar_shift) % len(Encoder.alphabet)
            new_word += Encoder.alphabet[index]
        return new_word

    @staticmethod
    def vigenere_encode(word: str) -> str:
        new_word = ''
        for i in range(len(word)):
            if word[i].upper() not in Encoder.alphabet: continue
            shift_index = Encoder.alphabet.index(Encoder.vigenere_key[i % len(Encoder.vigenere_key)].upper())
            index = (Encoder.alphabet.index(word[i].upper()) + shift_index) % len(Encoder.alphabet)
            new_word += Encoder.alphabet[index]
        return new_word

    @staticmethod
    def playfair_encode(word: str) -> str:
        new_word = ''
        word = word.upper()
        for i in range(len(word) - 1, -1, -1):  # delete all symbols which not in alphabet
            if word[i] not in Encoder.alphabet: word = word[:i] + word[i + 1:]
        if len(word) % 2: word += 'X'
        for i in range(int(len(word) / 2)):
            a, b = word[i * 2], word[i * 2 + 1]
            if a == b: b = 'X'
            ay, ax = divmod(Encoder.playfair_matrix.index(a), Encoder.playfair_mw)
            by, bx = divmod(Encoder.playfair_matrix.index(b), Encoder.playfair_mw)
            if ay == by:  # if in one string
                ax = (ax + 1) % Encoder.playfair_mw
                bx = (bx + 1) % Encoder.playfair_mw
            elif ax == bx:  # in in one column
                ay = (ay + 1) % Encoder.playfair_mh
                by = (by + 1) % Encoder.playfair_mh
            else:  # if in different strings and columns
                bx, ax = ax, bx
            new_word += Encoder.playfair_matrix[ay * Encoder.playfair_mw + ax] + \
                        Encoder.playfair_matrix[by * Encoder.playfair_mw + bx]
        return new_word


if __name__ == '__main__':
    print(Encoder.caesar_encode('hello'))  # KHOOR
    print(Encoder.vigenere_encode('hello'))  # CMRPB
    print(Encoder.playfair_encode('hello'))  # KGYVSV
