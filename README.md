<h1 align="center">🐾 FeederController Auto-Feeder 🐾</h1>

<p align="center">
  <a href="https://github.com/rembov/FeederController/stargazers"><img src="https://img.shields.io/github/stars/rembov/FeederController?style=social" alt="Stars"/></a>
  <a href="https://github.com/rembov/FeederController/network/members"><img src="https://img.shields.io/github/forks/rembov/FeederController?style=social" alt="Forks"/></a>
</p>


<p align="center">
  <a href="#описание">📖 Описание</a> •
  <a href="#структура-проекта">📂 Структура</a> •
  <a href="#особенности">✨ Особенности</a> •
  <a href="#зависимости">🔗 Зависимости</a> •
  <a href="#установка-и-использование">🚀 Установка</a> •
  <a href="#меню">🎛️ Меню</a> •
</p>

---

## 📖 Описание

Проект **FeederController** — умная автокормушка на базе Arduino Uno, позволяющая управлять до 4 кормушками по расписанию или вручную.

* 📅 Планирование до **10** кормлений в сутки
* 🔌 Управление **4 реле** для независимых каналов
* 🤏 Ручное кормление через меню
* 🖥️ Отображение на **LCD 16×2** с подсветкой
* 💾 Сохранение настроек в **EEPROM**
* ⏰ Синхронизация с модулем **RTC DS3231**
* 🎛️ Управление через энкодер (вращение + кнопка)

---

## 📂 Структура проекта

```plaintext
/FeederController
│
├── FeederController.ino      # Главный скетч
└── src                       # Модули
    ├── Settings.h           # Пины и константы
    ├── RTCManager.h/cpp     # Инициализация RTC
    ├── RelayController.h/cpp# Управление реле
    ├── FeedingSystem.h/cpp  # Логика расписаний и EEPROM
    ├── InputHandler.h/cpp   # Обработка энкодера и кнопки
    └── DisplayManager.h/cpp # Логика интерфейса LCD
```

---

## ✨ Особенности

* **Модульная архитектура**: четкое разделение ответственностей
* **Интуитивный интерфейс** с морганием и подсказками
* **Автоматическое восстановление** расписания после отключения питания
* **Гибкая настройка** времени и длительности порций

---

## 🔗 Зависимости

| Библиотека         | Ссылка                                                                                                |
| ------------------ | ----------------------------------------------------------------------------------------------------- |
| LiquidCrystal\_I2C | [https://github.com/johnrickman/LiquidCrystal\_I2C](https://github.com/johnrickman/LiquidCrystal_I2C) |
| RTClib             | [https://github.com/adafruit/RTClib](https://github.com/adafruit/RTClib)                              |
| EEPROM             | Входит в стандарт Arduino                                                                             |

---

## 🚀 Установка и использование

1. Клонируйте репозиторий:

git clone [https://github.com/rembov/FeederController.git](https://github.com/rembov/FeederController.git)

```
2. Откройте **FeederController.ino** в Arduino IDE.
3. Установите библиотеки через **Library Manager**.
4. Подключите модули согласно `Settings.h`.
5. Загрузите скетч на плату **Arduino Uno**.
6. Настройте время и расписание через меню.

---

## 🎛️ Меню

| Пункт    | Описание                                |
|----------|-----------------------------------------|
| Manual   | Ручное включение/выключение реле        |
| Time     | Установка времени каждого кормления     |
| Portion  | Длительность порции (в секундах)        |
| Count    | Общее число запланированных кормлений    |


---

<p align="center">Made with ❤️ by <a href="https://github.com/rembov">rembov</a></p>

```
