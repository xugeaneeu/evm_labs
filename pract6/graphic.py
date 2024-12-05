import matplotlib.pyplot as plt

# Данные
data_size = [
    1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 15, 18, 22, 26, 31, 38, 45, 54, 65, 78, 94,
    113, 136, 163, 196, 235, 282, 338, 406, 488, 585, 702, 843, 1012, 1214, 1457,
    1748, 2098, 2518, 3022, 3626, 4351, 5222, 6266, 7519, 9023, 10828, 12994,
    15593, 18711, 22454, 26945, 32334, 38801, 46561, 55873, 67048, 80457, 96549,
    115859
]
forward = [
    5, 5, 5, 5, 5, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7,
    7, 6, 6, 6, 6, 6, 6, 6, 6, 6
]
backward = [
    6, 5, 5, 5, 5, 7, 7, 6, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6
]
random = [
    5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 10, 10, 11, 12, 12, 13, 13,
    13, 13, 13, 13, 14, 15, 16, 18, 20, 23, 23, 25, 27, 30, 33, 34, 33, 33, 35,
    35, 42, 40, 41, 56, 52, 134, 177, 224, 270, 299, 326, 346, 378, 381, 393,
    402, 414
]

# Построение графика
plt.figure(figsize=(20, 7))
plt.plot(data_size, forward, label='Forward', marker='o', color='blue', markersize=8)  # Линия Forward
plt.plot(data_size, backward, label='Backward', marker='s', color='green')  # Линия Backward
plt.plot(data_size, random, label='Random', marker='^', color='red')  # Линия Random

# Настройки графика
plt.ylim(0,100)
plt.xscale('log', base=2)
# plt.xscale('log')  # Логарифмическая шкала для оси X
plt.xlabel('Data Size (Kb)', fontsize=12)  # Подпись оси X
plt.ylabel('Time (ticks)', fontsize=12)  # Подпись оси Y
plt.title('Performance Comparison by Access Pattern', fontsize=15)  # Заголовок графика
plt.legend(fontsize=12)  # Обозначения линий
plt.grid(visible=True, which="both", linestyle='--', linewidth=0.3)  # Сетка

# Отображение графика
plt.show()
