#
# 1. В табл. 3 найти для указанного варианта значения характеристик P, V, T.
# 2. Вычислить по формуле (1) нижнюю границу S* для заданных P, V, T.
# 3. Выбрать некоторый алфавит с мощностью A и получить минимальную длину пароля L, при котором выполняется условие (2).
# 4. Реализовать программу для генерации паролей пользователей. Программа должна формировать
# случайную последовательность символов длины L, при этом должен использоваться алфавит из A символов.
#
#  (1) S* = [V ∙ Т / Р]      (2) S* ≤ S = A^L
#   P = (V ∙ T) / S  =  (V ∙ T) / A^L
# -------------------------------------------------------------------------------------------------------------------- #

import random
import math


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


# ======== 1 ========
print('#1\n'
      'Вариант     P            V             T\n'
      '   3      10^-6     10 pass/min     5 дней\n')

P = 1e-06  # = 10^-6
V = 10  # pass / min
T = 5 * 24 * 60  # days * hours * minutes

# ======== 2 ========
# S_ = S*
S_ = math.floor(V * T / P)
print('#2\n'
      'S* = %d\n' % S_)

# ======== 3 ========
# L = Log A S
print('#3')
A = len(Pass.Characters)
L = math.ceil(math.log(S_, A))
print('A = %d' % A)
print('L = %d\n' % L)

# ======== 4 ========
print('#4')
print(Pass.get_alphabet())
print('passwords:')
for i in range(5):
    print(Pass.generate_pass(L))
