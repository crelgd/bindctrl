# BindGB

Отправляет команды с клавиатуры на геймпад

ПО использует драйвер VigemBus, [установка](https://vigembusdriver.com/download/#)
# Настройка

Конфигурационный файл находится в корне с программой `conf.ini`
Оформление этого файла:
```
Клавиша для бинда:Комманда для контроллера
```

`Главное` после всех биндов переходить на `новую линию`

### Клавиши для бинда
Можно писать все буквы с верхним регистром плюс все цифры от 0 до 9, включая дополнительные:

* UP\DOWN\LEFT\RIGHT - стрелка вверх\вниз\влево\вправо
* MLEFT\MRIGHT - нажатия мышки на левую\правую кнопки

### Бинды для контроллера
* BOX_A\BOX_B\BOX_X\BOX_Y - кнопки a, b, x, y
* BOX_UP\BOX_DOWN\BOX_LEFT\BOX_RIGHT - кнопки вверх, вних, влево, вправо
* BOX_START\BOX_BACK - кнопки start, back
* BOX_LT\BOX_RT - кнопки left\right thumb
* BOX_LS\BOX_RS - кнопки left\right shoulder
* BOX_RUP\BOX_RDOWN\BOX_RLEFT\BOX_RRIGHT - положения правого стика

# Компиляция

```sh
git clone https://github.com/crelgd/bindctrl.git
cd bindctrl
.\bindctrl.sln
```

Клонировать [vigem client](https://github.com/nefarius/ViGEmClient)

```sh
git clone https://github.com/nefarius/ViGEmClient.git
cd ViGEmClient\include\
move ViGEm ..\..\include
cd ..\..\
```

# License

BindGB использует MIT License