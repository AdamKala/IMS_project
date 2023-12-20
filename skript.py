import matplotlib.pyplot as plt
import pandas as pd
import math
# Simulovaná dat
data = {
    'Time': [30.00, 60.00, 90.00, 120.00, 150.00, 180.00, 210.00, 240.00, 270.00, 300.00, 330.00, 360.00, 390.00, 420.00, 450.00, 480.00, 510.00, 540.00, 570.00],
    'Queue': [2, 3, 4, 5, 6, 10, 12, 15, 12, 11, 14, 8, 7, 4, 5, 7, 6, 5, 4]




}

queue = [2, 3, 4, 5, 6, 10, 12, 15, 12, 11, 14, 8, 7, 4, 5, 7, 6, 5, 4]




average = sum(queue) / len(queue)
print(average)

# Vytvoření pandas DataFrame
df = pd.DataFrame(data)

# Zaokrouhlení času na nejbližší násobek 30
df['Rounded_Time'] = df['Time'].apply(lambda x: math.floor(x / 30) * 30)

# Výpočet celkového počtu lidí ve frontě
total_people = df['Queue'].sum()

# Vykreslení grafu
plt.figure(figsize=(8, 5))
plt.plot(df['Rounded_Time'], df['Queue'], marker='o', linestyle='-')
plt.xlabel('Čas (minuty)')
plt.ylabel('Prumerny cas ve frontě (minuty)')
plt.title('Prumerny cas straveny ve frontě do kavarnu (vikendovy den)')
plt.grid(True)
plt.show()

# Vypsání informací
print(f"Pocet lidi: {total_people}")
print(f"Pocet zaznamu: {len(df)}")
print(f"Prumerny pocet lidi ve fronte: {total_people / len(df)}")
