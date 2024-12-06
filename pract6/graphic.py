import matplotlib.pyplot as plt

# Данные
data_size = [
    1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 15, 18, 22, 26, 31, 38, 45, 54, 65, 78,
    94, 113, 136, 163, 196, 235, 282, 338, 406, 488, 585, 702, 843, 1012,
    1214, 1457, 1748, 2098, 2518, 3022, 3626, 4351, 5222, 6266, 7519, 9023,
    10828, 12994, 15593, 18711, 22454, 26945, 32334, 38801, 46561, 55873,
    67048, 80457, 96549, 115859
]

forward = [
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 4, 4, 4, 4, 4, 5
]

backward = [
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 4, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 9, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 4, 4, 4, 4, 4, 5, 5
]

random = [
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 5, 13, 10, 8, 10, 11, 11, 12,
    12, 12, 12, 12, 12, 13, 13, 14, 13, 13, 15, 19, 25, 28, 30, 33, 34, 36, 37,
    37, 39, 36, 36, 39, 40, 48, 166, 168, 200, 240, 276, 311, 340, 350, 370,
    402, 420
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
