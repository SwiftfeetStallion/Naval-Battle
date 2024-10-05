# Naval Battle

Игрок играет в морской бой с компьютером. Он запускает игру командой ./run.sh. Система предлагает ему  ввести координаты всех его кораблей (числа от 0 до 10), затем появляются две карты, одна из которых  принадлежит компьютеру и закрыта, а на другой отображаются координаты кораблей игрока. Далее игрок  стреляет, а система отвечает ему. Игра продолжается до тех пор, пока один из игроков не победит или  пользователь не закроет игровое окно.  
Данная версия кода позволяет расставлять корабли на поле, указав в начале игры их координаты, а потом  играть с компьютером, который выбирает выстрелы случайно (если он попал в корабль, он будет его  добивать). Когда все корабли одной из сторон разрушены, открывается соответствующее окно (поражения или  победы), причём в случае поражения игрока открывается расстановка компьютера.  
Чтобы текст выводился нормально, нужно расположить файл со шрифтом в папке проекта.  
Перед началом игры можно выбрать способ расстановки кораблей. Можно сделать это самостоятельно или  попросить систему расставить их случайным образом.  
Игру можно в любой момент перезапустить, нажав **r**.  
Игра со звуком.  


```
How to run:
git checkout checkpoint
cd checkpoint_3  
./run.sh  

```

