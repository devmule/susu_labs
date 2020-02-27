import random


class Pass:
    Characters = []

    Characters.extend([i for i in range(33, 40)])  # [!, “, #, $, %, &, ‘]

    Characters.extend([i for i in range(48, 58)])  # [0; 9]

    Characters.extend([i for i in range(65, 91)])  # [A; Z]
    Characters.extend([i for i in range(97, 123)])  # [a; z]

    Characters.extend([i for i in range(1040, 1104)])  # [А; я]

    @staticmethod
    def get_alphabet() -> str:
        letters = ''
        for letter in Pass.Characters:
            letters += chr(letter)
        return letters

    @staticmethod
    def generate_pass(pass_len: int = 0) -> str:
        password = ''
        alphabet_len = len(Pass.Characters)

        for i in range(pass_len):
            password += chr(Pass.Characters[random.randint(0, alphabet_len - 1)])

        return password
