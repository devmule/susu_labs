import random


def element_id(array, search_elem):
    for i in range(len(array)):
        elem = array[i]
        if elem == search_elem:
            return i
    return -1


rights_decodes = {
    "000": "Запрет",
    "001": "Только передача прав",
    "010": "Только запись",
    "011": "Запись, передача прав",
    "100": "Только чтение",
    "101": "Чтение, Передача прав",
    "110": "Чтение, Запись",
    "111": "Полные права",
}


class System:
    def __init__(self):

        self.objects = ["file_1", "file_2", "CD-RW", "drive"]
        self.users = {'Admin': []}

        for obj in self.objects:
            self.users['Admin'].append('111')
        users = ['guest', 'Vasya', 'Petya', 'Maxim']
        for user in users:
            self.users[user] = []
            for obj in self.objects:
                self.users[user].append(
                    str(int(random.randint(0, 1))) + str(int(random.randint(0, 1))) + str(int(random.randint(0, 1))))

        self.current_user = None
        self.current_act = 0

    def run(self):
        while True:
            self.log_in()
            self.command_cycle()

    def command_cycle(self):
        while not (self.current_user is None):
            command = input('%s > ' % self.current_user)
            while command.find('  ') != -1:
                command.replace('  ', ' ')
            values = command.strip().split(' ')

            if values[0] == 'read' or values[0] == 'write':
                if len(values) >= 2:
                    elem_id = element_id(self.objects, values[1])
                    if elem_id >= 0:
                        if values[0] == 'read':
                            if self.have_right(elem_id, 0):
                                print('\n< ЧТЕНИЕ ПРОИЗВЕДЕНО >\n')
                            else:
                                print('\nУ вас нет прав на чтение объекта \'%s\'\n' % values[1])
                        elif values[0] == 'write':
                            if self.have_right(elem_id, 1):
                                print('\n< ЗАПИСЬ ПРОИЗВЕДЕНА >\n')
                            else:
                                print('\nУ вас нет прав на запись в объект \'%s\'\n' % values[1])
                    else:
                        print('\nНеизвестный объект \'%s\'\n' % values[1])
                else:
                    print('\nНедостаточно аргуметнов\n')

            elif values[0] == 'give_right':
                if len(values) >= 4:
                    elem_id = element_id(self.objects, values[1])
                    if elem_id >= 0:
                        if values[2] in self.users.keys():
                            if self.have_right(elem_id, 2):
                                if values[3].isdigit():
                                    if 2 >= int(values[3]) >= 0:
                                        if self.have_right(elem_id, int(values[3])):
                                            self.set_right(values[2], elem_id, int(values[3]), True)
                                            print('\n< ПРАВА ПЕРЕДАНЫ ПОЛЬЗОВАТЕЛЮ %s >\n' % values[2])
                                        else:
                                            print('\nВы не можете делиться правами, которыми не обладаете\n')
                                    else:
                                        print('\nЗначение id должно быть в пределах [0;2]\n')
                                else:
                                    print('\nЗначение id должно быть целочисленным\n')
                            else:
                                print('\nУ вас нет прав на передачу прав на объект \'%s\'\n' % values[1])
                        else:
                            print('\nПользователя %s не существует!\n' % values[2])
                    else:
                        print('\nНеизвестный объект \'%s\'\n' % values[1])
                else:
                    print('\nНедостаточно аргуметнов\n')

            elif values[0] == 'help':
                print('\nКоманды:\n'
                      'read <название объекта>  - чтение объекта\n'
                      'write <название объекта>  - запись в объект\n'
                      'give_right <название объекта> <имя пользователя> <id права>  - выдача прав, '
                      'где 0 - чтение, 1 - запись, 2 - передача прав\n'
                      'logout  - выход из ситсемы\n'
                      'help  - помощь\n')

            elif values[0] == 'logout':
                self.log_out()

            else:
                print('\nНеизвестная команда \'%s\'\n' % values[0])

    def have_right(self, obj_id: int, right_id: int):
        return self.users[self.current_user][obj_id][right_id] != '0'

    def set_right(self, user: str, obj_id: int, right_id: int, val: bool):
        rights = list(self.users[user][obj_id])
        rights[right_id] = str(int(val))
        self.users[user][obj_id] = "".join(rights)

    def log_in(self):
        while self.current_user is None:
            name = input('Введите имя пользователя > ')
            if name in self.users.keys():
                self.current_user = name
                print('\nВход осуществлён. Добро пожаловать! \nперечень ваших прав:')
                for i in range(len(self.users[self.current_user])):
                    print('{0}:\t\t\t{1}'.format(self.objects[i],
                                                 rights_decodes[self.users[self.current_user][i]]))
                print('Введите \'help\' для помощи\n')
            else:
                print('\nОшибка входа: пользователя %s не существует!\n' % name)

    def log_out(self):
        print('\nПользователь %s Вышел!\n' % self.current_user)
        self.current_user = None
        return


if __name__ == '__main__':
    system = System()
    system.run()
