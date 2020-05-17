class Encoder:
    """Этот модуль содержит в себе алфавит и методы для шифровки
    и расшифровки тремя алгоритмами шифрования: caesar, vigenere, playfair"""
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.!()-\"\';:%*?&'

    @staticmethod
    def caesar_encode(word: str, caesar_shift: int = 3) -> str:
        new_word = ''
        for letter in word:
            if letter.upper() not in Encoder.alphabet: continue
            index = (Encoder.alphabet.index(letter.upper()) + caesar_shift) % len(Encoder.alphabet)
            new_word += Encoder.alphabet[index]
        return new_word

    @staticmethod
    def caesar_decode(word: str, caesar_shift: int = 3) -> str:
        return Encoder.caesar_encode(word, -caesar_shift)

    @staticmethod
    def vigenere_encode(word: str, vigenere_key: str = 'KEY') -> str:
        new_word = ''
        for i in range(len(word)):
            if word[i].upper() not in Encoder.alphabet: continue
            shift_index = Encoder.alphabet.index(vigenere_key[i % len(vigenere_key)].upper())
            index = (Encoder.alphabet.index(word[i].upper()) + shift_index) % len(Encoder.alphabet)
            new_word += Encoder.alphabet[index]
        return new_word

    @staticmethod
    def vigenere_decode(word: str, vigenere_key: str = 'KEY') -> str:
        new_word = ''
        for i in range(len(word)):
            if word[i].upper() not in Encoder.alphabet: continue
            shift_index = -Encoder.alphabet.index(vigenere_key[i % len(vigenere_key)].upper())
            index = (Encoder.alphabet.index(word[i].upper()) + shift_index) % len(Encoder.alphabet)
            new_word += Encoder.alphabet[index]
        return new_word

    @staticmethod
    def playfair_encode(word: str, playfair_key: str = 'KEY') -> str:
        playfair_matrix = ''
        playfair_mw = 5
        # !!! IMPORTANT !!! ( playfair_mw * playfair_mh ) MUST BE INTEGER !!!

        for letter in playfair_key + Encoder.alphabet:
            letter = letter.upper()
            if letter == 'J': letter = 'I'
            if letter not in playfair_matrix:
                playfair_matrix += letter
        playfair_mh = int(len(playfair_matrix) / playfair_mw)

        new_word = ''
        word = word.upper()

        for i in range(len(word) - 1, -1, -1):  # delete all symbols which not in alphabet
            if word[i] not in Encoder.alphabet: word = word[:i] + word[i + 1:]
        if len(word) % 2: word += 'X'
        for i in range(int(len(word) / 2)):
            a, b = word[i * 2], word[i * 2 + 1]
            if a == b: b = 'X'
            ay, ax = divmod(playfair_matrix.index(a), playfair_mw)
            by, bx = divmod(playfair_matrix.index(b), playfair_mw)
            if ay == by:  # if in one string
                ax = (ax + 1) % playfair_mw
                bx = (bx + 1) % playfair_mw
            elif ax == bx:  # in in one column
                ay = (ay + 1) % playfair_mh
                by = (by + 1) % playfair_mh
            else:  # if in different strings and columns
                bx, ax = ax, bx
            new_word += playfair_matrix[ay * playfair_mw + ax] + playfair_matrix[by * playfair_mw + bx]
        return new_word

    @staticmethod
    def playfair_decode(word: str, playfair_key: str = 'KEY') -> str:
        playfair_matrix = ''
        playfair_mw = 5
        # !!! IMPORTANT !!! ( playfair_mw * playfair_mh ) MUST BE INTEGER !!!

        for letter in playfair_key + Encoder.alphabet:
            letter = letter.upper()
            if letter == 'J': letter = 'I'
            if letter not in playfair_matrix:
                playfair_matrix += letter
        playfair_mh = int(len(playfair_matrix) / playfair_mw)

        new_word = ''
        word = word.upper()

        for i in range(len(word) - 1, -1, -1):  # delete all symbols which not in alphabet
            if word[i] not in Encoder.alphabet: word = word[:i] + word[i + 1:]
        if len(word) % 2: word += 'X'
        for i in range(int(len(word) / 2)):
            a, b = word[i * 2], word[i * 2 + 1]
            if a == "J": a = "I"
            if b == "J": b = "I"
            if a == b: b = 'X'
            ay, ax = divmod(playfair_matrix.index(a), playfair_mw)
            by, bx = divmod(playfair_matrix.index(b), playfair_mw)
            if ay == by:  # if in one string
                ax = (ax - 1) % playfair_mw
                bx = (bx - 1) % playfair_mw
            elif ax == bx:  # in in one column
                ay = (ay - 1) % playfair_mh
                by = (by - 1) % playfair_mh
            else:  # if in different strings and columns
                bx, ax = ax, bx
            new_word += playfair_matrix[ay * playfair_mw + ax] + playfair_matrix[by * playfair_mw + bx]
        return new_word
